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
#include <windows.h>
#include <process.h>
#include <SFML/Network.hpp>
#include "workOrder.cpp"

//Project Build options specify the location of gmp.h
#include "gmpxx.h"

using namespace std;

//TODO: this setting should be externally defined by a config.ini file
int MAXTHREADS = 2;

//Type for use with TTMATH library. This is slower but seems to be more C++ compliantMichelle Elaine Kelly
typedef ttmath::Big<TTMATH_BITS(32), TTMATH_BITS(1024)> LLDo;

struct workerThread{
    //ip of managment server
    string serverIp;
    //maximum number of threads to be used
    unsigned int maxThreads;
    //the value from 0 to maxThreads - 1 indicating this threads position.
    unsigned int threadID;
    //string which main function can access and print to display overall worker node progress
    string workProgress;
    //totaltime spent rendering
    unsigned long long int totalRenderTime;

    //seed for use in all random operations
    unsigned long long randSeed;


    //for debug in severless test scenarios
    workOrder_t testWork;
    long int testFramesToRender;

    workerThread(){
        maxThreads = 0;
        threadID = 0;
        totalRenderTime =0;
        workProgress = "";
        randSeed = 0;
    }
};

void threadWorker(workerThread* wT);
string intToString(long long int val);
string doubleToString(long double val);
int MandelRender(workOrder_t *w);
RGBApixel mandelPixel(workOrder_t *w, unsigned long long int x, unsigned long long int y);
unsigned long long randMult();
sf::Packet& operator <<(sf::Packet& packet, BMP& m);
sf::Packet& operator >>(sf::Packet& packet, workOrder_t& m);

