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
    string projectDetails[2]; //2 is only a placeholder value
                              //hash of the project file is to be used as primary detail
                              //[0] stores accepted project value
                              //[1] stores temporary received project value

    sf::Packet outPacket; //packet to be used for all uploads
    sf::Packet inPacket; //packet to be used for all downloads
    sf::TcpSocket socket;

    while(true){
        bool initFail = false;
        int failCount = 0;

        sf::Socket::Status status = socket.connect(wT -> serverIp, 60606);

        while (status != sf::Socket::Done){ //connecting to server
            cerr << "Socket failed to initialize with remote host. Retrying..." << endl;
            sf::Socket::Status status = socket.connect(wT -> serverIp, 60606);
            failCount++;
            if(failCount == wT -> maxRetries){
                return;
            }
        }
        failCount = 0;

        while(socket.receive(inPacket) != sf::Socket::Done){ //receive project details
            cerr << "Failed to receive project details from CMS. Retrying..." << endl;
            failCount++;
            if(failCount == wT -> maxRetries){
                return;
            }
        }
        failCount = 0;

        inPacket >> projectDetails[1];
        if(projectDetails[1] == projectDetails[0]){       //if the project details from server
            outPacket << 2 << (sf::Int32)workList.size(); //match those on file then send all work in worklist to server
            for(int i = 0; i < workList.size(); i++){
                outPacket << workList[i].WIN << workList[i].completedWork << (sf::Uint32)(workList[i].totalIterationsUsed >> 32) << (sf::Uint32)(workList[i].totalIterationsUsed) << (sf::Uint32)(workList[i].timeWorkFinshed - workList[i].timeWorkStarted);
            }
            workList.clear();
        } else {
            workList.clear();
        }



        sf::Packet workReq;
        workReq << "1"; //thread specs should go here
        while (socket.send(workReq) != sf::Socket::Done) {
            cerr << "Failed to send work request. Retrying..." << endl;
            failCount++;
            if(failCount == wT -> maxRetries){
                return;
            }
        }
        failCount = 0;

        sf::Packet workReception;
        while (socket.receive(workReception) != sf::Socket::Done) {
            cerr << "Failed to receive work allocation. Retrying..." << endl;
            failCount++;
            if(failCount == wT -> maxRetries){
                return;
            }
        }
        failCount = 0;

        sf::Int16 workType;
        sf::Uint32 FrameWidth, FrameHeight, maximumIterations, lineNum, pixelX, pixelY;
        sf::Uint64 timeReceived;
        std::string WIN, xCord, yCord, zoomFactor;
        bool isHor;
        workReception >> workType;
        workReception >> xCord;
        workReception >> yCord;
        workReception >> FrameWidth;
        workReception >> FrameHeight;
        workReception >> zoomFactor;
        workReception >> maximumIterations;
        workReception >> WIN;
        workReception >> isHor;

        cout << endl << "worktype: " << workType;
        cout << endl << "xCord: " << xCord;
        cout << endl << "yCord: " << yCord;
        cout << endl << "frameWidth: " << FrameWidth;
        cout << endl << "frameHeight: " << FrameHeight << endl;
        workOrder_t temp;
        temp.workType = workType;
        temp.xCord = xCord;
        temp.yCord = yCord;
        temp.FrameHeight = FrameHeight;
        temp.FrameWidth = FrameWidth;
        temp.zoomFactor = zoomFactor;
        temp.maximumIterations = maximumIterations;
        temp.WIN = WIN;
        temp.isHorizontal = isHor;

        cout << endl << "Tworktype: " << temp.workType;
        cout << endl << "TxCord: " << temp.xCord;
        cout << endl << "TyCord: " << temp.yCord;
        cout << endl << "TframeWidth: " << temp.FrameWidth;
        cout << endl << "TframeHeight: " << temp.FrameHeight << endl;

        MandelRender(&temp);

        workReception.clear();
        workReception << "2" << temp.completedWork;
        cout << endl << "Sending completed render!" << endl;
        while (socket.send(workReception) != sf::Socket::Done) {
            cerr << "Failed to send finished work. Retrying..." << endl;
            failCount++;
            if(failCount == wT -> maxRetries){
                return;
            }
        }
        failCount = 0;

        temp.completedWork.WriteToFile(("test" + intToString(time(NULL)) + ".bmp").c_str());
    }
}
#endif
