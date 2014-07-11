#ifndef WORKORDER_c
#define WORKORDER_c

#include "workOrder.hpp"

#include "depend\EasyBMP\EasyBMP.h"
#include <SFML/System.hpp>
#include <SFML/Network.hpp>

using namespace std;

    workOrder_t::workOrder_t(const workOrder_t& other){
        WIN = other.WIN;
        workType = other.workType;
        xCord = other.xCord;
        yCord = other.yCord;
        FrameWidth = other.FrameWidth;
        FrameHeight = other.FrameHeight;
        zoomFactor = other.zoomFactor;
        maximumIterations = other.maximumIterations;
        lineNum = other.lineNum;
        pixelX = other.pixelX;
        pixelY = other.pixelY;
        timeReceived = other.timeReceived;
        timeWorkStarted = other.timeWorkStarted;
        timeWorkFinsished = other.timeWorkFinsished;
        completedWork = other.completedWork;
    }
    workOrder_t::workOrder_t(){
        WIN = "";
        workType = -1;
        xCord = "";
        yCord = "";
        FrameWidth = 0;
        FrameHeight = 0;
        zoomFactor = "";
        maximumIterations = 0;
        lineNum = 0;
        pixelX = 0;
        pixelY = 0;
        timeReceived = 0;
        timeWorkStarted = 0;
        timeWorkFinsished = 0;
    }
#endif
