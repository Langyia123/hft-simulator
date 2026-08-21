#include <iostream>
#include "order.hpp"
#include "order_book.hpp"
int main(){
    std::cout << "HFT SIMULATOR" << std::endl;
    OrderBook book;
    Order a(1, Side::BUY, OrderType::LIMIT, 10030, 50, 1);
    Order b(2, Side::SELL, OrderType::LIMIT, 10025, 20, 2);
    Order c(3, Side::SELL, OrderType::LIMIT, 10020, 30, 3);
    book.addOrder(a);
    book.addOrder(b);
    book.addOrder(c);
    Order best = book.getBestBuy();
    Order best2 = book.getBestSell();
    std::cout << "ORDER ID: " << best.order_id << std::endl;
    std::cout << "ORDER ID: " << best2.order_id << std::endl;
    if (best.side == Side::BUY){
        std::cout << "SIDE: BUY" << std::endl;
    }
    else{
        std::cout << "SIDE: SELL" << std::endl;
    }
    if (best.type == OrderType::LIMIT){
        std::cout << "TYPE: LIMIT" << std::endl;
    }
    else{
        std::cout << "TYPE: MARKET" << std::endl;
    }
    std::cout << "PRICE: " << best.price << std::endl;
    std::cout << "QUANTITY: " << best.quantity << std::endl;
    std::cout << "SEQUENCE NUMBER: " << best.sequence_number << std::endl;
    std::cout << best.price << std::endl;

    if (best2.side == Side::BUY){
        std::cout << "SIDE: BUY" << std::endl;
    }
    else{
        std::cout << "SIDE: SELL" << std::endl;
    }
    if (best2.type == OrderType::LIMIT){
        std::cout << "TYPE: LIMIT" << std::endl;
    }
    else{
        std::cout << "TYPE: MARKET" << std::endl;
    }
    std::cout << "PRICE: " << best2.price << std::endl;
    std::cout << "QUANTITY: " << best2.quantity << std::endl;
    std::cout << "SEQUENCE NUMBER: " << best2.sequence_number << std::endl;
    std::cout << best2.price << std::endl;
    book.matchOrders();
    return 0;
}