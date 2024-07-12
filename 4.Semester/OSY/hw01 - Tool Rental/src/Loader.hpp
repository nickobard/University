// #PRIOR_6
// #EX_BEGIN
//
// Created by bardanik on 18/03/23.
//

#ifndef BI_OSY_PROGTEST_LOADER_HPP
#define BI_OSY_PROGTEST_LOADER_HPP

#include "ProblemPackWrapper.hpp"

#include <mutex>
#include <condition_variable>
#include <thread>

using namespace std;

// #EX_END

class WorkerStation;

class Loader {
public:
    Loader(WorkerStation &workerStation,
           ACompany clientCompany,
           Deliverer &deliverer);


    void start();

    void stop();

private:

    void loadProblemPacks();

    WorkerStation &workerStation;
    Deliverer &deliverer;
    ACompany clientCompany;

    thread loader;
    condition_variable cv_loader;

};

// #EX_BEGIN
#endif //BI_OSY_PROGTEST_LOADER_HPP
// #EX_END


