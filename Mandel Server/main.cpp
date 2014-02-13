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

#define MAX_CLIENTS 100

sf::Packet& operator>> (sf::Packet& packet,  BMP& m){
    int tempX, tempY; packet >> tempY; packet >> tempX;
    cout <<"tempX: " << tempX << " tempY: " << tempY << endl;
    cin.sync();
    cin.get();
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
    cout << endl << client ->getRemoteAddress() << ":" << client ->getRemotePort()  << "Connected" << endl;
    while(true){
        sf::Packet message;
        if (client ->receive(message) != sf::Socket::Done){
            cerr << "Failed to receive...";
            return;
        }
        string messageType;
        message >> messageType;
        cout << endl << client ->getRemoteAddress() << ":" << client ->getRemotePort()  << endl << messageType;
        if(messageType == "1"){
            message.clear();
            message << (sf::Uint16)1;
            message << "0";
            message << "0";
            message << (sf::Uint32)1920;
            message << (sf::Uint32)1080;
            message << "1";
            message << (sf::Uint32)10;
            message << "0";
            message << false;
            if(client ->send(message) != sf::Socket::Done){
                cerr << "Failed to send..." << endl;
                return;
            }
        } else if(messageType == "2"){
            cout << "Receiving work from" << client ->getRemoteAddress() << ":" << client ->getRemotePort() << "..." << endl;
            BMP receiveWork;
            message >> receiveWork;
            receiveWork.WriteToFile("workReception.bmp");
            cout << "Work flushed to file!" << endl;
        }
    }
}

int main(){
    sf::TcpListener listener;

    // bind the listener to a port
    if (listener.listen(60606) != sf::Socket::Done){
        cerr << "Failed to bind listener to port...";
        return(-1);
    }

    HANDLE threads[MAX_CLIENTS];
    sf::TcpSocket clientSockets[MAX_CLIENTS];
    long currentThreadNo = 0;

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
