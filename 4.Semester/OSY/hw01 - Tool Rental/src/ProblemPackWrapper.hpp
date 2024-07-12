// #PRIOR_1
// #EX_BEGIN
//
// Created by bardanik on 18/03/23.
//

#ifndef BI_OSY_PROGTEST_PROBLEMPACKWRAPPER_HPP
#define BI_OSY_PROGTEST_PROBLEMPACKWRAPPER_HPP

#include "../common.h"
#include <mutex>
using namespace std;
// #EX_END

class Deliverer;

class ProblemPackWrapper {
public:
    ProblemPackWrapper(Deliverer &deliverer, AProblemPack pack);

    AProblem retrieveProblem();

    void incrementSolved(int solvedNumber);

    void passToDeliverer();

    bool isSolvedPack();

    bool allProblemsInProgress() const;

    bool hasProblemsToBeProcessed() const;

    size_t problemsInProcess() const;

    size_t problemsCount() const;

    size_t solvedCount() const;

    static shared_ptr<ProblemPackWrapper> wrap(Deliverer &deliverer, AProblemPack &pack);

private:
    Deliverer &deliverer;
    AProblemPack wrappedPack;

    size_t solved;
    size_t inProcess;
    size_t packSize;

    mutex mx_pack;

};

using AProblemPackWrapper = shared_ptr<ProblemPackWrapper>;

// #EX_BEGIN
#endif //BI_OSY_PROGTEST_PROBLEMPACKWRAPPER_HPP
// #EX_END

