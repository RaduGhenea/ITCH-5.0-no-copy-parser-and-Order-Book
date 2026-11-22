#include "MatchingStrategy.hpp"
class PriceTimeStrategy : public MatchingStrategy {
public:
    std::vector<Allocation> allocate(
        const Order& incoming,
        const PriceLevel& level
    ) const;
};
