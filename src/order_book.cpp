#include "order_book.hpp"
#include <algorithm>
#include <iostream>
void OrderBook::addOrder(Side side, OrderType type, std::uint64_t price, std::uint32_t quantity){
    Order a(next_order_id, side, type, price, quantity, next_sequence_number);
    if (a.side == Side::BUY){
        buy_orders.push(a);
    }
    else{
        sell_orders.push(a);
    }
    next_order_id ++;
    next_sequence_number ++;
}
void OrderBook::addExistingOrder(Order a){
    if (a.side == Side::BUY){
        buy_orders.push(a);
    }
    else{
        sell_orders.push(a);
    }
}
Order OrderBook::getBestBuy(){
    return buy_orders.top();
}
Order OrderBook::getBestSell(){
    return sell_orders.top();
}
std::vector<Trade> OrderBook::getTrades(){
    return trades;
}
void OrderBook::matchOrders(){
    while(!buy_orders.empty() && !sell_orders.empty()){ //orders can't happen if both sell and buy orders are empty
        Order buy = getBestBuy();
        Order sell = getBestSell();
        if (buy.price < sell.price){
            return;
        }
        //trade happens here because the buying price is equal to or greater than the selling price
        std::uint32_t trade_quantity = std::min(buy.quantity, sell.quantity); // let us say the buyer wants 50 and the seller only has 25 that means we have 25 left and then we remove the smaller of the two.
        Trade trade{buy.order_id, sell.order_id, sell.price, trade_quantity};
        trades.push_back(trade);
        std::cout << "TRADE: " << trade_quantity << std::endl;
        buy.quantity = buy.quantity - trade_quantity;
        sell.quantity = sell.quantity - trade_quantity;
        buy_orders.pop(); //since the priority queue is protecting its ordering, we can't just modify values
        sell_orders.pop();
        if (buy.quantity > 0){
            addExistingOrder(buy);
        }
        if (sell.quantity > 0){
            addExistingOrder(sell);
        }
    }
}