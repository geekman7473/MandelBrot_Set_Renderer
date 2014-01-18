#ifndef PACKETOPS
#define PACKETOPS

sf::Packet& operator<< (sf::Packet& packet,  BMP& m){
    packet << m.TellHeight() << m.TellWidth();
    for(long i = 0; i < m.TellWidth(); i++){
        for(long j = 0; j < m.TellHeight(); j++){
                packet << m.GetPixel(i, j).Red << m.GetPixel(i, j).Green << m.GetPixel(i, j).Blue << m.GetPixel(i, j).Alpha ;
        }
    }
}

//sf::Packet& operator>> (sf::Packet& packet, workOrder_t& m){
//    return packet >> m.workType >> m.xCord >> m.yCord >> m.FrameWidth >> m.FrameHeight >> m.zoomFactor >> m.maximumIterations >> m.WIN >> m.isHorizontal >> m.lineNum >> m.pixelX >> m.pixelY >> m.timeReceived >> m.timeWorkStarted >> m.timeWorkFinsished;
//}
#endif
