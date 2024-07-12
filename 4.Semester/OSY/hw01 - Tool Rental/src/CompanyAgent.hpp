// #PRIOR_8
// #EX_BEGIN
//
// Created by bardanik on 18/03/23.
//

#ifndef BI_OSY_PROGTEST_COMPANYAGENT_HPP
#define BI_OSY_PROGTEST_COMPANYAGENT_HPP

#include "Loader.hpp"
#include "Deliverer.hpp"
#include <thread>
#include <iostream>
// #EX_END

class CompanyAgent {

public:

    CompanyAgent(ACompany &company, WorkerStation &station);

    void startAgent();

    void stopLoader();

    void stopDeliverer();

private:

    ACompany client;
    Deliverer deliverer;
    Loader loader;

};

using ACompanyAgent = shared_ptr<CompanyAgent>;


// #EX_BEGIN
#endif //BI_OSY_PROGTEST_COMPANYAGENT_HPP
// #EX_END


