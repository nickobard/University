// #EX_BEGIN
//
// Created by bardanik on 19/03/23.
//

#include "WorkerStation.hpp"
// #EX_END

size_t WorkerStation::workersCount() const {
    return workers.size();
}

void WorkerStation::startWorkers(int workersNumber) {
    for (int worker = 0; worker < workersNumber; worker++) {
        workers.emplace_back(loadConveyor,
                             deliveryConveyor,
                             solverManager,
                             cv_workers,
                             mx_workers,
                             mx_deliveryConveyor,
                             isStopSignal);
    }
    for (auto &worker: workers) {
        worker.start();
    }
}

void WorkerStation::stopWorkers() {
    isStopSignal = true;
    cv_workers.notify_all();
    for (auto &worker: workers) {
        worker.stop();
    }
}

void WorkerStation::loadPackToConveyor(AProblemPackWrapper &pack) {
    lock_guard lg(mx_loaders);
    loadConveyor.push(pack);
    cv_workers.notify_one();
}


