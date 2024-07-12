// #PRIOR_5
// #EX_BEGIN
//
// Created by bardanik on 18/03/23.
//

#ifndef BI_OSY_PROGTEST_DELIVERER_HPP
#define BI_OSY_PROGTEST_DELIVERER_HPP

#include "ProblemPackWrapper.hpp"
#include <mutex>
#include <condition_variable>
#include <queue>
#include <thread>

using namespace std;

// #EX_END


class Deliverer {
public:
    explicit Deliverer(ACompany clientCompany);

    void start();

    void stop();

    void acceptToDelivery(AProblemPack &solvedPack);

private:

    void deliverPacks();

    ACompany clientCompany;
    queue<AProblemPack> deliveryQueue;

    thread deliverer;
    condition_variable cv_delivery;
    mutex mx_delivery;
};

// #EX_BEGIN
#endif //BI_OSY_PROGTEST_DELIVERER_HPP
// #EX_END
