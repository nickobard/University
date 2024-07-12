// #EX_BEGIN
//
// Created by bardanik on 18/03/23.
//

#include "Worker.hpp"
#include <cassert>

// #EX_END


Worker::Worker(Conveyor &loadConveyor,
               Conveyor &deliveryConveyor,
               SolverManager &manager,
               condition_variable &cv_workers,
               mutex &mx_loadConveyor,
               mutex &mx_deliveryConveyor,
               const bool &signal)
        : loadConveyor(loadConveyor),
          deliveryConveyor(deliveryConveyor),
          manager(manager),
          cv_workers(cv_workers),
          mx_workers(mx_loadConveyor),
          mx_deliveryConveyor(mx_deliveryConveyor),
          isStopSignal(signal) {

}

void Worker::start() {
    worker = thread(&Worker::work, this);
}

void Worker::stop() {
    worker.join();
}


void Worker::work() {

    while (true) {
        unique_lock ulock(mx_workers);
        while (!hasWork() && !isStopSignal)
            cv_workers.wait(ulock);
        if (!hasWork() && isStopSignal) {
            if (isPendingSolver()) {
                solvingWork(ulock);
                deliveryWork();
            }
            break;
        }
        loadingWork();

        if (solverIsFull())
            solvingWork(ulock);
        else
            ulock.unlock();

        deliveryWork();
    }
}

void Worker::solvingWork(unique_lock<mutex> &ulock) {
    auto [solver, registry] = manager.getSolverAndReset();
    cv_workers.notify_one();
    ulock.unlock();

    solver->solve();

    for (auto &[solvedPack, solvedNumber]: registry) {
        solvedPack->incrementSolved(solvedNumber);
    }
}


void Worker::loadingWork() {
    if (!hasPacksForLoading())
        return;

    auto pack = getAndRegisterNextPack();

    while (solverHasCapacity()) {
        if (pack->hasProblemsToBeProcessed()) {
            manager.addProblem(pack->retrieveProblem());
        }
        if (!pack->hasProblemsToBeProcessed()) {
            deliveryConveyor.push(pack);
            loadConveyor.pop();
            if (!hasPacksForLoading() || !solverHasCapacity())
                return;

            pack = getAndRegisterNextPack();
        }
    }
}

void Worker::deliveryWork() {
    lock_guard lockGuard(mx_deliveryConveyor);
    if (!hasPacksForDelivery())
        return;
    auto pack = deliveryConveyor.front();
    while (pack->isSolvedPack()) {
        pack->passToDeliverer();
        deliveryConveyor.pop();
        if (!hasPacksForDelivery())
            return;
        pack = deliveryConveyor.front();
    }

}


bool Worker::hasWork() {
    return !loadConveyor.empty() || (!deliveryConveyor.empty() && deliveryConveyor.front()->isSolvedPack());
}

bool Worker::isPendingSolver() {
    return manager.hasProblemsToSolve();
}

bool Worker::hasPacksForDelivery() {
    return !deliveryConveyor.empty();
}

bool Worker::hasPacksForLoading() {
    return !loadConveyor.empty();
}

bool Worker::solverHasCapacity() {
    return manager.solverHasCapacity();
}

AProblemPackWrapper Worker::getAndRegisterNextPack() {
    auto pack = loadConveyor.front();
    manager.registerPack(pack);
    return pack;
}

bool Worker::solverIsFull() {
    return !manager.solverHasCapacity();
}
