#include "../include/Protocol_UDP.h"


struct pseudo_header {
    uint32_t source_address;
    uint32_t dest_address;
    uint8_t zero;
    uint8_t protocol;
    uint16_t udp_length;
};

uint16_t Protocol_UDP::calculate_checksum(const std::string& data, uint32_t sender_ip, uint32_t recipient_ip)
{
    unsigned short sum = 0;
    int len = sizeof(pseudo_header) + sizeof(UDP_Header) + data.size();

    pseudo_header psh;
    psh.source_address = sender_ip;
    psh.dest_address = recipient_ip;
    psh.udp_length = htons(sizeof(UDP_Header) + data.size());

    auto add_to_sum = [&sum](const void* buffer, int length) {
        const unsigned short* buf = static_cast<const unsigned short*>(buffer);
        for (int i = 0; i < length / 2; ++i) {
            sum += buf[i];
        }
        if (length % 2) {
            sum += *(static_cast<const unsigned char*>(buffer) + length - 1);
        }
        };

    add_to_sum(&psh, sizeof(psh));
    add_to_sum(&header, sizeof(header));
    add_to_sum(data.c_str(), data.size());

    sum = (sum & 0xFFFF) + (sum >> 16);
    return ~sum;
}

void Protocol_UDP::create_UDP_header(uint16_t sender_port, uint16_t recipient_port, const std::string& data)
{
    header.source = sender_port;
    header.dest = htons(recipient_port);
    header.len = htons(sizeof(UDP_Header) + data.size());
    header.check = 0;
    // header.check = calculate_checksum(data, inet_addr("127.0.0.1"), inet_addr("127.0.0.1"));
}

void Protocol_UDP::display_udp_header_info() const
{
    std::cout << std::endl << "UDP Header Information:" << std::endl;
    std::cout << "source: " << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(header.source) << std::endl;
    std::cout << "dest: " << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(header.dest) << std::endl;
    std::cout << "len: " << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(header.len) << std::endl;
    std::cout << "check: " << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(header.check) << std::endl;
    std::cout << std::endl;
}