/**
* funcs.hpp
* Defines several utility functions and random number generators
*
* @author Jiasheng Wu
*/

#ifndef FUNCS_HPP
#define FUNCS_HPP

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <random>
#include <chrono>
#include "products.hpp"

using namespace std;
using namespace chrono;

year_month_day from_string(const std::string& date_str) {
    std::istringstream iss(date_str);
    int year, month, day;
    char delim1, delim2;

    if (!(iss >> year >> delim1 >> month >> delim2 >> day) || delim1 != '/' || delim2 != '/') {
        // Handle error, possibly throw an exception or return a default date
    }
    return std::chrono::year{year}/month/day;
}

// Generate uniformly distributed random variables ~ U[0, 1]
vector<double> GenerateUniform(long count, unsigned long seed = 0) {
    if (seed == 0) {
        seed = static_cast<unsigned long>(steady_clock::now().time_since_epoch().count());
    }

    mt19937_64 rng(seed);
    uniform_real_distribution<double> dist(0.0, 1.0);

    vector<double> result;
    result.reserve(count);
    for (long i = 0; i < count; ++i) {
        result.push_back(dist(rng));
    }

    return result;
}


// Get Bond object for US Treasury 2Y, 3Y, 5Y, 7Y, 10Y, 20Y and 30Y.
Bond GetBond(string _cusip) {
	Bond _bond;
	if (_cusip == "91282CJL6") _bond = Bond("91282CJL6", CUSIP, "US2Y", 0.04875, from_string("2025/11/30"));
	if (_cusip == "91282CJP7") _bond = Bond("91282CJP7", CUSIP, "US3Y", 0.04375, from_string("2026/12/15"));
	if (_cusip == "91282CJN2") _bond = Bond("91282CJN2", CUSIP, "US5Y", 0.04375, from_string("2028/11/30"));
	if (_cusip == "91282CJM4") _bond = Bond("91282CJM4", CUSIP, "US7Y", 0.04375, from_string("2030/11/30"));
	if (_cusip == "91282CJJ1") _bond = Bond("91282CJJ1", CUSIP, "US10Y", 0.04500, from_string("2033/11/15"));
	if (_cusip == "912810TW8") _bond = Bond("912810TW8", CUSIP, "US20Y", 0.04750, from_string("2043/11/15"));
	if (_cusip == "912810TV0") _bond = Bond("912810TV0", CUSIP, "US30Y", 0.04750, from_string("2053/11/15"));
	return _bond;
}


// Get PV01 value for US Treasury 2Y, 3Y, 5Y, 7Y, 10Y, 20Y and 30Y.
double GetPV01Value(string _cusip)
{
	double _pv01 = 0;
	if (_cusip == "91282CJL6") 
		_pv01 = 0.02;
	if (_cusip == "91282CJP7") 
		_pv01 = 0.03;
	if (_cusip == "91282CJN2") 
		_pv01 = 0.05;
	if (_cusip == "91282CJM4") 
		_pv01 = 0.07;
	if (_cusip == "91282CJJ1") 
		_pv01 = 0.1;
	if (_cusip == "912810TW8") 
		_pv01 = 0.2;
	if (_cusip == "912810TV0") 
		_pv01 = 0.3;
	return _pv01;
}


// Convert fractional price to numerical price.
double ConvertPrice(const std::string& stringPrice) {
    std::string stringPrice100, stringPrice32, stringPrice8;
    int section = 0;

    for (char ch : stringPrice) {
        if (ch == '-') {
            section++;
            continue;
        }

        if (section == 0) {
            stringPrice100.push_back(ch);
        } else if (section == 1 || section == 2) {
            stringPrice32.push_back(ch);
            section++;
        } else if (section == 3) {
            stringPrice8.push_back(ch == '+' ? '4' : ch);
        }
    }

    double doublePrice100 = std::stod(stringPrice100);
    double doublePrice32 = stringPrice32.empty() ? 0.0 : std::stod(stringPrice32);
    double doublePrice8 = stringPrice8.empty() ? 0.0 : std::stod(stringPrice8);

    return doublePrice100 + doublePrice32 / 32.0 + doublePrice8 / 256.0;
}


// Convert numerical price to fractional price.
std::string ConvertPrice(double doublePrice) {
    int wholePart = floor(doublePrice);
    int fractionalPart256 = floor((doublePrice - wholePart) * 256.0);
    int fractionalPart32 = floor(fractionalPart256 / 8.0);
    int fractionalPart8 = fractionalPart256 % 8;

    std::string wholePartStr = to_string(wholePart);
    std::string fractionalPart32Str = (fractionalPart32 < 10) ? "0" + to_string(fractionalPart32) : to_string(fractionalPart32);
    std::string fractionalPart8Str = (fractionalPart8 == 4) ? "+" : to_string(fractionalPart8);

    return wholePartStr + "-" + fractionalPart32Str + fractionalPart8Str;
}


// Output Time Stamp with millisecond precision.
string TimeStamp()
{
	auto _timePoint = system_clock::now();
	auto _sec = chrono::time_point_cast<chrono::seconds>(_timePoint);
	auto _millisec = chrono::duration_cast<chrono::milliseconds>(_timePoint - _sec);

	auto _millisecCount = _millisec.count();
	string _milliString = to_string(_millisecCount);
	if (_millisecCount < 10) _milliString = "00" + _milliString;
	else if (_millisecCount < 100) _milliString = "0" + _milliString;

	time_t _timeT = system_clock::to_time_t(_timePoint);
	char _timeChar[24];
	strftime(_timeChar, 24, "%F %T", localtime(&_timeT));
	string _timeString = string(_timeChar) + "." + _milliString + " ";

	return _timeString;
}


// Get the millisecond count of current time.
long GetMillisecond()
{
	auto _timePoint = system_clock::now();
	auto _sec = chrono::time_point_cast<chrono::seconds>(_timePoint);
	auto _millisec = chrono::duration_cast<chrono::milliseconds>(_timePoint - _sec);
	long _millisecCount = _millisec.count();
	return _millisecCount;
}


#endif