cmake_minimum_required(VERSION 3.10)
project(tradingsystem)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Include directories
include_directories(${PROJECT_SOURCE_DIR})

# Add executable
add_executable(tradingsystem
		main.cpp
		soa.hpp
		products.hpp
		funcs.hpp
		datagenerator.hpp
        executionservice.hpp
        historicaldataservice.hpp
        inquiryservice.hpp
        marketdataservice.hpp
        positionservice.hpp
        pricingservice.hpp
        riskservice.hpp
        streamingservice.hpp
        tradebookingservice.hpp
        algostreamingservice.hpp
        algostreamingservice.hpp
        guiservice.hpp)
