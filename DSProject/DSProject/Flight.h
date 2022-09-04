#pragma once
#include "Utilities.h"
#include "Lane.h"

class Flight {
private:
	
	float PassengersNumberWeight = 0.6;
	float FlightTimeDiffWeight = 0.2;
	

public:
	
	bool operator>(const Flight* OtherFlight) {
		return (PassengersNumberWeight * (float)(PassengersNumber - OtherFlight->GetPassengersNumber()) + 
			FlightTimeDiffWeight * (float)(OtherFlight->GetBookingTime() - BookingTime)) > 0;
	}
	unsigned  int GetPassengersNumber() const;
	unsigned  int GetBookingTime() const;
	unsigned  int GetDepartureArea() const;
	unsigned  int GetArrivalArea() const;
	unsigned  int GetFlightType() const;
	unsigned int BookingTime;
	unsigned int DepartureArea;
	unsigned int ArrivalArea;
	unsigned int PassengersNumber;
	int RemainingTimeToNextState;
	bool UpdateState() ;
	int WaitMore() { return waitingTime++; }
	int waitingTime = 0;
	int FinishTime = -1;
	int ID;
	FLightState State;
	LaneFlightType FlightType;
	Lane* AssociatedLane;




};

