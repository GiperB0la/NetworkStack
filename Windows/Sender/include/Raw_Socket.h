#pragma once
#include <iostream>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <thread>
#include <mutex>
#include <unordered_map>
#include <string>
#include <chrono>
#include <iomanip>
#include <vector>

#pragma comment(lib, "Ws2_32.lib")
#pragma warning(disable: 4996)

#include "../include/Protocol_UDP.h"
#include "../include/Protocol_IP.h"


class NetworkStack;
class Raw_Socket
{
    friend NetworkStack;

public:
    Raw_Socket(uint16_t recipient_port, uint32_t recipient_IP, const std::string& data);
    ~Raw_Socket();

public:
    void start();

private:
    void create_packet_udp();
    void send_packet();
    void print_packet() const;
    void print_protocols() const;

private:
    void init();
    void cleanup();

private:
    uint32_t recipient_IP;
    uint16_t recipient_port;
    const std::string data;

private:
    WSADATA wsa;
    sockaddr_in info;
    SOCKET raw_socket;
    char packet[4096];

private:
    Protocol_IP* iph;
    Protocol_UDP* udph;
};