#include <iostream>
#include "LimitOrderBook.hpp"

int main() {
    LimitOrderBook ob;
    ob.addOrder({1, Side::SELL, 101, 50, 1});
    ob.addOrder({5, Side::SELL, 102, 20, 3});
    ob.addOrder({2, Side::SELL, 101, 30, 2});
    ob.addOrder({3, Side::SELL, 102, 20, 3});

    ob.addOrder({4, Side::BUY, 102, 20, 3});
    ob.cancelOrder(2);
    ob.modifyOrder(5, 102, 30);
    ob.print(std::cout);
    return 0;
}