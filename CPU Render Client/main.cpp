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

    workerThread workers [255];
    vector<thread *> threadList;

    for(int i = 0; i < MAXTHREADS; i++){
        workers[i].maxThreads = MAXTHREADS;
        workers[i].threadID = i;
        workers[i].totalRenderTime =0;
        workers[i].workProgress = "";
        workers[i].serverIp = tempIP;
        threadList.push_back(new thread(threadWorker, (void *)&workers[i]));
    }

    cin.get();
    return 0;
}
