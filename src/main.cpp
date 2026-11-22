#include <iostream>
#include "LimitOrderBook.hpp"
#include "MatchingEngine.hpp"
#include "PriceTimeStrategy.hpp"

int main() {
    LimitOrderBook ob;
    ob.addOrder({1, Side::SELL, 101, 50, 1});
    ob.addOrder({2, Side::SELL, 101, 30, 2});
    ob.addOrder({3, Side::SELL, 102, 20, 3});
    ob.addOrder({5, Side::SELL, 102, 20, 3});

    ob.print(std::cout);

    MatchingEngine engine = MatchingEngine(ob, std::make_unique<PriceTimeStrategy>());
    engine.processOrder({4, Side::BUY, 101, 105, 4});

    ob.print(std::cout);

    std::cout<<ob.getTotalAskQuantity(101) << '\n' << ob.getTotalBidQuantity(102) << '\n';

    const Order* bestAsk = ob.getBestAsk();
    if(bestAsk) {
        std::cout<<bestAsk->id<<'\n';
    }
    else {
        std::cout<<"No ask found\n";
    }
    const Order* bestBid = ob.getBestBid();
    if(bestBid) {
        std::cout<<bestBid->id<<'\n';
    }
    else {
        std::cout<<"No bid found\n";
    }

    return 0;
}