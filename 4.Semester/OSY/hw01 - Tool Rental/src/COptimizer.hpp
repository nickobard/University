// #PRIOR_9
// #EX_BEGIN
//
// Created by bardanik on 18/03/23.
//

#ifndef BI_OSY_PROGTEST_COPTIMIZER_HPP
#define BI_OSY_PROGTEST_COPTIMIZER_HPP

#include "CompanyAgent.hpp"
#include "WorkerStation.hpp"
#include <vector>
// #EX_END

class COptimizer {
public:
    static bool usingProgtestSolver(void) {
        return true;
    }

    static void checkAlgorithm(AProblem problem) {
        // dummy implementation if usingProgtestSolver() returns true
    }

    void start(int threadCount);

    void stop(void);

    void addCompany(ACompany company);

private:
    WorkerStation station;
    vector<ACompanyAgent> agents;
};

// #EX_BEGIN
#endif //BI_OSY_PROGTEST_COPTIMIZER_HPP
// #EX_END

