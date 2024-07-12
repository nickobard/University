// #PRIOR_2
// #EX_BEGIN
//
// Created by bardanik on 18/03/23.
//

#ifndef BI_OSY_PROGTEST_SOLVERMANAGER_HPP
#define BI_OSY_PROGTEST_SOLVERMANAGER_HPP

#include "ProblemPackWrapper.hpp"
#include "../progtest_solver.h"
#include <vector>
#include <mutex>

using namespace std;
// #EX_END

using Registry = pair<AProblemPackWrapper, int>;

class SolverManager {
public:
    SolverManager();

    bool hasProblemsToSolve();

    void registerPack(AProblemPackWrapper &pack);

    bool solverHasCapacity() const;

    bool addProblem(AProblem problem);

    pair<AProgtestSolver, vector<Registry>> getSolverAndReset();

private:

    void reset();

    AProgtestSolver solver;
    vector<Registry> registeredPacks;
};

// #EX_BEGIN
#endif //BI_OSY_PROGTEST_SOLVERMANAGER_HPP
// #EX_END


