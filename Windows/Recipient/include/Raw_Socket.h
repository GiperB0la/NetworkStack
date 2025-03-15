#pragma once
#include <iostream>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <thread>
#include <mutex>
#include <unordered_map>
#include <string>
#include <chrono>

#pragma comment(lib, "Ws2_32.lib")
#pragma warning(disable: 4996)


class Raw_Socket
{
public:
    Raw_Socket();
    ~Raw_Socket();

public:
    void start();

private:
    void init();
    void cleanup();
    void recv_packet();

private:
    WSADATA wsa;
    sockaddr_in info;
    SOCKET raw_socket;
};