#pragma once
#include "LimitOrderBook.hpp"
#include "MatchingStrategy.hpp"

class MatchingEngine {
public:
    explicit MatchingEngine(
        LimitOrderBook& book,
        std::unique_ptr<MatchingStrategy> strategy
    );

    void processOrder(Order incoming);

    bool canMatch(const Order& incoming, const PriceLevel& opposite);

private:
    LimitOrderBook& orderBook;
    std::unique_ptr<MatchingStrategy> strategy_;
};