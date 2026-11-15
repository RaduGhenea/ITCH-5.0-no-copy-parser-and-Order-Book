#pragma once

#include "Order.hpp"
#include "PriceLevel.hpp"
#include <map>
#include <unordered_map>

struct ORderLocation {
    Side side;
    Price price;
    OrderList::iterator orderIt;
};

class LimitOrderBook {
private:
    std::map<Price, PriceLevel, std::greater<Price>> bids;
    std::map<Price, PriceLevel, std::less<Price>> asks;

    std::unordered_map<OrderId, ORderLocation> order_addr;

public:
    void addOrder(const Order& order);
    bool cancelOrder(OrderId id);
    bool modifyOrder(OrderId id, Price newPrice, Quantity newQuantity);

    const Order* getBestBid() const;
    const Order* getBestAsk() const;

    void matchOrders();

    Quantity getTotalBidQuantity(Price price) const;
    Quantity getTotalAskQuantity(Price price) const;

};