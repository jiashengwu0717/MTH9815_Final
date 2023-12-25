/**
* historicaldataservice.hpp
* Defines the data types and Service for historical data.
*
* @author Breman Thuraisingham
* @coauthor Jiasheng Wu
*/

#ifndef HISTORICAL_DATA_SERVICE_HPP
#define HISTORICAL_DATA_SERVICE_HPP

#include "soa.hpp"

enum ServiceType { POSITION, RISK, EXECUTION, STREAMING, INQUIRY };


// Pre-declearations
template<typename T>
class HistoricalDataConnector;
template<typename T>
class HistoricalDataListener;

/**
* Service for processing and persisting historical data to a persistent store.
* Keyed on some persistent key.
* Type V is the data type to persist.
*/
template<typename T>
class HistoricalDataService : Service<string, T>
{

private:

	map<string, T> historicalDatas;
	vector<ServiceListener<T>*> listeners;	
	HistoricalDataConnector<T>* connector;
	ServiceListener<T>* listener;
	ServiceType type;

public:

	// Constructor and destructor
	HistoricalDataService();
	HistoricalDataService(ServiceType _type);
	~HistoricalDataService();

	// Get data on our service given a key
	T& GetData(string _key);

	// The callback that a Connector should invoke for any new or updated data
	void OnMessage(T& _data);

	// Add a listener to the Service for callbacks on add, remove, and update events for data to the Service
	void AddListener(ServiceListener<T>* _listener);

	// Get all listeners on the Service
	const vector<ServiceListener<T>*>& GetListeners() const;

	// Get the connector of the service
	HistoricalDataConnector<T>* GetConnector();

	// Get the listener of the service
	ServiceListener<T>* GetListener();

	// Get the service type that historical data comes from
	ServiceType GetServiceType() const;

	// Persist data to a store
	void PersistData(string persistKey, T& data);

};

template<typename T>
HistoricalDataService<T>::HistoricalDataService()
{
	historicalDatas = map<string, T>();
	listeners = vector<ServiceListener<T>*>();
	connector = new HistoricalDataConnector<T>(this);
	listener = new HistoricalDataListener<T>(this);
	type = INQUIRY;
}

template<typename T>
HistoricalDataService<T>::HistoricalDataService(ServiceType _type)
{
	historicalDatas = map<string, T>();
	listeners = vector<ServiceListener<T>*>();
	connector = new HistoricalDataConnector<T>(this);
	listener = new HistoricalDataListener<T>(this);
	type = _type;
}

template<typename T>
HistoricalDataService<T>::~HistoricalDataService() {}

template<typename T>
T& HistoricalDataService<T>::GetData(string _key)
{
	return historicalDatas[_key];
}

template<typename T>
void HistoricalDataService<T>::OnMessage(T& _data)
{
	historicalDatas[_data.GetProduct().GetProductId()] = _data;
}

template<typename T>
void HistoricalDataService<T>::AddListener(ServiceListener<T>* _listener)
{
	listeners.push_back(_listener);
}

template<typename T>
const vector<ServiceListener<T>*>& HistoricalDataService<T>::GetListeners() const
{
	return listeners;
}

template<typename T>
HistoricalDataConnector<T>* HistoricalDataService<T>::GetConnector()
{
	return connector;
}

template<typename T>
ServiceListener<T>* HistoricalDataService<T>::GetListener()
{
	return listener;
}

template<typename T>
ServiceType HistoricalDataService<T>::GetServiceType() const
{
	return type;
}

template<typename T>
void HistoricalDataService<T>::PersistData(string persistKey, T& data)
{
	connector->Publish(data);
}

/**
* Historical Data Connector publishing data from Historical Data Service.
* Type V is the data type to persist.
*/
template<typename T>
class HistoricalDataConnector : public Connector<T>
{

private:

	HistoricalDataService<T>* service;

public:

	// Connector and Destructor
	HistoricalDataConnector(HistoricalDataService<T>* _service);
	~HistoricalDataConnector();

	// Publish data to the Connector
	void Publish(T& _data);

	// Subscribe data from the Connector
	void Subscribe(ifstream& _data);

};

template<typename T>
HistoricalDataConnector<T>::HistoricalDataConnector(HistoricalDataService<T>* _service)
{
	service = _service;
}

template<typename T>
HistoricalDataConnector<T>::~HistoricalDataConnector() {}

template<typename T>
void HistoricalDataConnector<T>::Publish(T& _data)
{
	ServiceType _type = service->GetServiceType();
	ofstream _file;
	switch (_type)
	{
	case POSITION:
		_file.open("positions.txt", ios::app);
		break;
	case RISK:
		_file.open("risk.txt", ios::app);
		break;
	case EXECUTION:
		_file.open("executions.txt", ios::app);
		break;
	case STREAMING:
		_file.open("streaming.txt", ios::app);
		break;
	case INQUIRY:
		_file.open("allinquiries.txt", ios::app);
		break;
	}

	_file << TimeStamp() << ",";
	vector<string> _strings = _data.ToStrings();
	for (auto& s : _strings)
	{
		_file << s << ",";
	}
	_file << endl;
}

template<typename T>
void HistoricalDataConnector<T>::Subscribe(ifstream& _data) {}

/**
* Historical Data Service Listener subscribing data to Historical Data.
* Type T is the data type to persist.
*/
template<typename T>
class HistoricalDataListener : public ServiceListener<T>
{

private:

	HistoricalDataService<T>* service;

public:

	// Connector and Destructor
	HistoricalDataListener(HistoricalDataService<T>* _service);
	~HistoricalDataListener();

	// Listener callback to process an add event to the Service
	void ProcessAdd(T& _data);

	// Listener callback to process a remove event to the Service
	void ProcessRemove(T& _data);

	// Listener callback to process an update event to the Service
	void ProcessUpdate(T& _data);

};

template<typename T>
HistoricalDataListener<T>::HistoricalDataListener(HistoricalDataService<T>* _service)
{
	service = _service;
}

template<typename T>
HistoricalDataListener<T>::~HistoricalDataListener() {}

template<typename T>
void HistoricalDataListener<T>::ProcessAdd(T& _data)
{
	string _persistKey = _data.GetProduct().GetProductId();
	service->PersistData(_persistKey, _data);
}

template<typename T>
void HistoricalDataListener<T>::ProcessRemove(T& _data) {}

template<typename T>
void HistoricalDataListener<T>::ProcessUpdate(T& _data) {}

#endif
