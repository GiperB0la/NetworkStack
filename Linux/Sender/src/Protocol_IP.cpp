#include "../include/Protocol_IP.h"


uint16_t Protocol_IP::calculate_checksum()
{
    unsigned short* buf = reinterpret_cast<unsigned short*>(&header);
    unsigned int sum = 0;
    unsigned short result;
    int len = sizeof(IP_Header);

    for (sum = 0; len > 1; len -= 2) {
        sum += *buf++;
    }
    if (len == 1) {
        sum += *(reinterpret_cast<unsigned char*>(buf));
    }

    sum = (sum >> 16) + (sum & 0xFFFF);
    sum += (sum >> 16);
    result = ~sum;
    return result;
}

void Protocol_IP::create_IPv4_header(uint32_t sender_IP, uint32_t recipient_IP, const std::string& data)
{
    header.version_length = (4 << 4) | 5;
    header.tos = 0;
    header.tot_len = htons(sizeof(IP_Header) + sizeof(UDP_Header) + data.size());
    header.id = htons(54321);
    header.frag_off = 0;
    header.ttl = 64;
    header.protocol = IPPROTO_UDP;
    header.check = 0;
    // header.check = calculate_checksum();
    header.saddr = sender_IP;
    header.daddr = recipient_IP;
}

void Protocol_IP::display_ip_header_info() const
{
    std::cout << std::endl << "IP Header Information:" << std::endl;
    std::cout << "version_length: " << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(header.version_length) << std::endl;
    std::cout << "tos: " << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(header.tos) << std::endl;
    std::cout << "tot_len: " << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(header.tot_len) << std::endl;
    std::cout << "id: " << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(header.id) << std::endl;
    std::cout << "frag_off: " << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(header.frag_off) << std::endl;
    std::cout << "ttl: " << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(header.ttl) << std::endl;
    std::cout << "protocol: " << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(header.protocol) << std::endl;
    std::cout << "check: " << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(header.check) << std::endl;
    std::cout << "saddr: " << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(header.saddr) << std::endl;
    std::cout << "daddr: " << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(header.daddr) << std::endl;
    std::cout << std::endl;
}