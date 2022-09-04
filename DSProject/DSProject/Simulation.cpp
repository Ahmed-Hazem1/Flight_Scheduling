#include "Simulation.h"


void Simulation::EnterMainLoop()
{
	while (true)
	{
		while ((EventsQueue->peek()) && (EventsQueue->peek())->EventTime <= CurrentTime)
		{
			EvaluateEvent(EventsQueue->dequeue());
		}
		// Evaluate flights here
		// first check VIP flights
		while (VipFlightsQueue.peek() && VipFlightsQueue.peek()->BookingTime <= CurrentTime)
		{
			auto newFlight = VipFlightsQueue.dequeue();
			if (newFlight->State == WAITING)
			{
				newFlight->WaitMore();
			}
			newFlight->State = WAITING;
			int StartLoc = newFlight->DepartureArea;
			// check if there VIP lanes in the area
			if (GetArea(StartLoc)->GetFreeLaneByType(VIPL))
			{
				auto lane = GetArea(StartLoc)->GetFreeLaneByType(VIPL);
				lane->IsFree = false;
				newFlight->RemainingTimeToNextState = OffBoardingTime;

				TakingOffFlightsList.appendNode(newFlight);

			}
			else if (GetArea(StartLoc)->GetFreeLaneByType(NORMALL)) {
				auto lane = GetArea(StartLoc)->GetFreeLaneByType(NORMALL);
				lane->IsFree = false;
				newFlight->AssociatedLane = lane;
				newFlight->RemainingTimeToNextState = OffBoardingTime;

				TakingOffFlightsList.appendNode(newFlight);
			}
			else {
				VipFlightsQueue.enqueue(newFlight);
			}


		}
		// second check normal flights
		while (NormalFlightsPQueue.peek() && NormalFlightsPQueue.peek()->BookingTime <= CurrentTime)
		{
			auto newFlight = NormalFlightsPQueue.dequeue();
			if (newFlight->State == WAITING)
			{
				newFlight->WaitMore();
			}
			newFlight->State = WAITING;
			int StartLoc = newFlight->DepartureArea;
			// check if there Normal lanes in the area
			if (GetArea(StartLoc)->GetFreeLaneByType(NORMALL))
			{
				auto lane = GetArea(StartLoc)->GetFreeLaneByType(NORMALL);
				lane->IsFree = false;
				newFlight->RemainingTimeToNextState = OffBoardingTime;

				TakingOffFlightsList.appendNode(newFlight);

			}
			else if (newFlight->waitingTime >= AutoPromotionTime)
			{

				VipFlightsQueue.enqueue(newFlight);
			}
			else {
				NormalFlightsPQueue.enqueue(newFlight);
			}

		}

		//check off boarding flights
		auto TakingOffFlight = TakingOffFlightsList.head;
		while (TakingOffFlight)
		{
			if (TakingOffFlight->getItem()->UpdateState()) //if it has finished taking off
			{
				auto flight = TakingOffFlight->getItem();
				flight->AssociatedLane->IsFree = true;
				flight->AssociatedLane = nullptr;
				flight->RemainingTimeToNextState = GetAreaDist(flight->DepartureArea, flight->ArrivalArea);
				cout << "Flight with ID " << flight->ID << "Toke off" << endl;
				FlyingFlightsList.appendNode(flight);
				TakingOffFlight = TakingOffFlight->getNext();
				TakingOffFlightsList.deleteAtFront();
			}
		}

		//check flying flights
		auto flyingFlight = FlyingFlightsList.head;
			while (flyingFlight)
		{
			auto flight = TakingOffFlight->getItem();
			if (flight->UpdateState())
			{
				WatingToLandFlightsList.appendNode(flight);
				cout << "Flight with ID " << flight->ID << "Waiting to land" << endl;
				flyingFlight = flyingFlight->getNext();
				FlyingFlightsList.deleteAtFront();
			}
		}

		//check flights waiting to land
			auto LandingFlight = WatingToLandFlightsList.head;
		while (LandingFlight)
		{
			auto flight = LandingFlight->getItem();
			// check if there is an availalbe lane in the wanted area of wanted type
			if (GetArea(flight->ArrivalArea)->GetFreeLaneByType(flight->FlightType))
			{
				landingFlightsList.appendNode(flight);
				auto lane = GetArea(flight->ArrivalArea)->GetFreeLaneByType(flight->FlightType);
				lane->IsFree = false;
				flight->AssociatedLane = lane;
				flight->RemainingTimeToNextState = LandingTime;
				cout << "Flight with ID" << flight->ID << "started to land at time" << CurrentTime;
				LandingFlight = LandingFlight->getNext();
			}
			else
			{
				WatingToLandFlightsList.appendNode(flight);
			}
		}

		// check flights that are landing
		auto flght = landingFlightsList.head;
		while (flght)
		{
			auto flight = flght->getItem();

			if (flight->UpdateState())
			{

				flight->AssociatedLane->IsFree = true;
				flight->AssociatedLane = NULL;
				flight->FinishTime = CurrentTime;
				FinishedFlights.appendNode(flight);
				cout << "Flight with ID" << flight->ID << "Landed at time" << CurrentTime;
				flght = flght->next;

			}
		}





		if (EventsQueue->isEmpty() &&
			FlyingFlightsQueue.isEmpty() &&
			VipFlightsQueue.isEmpty() &&
			NormalFlightsPQueue.isEmpty() &&
			landingFlightsList.head == NULL &&
			WatingToLandFlightsList.head == NULL &&
			TakingOffFlightsList.head == NULL
			)
		{
			break;
		}
		//
		CurrentTime++;
	}
}

