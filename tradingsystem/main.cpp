/**
* main.cpp
* The main program of the trading system
*
* @author Jiasheng
*/

#include <iostream>
#include <string>
#include <map>

#include "soa.hpp"
#include "products.hpp"
#include "algoexecutionservice.hpp"
#include "algostreamingservice.hpp"
#include "executionservice.hpp"
#include "guiservice.hpp"
#include "historicaldataservice.hpp"
#include "inquiryservice.hpp"
#include "marketdataservice.hpp"
#include "positionservice.hpp"
#include "pricingservice.hpp"
#include "riskservice.hpp"
#include "streamingservice.hpp"
#include "tradebookingservice.hpp"
#include "datagenerator.hpp"

using namespace std;


int main() {
	cout << "---------------------- Program Start ----------------------" << endl;

	std::cout << TimeStamp() << "Data generating..." << endl;
	GeneratePriceData();
	GenerateTradeData();
	GenerateMarketData();
	GenerateInquiries();
	std::cout << TimeStamp() << "Data generated successfully." << endl;

	cout << TimeStamp() << "Services initializing..." << endl;
	PricingService<Bond> pricingService;
	TradeBookingService<Bond> tradeBookingService;
	PositionService<Bond> positionService;
	RiskService<Bond> riskService;
	MarketDataService<Bond> marketDataService;
	AlgoExecutionService<Bond> algoExecutionService;
	AlgoStreamingService<Bond> algoStreamingService;
	GUIService<Bond> guiService;
	ExecutionService<Bond> executionService;
	StreamingService<Bond> streamingService;
	InquiryService<Bond> inquiryService;
	HistoricalDataService<Position<Bond>> historicalPositionService(POSITION);
	HistoricalDataService<PV01<Bond>> historicalRiskService(RISK);
	HistoricalDataService<ExecutionOrder<Bond>> historicalExecutionService(EXECUTION);
	HistoricalDataService<PriceStream<Bond>> historicalStreamingService(STREAMING);
	HistoricalDataService<Inquiry<Bond>> historicalInquiryService(INQUIRY);
	cout << TimeStamp() << "Services initialized successfully." << endl;

	cout << TimeStamp() << "Services linking..." << endl;
	pricingService.AddListener(algoStreamingService.GetListener());
	pricingService.AddListener(guiService.GetListener());
	algoStreamingService.AddListener(streamingService.GetListener());
	streamingService.AddListener(historicalStreamingService.GetListener());
	marketDataService.AddListener(algoExecutionService.GetListener());
	algoExecutionService.AddListener(executionService.GetListener());
	executionService.AddListener(tradeBookingService.GetListener());
	executionService.AddListener(historicalExecutionService.GetListener());
	tradeBookingService.AddListener(positionService.GetListener());
	positionService.AddListener(riskService.GetListener());
	positionService.AddListener(historicalPositionService.GetListener());
	riskService.AddListener(historicalRiskService.GetListener());
	inquiryService.AddListener(historicalInquiryService.GetListener());
	cout << TimeStamp() << "Services linked successfully." << endl;

	cout << TimeStamp() << "Price data processing..." << endl;
	ifstream priceData("prices.txt");
	pricingService.GetConnector()->Subscribe(priceData);
	cout << TimeStamp() << "Price data processed successfully." << endl;

	cout << TimeStamp() << "Trade data processing..." << endl;
	ifstream tradeData("trades.txt");
	tradeBookingService.GetConnector()->Subscribe(tradeData);
	cout << TimeStamp() << "Trade data processed successfully." << endl;

	cout << TimeStamp() << "Market data processing..." << endl;
	ifstream marketData("marketdata.txt");
	marketDataService.GetConnector()->Subscribe(marketData);
	cout << TimeStamp() << "Market data processed successfully." << endl;

	cout << TimeStamp() << "Inquiry data processing..." << endl;
	ifstream inquiryData("inquiries.txt");
	inquiryService.GetConnector()->Subscribe(inquiryData);
	cout << TimeStamp() << "Inquiry data processed successfully." << endl;

	cout << "---------------------- Program End ----------------------" << endl;

	return 0;

}