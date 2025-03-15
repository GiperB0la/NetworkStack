#include "../include/Raw_Socket.h"


Raw_Socket::Raw_Socket()
    : wsa{ 0 }, info{ 0 }, raw_socket(INVALID_SOCKET)
{
    int wsaStartupResult = WSAStartup(MAKEWORD(2, 2), &wsa);
    if (wsaStartupResult != 0) {
        std::cerr << std::endl << "[-] WSAStartup failed: " << wsaStartupResult << std::endl;
        exit(1);
    }
}

Raw_Socket::~Raw_Socket()
{
    closesocket(raw_socket);
    WSACleanup();
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
    if (raw_socket == INVALID_SOCKET) {
        std::cerr << std::endl << "[-] Error creating socket: " << WSAGetLastError() << std::endl;
        return;
    }

    info.sin_family = AF_INET;
    info.sin_port = htons(4444);
    info.sin_addr.s_addr = inet_addr("127.0.0.1");

    if (bind(raw_socket, (struct sockaddr*)&info, sizeof(info)) < 0) {
        std::cerr << "Bind failed" << std::endl;
        return;
    }

    std::cout << "[+] The raw socket is running." << std::endl;
    std::cout << "127.0.0.1" << ":" << std::dec << htons(info.sin_port) << std::endl;
}

void Raw_Socket::recv_packet()
{
    char packet[4096];
    struct sockaddr_in sender_addr;
    int sender_addr_len = sizeof(sender_addr);

    int bytesReceived = recvfrom(raw_socket, packet, sizeof(packet), 0, (struct sockaddr*)&sender_addr, &sender_addr_len);
    if (bytesReceived < 0) {
        int error_code = WSAGetLastError();
        std::cerr << "Error receiving data: " << error_code << std::endl;
        return;
    }

    std::cout << "Received packet of size: " << bytesReceived << " bytes" << std::endl;

    std::cout << std::endl << "Packet: " << std::endl;
    for (size_t i = 0; i < bytesReceived; i++) {
        printf("%02x ", (unsigned char)packet[i]);
        if ((i + 1) % 16 == 0)
            printf("\n");
    }
    std::cout << std::endl;
}