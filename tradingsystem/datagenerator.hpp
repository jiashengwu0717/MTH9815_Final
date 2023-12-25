/**
* datagenerator.hpp
* Generate the Data 
* 
* @author Jiasheng Wu
*/

#ifndef datagenerator_HPP
#define datagenerator_HPP
#include "soa.hpp"
#include "tradebookingservice.hpp"
#include <fstream>
#include <string>
#include <vector>

using namespace std;

// Constants
const int NUM_SECURITIES = 7;
const int NUM_PRICES = 1000;
const int NUM_TRADES = 10;
const int NUM_MARKETDATA = 10000;
const int NUM_INQUIRIES = 10;
const std::vector<std::string> CUSIPS = {
    "91282CJL6", "91282CJP7", "91282CJN2", "91282CJM4", "91282CJJ1", "912810TW8", "912810TV0"
};

// Generate prices.txt
void GeneratePriceData() {
    std::ofstream file("prices.txt");
    for (int i = 0; i < NUM_SECURITIES; ++i) {
        double midprice = 99.0;
        bool direction = true, spread = true;
        for (int j = 0; j < NUM_PRICES; ++j) {
            double bidprice = midprice - (spread ? 1.0 / 256 : 1.0 / 128);
            double offerprice = midprice + (spread ? 1.0 / 256 : 1.0 / 128);
            spread = !spread;

            file << CUSIPS[i] << "," << ConvertPrice(bidprice) << "," << ConvertPrice(offerprice) << endl;

            midprice += direction ? 1.0 / 256 : -1.0 / 256;
            if (std::abs(midprice - 99.0) < 1e-6 || std::abs(midprice - 101.0) < 1e-6) {
                direction = !direction;
            }
        }
    }
}

// Generate trades.txt
void GenerateTradeData() {
    std::ofstream file("trades.txt");
    int tradeCount = 0;
    for (int i = 0; i < NUM_SECURITIES; ++i) {
        for (int j = 0; j < NUM_TRADES; ++j) {
            std::string tradeId = GenerateId();
            std::string side = tradeCount % 2 ? "BUY" : "SELL";
            std::string price = ConvertPrice(tradeCount % 2 ? 99.0 : 100.0);
            std::string book = "TRSY" + std::to_string(tradeCount % 3 + 1);
            long quantity = ((tradeCount % 5) + 1) * 1000000;

            file << CUSIPS[i] << "," << tradeId << "," << price << "," << book << "," << quantity << "," << side << endl;
            ++tradeCount;
        }
    }
}

// Generate marketdata.txt
void GenerateMarketData() {
    std::ofstream file("marketdata.txt");
    long count = 0;
    for (int i = 0; i < NUM_SECURITIES; ++i) {
        double midprice = 99.0;
        bool direction = true, spread = true;
        for (int j = 0; j < NUM_MARKETDATA; ++j) {
            long quantity = 1000000 * ((count % 5) + 1);
            double bidprice = midprice - (spread ? 1.0 / 256 : 1.0 / 128);
            double offerprice = midprice + (spread ? 1.0 / 256 : 1.0 / 128);
            spread = !spread;

            file << CUSIPS[i] << "," << ConvertPrice(bidprice) << "," << quantity << ",BID" << endl;
            file << CUSIPS[i] << "," << ConvertPrice(offerprice) << "," << quantity << ",OFFER" << endl;

            midprice += direction ? 1.0 / 256 : -1.0 / 256;
            if (std::abs(midprice - 99.0) < 1e-6 || std::abs(midprice - 101.0) < 1e-6) {
                direction = !direction;
            }
            ++count;
        }
    }
}

// Generate inquiries.txt
void GenerateInquiries() {
    std::ofstream file("inquiries.txt");
    int tradeCount = 0;
    for (int i = 0; i < NUM_SECURITIES; ++i) {
        for (int j = 0; j < NUM_INQUIRIES; ++j) {
            std::string tradeId = GenerateId();
            std::string side = tradeCount % 2 ? "BUY" : "SELL";
            std::string price = ConvertPrice(tradeCount % 2 ? 99.0 : 100.0);
            long quantity = ((tradeCount % 5) + 1) * 1000000;

            file << tradeId << "," << CUSIPS[i] << "," << side << "," << quantity << "," << price << ",RECEIVED" << endl;
            ++tradeCount;
        }
    }
}

#endif