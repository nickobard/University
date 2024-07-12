// #EX_BEGIN

//
// Created by bardanik on 18/03/23.
//
#include "Deliverer.hpp"

// #EX_END


Deliverer::Deliverer(ACompany clientCompany)
        : clientCompany(std::move(clientCompany)) {

}

void Deliverer::deliverPacks() {
    while (true) {
        unique_lock<mutex> ulock(mx_delivery);
        cv_delivery.wait(ulock, [this]() { return !deliveryQueue.empty(); });
        AProblemPack pack = deliveryQueue.front();
        deliveryQueue.pop();
        if (pack == nullptr)
            break;
        else
            clientCompany->solvedPack(pack);
    }
}

void Deliverer::start() {
    deliverer = thread(&Deliverer::deliverPacks, this);
}

void Deliverer::stop() {
    deliveryQueue.push(nullptr);
    cv_delivery.notify_one();
    deliverer.join();
}

void Deliverer::acceptToDelivery(AProblemPack &solvedPack) {
    deliveryQueue.push(solvedPack);
    cv_delivery.notify_one();
}

