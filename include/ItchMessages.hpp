#pragma once
#include <cstdint>

#pragma pack(push, 1)
struct SystemEventMessage {
    uint8_t messageType;
    uint8_t stockLocate;
    uint8_t trackingNumber;
    uint8_t timestamp[6];
    uint8_t eventCode;
};
struct AddOrderMessage {
    uint8_t messageType;
    uint8_t stockLocate[2];
    uint8_t trackingNumber[2];
    uint8_t timestamp[6];
    uint8_t orderReferenceNumber[8];
    uint8_t indicator;
    uint8_t shares[4];
    uint8_t stock[8];
    uint8_t price[4];
};
#pragma pack(pop)
