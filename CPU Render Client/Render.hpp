#ifndef RENDER
#define RENDER

#include "gmpxx.h"
#include "depend\EasyBMP\EasyBMP.h"
#include "Util.hpp"
#include "workOrder.hpp"
#include "workerThread.hpp"
#include "PacketOps.hpp"

RGBApixel mandelPixel(workOrder_t *w, unsigned long long int x, unsigned long long int y);
int MandelRender(workOrder_t *w);

#endif // RENDER
