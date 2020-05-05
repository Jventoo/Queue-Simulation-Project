/*
	    Team Vento
		Vento, Jack (W 2:20)

		10 May 2020

		CS A250
		Project 1 - Part A
*/

#include "Simulation.h"

#include <cstdlib>
#include <iomanip>
#include <cmath>

using namespace std;

void runSimulation()
{
	int simTime = 0,
		numServers = 0,
		transTime = 0,
		timeBetweenCustArrival = 0;

	setSimulationParameters(simTime, numServers, 
		transTime, timeBetweenCustArrival);

	ServerList serveList(numServers);
	queue<CustomerType> custQueue;

	int servedWaitTime = 0, numCusts = 0,
		freeServer = 0;

	for (int clock = 1; clock <= simTime; ++clock)
	{
		serveList.updateServers();

		if (custQueue.size() > 0)
		{
			updateCustQueue(custQueue);
		}

		if (isCustomerArrived(timeBetweenCustArrival))
		{
			++numCusts;

			CustomerType newCust(numCusts, clock, 0, transTime);

			custQueue.push(newCust);

			cout << "Customer number " << numCusts
				<< " arrived at time unit " << clock << endl;
		}

		freeServer = serveList.getFreeServerID();
		if (freeServer != -1 && custQueue.size() > 0)
		{
			CustomerType custToServe = custQueue.front();
			custQueue.pop();

			servedWaitTime += custToServe.getWaitingTime();

			serveList.setServerBusy(freeServer, custToServe);
		}
	}

	cout << endl << "Simulation ran for " << simTime
		<< " time units" << endl;
	cout << "Number of lanes: " << numServers << endl;
	cout << "Average transaction time: " << transTime << endl;
	cout << "Average arrival time between customers: " 
		<< timeBetweenCustArrival << endl;

	generateStatistics(serveList, custQueue, numCusts, servedWaitTime);
}

void setSimulationParameters(int& simulationTime, int& numOfServers,
	int& transactionTime,
	int& timeBetweenCustomerArrival)
{
	cout << "Enter the simulation time: " << flush;
	cin >> simulationTime;
	cout << endl;

	cout << "Enter the number of lanes: " << flush;
	cin >> numOfServers;
	cout << endl;

	cout << "Enter the transaction time: " << flush;
	cin >> transactionTime;
	cout << endl;

	cout << "Enter the time between customer arrivals: " << flush;
	cin >> timeBetweenCustomerArrival;
	cout << endl;
}

bool isCustomerArrived(double arrivalTimeDifference)
{
	double value = 0.0;

	value = static_cast<double> (rand()) / static_cast<double>(RAND_MAX);

	return (value > exp(-1.0 / arrivalTimeDifference));
}


void generateStatistics(ServerList& serverList,
	queue<CustomerType>& customerQueue,
	int numOfCustomersArrived,
	int waitTimeServedCustomers)
{
	int customersLeftInQueue = 0;

	int totalWaitTime = waitTimeServedCustomers;

	CustomerType customer;

	while (!customerQueue.empty())
	{
		customer = customerQueue.front();
		customerQueue.pop();
		totalWaitTime = totalWaitTime + customer.getWaitingTime();
		customersLeftInQueue++;
	}

	//Find number of customers left in servers
	int customersLeftInServers = serverList.getNumberOfBusyServers();
	//Find number of customers completely served
	int numberOfCustomersServed = numOfCustomersArrived -
		customersLeftInServers -
		customersLeftInQueue;

	double averageWaitTime = 0;

	cout << "Total wait time: " << totalWaitTime << endl;
	cout << "Number of customers arrived: "
		<< numOfCustomersArrived << endl;
	cout << "Number of customers who completed a transaction: "
		<< numberOfCustomersServed << endl;
	cout << "Number of customers left in the servers: "
		<< customersLeftInServers << endl;
	cout << "Number of customers left in the queue: " << customersLeftInQueue
		<< endl;

	if (numOfCustomersArrived > 0)  // If number of customers arrived is > 0
		averageWaitTime = (static_cast<double>(totalWaitTime)) / numOfCustomersArrived;

	cout << fixed << showpoint;
	cout << setprecision(2);
	cout << "Average wait time: " << averageWaitTime << endl;

	cout << "\n************** END SIMULATION *************" << endl;

}

void updateCustQueue(queue<CustomerType>& customerQueue)
{
	CustomerType customer;

	customer.setWaitingTime(-1);
	int wTime = 0;

	customerQueue.push(customer);

	while (wTime != -1)
	{
		customer = customerQueue.front();
		customerQueue.pop();
		wTime = customer.getWaitingTime();
		if (wTime != -1)
		{
			customer.incrementWaitingTime();
			customerQueue.push(customer);
		}
	}
}

