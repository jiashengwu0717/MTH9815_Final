# MTH9815_Final
Final Project for MTH 9815: Software Engineering for Finance

## Overview

This project develops a bond trading system for managing and trading U.S. Treasury securities, specifically targeting 2Y, 3Y, 5Y, 7Y, 10Y, 20Y, and 30Y maturities. The system includes a variety of services for trading operations, risk management, and market data handling, ensuring a robust platform for bond trading activities.



## Data

**Bond data source**: https://treasurydirect.gov/TA_WS/securities/auctioned



## File Descriptions

### `main.cpp`

- **Purpose**: Serves as the entry point for the trading system.
- **Functionality**: Initializes and links various services, subscribes to data sources, and orchestrates the overall process flow.

### `soa.hpp`

- **Purpose**: Defines the Service-Oriented Architecture (SOA) framework used in the trading system.
- **Functionality**: Includes definitions for the Service, ServiceListener, and Connector classes.

### `products.hpp`

- **Purpose**: Contains definitions related to trading products, specifically bonds.
- **Functionality**: Defines the Bond class and other related product attributes.

### `funcs.hpp`

- **Purpose**: Provides utility functions and random number generators for the system.
- **Functionality**: Includes functions for date conversion, random number generation, bond details retrieval (CUSIP, coupon rate, maturity), price conversion between fractional and numerical formats, and timestamp generation.

### `datagenerator.hpp`

- **Purpose**: Responsible for generating mock data for the trading system.
- **Functionality**: Includes functions to generate price, trade, market, and inquiry data.

### `Service Implementation Files`

- `algoexecutionservice.hpp`: Manages the algorithmic execution logic for trading orders.
- `algostreamingservice.hpp`: Handles streaming of algorithmic trading information.
- `executionservice.hpp`: Executes trades based on instructions from the algo execution service.
- `guiservice.hpp`: Manages the GUI components, displaying streaming prices with specified throttles.
- `historicaldataservice.hpp`: Stores historical data for different types of financial information.
- `inquiryservice.hpp`: Processes and responds to inquiries related to bond trading.
- `marketdataservice.hpp`: Provides market data updates, including order book details.
- `positionservice.hpp`: Tracks and manages positions in different securities.
- `pricingservice.hpp`: Offers pricing information for various securities.
- `riskservice.hpp`: Assesses and manages the risk associated with bond positions.
- `streamingservice.hpp`: Streams price quotes for bonds.
- `tradebookingservice.hpp`: Manages the booking of trade orders.

### `Data Files`

- **Files**: `prices.txt`, `trades.txt`, `marketdata.txt`, `inquiries.txt`.
- **Purpose**: Provide input data for the trading system.
- **Functionality**: These text files are genrated bt datagenerator.hpp. They are read by the respective services to simulate real-world trading data.



## Contributing

**Author**: Jiasheng Wu

**Contact**: jiasheng.wu.BaruchMFE@gmail.com

