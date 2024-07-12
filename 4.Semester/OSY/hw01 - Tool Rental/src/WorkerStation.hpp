// #PRIOR_4
// #EX_BEGIN
//
// Created by bardanik on 19/03/23.
//

#ifndef BI_OSY_PROGTEST_WORKERSTATION_HPP
#define BI_OSY_PROGTEST_WORKERSTATION_HPP

#include "Worker.hpp"
#include <condition_variable>
#include <mutex>

/**
 * Encapsulates the working queue with registered workers
 * that are working on the station
 */

// #EX_END

using Workers = vector<Worker>;

class WorkerStation {
public:

    void startWorkers(int workersNumber);

    void stopWorkers();

    void loadPackToConveyor(AProblemPackWrapper &pack);

    size_t workersCount() const;

private:
    Conveyor loadConveyor;
    Conveyor deliveryConveyor;
    Workers workers;
    SolverManager solverManager;

    bool isStopSignal = false;

    condition_variable cv_workers;
    mutex mx_workers;
    mutex mx_deliveryConveyor;
    mutex mx_loaders;
};

// #EX_BEGIN
#endif //BI_OSY_PROGTEST_WORKERSTATION_HPP
// #EX_END


