#include <iostream>
#include "order.hpp"
#include "order_book.hpp"
int main(){
    std::cout << "HFT SIMULATOR" << std::endl;
    OrderBook book;
    book.addOrder(Side::BUY, OrderType::LIMIT, 10030, 20);
    book.addOrder(Side::SELL, OrderType::LIMIT, 10020, 20);
    //book.addOrder(Side::SELL, OrderType::LIMIT, 10025, 30);
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
    //book.cancelOrder(1);
    book.matchOrders();
    book.printActiveOrders();
    std::vector<Trade> trades = book.getTrades();
    for (int i = 0; i < trades.size(); i++){
        std::cout << trades[i].buy_order_id << std::endl;
        std::cout << trades[i].sell_order_id << std::endl;
        std::cout << trades[i].price << std::endl;
        std::cout << trades[i].trade_quantity << std::endl;
    }
    return 0;
}