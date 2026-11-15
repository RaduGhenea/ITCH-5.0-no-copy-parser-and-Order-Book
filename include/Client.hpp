#pragma once
#include <string>

class Client {
private:
    int sock_;

public:
    Client();
    ~Client();

    bool connect_to(const std::string& ip, uint16_t port);
    void disconnect();
    bool is_connected();
    bool read_exact(uint8_t* out, size_t len);
};