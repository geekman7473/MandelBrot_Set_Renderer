#include <iostream>
#include <stdio.h>
#include <stdio.h>
#include <time.h>
#include <assert.h>
#include <cstdlib>
#include <string>
#include <sstream>
#include <SFML/Network.hpp>
#include <windows.h>
#include <process.h>

using namespace std;

#define MAX_CLIENTS 100

void manageConnection(sf::TcpSocket *client){
    while(true){
        sf::Packet message;
        if (client ->receive(message) != sf::Socket::Done){
            cerr << "Failed to receive...";
            return;
        }
        //std::cout << "Received " << received << " bytes" << std::endl;
        //for (int i =0; i < 100; i++){
        //    cout << data[i];
        //}
        string test1;
        message >> test1;
        /*for(int i = 0; i< test1.size(); i++){
            if(test1[i] == '_'){
                test1[i] = ' ';
            }
        }*/
        cout << endl << client ->getRemoteAddress() << ":" << client ->getRemotePort()  << endl << test1;
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
