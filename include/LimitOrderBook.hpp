#pragma once

#include "Order.hpp"
#include "PriceLevel.hpp"
#include <map>
#include <unordered_map>
#include <ostream>

struct OrderLocation {
    Side side;
    Price price;
    OrderList::iterator orderIt;
};

class LimitOrderBook {
private:
    std::map<Price, PriceLevel, std::greater<Price>> bids;
    std::map<Price, PriceLevel, std::less<Price>> asks;

    std::unordered_map<OrderId, OrderLocation> order_addr;

public:
    void print(std::ostream& os) const;

    void addOrder(const Order& order);
    bool cancelOrder(OrderId id);
    bool modifyOrder(OrderId id, Price newPrice, Quantity newQuantity);

    const Order* getBestBid() const;
    const Order* getBestAsk() const;
    const PriceLevel* getBestBidLevel() const;
    const PriceLevel* getBestAskLevel() const;

    void applyFill(OrderId id, Quantity executedQuantity);

    Quantity getTotalBidQuantity(Price price) const;
    Quantity getTotalAskQuantity(Price price) const;

};