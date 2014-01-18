#include <iostream>
#include <stdio.h>
#include "depend\EasyBMP\EasyBMP.h"
#include <stdio.h>
#include <time.h>
#include <assert.h>
#include <cstdlib>
#include <string>
#include <sstream>
#include "depend\ttmath\ttmath\ttmath.h"
#include <SFML/System.hpp>
#include <SFML/Network.hpp>

//Project Build options specify the location of gmp.h
#include "gmpxx.h"

using namespace std;

#include "Util.cpp"
#include "workOrder.cpp"
#include "workerThread.cpp"
#include "PacketOps.cpp"
#include "Render.cpp"

//Type for use with TTMATH library. This is slower but seems to be more C++ compliant
typedef ttmath::Big<TTMATH_BITS(32), TTMATH_BITS(1024)> LLDo;

int main(){

    cout << "Enter server IP: ";
    string tempIP;

    int MAXTHREADS = 0;
    cout << "Enter Maximum number of render threads: ";
    cin >> MAXTHREADS;

    unsigned long long int totalRenderTime = 0;

    workerThread workers [15];

    sf::Thread thread0 (&threadWorker, &workers[0]);
    sf::Thread thread1 (&threadWorker, &workers[1]);
    sf::Thread thread2 (&threadWorker, &workers[2]);
    sf::Thread thread3 (&threadWorker, &workers[3]);
    sf::Thread thread4 (&threadWorker, &workers[4]);
    sf::Thread thread5 (&threadWorker, &workers[5]);
    sf::Thread thread6 (&threadWorker, &workers[6]);
    sf::Thread thread7 (&threadWorker, &workers[7]);
    sf::Thread thread8 (&threadWorker, &workers[8]);
    sf::Thread thread9 (&threadWorker, &workers[9]);
    sf::Thread thread10 (&threadWorker, &workers[10]);
    sf::Thread thread11 (&threadWorker, &workers[11]);
    sf::Thread thread12 (&threadWorker, &workers[12]);
    sf::Thread thread13 (&threadWorker, &workers[13]);
    sf::Thread thread14 (&threadWorker, &workers[14]);
    sf::Thread thread15 (&threadWorker, &workers[15]);

    //cout << test << "  " << test + 1 << endl << *test

    workOrder_t _temp;

    if(MAXTHREADS >= 1){
        workers[0].maxThreads = MAXTHREADS;
        workers[0].threadID = 0;
        workers[0].totalRenderTime =0;
        workers[0].workProgress = "";
        workers[0].serverIp = tempIP;

        thread0.launch();
    }
    if(MAXTHREADS >= 2){
        workers[1].maxThreads = MAXTHREADS;
        workers[1].threadID = 1;
        workers[1].totalRenderTime =0;
        workers[1].workProgress = "";
        workers[1].serverIp = tempIP;

        thread1.launch();
    }
    if(MAXTHREADS >= 3){
        workers[2].maxThreads = MAXTHREADS;
        workers[2].threadID = 2;
        workers[2].totalRenderTime =0;
        workers[2].workProgress = "";
        workers[2].serverIp = tempIP;

        thread2.launch();
    }
    if(MAXTHREADS >= 4){
        workers[3].maxThreads = MAXTHREADS;
        workers[3].threadID = 3;
        workers[3].totalRenderTime =0;
        workers[3].workProgress = "";
        workers[3].serverIp = tempIP;

        thread3.launch();
    }
    if(MAXTHREADS >= 5){
        workers[4].maxThreads = MAXTHREADS;
        workers[4].threadID = 4;
        workers[4].totalRenderTime =0;
        workers[4].workProgress = "";
        workers[4].serverIp = tempIP;

        thread4.launch();
    }
    if(MAXTHREADS >= 6){
        workers[5].maxThreads = MAXTHREADS;
        workers[5].threadID = 5;
        workers[5].totalRenderTime =0;
        workers[5].workProgress = "";
        workers[5].serverIp = tempIP;

        thread5.launch();
    }
    if(MAXTHREADS >= 7){
        workers[6].maxThreads = MAXTHREADS;
        workers[6].threadID = 6;
        workers[6].totalRenderTime =0;
        workers[6].workProgress = "";
        workers[6].serverIp = tempIP;

        thread6.launch();
    }
    if(MAXTHREADS >= 8){
        workers[7].maxThreads = MAXTHREADS;
        workers[7].threadID = 7;
        workers[7].totalRenderTime =0;
        workers[7].workProgress = "";
        workers[7].serverIp = tempIP;

        thread7.launch();
    }
    if(MAXTHREADS >= 9){
        int x = 8;
        workers[x].maxThreads = MAXTHREADS;
        workers[x].threadID = x;
        workers[x].totalRenderTime =0;
        workers[x].workProgress = "";
        workers[x].serverIp = tempIP;

        thread8.launch();
    }
    if(MAXTHREADS >= 10){
        int x = 9;
        workers[x].maxThreads = MAXTHREADS;
        workers[x].threadID = x;
        workers[x].totalRenderTime =0;
        workers[x].workProgress = "";
        workers[x].serverIp = tempIP;

        thread9.launch();
    }
    if(MAXTHREADS >= 11){
        int x = 10;
        workers[x].maxThreads = MAXTHREADS;
        workers[x].threadID = x;
        workers[x].totalRenderTime =0;
        workers[x].workProgress = "";
        workers[x].serverIp = tempIP;

        thread10.launch();
    }
    if(MAXTHREADS >= 12){
        int x = 11;
        workers[x].maxThreads = MAXTHREADS;
        workers[x].threadID = x;
        workers[x].totalRenderTime =0;
        workers[x].workProgress = "";
        workers[x].serverIp = tempIP;

        thread11.launch();
    }
    if(MAXTHREADS >= 13){
        int x = 12;
        workers[x].maxThreads = MAXTHREADS;
        workers[x].threadID = x;
        workers[x].totalRenderTime =0;
        workers[x].workProgress = "";
        workers[x].serverIp = tempIP;

        thread12.launch();
    }
    if(MAXTHREADS >= 14){
        int x = 13;
        workers[x].maxThreads = MAXTHREADS;
        workers[x].threadID = x;
        workers[x].totalRenderTime =0;
        workers[x].workProgress = "";
        workers[x].serverIp = tempIP;

        thread13.launch();
    }
    if(MAXTHREADS >= 15){
        int x = 14;
        workers[x].maxThreads = MAXTHREADS;
        workers[x].threadID = x;
        workers[x].totalRenderTime =0;
        workers[x].workProgress = "";
        workers[x].serverIp = tempIP;

        thread14.launch();
    }
    if(MAXTHREADS >= 16){
        int x = 15;
        workers[x].maxThreads = MAXTHREADS;
        workers[x].threadID = x;
        workers[x].totalRenderTime =0;
        workers[x].workProgress = "";
        workers[x].serverIp = tempIP;

        thread15.launch();
    }

    if(MAXTHREADS >= 1){
        thread0.wait();
    }
    if(MAXTHREADS >= 2){
        thread1.wait();
    }
    if(MAXTHREADS >= 3){
        thread2.wait();
    }
    if(MAXTHREADS >= 4){
        thread3.wait();
    }
    if(MAXTHREADS >= 5){

        thread0.wait();
    }
    if(MAXTHREADS >= 6){

        thread5.wait();
    }
    if(MAXTHREADS >= 7){

        thread6.wait();
    }
    if(MAXTHREADS >= 8){

        thread7.wait();
    }
    if(MAXTHREADS >= 9){

        thread8.wait();
    }
    if(MAXTHREADS >= 10){

        thread9.wait();
    }
    if(MAXTHREADS >= 11){
        thread10.wait();
    }
    if(MAXTHREADS >= 12){
        thread11.wait();
    }
    if(MAXTHREADS >= 13){
        thread12.wait();
    }
    if(MAXTHREADS >= 14){
        thread13.wait();
    }
    if(MAXTHREADS >= 15){
        thread14.wait();
    }
    if(MAXTHREADS >= 16){
        thread15.wait();
    }

    cin.get();
    return 0;
}
