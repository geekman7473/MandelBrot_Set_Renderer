#ifndef PACKETOPS
#define PACKETOPS

#include "depend\EasyBMP\EasyBMP.h"
#include <SFML/System.hpp>
#include <SFML/Network.hpp>

sf::Packet& operator<< (sf::Packet& packet,  BMP& m);
//sf::Packet& operator>> (sf::Packet& packet, workOrder_t& m){
//    return packet >> m.workType >> m.xCord >> m.yCord >> m.FrameWidth >> m.FrameHeight >> m.zoomFactor >> m.maximumIterations >> m.WIN >> m.isHorizontal >> m.lineNum >> m.pixelX >> m.pixelY >> m.timeReceived >> m.timeWorkStarted >> m.timeWorkFinsished;
//}
#endif