int main(){

//cin.get();
    //mpf_set()

    /*workOrder_t testWork;
    testWork.workType = 1;
    testWork.xCord = "-1.5";
    testWork.yCord = "0";
    testWork.FrameWidth = 700;
    testWork.FrameHeight = 400;
    testWork.zoomFactor = "1";
    testWork.maximumIterations = 100;

    cout << "Specify width: ";
    cin >> testWork.FrameWidth;
    cout << endl << "Specify height: ";
    cin >> testWork.FrameHeight;
    cout << endl << "Specify MaxIter: ";
    cin >> testWork.maximumIterations; */


    /*LLDo MAX_ZOOM;
    MAX_ZOOM = 2;
    for(int i = 0; i < 600; i++ ){
        MAX_ZOOM *= 2;
    }
    cout << MAX_ZOOM << endl;*/
    cout << "Enter server IP: ";
    string tempIP;

    cout << "Enter Maximum number of render threads: ";
    cin >> MAXTHREADS;

    unsigned long long int totalRenderTime = 0;

    HANDLE threads[255];
    workerThread workers [255];

    //cout << test << "  " << test + 1 << endl << *test

    workOrder_t _temp;
    cout << "Enter frame width and height seperated by a space: ";
    cin >> _temp.FrameWidth >> _temp.FrameHeight;

    cout << "Enter x and y cordinates seperated by a space: ";
    cin >> _temp.xCord >>_temp.yCord;

    cout << "Enter Maximum number of iterations (10000 reccomended): ";
    cin  >> _temp.maximumIterations;

    for(int i = 0; i < MAXTHREADS; i++){
        workers[i].maxThreads = MAXTHREADS;
        workers[i].threadID = i;
        workers[i].totalRenderTime =0;
        workers[i].workProgress = "";
        workers[i].serverIp = tempIP;
        workers[i].testWork = _temp;

        cout << "Enter Rand seed for thread #" << i;
        cin >> workers[i].randSeed;
        cout << sizeof _temp << endl;
        _temp.zoomFactor = "1000000000";
        cout << sizeof _temp << endl;
        system("PAUSE");
        threads[i] = (HANDLE)_beginthread((void(*)(void*))threadWorker, 0, (void*)&workers[i]);
    }
    WaitForMultipleObjects(MAXTHREADS, threads,true, INFINITE);
    /*for(LLDo i = 0; i < 9000; i++){
        if(i.ToInt() % 30 != 0){
            LLDo temp = testWork.zoomFactor;
            LLDo temp2, temp4;

            temp4 = temp;
            ttmath::Int<TTMATH_BITS(1024)> temp3 = temp4.ToUInt();
            temp4 = temp3;

            temp2.Log(temp4,2);

            ttmath::Int<TTMATH_BITS(1024)> temp5 = temp2.ToUInt();
            temp2 = temp5;

            temp += (temp2 + 1) / 30;
            testWork.zoomFactor = temp.ToString();
        } else {
            LLDo temp = 2;
            temp.Pow(i / 30);
            testWork.zoomFactor = temp.ToString();
        }

        MandelRender(&testWork);
        cout << "Frame #: " << i + 1 << endl;
        cout << "ZoomFactor: " << testWork.zoomFactor.substr(0, 40) << endl;
        cout << endl << "Render Time: " << testWork.timeWorkFinsished - testWork.timeWorkStarted << endl;
        totalRenderTime += testWork.timeWorkFinsished - testWork.timeWorkStarted;
        cout << "Average Render time per frame: " << totalRenderTime / (i.ToInt() + 1) << endl;
        cout << "Overall Render time: " << totalRenderTime << endl << endl;
        //cout << testWork.completedWork.GetPixel(320, 240).Red << " " << testWork.completedWork.GetPixel(320, 240).Green << " "<< testWork.completedWork.GetPixel(320, 240).Blue;
        string Filename = i.ToString() + ".bmp";
        testWork.completedWork.WriteToFile(Filename.c_str());
    } */
    system("PAUSE");


    //LLDo xPan = 0;//-1.74006238257933990522084416706582563829664172043617;
    //LLDo yPan = 0;//0.02817533977921104899241152114431950968753907674299;

    //zoomFactor = "1";
    //for (int k = 0; k < 800; k++){
    //    zoomFactor *= 10;
    //}
    //string filename = intToString(totalZooms) + " " + xPan.ToString().substr(0,8)+ "," + yPan.ToString().substr(0,8) + " AT " + zoomFactor.ToString() + " " +  intToString(test.TellWidth()) + "x" + intToString(test.TellHeight()) + "@" + intToString(max_iteration) + ".bmp";
    //cout <<endl << filename << endl;
    //MandelFrameRender(xPan, yPan, iterMax, zoomFactor , 640, 480).WriteToFile(filename.c_str());
    //zoomFactor  += ((pow(2,floor(log2(zoomFactor.ToDouble()))) / 30) * .75) * (1 + (((totalZooms +0) % 30) / 30));
    //totalZoomFactNum += ((pow(2,floor(log2(zoomFactor.ToDouble()))) / 30) * .75) * (1 + ((totalZooms % 30) / 30));
    //cout <<endl <<totalZoomFactNum / totalZooms << endl;
    return 0;
}

int MandelRender(workOrder_t *w){

    w->timeWorkStarted = time(NULL);

    switch(w->workType){
        case -1:
            return -1;
            break;
        case 0:
            return 1;
            break;
        case 1:
            w->completedWork.SetSize(w->FrameWidth, w->FrameHeight);

            //iterate through pixels in frame where x = i and j = y
            for(unsigned long long int i = 0; i < w->FrameWidth; i++){
                for(unsigned long long int j = 0; j < w->FrameHeight; j++){
                    w->completedWork.SetPixel(i,j,mandelPixel(w,i,j));
                }
                if (i % 100 == 0){
                    //cout << i << "/" << w->FrameWidth << endl;
                }
            }
            break;

        case 2:
            if (w->isHorizontal){
                w->completedWork.SetSize(w->FrameWidth, 1);

                for(unsigned long long int j =0; j < w->FrameHeight ; j++){
                    w->completedWork.SetPixel(w->lineNum,j,mandelPixel(w,w->lineNum,j));
                    if (j % 20 == 0){
                        //cout << j << "/" << w->FrameHeight << endl;
                    }
                }
            } else {
                w->completedWork.SetSize(1, w->FrameHeight);

                for(unsigned long long int j =0; j < w->FrameWidth ; j++){
                    w->completedWork.SetPixel(w->lineNum,j,mandelPixel(w,j,w->lineNum));
                    if (j % 20 == 0){
                       // cout << j << "/" << w->FrameWidth<< endl;
                    }
                }
            }
            break;
        case 3:
            w->completedWork.SetSize(1,1);

            w->completedWork.SetPixel(w->pixelX, w->pixelY, mandelPixel(w, w->pixelX, w->pixelY));
            break;
        default:
            return -2;
            break;
    }

    w->timeWorkFinsished = time(NULL);
    return (0);
}

