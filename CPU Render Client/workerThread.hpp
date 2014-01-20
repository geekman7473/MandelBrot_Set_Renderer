#ifndef WORKERTHREAD
#define WORKERTHREAD

#include <string>
#include "Util.hpp"
#include "workOrder.hpp"
#include "PacketOps.hpp"
#include "Render.hpp"

using namespace std;

class workerThread {
    public:
    //ip of managment server
    std::string serverIp;
    //maximum number of threads to be used
    unsigned int maxThreads;
    //the value from 0 to maxThreads - 1 indicating this threads position.
    unsigned int threadID;
    //string which main function can read/print to display overall worker node progress
    std::string workProgress;
    //totaltime spent rendering
    unsigned long long int totalRenderTime;

    //seed for use in all random operations
    unsigned long long randSeed;

    //for debug in server-less test scenarios
    workOrder_t testWork;
    long int testFramesToRender;
    workerThread();
};

void threadWorker(void * arg);
#endif
