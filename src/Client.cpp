#include "Client.hpp"
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

Client::Client() : sock_(-1) {}
Client::~Client() { disconnect(); }

bool Client::connect_to(const std::string& ip, uint16_t port) {
    sock_ = socket(AF_INET, SOCK_STREAM, 0);

    sockaddr_in clientAddress;
    clientAddress.sin_family = AF_INET;
    clientAddress.sin_port = htons(port);
    inet_pton(AF_INET ,ip.c_str(), &clientAddress.sin_addr.s_addr);

    if(connect(sock_, (sockaddr*)&clientAddress, sizeof(clientAddress)) < 0) return 0;

    return 1;
}

void Client::disconnect() { if(sock_ > 0) close(sock_); }
bool Client::is_connected() { return sock_ > 0; }

bool Client::read_exact(uint8_t* out, size_t len) {
    size_t got = 0;
    while(got < len) {
        ssize_t n = recv(sock_, out+got, len-got, 0);
        if (n < 0) return false;
        got += n;
    }
    return true;
}