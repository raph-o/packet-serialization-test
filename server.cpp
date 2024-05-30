#include <atomic>
#include <iostream>
#include <sstream>
#include <thread>

#include <cereal/types/string.hpp>
#include <cereal/archives/portable_binary.hpp>

#include <enet/enet.h>

#include "headers/player.h"

std::atomic<bool> quit(false);
void listenForExit()
{
    std::string input;
    while (true)
    {
        std::cin >> input;
        if (input == "quit")
        {
            quit = true;
            break;
        }
    }
}

void sendPacketToAllPeers(const ENetHost* host)
{
    for (int i = 0; i < host->peerCount; i++)
    {
        ENetPeer* peer = &host->peers[i];
        if (peer->state == ENET_PEER_STATE_DISCONNECTED) continue;
        std::ostringstream os;
        {
            cereal::PortableBinaryOutputArchive oarchive(os);
            Player player("Player " + std::to_string(i), i + 1, i + 2);
            oarchive(player);
        }
        std::string data = os.str();
        ENetPacket* packet = enet_packet_create(data.c_str(), data.size(), ENET_PACKET_FLAG_RELIABLE);
        enet_peer_send(peer, 0, packet);
    }
}

int main()
{
    enet_initialize();
    atexit(enet_deinitialize);

    ENetAddress address;
    address.host = ENET_HOST_ANY;
    address.port = 1234;

    ENetHost* server = enet_host_create(&address, 2, 1, 0, 0);
    std::thread inputThread(listenForExit);

    while (!quit)
    {
        ENetEvent event;
        if (enet_host_service(server, &event, 1000) > 0)
        {
            switch (event.type)
            {
            case ENET_EVENT_TYPE_CONNECT:
                std::cout << "A new client connected" << std::endl;
                sendPacketToAllPeers(server);
                break;
            case ENET_EVENT_TYPE_DISCONNECT:
                std::cout << "A client disconnected" << std::endl;
                break;
            default:
                break;
            }
        }
    }

    inputThread.join();
    enet_host_destroy(server);
    return EXIT_SUCCESS;
}