RGBApixel mandelPixel(workOrder_t *w, unsigned long long int x, unsigned long long int y){

    //these values are used in replacement of constants during view scaling
    mpf_class a, b, c, d;
    a = "3.5";
    b = "2.5";
    c = "2.0";
    d = "1";
    RGBApixel output;
    //Variable Declaration, values to be determined in loop
    mpf_class x0, y0, xtemp, mpfX, mpfY, i, j, _x, _y;

    mpfX = intToString(x);
    mpfY = intToString(y);

    mpf_class zoomFactor;
    zoomFactor = w->zoomFactor;

    mpf_class xPan;
    xPan = w->xCord;

    mpf_class yPan;
    yPan = w->yCord;

    mpf_class FrW, FrH;

    FrW = intToString(w->FrameWidth);
    FrH = intToString(w->FrameHeight);

    x0 = (mpfX / ( FrW / (a/ zoomFactor))) -(b/ zoomFactor) + xPan;
    y0 = (mpfY /  (FrH / (c/zoomFactor))) - (d/zoomFactor) + yPan;

    unsigned long long int iteration = 0;
    while((_x*_x) + (_y*_y) < 4 && iteration < w->maximumIterations){
        xtemp = (_x*_x) - (_y*_y) + x0;
        _y = (c*_x*_y) + y0;

        _x = xtemp;
        iteration++;
    }

    if (iteration >= w->maximumIterations){
        output.Red = 0;
        output.Green = 0;
        output.Blue = 0;
    } else {
        long temp = iteration * (16777216 / w->maximumIterations);
        output.Red = temp / 65025;
        temp -= output.Red * 65025;
        output.Green = temp / 255;
        temp -= output.Green * 255;
        output.Blue = temp;
    }
    w->totalIterationsUsed += iteration;
    return output;
}

string intToString(long long int val){
    stringstream ss;
    ss << val;
    return  ss.str();
}
string doubleToString(long double val){
    stringstream ss;
    ss << val;
    return  ss.str();
}

