#ifndef PACKETOPS
#define PACKETOPS

#include "depend\EasyBMP\EasyBMP.h"
#include <SFML/System.hpp>
#include <SFML/Network.hpp>
#include "workOrder.hpp"

sf::Packet& operator>> (sf::Packet& packet,  BMP& m);
sf::Packet& operator<< (sf::Packet& packet, workOrder_t& m);

#endif
