// #EX_BEGIN
//
// Created by bardanik on 18/03/23.
//

#include "CompanyAgent.hpp"
#include "WorkerStation.hpp"

// #EX_END

CompanyAgent::CompanyAgent(ACompany &company, WorkerStation &station)
        : client(company),
          deliverer(company),
          loader(station, client, deliverer) {

}


void CompanyAgent::startAgent() {
    loader.start();
    deliverer.start();
}

void CompanyAgent::stopLoader() {
    loader.stop();
}

void CompanyAgent::stopDeliverer() {
    deliverer.stop();
}





