#include <iostream>
#include <stdio.h>
#include <stdio.h>
#include <time.h>
#include <assert.h>
#include <cstdlib>
#include <string>
#include <sstream>
#include "depend/easyBMP/EasyBMP.h"
#include "depend/easyBMP/EasyBMP.cpp"
#include <SFML/Network.hpp>
#include <windows.h>
#include <process.h>
#include "depend\ttmath\ttmath\ttmath.h"

using namespace std;

typedef ttmath::Big<TTMATH_BITS(32), TTMATH_BITS(1024)> LLDo;

//I have no idea if this is an appropriate upper limit
#define MAX_CLIENTS 255

#include "Util.hpp"
#include "workOrder.hpp"
#include "PacketOps.hpp"

unsigned long long projCreationTime;

vector<workOrder_t> unAsWorkList;
vector<workOrder_t> AsWorkList;
vector<workOrder_t> compWorkList;

void manageConnection(sf::TcpSocket *client){
    cout << endl << client ->getRemoteAddress() << ":" << client ->getRemotePort()  << " Connected " << endl;
    sf::Packet projDet;
    projDet << "4" << intToString(projCreationTime);
    int failCount = 0;
    while(client ->send(projDet) != sf::Socket::Done && failCount < 10){
        cerr << "Failed to send proj details to " << client ->getRemoteAddress() << ":" << client ->getRemotePort();
        failCount++;
    }
    if(failCount >= 10){ //I hope to god this works
        return;
    }

    while(true){
        sf::Packet message;
        if (client ->receive(message) != sf::Socket::Done){
            cerr << endl <<"Failed to receive..." << endl;
            return;
        }
        string messageType;
        message >> messageType;
        cout << endl << client ->getRemoteAddress() << ":" << client ->getRemotePort() << " mess: " << messageType;
        if(messageType== "1"){ //client details sent
            string remoteWorkerID;
            sf::Int32 remoteThreadID;
            message >> remoteWorkerID >> remoteThreadID;
            cout << " " << client ->getRemoteAddress() << ":" << client ->getRemotePort() << " = " << remoteWorkerID <<":" << remoteThreadID;
        }else if (messageType == "2"){//completed work reception
            cout << "Receiving work from" << client ->getRemoteAddress() << ":" << client ->getRemotePort() << "..." << endl;
            sf::Int32 workNum;
            message >> workNum;
            BMP receiveWork;
            for(int i = 0; i < workNum; i++){
                string WIN;
                sf::Uint64 totalIters;
                sf::Uint32 tempA, tempB, workTime;
                message >> WIN; //these are all of those values that you should probably do something with
                message >> receiveWork;
                message >> tempA;
                message >> tempB;
                totalIters = (tempA * 4294967296) + tempB;
                message >> workTime;
                cout << "Total Iters: " << totalIters;
                receiveWork.WriteToFile((WIN + ".bmp").c_str());
                cout << "Work flushed to file!" << endl;
                //check if this WIN is in AsWorkList and remove it if found
                for(int i = 0; i < AsWorkList.size(); i++){
                    if(AsWorkList.at(i).WIN == WIN){
                        compWorkList.push_back(AsWorkList.at(i));
                        AsWorkList.erase(AsWorkList.begin() + i);
                    }
                }
            }
        }else if (messageType ==  "3"){//request for work
            message.clear();
            workOrder_t temp;
            if(unAsWorkList.size() > 0){
                temp = unAsWorkList.at(0);
                unAsWorkList.erase(unAsWorkList.begin());
                AsWorkList.push_back(temp);
            } else if(AsWorkList.size() > 0){
                temp = AsWorkList.at(rand() % AsWorkList.size());
            } else {
                return;
            }
            message << "5";
            message << 1;
            message << temp;
            if(client ->send(message) != sf::Socket::Done){
                cerr << "Failed to send..." << endl;
                return;
            }
        }
    }
}

int main(){
    srand(NULL);
    //The following is a placeholder
    //This code will initialize the project
    //with an array list of jobs designed
    //to render a large scale "panoramic" style image
    int projHeight, projWidth, vertChunks, horChunks;

    cout << "Enter the height of the desired output image (image must be square): ";
    cin >> projHeight;
    projWidth = projHeight;
    cout << endl << "Enter the number of vertical chunks (must be square): ";
    cin >> vertChunks;
    horChunks = vertChunks;
    for(int i = 0; i < vertChunks * horChunks; i++){
        workOrder_t * temp = new workOrder_t;
        double x = (i%vertChunks)*(4/vertChunks) + ((4/vertChunks)/2) - 2; //as of now vert and hor chunks should be interchangeable
        double y = (i/horChunks)*(4/horChunks) + ((4/horChunks)/2) - 2; //but this line of code was left as in as a contingency
        temp->workType = 1;
        temp->xCord = doubleToString(x);
        temp->yCord = doubleToString(y);
        temp->zoomFactor = intToString(vertChunks);
        temp->FrameHeight = projHeight / horChunks;
        temp->FrameWidth = projWidth / vertChunks;
        temp->maximumIterations = 1000;
        temp->WIN = intToString(i);
        unAsWorkList.push_back(*temp);
        delete temp;
        cout << unAsWorkList.size() << endl;
    }
    projCreationTime = time(NULL);
    sf::TcpListener listener;

    // bind the listener to a port
    if (listener.listen(60606) != sf::Socket::Done){
        cerr << "Failed to bind listener to port...";
        return(-1);
    }

    HANDLE threads[MAX_CLIENTS];
    sf::TcpSocket clientSockets[MAX_CLIENTS];
    long currentThreadNo = 0;

    projCreationTime = time(NULL);

    while(true){
        // accept a new connection
        if (listener.accept(clientSockets[currentThreadNo]) != sf::Socket::Done){
            cerr << "Failed to accept a connection...";
        } else {
            threads[currentThreadNo] = (HANDLE)_beginthread((void(*)(void*))manageConnection, 0, (void*)&clientSockets[currentThreadNo]);
            currentThreadNo++;
        }
    }
    //char data[100];
    //memset(data, 0, 100);
    //std::size_t received;

    // TCP socket:

    system("PAUSE");
    // use "client" to communicate with the connected client,
    // and continue to accept new connections with the listener
}
