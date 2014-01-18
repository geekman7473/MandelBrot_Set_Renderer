#ifndef WORKERTHREAD
#define WORKERTHREAD

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

    workerThread(){
        maxThreads = 0;
        threadID = 0;
        totalRenderTime =0;
        workProgress = "";
        randSeed = 0;
    }
};

void threadWorker(workerThread *wT){
    vector<workOrder_t> workList;

    sf::TcpSocket socket;

    sf::Socket::Status status = socket.connect(wT -> serverIp, 60606);

    while (status != sf::Socket::Done){
        cerr << "Socket failed to initialize with remote host. Retrying...";
        sf::Socket::Status status = socket.connect(wT -> serverIp, 60606);
    }

    sf::Packet workReception;

    while (socket.receive(workReception) != sf::Socket::Done) {
        cerr << "Failed to receive work allocation. Retrying...";
    }

    sf::Int8 workType;
    sf::Uint64 FrameWidth, FrameHeight, maximumIterations, lineNum, pixelX, pixelY, timeReceived;
    std::string WIN, xCord, yCord, zoomFactor;
    bool isHor;
    /*workReception >> workType;
    workReception >> xCord;
    workReception >> yCord;
    workReception >> FrameWidth;
    workReception >> FrameHeight;
    workReception >> zoomFactor;
    workReception >> maximumIterations;
    workReception >> WIN;
    workReception >> isHor;
    */

    socket.disconnect();

    workList.clear();
}

#endif
