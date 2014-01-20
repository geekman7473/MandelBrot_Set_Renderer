#ifndef WORKERTHREAD_c
#define WORKERTHREAD_c
#include "workerThread.hpp"

#include <string>
#include "Util.hpp"
#include "workOrder.hpp"
#include "PacketOps.hpp"
#include "Render.hpp"

using namespace std;

workerThread::workerThread(){
        maxThreads = 0;
        threadID = 0;
        totalRenderTime =0;
        workProgress = "";
        randSeed = 0;
}

void threadWorker(void * arg){
    workerThread* wT = (workerThread *) arg;

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
