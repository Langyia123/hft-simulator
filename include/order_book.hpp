#pragma once
#include "order.hpp"
#include "trade.hpp"
#include <queue>
#include <vector>
#include <cstdint>
#include <unordered_map>
struct BuyComparator{
    bool operator()(Order a, Order b){
        if (a.price < b.price){
            return true; // means that a has a lower priority than b cause it's less than b
        }
        else if (a.price > b.price){
            return false;
        }
        else{
            if (a.sequence_number < b.sequence_number){
                return false;
            }
            else{
                return true;
            }
        }
    }
};
struct SellComparator{
    bool operator()(Order a, Order b){
        if (a.price > b.price){
            return true;
        }
        else if (a.price < b.price){
            return false;
        }
        else{
            if (a.sequence_number < b.sequence_number){
                return false;
            }
            else{
                return true;
            }
        }
    }
};
class OrderBook{
    private:
    std::priority_queue<Order, std::vector<Order>, BuyComparator>buy_orders;
    std::priority_queue<Order, std::vector<Order>, SellComparator>sell_orders;
    std::vector<Trade> trades;
    std::uint64_t next_order_id = 1;
    std::uint64_t next_sequence_number = 1;
    void addExistingOrder(Order a); //this is because we do not want to generate new ids and sequence numbers for already existing orders in an order book.
    std::unordered_map<int, Order> active_orders;
    public:
    void addOrder(Side side, OrderType type, std::uint64_t price, std::uint32_t quantity);
    Order getBestBuy();
    Order getBestSell();
    void matchOrders();
    std::vector<Trade> getTrades(); // we are returning multiple trades
    void cancelOrder(int order_id);
    void printActiveOrders() const; //kinda like a debug to see if active orders has been updated
};