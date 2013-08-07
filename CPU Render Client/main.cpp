#include <iostream>
#include "EasyBMP\EasyBMP.h"
#include <stdio.h>
#include <time.h>
#include <assert.h>
#include<cstdlib>
#include<string>
#include<sstream>
#include "gmp.h"
#include "ttmath\ttmath\ttmath.h"

using namespace std;

#define iterMax 10000

typedef ttmath::Big<TTMATH_BITS(128), TTMATH_BITS(256)> LLDo;

string intToString(long long int val);
string doubleToString(long double val);
BMP MandelFrameRender(LLDo xPan, LLDo yPan, long long maxIter, LLDo zoomFactor, long imgWidth, long imgHeight);

int main()
{
    /*
mpf_t a,b,c;
mpf_init2(a,NULL);
mpf_init2(b,NULL);
mpf_init2(c,NULL);

mpf_set_str(a, "12348274342894733242342342.0",10);
mpf_set_str(b,"-567832434238472963946287637846.0",10); //Decimal base

mpf_add(c,a,b);

cout<<"\nThe exact result is:";
mpf_out_str(stdout,10,0,c);
cout<<endl;

mpf_abs(c,c);
cout<<"The absolute value result is:";
mpf_out_str(stdout,10,0,c);
cout<<endl; */

LLDo lol;
lol = "-1.740062382579339905220844167065825638296641720436171866879862418461182919644153056054840718339483225743450008259172138785492983677893366503417299549623738838303346465461290768441055486136870719850559269507357211790243666940134793753068611574745943820712885258222629105433648695946003865";
cout << lol << endl;
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
while (zoomFactor < 100000000000000000000000000000000000){

    LLDo xPan = -1.74006238257933990522084416706582563829664172043617;
    LLDo yPan = 0;//0.02817533977921104899241152114431950968753907674299;



    string filename = intToString(totalZooms) + " " + xPan.ToString().substr(0,8)+ "," + yPan.ToString().substr(0,8) + " AT " + zoomFactor.ToString() + " " +  intToString(test.TellWidth()) + "x" + intToString(test.TellHeight()) + "@" + intToString(max_iteration) + ".bmp";
    cout <<endl << filename << endl;
    MandelFrameRender(xPan, yPan, iterMax, zoomFactor, 1920, 1080).WriteToFile(filename.c_str());
    zoomFactor  += ((pow(2,floor(log2(zoomFactor.ToDouble()))) / 30) * .75) * (1 + (((totalZooms +0) % 30) / 30));
    totalZoomFactNum += ((pow(2,floor(log2(zoomFactor.ToDouble()))) / 30) * .75) * (1 + ((totalZooms % 30) / 30));
    //cout <<endl <<totalZoomFactNum / totalZooms << endl;
    totalZooms++;
}
    return 0;
}

BMP MandelFrameRender(LLDo xPan, LLDo yPan, long long maxIter, LLDo zoomFactor, long imgWidth, long imgHeight){
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
