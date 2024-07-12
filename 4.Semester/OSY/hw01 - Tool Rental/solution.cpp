#ifndef __PROGTEST__

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cstdint>
#include <climits>
#include <cfloat>
#include <cassert>
#include <cmath>
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <numeric>
#include <string>
#include <vector>
#include <array>
#include <iterator>
#include <set>
#include <list>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <queue>
#include <stack>
#include <deque>
#include <memory>
#include <functional>
#include <thread>
#include <mutex>
#include <atomic>
#include <chrono>
#include <stdexcept>
#include <condition_variable>
#include <pthread.h>
#include <semaphore.h>
#include "progtest_solver.h"
#include "sample_tester.h"

using namespace std;
#endif /* __PROGTEST__ */

#include "src/COptimizer.hpp"


#ifndef __PROGTEST__

int main(void) {
    int companiesNumber = 4;
    int threadsNumber = 4;


    COptimizer optimizer;
    vector<ACompanyTest> companies;
    for (int company = 0; company < companiesNumber; company++) {
        ACompanyTest c = std::make_shared<CCompanyTest>();
        optimizer.addCompany(c);
        companies.push_back(c);
    }
    optimizer.start(threadsNumber);
    optimizer.stop();
    for (auto &company: companies) {
        if (!company->allProcessed())
            throw std::logic_error("(some) problems were not correctly processsed");
    }

    return 0;
}

#endif /* __PROGTEST__ */
