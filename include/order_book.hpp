#pragma once
#include "order.hpp"
#include "trade.hpp"
#include <queue>
#include <vector>
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
    public:
    void addOrder(Order a);
    Order getBestBuy();
    Order getBestSell();
    void matchOrders();
    std::vector<Trade> getTrades(); // we are returning multiple trades
};