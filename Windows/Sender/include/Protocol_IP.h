#pragma once
#include <winsock2.h>
#include <iostream>
#include <windows.h>
#include <iomanip>
#include <string>

#pragma comment(lib, "ws2_32.lib")
#pragma warning(disable: 4996)

#include "../include/Protocol_UDP.h"


struct IP_Header
{
    uint8_t version_length;
    uint8_t tos;
    uint16_t tot_len;
    uint16_t id;
    uint16_t frag_off;
    uint8_t ttl;
    uint8_t protocol;
    uint16_t check;
    uint32_t saddr;
    uint32_t daddr;
};

class Raw_Socket;
class Protocol_IP
{
    friend Raw_Socket;

private:
    Protocol_IP() = default;
    ~Protocol_IP() = default;

private:
    void create_IPv4_header(uint32_t sender_IP, uint32_t recipient_IP, const std::string& data);
    void display_ip_header_info() const;

private:
    uint16_t calculate_checksum();

private:
    IP_Header header;
};