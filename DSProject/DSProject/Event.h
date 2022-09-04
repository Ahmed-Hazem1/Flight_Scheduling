#pragma once
#include <iostream>
#include "Utilities.h"
using namespace std;
class Event
{
public:
	int EventTime;
	int ID;
	EventType Type;
	LaneFlightType FlightType;
	int PassengersNumber;
	int From;
	int To;
	void Print() {
		cout << "Event with ID" << ID << endl << "Type :" << Type << endl << "Time :" << EventTime << endl
			<< "Number of passengers is" << PassengersNumber << endl << "From :" << From << endl <<
			"To :" << To << endl
			;
	}

};

