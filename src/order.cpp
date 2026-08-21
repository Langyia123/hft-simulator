#include "order.hpp"
Order::Order(
    int order_id,
    Side side,
    OrderType type,
    std::uint64_t price,
    std::uint32_t quantity,
    std::uint64_t sequence_number
): order_id(order_id), side(side), type(type), price(price), quantity(quantity), sequence_number(sequence_number)//member -> parameter
{

}