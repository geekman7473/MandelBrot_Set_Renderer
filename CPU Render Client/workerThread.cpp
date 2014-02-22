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
        sf::Socket::Status status = socket.connect(wT -> serverIp, 60606);

        while (status != sf::Socket::Done){ //connecting to server
            cerr << "Socket failed to initialize with remote host. Retrying..." << endl;
            sf::Socket::Status status = socket.connect(wT -> serverIp, 60606);
        }

        while(socket.receive(inPacket) != sf::Socket::Done){ //receive project details
            cerr << "Failed to receive project details from CMS. Retrying..." << endl;
        }

        outPacket.clear();
        outPacket << "1"; //designates message as a client details message
        outPacket << wT -> workerID << wT -> threadID;
        while (socket.send(outPacket) != sf::Socket::Done) {
            cerr << "Failed to send client specifications. Retrying..." << endl;
        }

        string messageType;
        inPacket >> messageType >> projectDetails[1];
        if(projectDetails[1] == projectDetails[0]){       //if the project details from server match those on file then send all work in worklist to server
            outPacket.clear();
            outPacket << "2"; //the "2" designates the message type
            outPacket << (sf::Int32)workList.size();
            cout << "test1";
            for(int i = 0; i < workList.size(); i++){
                outPacket << workList[i].WIN;
                outPacket << workList[i].completedWork;
                outPacket << (sf::Uint32)(workList[i].totalIterationsUsed >> 32);
                outPacket << (sf::Uint32)(workList[i].totalIterationsUsed);
                outPacket << (sf::Uint32)(workList[i].timeWorkFinsished - workList[i].timeWorkStarted);
                //the server only needs certain data back from the client
                //namely the time required to complete a render, the WIN, iterations used, and the image itself
            }
            cout << "test4";
            workList.clear();
            cout << "test5";
            while(socket.send(outPacket) != sf::Socket::Done){
                cerr << "Failed to upload completed renders to CMS. Retrying..." << endl;
            }
        } else {
            workList.clear(); //if project details do not match then discard all previous work
            projectDetails[0] = projectDetails[1]; //sets the current project ([0]) to what the server sent
            projectDetails[1] = ""; //reset temp project ID
        }


        outPacket.clear();
        outPacket << "3"; //work request
        //work request paramaters
        //sf::Uint16 number_of_work_orders (keep this reasonable, value above 16k may behave... unexpectedly)
        //sf::int16 work_type_request (current server software only supports distribution of type 1)
        //these parameters are to be expanded upon and dynamically defined in later versions
        outPacket << 10 << 1;
        while(socket.send(outPacket) != sf::Socket::Done){
            cerr << "Failed to request work. Retrying..." << endl;
        }

        inPacket.clear();
        while (socket.receive(inPacket) != sf::Socket::Done) {
            cerr << "Failed to receive work allocation. Retrying..." << endl;
        }


        inPacket >> messageType;
        //the second value in the work allocation should specify the quantity of workorder objects sent
        //a value of 0 indicates... something...
        //a value of -1 indicates an error
        //a value of -2 indicates the completion of the project
        sf::Int32 workQuant;
        inPacket >> workQuant;

        if(workQuant < 0){
            cerr << "The server failed to send a work allocation." << endl;
            return;
        }
        socket.disconnect(); //disconnect until a connection is needed on next loop iteration
        for(sf::Int32 i = 0; i < workQuant; i++){ //populates worklist
            workOrder_t temp;
            inPacket >> temp;
            cout << endl << "Tworktype: " << temp.workType;
            cout << endl << "TxCord: " << temp.xCord;
            cout << endl << "TyCord: " << temp.yCord;
            cout << endl << "TframeWidth: " << temp.FrameWidth;
            cout << endl << "TframeHeight: " << temp.FrameHeight << endl;
            workList.push_back(temp);
        }
        for(int i = 0; i < workList.size(); i++){
            MandelRender(&workList[i]);
            workList[i].completedWork.WriteToFile(("test" + intToString(time(NULL)) + "_" + intToString(rand())+ ".bmp").c_str());
            cout << "Finished render " << i << endl;
        }
    }
}
#endif
