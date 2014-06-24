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

using namespace std;

#define MAX_CLIENTS 1000

#include "Util.hpp"
#include "workOrder.hpp"

unsigned long long projCreationTime;

vector<workOrder_t> unAsWorkList;

sf::Packet& operator>> (sf::Packet& packet,  BMP& m){
    sf::Int32 tempX, tempY; packet >> tempY; packet >> tempX;
    cout << endl <<"tempX: " << tempX << " tempY: " << tempY << endl;
    m.SetSize(tempX, tempY);
    for(long i = 0; i < tempX; i++){
        for(long j = 0; j < tempY; j++){
                sf::Int16 red, green, blue, alpha; packet >> red; packet >> green; packet >> blue; packet >> alpha;
                RGBApixel tempPx; tempPx.Red = (int)red; tempPx.Green = (int)green; tempPx.Blue = (int)blue; tempPx.Alpha = (int)alpha;
                m.SetPixel(i, j, tempPx);
        }
    }
}

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
                receiveWork.WriteToFile("workReception.bmp");
                cout << "Work flushed to file!" << endl;
            }
        }else if (messageType ==  "3"){//request for work
            message.clear();
            message << "5";
            message << 1;
            message << (sf::Uint16)1;
            message << "0";
            message << "0";
            message << (sf::Uint32)1000;
            message << (sf::Uint32)1000;
            message << "1";
            message << (sf::Uint32)100;
            message << "0";
            message << false;
            message << 0;
            message << 0;
            if(client ->send(message) != sf::Socket::Done){
                cerr << "Failed to send..." << endl;
                return;
            }
        }
    }
}

int main(){

    //The following is a placeholder
    //This code will initialize the project
    //with an array list of renders designed to render a large scale "panoramic" style image
  /*  int projHeight, projWidth, vertChunks, horChunks;

    cout << "Enter the height and width of the desired output image separated by a space: ";
    cin >> projHeight >> projWidth;
    cout << endl << "Enter the number of vertical and horizontal chunks separated by a space: ";
    cin >> vertChunks >> horChunks;

    for(int i = 0; i < (projHeight * projWidth)/ (vertChunks * horChunks); i++){
        workOrder_t temp;
        temp.
        workList.push_back()
    } */
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
