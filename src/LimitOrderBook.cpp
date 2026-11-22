#include "LimitOrderBook.hpp"
#include <iomanip>
#include <iostream>

void LimitOrderBook::addOrder(const Order& order) {
    if(order_addr.contains(order.id)) {
        throw std::runtime_error("Duplicate order ID");
    }
    auto insert = [&](auto& levels) {
        auto& level = levels[order.price];

        level.price = order.price;
        level.orders.push_back(order);

        auto orderIt = std::prev(level.orders.end());
        level.totalQuantity += order.quantity;

        order_addr.emplace(
            order.id,
            OrderLocation{
                order.side,
                order.price,
                orderIt
            }
        );
    };

    if(order.side == Side::SELL) {
        insert(asks);
    }
    else {
        insert(bids);
    }
}

bool LimitOrderBook::cancelOrder(OrderId id) {
    auto it = order_addr.find(id);
    if(it == order_addr.end()) return false;

    const auto& location = it->second;

    auto remove_from = [&](auto& levels) {
        auto& level = levels[location.price];
        level.totalQuantity -= location.orderIt->quantity;
        level.orders.erase(location.orderIt);
        if(level.orders.empty()) {
            levels.erase(level.price);
        }
    };

    if(location.side == Side::SELL) {
        remove_from(asks);
    }
    else {
        remove_from(bids);
    }
    order_addr.erase(id);

    return true;
}

bool LimitOrderBook::modifyOrder(OrderId id, Price newPrice, Quantity newQuantity) {
    if(!order_addr.contains(id)) return false;

    auto& location = order_addr[id];

    if(newQuantity == 0) {
        return cancelOrder(id);
    }

    Order modifiedOrder = *location.orderIt;
    if(newPrice != modifiedOrder.price || newQuantity > modifiedOrder.quantity) {
        cancelOrder(id);

        modifiedOrder.price = newPrice;
        modifiedOrder.quantity = newQuantity;

        addOrder(modifiedOrder);
        return true;
    }

    auto updateLevel = [&](auto& levels) {
        auto& level = levels.at(location.price);
        Order& order = *location.orderIt;

        level.totalQuantity -= order.quantity;
        order.quantity = newQuantity;
        level.totalQuantity += order.quantity;
    };

    if(location.side == Side::SELL) {
        updateLevel(asks);
    }
    else {
        updateLevel(bids);
    }

    return true;
}

void LimitOrderBook::applyFill(OrderId id, Quantity executedQuantity) {
    auto it = order_addr.find(id);
    if(it == order_addr.end()) {
        throw std::runtime_error("Order not found");
    }

    Order& order = *it->second.orderIt;

    modifyOrder(id, order.price, order.quantity - executedQuantity);
}

namespace {
    template<typename Levels>
    void printSide(std::ostream& os, const std::string& title, const Levels& levels) {
        os << '\n' << title << '\n';

        os << std::string(65, '-') << '\n';

        os << std::left
           << std::setw(12) << "PRICE"
           << std::right
           << std::setw(15) << "TOTAL QTY"
           << "      ORDERS\n";

        os << std::string(65, '-') << '\n';
        for(const auto& [price, level] : levels) {
            os << std::right
               << std::setw(5) << price
               << std::setw(22) << level.totalQuantity
               << "      ";
            for(const auto& order : level.orders) {
                os << "[#" << order.id
                   << ": " << order.quantity << "] ";
            }
            os << '\n';
        }
        os << std::string(65, '-') << '\n';
    }
}

Quantity LimitOrderBook::getTotalBidQuantity(Price price) const {
    if(!bids.contains(price)) {
        return 0;
    }
    return bids.at(price).totalQuantity;
}

Quantity LimitOrderBook::getTotalAskQuantity(Price price) const {
    if(!asks.contains(price)) {
        return 0;
    }
    return asks.at(price).totalQuantity;
}

const PriceLevel* LimitOrderBook::getBestBidLevel() const {
    if(bids.empty()) {
        return nullptr;
    }
    return &bids.begin()->second;
}

const Order* LimitOrderBook::getBestBid() const {
    if(bids.empty()) {
        return nullptr;
    }
    const auto& bestLevel = bids.begin()->second;
    return &bestLevel.orders.front();
}

const PriceLevel* LimitOrderBook::getBestAskLevel() const {
    if(asks.empty()) {
        return nullptr;
    }
    return &asks.begin()->second;
}

const Order* LimitOrderBook::getBestAsk() const {
    if(asks.empty()) {
        return nullptr;
    }
    const auto& bestLevel = asks.begin()->second;
    return &bestLevel.orders.front();
}

void LimitOrderBook::print(std::ostream& os) const {
    os << "\n"
       << std::right << std::setw(65/2 + 5) << "ORDER BOOK\n"
       << std::string(65, '=') << '\n';

    printSide(os, "SELL ORDERS", asks);
    printSide(os, "BUY ORDERS", bids);

    os << '\n';
}
