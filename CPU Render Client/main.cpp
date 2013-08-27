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
#include <winsock.h>

//Project Build options specify the location of gmp.h
#include "gmpxx.h"

using namespace std;

//TODO: this setting should be externally defined by a config.ini file
#define maxThreads 6


//global socket for communication to central server
SOCKET s;

//Type for use with TTMATH library. This is slower but seems to be more C++ compliant
typedef ttmath::Big<TTMATH_BITS(32), TTMATH_BITS(1024)> LLDo;

struct workerThread{
    //maximum number of threads to be used
    unsigned int maxThreads;

    //the value from 0 to maxThreads - 1 indicating this threads position.
    unsigned int threadID;
};

struct workOrder_t {
    //defines the type of work the client is required to do
    //1 = full frame render
    //2 = scan line
    //3 = pixel
    //0 = Null Work, when encountered these work allocations should be ignored
    // -1 = Error, when encountered these work allocations should be ignored
    short int workType;
    //This string represents the coordinates of the center point of the current frame
    //for pixel and scan line renders, the work assigned will be determined by the full
    //frame determined by these coordinates, as well as dimensions and zoomFactor
    string xCord, yCord;
    //these value determine the width and height of the "frame of reference"
    unsigned long long int FrameWidth, FrameHeight;
    //this value determines the zoomFactor for the frame of reference upon which the work is to be based
    string zoomFactor;
    //Determines the maximum iterations for the work
    unsigned long long int maximumIterations;

    //For type 2 work orders only: specifies whether renders are horizontal or vertical lines from the "frame of reference"
    bool isHorizontal;
    //For type 2 work orders only: specifies the numerical value of the line to be rendered
    unsigned long long int lineNum;

    //For type 3 work orders only: specifies the coordinates of the pixel to be rendered from the "frame of reference"
    unsigned long long int pixelX, pixelY;

    //Time as a Unix timestamp that the work order was recieved from the Project Coordination Server
    unsigned long long int timeReceived;
    //Time as a Unix timestamp that the worker began working on the work order
    unsigned long long int timeWorkStarted;
    //Time as a Unix timestamp that the worker finished work on the work order
    unsigned long long int timeWorkFinsished;

    //Finished work will be stored in this variable for transmission back to the Project Coordination Server
    BMP completedWork;

    //total size of workOrder_t is at minimum 60 Bytes, size varies greatly depending on the length of its string components
};

bool ConnectToHost(int PortNo, char* IPAddress);
void CloseConnection ();
string intToString(long long int val);
string doubleToString(long double val);
int MandelRender(workOrder_t *w);
RGBApixel mandelPixel(workOrder_t *w, unsigned long long int x, unsigned long long int y);

int main(){

//cin.get();
    //mpf_set()

    workOrder_t testWork;
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
    cin >> testWork.maximumIterations;


    LLDo MAX_ZOOM;
    MAX_ZOOM = 2;
    for(int i = 0; i < 600; i++ ){
        MAX_ZOOM *= 2;
    }
    cout << MAX_ZOOM << endl;
    unsigned long long int totalRenderTime = 0;

    for(LLDo i = 0; i < 9000; i++){
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
    }
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
                    cout << i << "/" << w->FrameWidth << endl;
                }
            }
            break;

        case 2:
            if (w->isHorizontal){
                w->completedWork.SetSize(w->FrameWidth, 1);

                for(unsigned long long int j =0; j < w->FrameHeight ; j++){
                    w->completedWork.SetPixel(w->lineNum,j,mandelPixel(w,w->lineNum,j));
                    if (j % 20 == 0){
                        cout << j << "/" << w->FrameHeight << endl;
                    }
                }
            } else {
                w->completedWork.SetSize(1, w->FrameHeight);

                for(unsigned long long int j =0; j < w->FrameWidth ; j++){
                    w->completedWork.SetPixel(w->lineNum,j,mandelPixel(w,j,w->lineNum));
                    if (j % 20 == 0){
                        cout << j << "/" << w->FrameWidth<< endl;
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

bool ConnectToHost(int PortNo, char* IPAddress){
     //Start up Winsock…
    WSADATA wsadata;

    int error = WSAStartup(0x0202, &wsadata);

    //Did something happen?
    if (error){
        return false;
    }

    //Did we get the right Winsock version?
    if (wsadata.wVersion != 0x0202){
        WSACleanup(); //Clean up Winsock
        return false;
    }

    //Fill out the information needed to initialize a socket…
    SOCKADDR_IN target; //Socket address information

    target.sin_family = AF_INET; // address family Internet
    target.sin_port = htons (PortNo); //Port to connect on
    target.sin_addr.s_addr = inet_addr (IPAddress); //Target IP

    s = socket (AF_INET, SOCK_STREAM, IPPROTO_TCP); //Create socket
    if (s == INVALID_SOCKET)
    {
        return false; //Couldn't create the socket
    }

    //Try connecting...

    if (connect(s, (SOCKADDR *)&target, sizeof(target)) == SOCKET_ERROR)
    {
        return false; //Couldn't connect
    }
    else
        return true; //Success
}

void CloseConnection ()
{
    //Close the socket if it exists
    if (s)
        closesocket(s);

    WSACleanup(); //Clean up Winsock
}