void threadWorker(workerThread* wT){
    string cachedProjectName; //stores the project name for the most recently conencted to server
    vector<workOrder_t> workList;

    while(true){
        sf::TcpSocket socket;

        sf::Socket::Status status = socket.connect(wT ->serverIp, 60606);

        int retries = 0;
        while (status != sf::Socket::Done){
            cerr << "Socket failed to initialize with remote host. Retrying...";
            sf::Socket::Status status = socket.connect(wT ->serverIp, 60606);
        }

        sf::Packet serverDetails;

        while (socket.receive(serverDetails) != sf::Socket::Done) {
            cerr << "Failed to receive server_Details. Retrying...";
        }

        sf::Packet clientDetails;
        clientDetails << wT -> threadID;

        while(socket.send(clientDetails) != sf::Socket::Done){
            cerr << "Failed to send client_Details. Retrying...";
        }

        string tempProjectName;
        serverDetails >> tempProjectName;

        if(tempProjectName == cachedProjectName){
            sf::Packet sendWork;
            for(vector<workOrder_t>::iterator it = workList.begin(); it != workList.end(); ++it){
                if(it ->workType != 0 && it ->workType != -1){
                    sendWork << 2 << 1 << it-> WIN <<it ->completedWork;
                    socket.send(sendWork);
                }
            }
        } else {
            sf::Packet sendNullWork;
            sendNullWork << 2 << 0;
            //socket.send(sendNullWork);
        }

        sf::Packet workReception;

        while (socket.receive(workReception) != sf::Socket::Done) {
            cerr << "Failed to receive work allocation. Retrying...";
        }

        socket.disconnect();

        int workQuant = 0;
        workReception >> workQuant;

        workList.clear();

        for(long int i = 0; i < workQuant; i++){
            workOrder_t temp;
            workReception >> temp;
            workList.push_back(temp);
        }



    //get workorders from server here
    //server work will populate workList

        /*workOrder_t tempWork;
        tempWork.workType = 1;
        tempWork.xCord = wT -> testWork.xCord;
        tempWork.yCord = wT -> testWork.yCord;
        tempWork.FrameWidth = wT -> testWork.FrameWidth;
        tempWork.FrameHeight = wT -> testWork.FrameHeight;
        tempWork.maximumIterations = wT -> testWork.maximumIterations;

        srand(wT ->randSeed);

        for(int i = 0; i < 100; i++){
            tempWork.zoomFactor = intToString(randMult());
            workList.push_back(workOrder_t(tempWork));
        }
*/
        for(vector<workOrder_t>::iterator it = workList.begin(); it != workList.end(); ++it){
            it -> totalIterationsUsed = 0;
            MandelRender(&(*it));
            wT ->totalRenderTime +=  it ->timeWorkFinsished - it ->timeWorkStarted;
            string filename = intToString(it ->FrameWidth) + "x" + intToString(it ->FrameHeight) +" " + it ->xCord + "," + it ->yCord + "&" + it ->zoomFactor + "@" + intToString(it ->maximumIterations) + ".bmp";
            it ->completedWork.WriteToFile(filename.c_str());
            //string status = "Thread #" + intToString(wT ->threadID) + " completed in " + intToString(it ->timeWorkFinsished - it ->timeWorkStarted) + " seconds./nTotal iterations: " + it ->totalIterationsUsed.ToString;
            cout << "Thread #" << intToString(wT ->threadID) << " completed in " << intToString(it ->timeWorkFinsished - it ->timeWorkStarted) << " seconds" << endl << "Total iterations: " << intToString(it ->totalIterationsUsed) << endl << it ->totalIterationsUsed /(it ->timeWorkFinsished - it ->timeWorkStarted) << " it/s" << endl << (it ->completedWork.TellHeight() * it ->completedWork.TellWidth()) / (it ->timeWorkFinsished - it ->timeWorkStarted) << " px/s" << endl<< endl ;
        }
    }
}

unsigned long long randMult(){
    return (unsigned long long)((rand()) + (rand() * 16)); //+ (rand() * 524288) + (rand() * 17179869184) + (rand()* 562949953421312));
}

sf::Packet& operator<< (sf::Packet& packet,  BMP& m){
    packet << m.TellHeight() << m.TellWidth();
    for(long i = 0; i < m.TellWidth(); i++){
        for(long j = 0; j < m.TellHeight(); j++){
                packet << m.GetPixel(i, j).Red << m.GetPixel(i, j).Green << m.GetPixel(i, j).Blue << m.GetPixel(i, j).Alpha ;
        }
    }
}

sf::Packet& operator>> (sf::Packet& packet, workOrder_t& m){
    return packet >> m.workType >> m.xCord >> m.yCord >> m.FrameWidth >> m.FrameHeight >> m.zoomFactor >> m.maximumIterations >> m.WIN >> m.isHorizontal >> m.lineNum >> m.pixelX >> m.pixelY >> m.timeReceived >> m.timeWorkStarted >> m.timeWorkFinsished;
}

/*sf::Packet& operator <<(sf::Packet& packet, const unsigned long long int& m)
{
    return packet << (UINT32)m/4294967296 <<(((UINT32)m * 4294967296) / 4294967296)<< m.str;
}
sf::Packet& operator >>(sf::Packet& packet, unsigned long long int& m)
{
    return packet >> (UINT32)m * 4294967296 >> (UINT32)m >> m.str;
}*/
