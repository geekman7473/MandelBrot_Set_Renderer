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

//Project Build options specify the location of gmp.h
#include "gmpxx.h"

using namespace std;

#define iterMax 100

typedef ttmath::Big<TTMATH_BITS(32), TTMATH_BITS(1024)> LLDo;

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
    long long FrameWidth, FrameHeight;
    //this value determines the zoomFactor for the frame of reference upon which the work is to be based
    string zoomFactor;
    //Determines the maximum iterations for the work
    long long int maximumIterations;
    //Finished work will be stored in this variable for transmission back to server
    BMP completedWork;
};

string intToString(long long int val);
string doubleToString(long double val);
BMP MandelFrameRender(LLDo xPan, LLDo yPan, long long maxIter, LLDo zoomFactor, long long imgWidth, long long imgHeight);

int main(){
LLDo lol;
lol = "-1.740062382579339905220844167065825638296641720436171866879862418461182919644153056054840718339483225743450008259172138785492983677893366503417299549623738838303346465461290768441055486136870719850559269507357211790243666940134793753068611574745943820712885258222629105433648695946003865";
cout << lol << endl << lol.ToString().length();
system("PAUSE");
mpf_class aBigPO2 (1073741824, 1024);
  aBigPO2*=aBigPO2; //2^60
  aBigPO2*=aBigPO2; //2^120
  aBigPO2*=aBigPO2; //2^240
  aBigPO2*=aBigPO2; //2^480
  aBigPO2*=aBigPO2; //2^960
  aBigPO2*=aBigPO2; //2^1920

  mpf_out_str(stdout,10,1000, aBigPO2.get_mpf_t());
  system("PAUSE");


//cin.get();
    //mpf_set()

    long long int totalIters = 0;
    long long max_iteration = iterMax;
    BMP test;
    test.SetSize(1920, 1080);
    LLDo zoomFactor =1;
    long long int totalZooms = 1;
    LLDo totalZoomFactNum = 0;
while (true){

    LLDo xPan = 0;//-1.74006238257933990522084416706582563829664172043617;
    LLDo yPan = 0;//0.02817533977921104899241152114431950968753907674299;

    zoomFactor = "1";
    //for (int k = 0; k < 800; k++){
    //    zoomFactor *= 10;
    //}
    string filename = intToString(totalZooms) + " " + xPan.ToString().substr(0,8)+ "," + yPan.ToString().substr(0,8) + " AT " + zoomFactor.ToString() + " " +  intToString(test.TellWidth()) + "x" + intToString(test.TellHeight()) + "@" + intToString(max_iteration) + ".bmp";
    cout <<endl << filename << endl;
    MandelFrameRender(xPan, yPan, iterMax, zoomFactor , 640, 480).WriteToFile(filename.c_str());
    zoomFactor  += ((pow(2,floor(log2(zoomFactor.ToDouble()))) / 30) * .75) * (1 + (((totalZooms +0) % 30) / 30));
    totalZoomFactNum += ((pow(2,floor(log2(zoomFactor.ToDouble()))) / 30) * .75) * (1 + ((totalZooms % 30) / 30));
    //cout <<endl <<totalZoomFactNum / totalZooms << endl;
    totalZooms++;
}
    return 0;
}

BMP MandelFrameRender(LLDo xPan, LLDo yPan, long long maxIter, LLDo zoomFactor, long long imgWidth, long long imgHeight){
    long long startT = time(NULL);
    BMP Frame;
    Frame.SetSize(imgWidth, imgHeight);

    LLDo a, b, c, d;
    a = "3.5";
    b = "2.5";
    c = "2.0";
    d = "1";

    //Variable Declaration, values to be determined in loop
    LLDo x0, y0, xtemp, x, y, i, j;
    for(i = 0; i < Frame.TellWidth(); i++){
        for(j = 0; j < Frame.TellHeight(); j++){


                x0 = (i / ((LLDo) Frame.TellWidth() / (a/zoomFactor))) -(b/zoomFactor) + xPan;
                y0 = (j /  ((LLDo)Frame.TellHeight()/ (c/zoomFactor))) - (d/zoomFactor) + yPan;
                //cout << i << " " << x0 << " " << j << " " << y0 << endl;
                //system("PAUSE");
                x = 0;
                y =0;

                long long iteration = 0;

                while((x*x) + (y*y) < 4 && iteration < maxIter){
                    xtemp = (x*x) - (y*y) + x0;
                    y = (c*x*y) + y0;

                    x = xtemp;
                    iteration++;
                }
                //cout << iteration << " " << max_iteration << endl << 255 - (iteration / ((max_iteration/2) / 255)) << endl;
                //system("PAUSE");
                if (iteration >= maxIter){
                    Frame(i.ToDouble(), j.ToDouble())->Red = 0;
                    Frame(i.ToDouble(), j.ToDouble())->Green = 0;
                    Frame(i.ToDouble(), j.ToDouble())->Blue = 0;
                } else {

                    long temp = iteration * (16777216 / maxIter);
                    Frame(i.ToDouble(), j.ToDouble())->Red = temp / 65025;
                    temp -= Frame(i.ToDouble(), j.ToDouble())->Red * 65025;
                    Frame(i.ToDouble(), j.ToDouble())->Green = temp / 255;
                    temp -= Frame(i.ToDouble(), j.ToDouble())->Green * 255;
                    Frame(i.ToDouble(), j.ToDouble())->Blue = temp;
                }
                /*} else if (iteration < max_iteration/2) {
                    Frame(i, j)->Red = iteration / ((max_iteration/2) / 255);
                    Frame(i, j)->Green = 0;
                    Frame(i, j)->Blue = 255 - (iteration / ((max_iteration/2) / 255));
                } else {
                    Frame(i, j)->Red = iteration / ((max_iteration/2) / 255);
                    Frame(i, j)->Green = iteration / ((max_iteration/2) / 255);
                    Frame(i, j)->Blue = 255;// - (iteration / ((max_iteration/2) / 255));
                }*/
        }
        if ((long long)i.ToDouble() % 20 == 0){
            cout << i << "/" << Frame.TellWidth() << endl;
        }
    }
    cout << time(NULL) - startT << endl << endl;
    system("PAUSE");
    return (Frame);
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
