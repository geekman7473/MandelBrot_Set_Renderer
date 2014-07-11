#ifndef PACKETOPS_c
#define PACKETOPS_c
#include "packetOps.hpp"

#include <SFML/System.hpp>
#include <SFML/Network.hpp>
#include "workOrder.hpp"

sf::Packet& operator<< (sf::Packet& packet, workOrder_t& m){
    return packet << m.workType << m.xCord << m.yCord << m.FrameWidth << m.FrameHeight << m.zoomFactor << m.maximumIterations << m.WIN << m.isHorizontal << m.lineNum << m.pixelX << m.pixelY;
}

sf::Packet& operator>> (sf::Packet& packet,  BMP& m){
    sf::Int32 tempX, tempY; packet >> tempY; packet >> tempX;
    cout << endl <<"tempX: " << tempX << " tempY: " << tempY << endl;
    m.SetSize(tempX, tempY);
    for(long i = 0; i < tempX; i++){
        for(long j = 0; j < tempY; j++){
                sf::Int16 red, green, blue, alpha; packet >> red; packet >> green; packet >> blue; packet >> alpha;
                RGBApixel tempPx; tempPx.Red = (int)red; tempPx.Green = (int)green; tempPx.Blue = (int)blue; tempPx.Alpha = (int)alpha;
                m.SetPixel(i, j, tempPx);
        }
    }
}

#endif
