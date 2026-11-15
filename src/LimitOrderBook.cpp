#include "LimitOrderBook.hpp"

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
            ORderLocation{
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
    if(!order_addr.contains(id)) return false;

    const auto& location = order_addr[id];

    auto remove_from = [&](auto& levels) {
        auto& level = levels[location.price];
        level.totalQuantity -= location.price;
        level.orders.erase(location.orderIt);
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