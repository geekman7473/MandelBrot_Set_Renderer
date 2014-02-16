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
#include "depend\TinyThread++\tinythread.h"
#include "depend\TinyThread++\tinythread.cpp"

//Project Build options specify the location of gmp.h
#include "gmpxx.h"

using namespace std;
using namespace tthread;

#include "Util.hpp"
#include "workOrder.hpp"
#include "workerThread.hpp"
#include "PacketOps.hpp"
#include "Render.hpp"

//Type for use with TTMATH library. This is slower but seems to be more C++ compliant
typedef ttmath::Big<TTMATH_BITS(32), TTMATH_BITS(1024)> LLDo;

void pause() __attribute__((destructor));

int main(){
    srand(NULL);

    cout << "Enter server IP:  ";
    string tempIP;
    cin >> tempIP;
    int MAXTHREADS = 0;
    cout << endl <<"Enter Maximum number of render threads: ";
    cin >> MAXTHREADS;

    unsigned long long int totalRenderTime = 0;

    workerThread workers [255];
    vector<thread *> threadList;

    for(int i = 0; i < MAXTHREADS; i++){
        workers[i].maxThreads = MAXTHREADS;
        workers[i].threadID = i + 7; //+7 is for debug purposes
        workers[i].totalRenderTime =0;
        workers[i].workProgress = "";
        workers[i].serverIp = tempIP;
        //workers[i].maxRetries = 5;
        workers[i].workerID = "ISAAC";
        threadList.push_back(new thread(threadWorker, (void *)&workers[i]));
    }

    for(vector<thread *>::iterator i = threadList.begin(); i != threadList.end(); ++ i){
        thread * t = *i;
        t->join();
        delete t;
    }
    cout << "All threads terminated. Press any key to continue...";
    pause();
    return 0;
}

void pause(){
   std::cin.sync();
   std::cin.ignore();
}
