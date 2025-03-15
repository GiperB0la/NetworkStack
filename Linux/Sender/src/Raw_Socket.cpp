#include "../include/Raw_Socket.h"


Raw_Socket::Raw_Socket(uint16_t recipient_port, uint32_t recipient_IP, const std::string& data)
    : recipient_port(recipient_port), recipient_IP(recipient_IP), data(data), raw_socket(-1),
    iph(reinterpret_cast<Protocol_IP*>(packet)), udph(reinterpret_cast<Protocol_UDP*>(packet + sizeof(IP_Header)))
{
    init();
}

Raw_Socket::~Raw_Socket()
{
    cleanup();
}

void Raw_Socket::init()
{
    raw_socket = socket(AF_INET, SOCK_RAW, IPPROTO_RAW);
    if (raw_socket < 0) {
        std::cerr << "[-] Error creating socket: " << strerror(errno) << std::endl;
        return;
    }

    int optval = 1;
    if (setsockopt(raw_socket, IPPROTO_IP, IP_HDRINCL, &optval, sizeof(optval)) < 0) {
        std::cerr << "[-] Failed to set IP_HDRINCL: " << strerror(errno) << std::endl;
        return;
    }

    info.sin_family = AF_INET;
    info.sin_port = htons(5555);
    info.sin_addr.s_addr = inet_addr("127.0.0.1");

    if (bind(raw_socket, reinterpret_cast<struct sockaddr*>(&info), sizeof(info)) < 0) {
        std::cerr << "[-] Bind failed: " << strerror(errno) << std::endl;
        return;
    }

    std::cout << "[+] The raw socket is running." << std::endl;
}

void Raw_Socket::cleanup()
{
    if (raw_socket >= 0) {
        close(raw_socket);
    }
}

void Raw_Socket::start()
{
    std::string str;
    while (str != "x") {
        create_packet_udp();
        send_packet();
        std::getline(std::cin, str);
        system("clear");
    }
}

void Raw_Socket::send_packet()
{
    const size_t size = ntohs(iph->header.tot_len);
    std::vector<char> send_packet(size);
    std::memcpy(send_packet.data(), packet, size);

    if (sendto(raw_socket, send_packet.data(), size, 0, reinterpret_cast<struct sockaddr*>(&info), sizeof(info)) < 0) {
        std::cerr << "[-] Send failed: " << strerror(errno) << std::endl;
    }
    else {
        std::cout << "[+] The packet has been sent." << std::endl;
        print_packet();
        print_protocols();
    }
}

void Raw_Socket::create_packet_udp()
{
    std::memset(packet, 0, sizeof(packet));

    iph->create_IPv4_header(info.sin_addr.s_addr, recipient_IP, data);
    udph->create_UDP_header(info.sin_port, recipient_port, data);

    std::memcpy(packet + sizeof(IP_Header) + sizeof(UDP_Header), data.c_str(), data.size());
}

void Raw_Socket::print_packet() const
{
    std::cout << "\nPacket:\n";
    for (size_t i = 0; i < ntohs(iph->header.tot_len); i++) {
        printf("%02x ", static_cast<unsigned char>(packet[i]));
        if ((i + 1) % 16 == 0) {
            printf("\n");
        }
    }
    std::cout << std::endl;
}

void Raw_Socket::print_protocols() const
{
    iph->display_ip_header_info();
    udph->display_udp_header_info();
}