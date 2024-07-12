// #EX_BEGIN
//
// Created by bardanik on 18/03/23.
//

#include "SolverManager.hpp"
// #EX_END


SolverManager::SolverManager()
        : solver(createProgtestSolver()) {

}

void SolverManager::registerPack(AProblemPackWrapper &pack) {
    registeredPacks.emplace_back(pack, 0);
}

bool SolverManager::solverHasCapacity() const {
    return solver->hasFreeCapacity();
}

bool SolverManager::addProblem(AProblem problem) {
    auto success = solver->addProblem(std::move(problem));
    if (!success)
        return false;
    registeredPacks.back().second++;
    return true;
}

void SolverManager::reset() {
    solver = createProgtestSolver();
    registeredPacks.clear();
}

bool SolverManager::hasProblemsToSolve() {
    return !registeredPacks.empty();
}

pair<AProgtestSolver, vector<Registry>> SolverManager::getSolverAndReset() {
    auto solverProblem = make_pair(solver, registeredPacks);
    reset();
    return solverProblem;
}


