// #EX_BEGIN
//
// Created by bardanik on 18/03/23.
//

#include "Loader.hpp"
#include "WorkerStation.hpp"
#include "Deliverer.hpp"
#include <cassert>
// #EX_END

Loader::Loader(WorkerStation &workerStation,
               ACompany clientCompany,
               Deliverer &deliverer)
        : workerStation(workerStation),
          deliverer(deliverer),
          clientCompany(std::move(clientCompany)) {

}


void Loader::loadProblemPacks() {

    AProblemPack pack = clientCompany->waitForPack();
    while (pack != nullptr) {
        AProblemPackWrapper wrappedPack = ProblemPackWrapper::wrap(deliverer, pack);
        workerStation.loadPackToConveyor(wrappedPack);
        pack = clientCompany->waitForPack();
    }
}

void Loader::start() {
    loader = thread(&Loader::loadProblemPacks, this);
}

void Loader::stop() {
    loader.join();
}


