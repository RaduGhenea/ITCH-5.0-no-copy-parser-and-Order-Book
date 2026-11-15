#pragma once
#include "Parser.hpp"
#include <algorithm>

Parser::Parser() {
    std::fill(dispatchTable.begin(), dispatchTable.end(), &Parser::parseUnknown);
}

void Parser::parseUnknown(const uint8_t* buffer) {

}

void Parser::parseSystemEvent(const uint8_t* buffer) {

}

void Parser::parseAddOrder(const uint8_t* buffer) {

}

void Parser::parse(uint8_t msgType, const uint8_t* buffer) {

}