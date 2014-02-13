#ifndef PACKETOPS_c
#define PACKETOPS_c
#include "packetOps.hpp"

#include "depend\EasyBMP\EasyBMP.h"
#include <SFML/System.hpp>
#include <SFML/Network.hpp>

sf::Packet& operator<< (sf::Packet& packet,  BMP& m){
    packet << m.TellHeight() << m.TellWidth();
    for(long i = 0; i < m.TellWidth(); i++){
        for(long j = 0; j < m.TellHeight(); j++){
                packet << (sf::Int16) m.GetPixel(i, j).Red << (sf::Int16) m.GetPixel(i, j).Green << (sf::Int16) m.GetPixel(i, j).Blue << (sf::Int16) m.GetPixel(i, j).Alpha;
        }
    }
}

//sf::Packet& operator>> (sf::Packet& packet, workOrder_t& m){
//    return packet >> m.workType >> m.xCord >> m.yCord >> m.FrameWidth >> m.FrameHeight >> m.zoomFactor >> m.maximumIterations >> m.WIN >> m.isHorizontal >> m.lineNum >> m.pixelX >> m.pixelY >> m.timeReceived >> m.timeWorkStarted >> m.timeWorkFinsished;
//}
#endif
