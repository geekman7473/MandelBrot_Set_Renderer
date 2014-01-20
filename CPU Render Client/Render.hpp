#ifndef RENDER
#define RENDER

#include "gmpxx.h"
#include "depend\EasyBMP\EasyBMP.h"
#include "Util.cpp"
#include "workOrder.cpp"
#include "workerThread.cpp"
#include "PacketOps.cpp"

RGBApixel mandelPixel(workOrder_t *w, unsigned long long int x, unsigned long long int y);
int MandelRender(workOrder_t *w);

#endif // RENDER
