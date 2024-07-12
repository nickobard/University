// #PRIOR_3
// #EX_BEGIN
//
// Created by bardanik on 18/03/23.
//

#ifndef BI_OSY_PROGTEST_WORKER_HPP
#define BI_OSY_PROGTEST_WORKER_HPP

#include "SolverManager.hpp"
#include <queue>
#include <vector>
#include <condition_variable>
#include <mutex>
#include <thread>

using namespace std;

// #EX_END

using Conveyor = queue<AProblemPackWrapper>;

class Worker {
public:
    Worker(Conveyor &loadConveyor,
           Conveyor &deliveryConveyor,
           SolverManager &manager,
           condition_variable &cv_workers,
           mutex &mx_loadConveyor,
           mutex &mx_deliveryConveyor,
           const bool &signal);

    void start();

    void stop();


private:

    AProblemPackWrapper getAndRegisterNextPack();

    bool hasPacksForDelivery();

    bool hasPacksForLoading();

    bool solverIsFull();

    bool solverHasCapacity();

    bool isPendingSolver();

    bool hasWork();

    void work();

    void loadingWork();

    void deliveryWork();

    void solvingWork(unique_lock<mutex> &ulock);

    Conveyor &loadConveyor;
    Conveyor &deliveryConveyor;
    SolverManager &manager;

    condition_variable &cv_workers;
    mutex &mx_workers;
    mutex &mx_deliveryConveyor;
    thread worker;

    const bool &isStopSignal;
};

// #EX_BEGIN
#endif //BI_OSY_PROGTEST_WORKER_HPP
// #EX_END

