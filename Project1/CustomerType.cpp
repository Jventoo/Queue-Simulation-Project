/*
		Team Vento
		Vento, Jack (W 2:20)

		10 May 2020

		CS A250
		Project 1 - Part A
*/

#include "CustomerType.h"

using namespace std;

	//overloaded constructor
CustomerType::CustomerType(int theCustomerNumber, int theArrivalTime,
					int theWaitingTime, int theTransactionTime)
{
	customerNumber = theCustomerNumber;
    arrivalTime = theArrivalTime;
    waitingTime = theWaitingTime; 
    transactionTime = theTransactionTime;
}

	//setCustomerInformation
void CustomerType::setCustomerInfo(int theCustomerNumber, int theArrivalTime,
	int theWaitingTime, int theTransactionTime)
{
	customerNumber = theCustomerNumber;
	arrivalTime = theArrivalTime;
	waitingTime = theWaitingTime;
	transactionTime = theTransactionTime;
}

	//setWaitingTime
void CustomerType::setWaitingTime(int theWaitingTime)
{
	waitingTime = theWaitingTime;
}

	//getWaitingTime
int CustomerType::getWaitingTime() const
{
	return waitingTime;
}

	//getArrivalTime
int CustomerType::getArrivalTime() const
{
	return arrivalTime;
}

	//getTransactionTime
int CustomerType::getTransactionTime() const
{
	return transactionTime;
}

	//getCustomerNumber
int CustomerType::getCustomerNumber() const
{
	return customerNumber;
}

	//incrementWaitingTime
void CustomerType::incrementWaitingTime()
{
	++waitingTime;
}

	//destructor
CustomerType::~CustomerType(){}
