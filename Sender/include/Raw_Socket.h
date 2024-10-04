#pragma once
#include <iostream>
#include <thread>
#include <mutex>
#include <unordered_map>
#include <string>
#include <chrono>
#include <iomanip>
#include <vector>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <cstring>
#include <unistd.h>

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
    sockaddr_in info;
    int raw_socket;
    char packet[4096];

private:
    Protocol_IP* iph;
    Protocol_UDP* udph;
};