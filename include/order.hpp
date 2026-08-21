#pragma once
#include <cstdint>
enum class Side{
    BUY,
    SELL
};
enum class OrderType{
    LIMIT,
    MARKET
};
struct Order{
    int order_id;
    Side side;
    OrderType type;
    std::uint64_t price;
    std::uint32_t quantity;
    std::uint64_t sequence_number;
    Order(
        int order_id,
        Side side,
        OrderType type,
        std::uint64_t price,
        std::uint32_t quantity,
        std::uint64_t sequence_number
    );
};