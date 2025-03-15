#pragma once
#include <winsock2.h>
#include <iostream>
#include <windows.h>
#include <iomanip>
#include <string>

#pragma comment(lib, "Ws2_32.lib")
#pragma warning(disable: 4996)


struct UDP_Header
{
    uint16_t source;
    uint16_t dest;
    uint16_t len;
    uint16_t check;
};

class Raw_Socket;
class Protocol_UDP
{
    friend Raw_Socket;

private:
    Protocol_UDP() = default;
    ~Protocol_UDP() = default;
    
private:
    void create_UDP_header(uint16_t sender_port, uint16_t recipient_port, const std::string& data);
    void display_udp_header_info() const;

private:
    uint16_t calculate_checksum(const std::string& data, uint32_t sender_ip, uint32_t recipient_ip);

private:
    UDP_Header header;
};