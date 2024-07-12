// #EX_BEGIN
//
// Created by bardanik on 18/03/23.
//
#include "COptimizer.hpp"
// #EX_END

void COptimizer::start(int threadCount) {
    for (auto &agent: agents) {
        agent->startAgent();
    }
    station.startWorkers(threadCount);
}

void COptimizer::stop(void) {

    for (auto &agent: agents) {
        agent->stopLoader();
    }

    station.stopWorkers();

    for (auto &agent: agents) {
        agent->stopDeliverer();
    }
}

void COptimizer::addCompany(ACompany company) {
    agents.emplace_back(make_shared<CompanyAgent>(company, station));
}

