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
    }
#endif
