// #EX_BEGIN
//
// Created by bardanik on 18/03/23.
//

#include "ProblemPackWrapper.hpp"
#include "Deliverer.hpp"
#include <cassert>

// #EX_END

ProblemPackWrapper::ProblemPackWrapper(Deliverer &deliverer, AProblemPack pack)
        : deliverer(deliverer),
          wrappedPack(std::move(pack)),
          solved(0),
          inProcess(0),
          packSize(wrappedPack->m_Problems.size()) {

}

void ProblemPackWrapper::passToDeliverer() {
    deliverer.acceptToDelivery(wrappedPack);
}


size_t ProblemPackWrapper::problemsInProcess() const {
    return inProcess;
}

size_t ProblemPackWrapper::problemsCount() const {
    return packSize;
}


bool ProblemPackWrapper::allProblemsInProgress() const {
    return inProcess == packSize;
}

AProblem ProblemPackWrapper::retrieveProblem() {
    if (allProblemsInProgress())
        assert(true);
    return wrappedPack->m_Problems[inProcess++];
}

bool ProblemPackWrapper::isSolvedPack() {
    return solved == packSize;
}

void ProblemPackWrapper::incrementSolved(int solvedNumber) {
    lock_guard lockGuard(mx_pack);
    solved += solvedNumber;
}

shared_ptr<ProblemPackWrapper> ProblemPackWrapper::wrap(Deliverer &deliverer, AProblemPack &pack) {
    return make_shared<ProblemPackWrapper>(deliverer, pack);
}


bool ProblemPackWrapper::hasProblemsToBeProcessed() const {
    return inProcess < packSize;
}

size_t ProblemPackWrapper::solvedCount() const {
    return solved;
}

