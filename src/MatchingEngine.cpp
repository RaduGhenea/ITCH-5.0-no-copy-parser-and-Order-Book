#include "MatchingEngine.hpp"
#include <memory>

MatchingEngine::MatchingEngine(
    LimitOrderBook& book,
    std::unique_ptr<MatchingStrategy> strategy
) : orderBook(book), strategy_(std::move(strategy)) {}

void MatchingEngine::processOrder(Order incoming) {
    while(incoming.quantity > 0) {
        const PriceLevel* bestLevel =
        (incoming.side == Side::SELL)?
        orderBook.getBestBidLevel() : orderBook.getBestAskLevel();

        if(bestLevel == nullptr) {
            break;
        }

        if(!canMatch(incoming, *bestLevel)) {
            break;
        }

        auto allocations = strategy_->allocate(incoming, *bestLevel);
        Quantity executedQuantity = 0;
        for (const auto& allocation : allocations) {
            orderBook.applyFill(allocation.orderId, allocation.quantity);
            executedQuantity += allocation.quantity;
        }
        incoming.quantity -= executedQuantity;

        if(executedQuantity == 0) {
            break;
        }
    }
    if(incoming.quantity > 0) {
        orderBook.addOrder(incoming);
    }
}

bool MatchingEngine::canMatch(const Order& incoming, const PriceLevel& opposite) {
    if(incoming.side == Side::BUY) {
        return incoming.price >= opposite.price;
    }
    return incoming.price <= opposite.price;
}