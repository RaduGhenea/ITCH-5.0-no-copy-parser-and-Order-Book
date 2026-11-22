#include "PriceTimeStrategy.hpp"

std::vector<Allocation> PriceTimeStrategy::allocate(
    const Order& incoming,
    const PriceLevel& level
) const {
    std::vector<Allocation> res;

    Quantity remaining = incoming.quantity;

    for(const auto& order : level.orders) {
        if(remaining == 0) {
            break;
        }

        Quantity executed = std::min(remaining, order.quantity);

        res.push_back(Allocation{
            .orderId = order.id,
            .quantity = executed
        });
        remaining -= executed;
    }

    return res;
}
