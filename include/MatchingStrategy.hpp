#pragma once
#include "Order.hpp"
#include "PriceLevel.hpp"
#include <vector>

struct Allocation {
    OrderId orderId;
    Quantity quantity;
};

class MatchingStrategy {
public:
    virtual ~MatchingStrategy() = default;

    virtual std::vector<Allocation> allocate(
        const Order& incoming,
        const PriceLevel& level
    ) const = 0;

};