#pragma once

#include "Order.hpp"
#include <list>

using OrderList = std::list<Order>;

class PriceLevel {
public:
    Price price;
    Quantity totalQuantity;
    OrderList orders;
};