#pragma once
#include <iostream>
#include <thread>
#include <mutex>
#include <unordered_map>
#include <string>
#include <chrono>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <cstring>


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
    sockaddr_in info;
    int raw_socket;
};