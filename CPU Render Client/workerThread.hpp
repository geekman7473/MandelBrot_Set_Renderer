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
    //ip/address of managment server
    std::string serverIp;
    //maximum number of threads to be used
    unsigned int maxThreads;
    //the value from 0 to maxThreads - 1 indicating this threads position.
    unsigned int threadID;
    //string which main function can read in order to display overall node status
    std::string workProgress;
    //totaltime spent rendering in seconds
    unsigned long long int totalRenderTime;
    //max number of retries before declaring a failure and begging the handshake again
    int maxRetries;

    //for debug in server-less test scenarios
    workOrder_t testWork;
    unsigned long long randSeed;
    long int testFramesToRender;

    workerThread();
};

void threadWorker(void * arg);
#endif
