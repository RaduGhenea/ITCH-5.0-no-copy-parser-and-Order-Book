#pragma once
#include <cstdint>
#include <array>

class Parser {
private:
    using ParserFunc = void(Parser::*)(const uint8_t*);

    std::array<ParserFunc, 256> dispatchTable;

    void parseUnknown(const uint8_t* buffer);
    void parseSystemEvent(const uint8_t* buffer);
    void parseAddOrder(const uint8_t* buffer);
public:
    Parser();
    void parse(uint8_t msgType, const uint8_t* buffer);
};