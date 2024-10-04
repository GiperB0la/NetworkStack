#include "../include/Raw_Socket.h"

Raw_Socket::Raw_Socket()
    : info{ 0 }, raw_socket(-1)
{ }

Raw_Socket::~Raw_Socket()
{
    close(raw_socket);
}

void Raw_Socket::start()
{
    init();

    while (true) {
        recv_packet();
    }
}

void Raw_Socket::init()
{
    raw_socket = socket(AF_INET, SOCK_RAW, IPPROTO_UDP);
    if (raw_socket < 0) {
        std::cerr << "[-] Error creating socket: " << strerror(errno) << std::endl;
        return;
    }

    info.sin_family = AF_INET;
    info.sin_port = htons(4444);
    info.sin_addr.s_addr = inet_addr("127.0.0.1");

    if (bind(raw_socket, (struct sockaddr*)&info, sizeof(info)) < 0) {
        std::cerr << "[-] Bind failed: " << strerror(errno) << std::endl;
        return;
    }

    std::cout << "[+] The raw socket is running." << std::endl;
}

void Raw_Socket::recv_packet()
{
    char packet[4096];
    struct sockaddr_in sender_addr;
    socklen_t sender_addr_len = sizeof(sender_addr);

    ssize_t bytesReceived = recvfrom(raw_socket, packet, sizeof(packet), 0, (struct sockaddr*)&sender_addr, &sender_addr_len);
    if (bytesReceived < 0) {
        std::cerr << "[-] Error receiving data: " << strerror(errno) << std::endl;
        return;
    }

    std::cout << "Received packet of size: " << bytesReceived << " bytes" << std::endl;

    std::cout << std::endl << "Packet: " << std::endl;
    for (size_t i = 0; i < static_cast<size_t>(bytesReceived); i++) {
        printf("%02x ", (unsigned char)packet[i]);
        if ((i + 1) % 16 == 0)
            printf("\n");
    }
    std::cout << std::endl;
}