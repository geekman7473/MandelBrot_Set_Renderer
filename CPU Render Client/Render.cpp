#ifndef RENDER_c
#define RENDER_c
#include "Render.hpp"

#include "gmpxx.h"
#include "depend\EasyBMP\EasyBMP.h"
#include "Util.cpp"
#include "workOrder.cpp"
#include "workerThread.cpp"
#include "PacketOps.cpp"

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
#endif
