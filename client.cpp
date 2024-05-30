#include <iostream>
#include <ostream>
#include <sstream>

#include <cereal/types/string.hpp>
#include <cereal/archives/binary.hpp>
#include <cereal/archives/portable_binary.hpp>

#include <enet/enet.h>

#include "headers/player.h"

int main()
{
    enet_initialize();
    atexit(enet_deinitialize);

    ENetAddress address;
    enet_address_set_host(&address, "127.0.0.1");
    address.port = 1234;

    ENetHost* client = enet_host_create(nullptr, 1, 1, 0, 0);
    ENetPeer* peer = enet_host_connect(client, &address, 1, 0);

    ENetEvent event;
    if (enet_host_service(client, &event, 5000) > 0 && event.type == ENET_EVENT_TYPE_CONNECT)
    {
        std::cout << "Connection to server succeded" << std::endl;
    } else enet_peer_reset(peer);

    Player player;
    if (enet_host_service(client, &event, 5000) > 0 && event.type == ENET_EVENT_TYPE_RECEIVE)
    {
        {
            std::string data(reinterpret_cast<char*>(event.packet->data), event.packet->dataLength);
            std::istringstream is(data);
            cereal::PortableBinaryInputArchive iarchive(is);
            iarchive(player);
        }
    }

    std::cout << player.name << ", " << player.x << ", " << player.y << std::endl;

    enet_peer_disconnect(peer, 0);
    if (enet_host_service(client, &event, 10000) > 0 && event.type == ENET_EVENT_TYPE_DISCONNECT)
        std::cout << "Disconnection succcessful";

    enet_host_destroy(client);
    return 0;
}
