#include <cstdint>
struct Trade{
    int buy_order_id;
    int sell_order_id;
    uint64_t price;
    uint32_t trade_quantity;
};