void Simulation::GetInputData(string s)
{
	Input->ReadDataFromFile(s, this);
	AreaWeights->toString();
}

void Simulation::EvaluateEvent(Event* _event)
{
	switch (_event->Type)
	{
	case BOOK: {
		auto newFlight = new Flight();
		newFlight->FlightType = _event->FlightType;
		newFlight->BookingTime = _event->EventTime;
		newFlight->ArrivalArea = _event->To;
		newFlight->DepartureArea = _event->From;
		newFlight->ID = _event->ID;
		newFlight->PassengersNumber = _event->PassengersNumber;
		switch (newFlight->FlightType)
		{
		case VIPL:
			VipFlightsQueue.enqueue(newFlight);
			break;
		case NORMALL:
			NormalFlightsPQueue.enqueue(newFlight);

		default:
			break;
		}
		break;
	}
	case CANCEL:
		DeleteFLightWithId(_event->ID);
		break;
	case PROMOTE:
		PromoteFLightWithId(_event->ID);
		break;
	default:
		break;
	}

}

void Simulation::DeleteFLightWithId(int ID)
{
}

void Simulation::PromoteFLightWithId(int ID)
{
}

void Simulation::StartSimulation(string s)
{
	GetInputData(s);
	EnterMainLoop();

}

void Simulation::InstantiateAreas(int n)
{
	NumAreas = n;
	AreaWeights = new Graph(n);

	Areas = new Area * [n];
	for (size_t i = 0; i < n; i++)
	{
		auto NewArea = new Area();
		/// set area number to i +1
		Areas[i] = NewArea;

	}


}

void Simulation::SetTakeOffTime(int TOff)
{
	this->TakeOffTime = TOff;
}

void Simulation::SetLandingTime(int LT)
{
	LandingTime = LT;

}

void Simulation::SetBoardingTime(int BT)
{
	BoardingTime = BT;
}

void Simulation::SetOffBoardingTime(int OBT)
{
	OffBoardingTime = OBT;

}

Area* Simulation::GetArea(int areaNum)
{
	return Areas[areaNum - 1];
}

void Simulation::SetAreaDist(int area1, int area2, int dist)
{
	AreaWeights->addEdge(area1 - 1, area2 - 1, dist);
}

int Simulation::GetAreaDist(int area1, int area2)
{
	return AreaWeights->getEdge(area1 - 1, area2 - 1);
}


Simulation::Simulation()
{
	Input = new InputManger();

}

