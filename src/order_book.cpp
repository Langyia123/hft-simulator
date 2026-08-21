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
    active_orders.emplace(a.order_id, a); //store the index of the order as the key and the order as the value. If it doesn't exist, assign the index to the order instead of creating a new order
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
void OrderBook::cancelOrder(int order_id){
    auto it = active_orders.find(order_id); //.find() points to the location of where the thing is and not an actual value
    if (it != active_orders.end()){ // .end() means that we have reached the value after the end
        active_orders.erase(it); //remove it from the hashmap
    }
}
void OrderBook::printActiveOrders() const { //not going to modify the order book
    for (const auto& [order_id, order] : active_orders) {
        std::cout << "ACTIVE ORDER ID: " << order_id << std::endl;
        std::cout << "SIDE: "
                  << (order.side == Side::BUY ? "BUY" : "SELL")
                  << std::endl;
        std::cout << "PRICE: " << order.price << std::endl;
        std::cout << "QUANTITY: " << order.quantity << std::endl;
        std::cout << "SEQUENCE: " << order.sequence_number << std::endl;
    }
}
void OrderBook::matchOrders(){
    while(!buy_orders.empty() && !sell_orders.empty()){ //orders can't happen if both sell and buy orders are empty
        Order buy = getBestBuy();
        Order sell = getBestSell();
        if (active_orders.find(buy.order_id) == active_orders.end()){
            buy_orders.pop();
            continue;
        }
        if (active_orders.find(sell.order_id) == active_orders.end()){
            sell_orders.pop();
            continue;
        }
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
            active_orders.insert_or_assign(buy.order_id, buy); //they already exist so we are just updating so we use .insert_or_assign
        }
        else{
            active_orders.erase(buy.order_id);
        }
        if (sell.quantity > 0){
            addExistingOrder(sell);
            active_orders.insert_or_assign(sell.order_id, sell);
        }
        else{
            active_orders.erase(sell.order_id);
        }
    }
}