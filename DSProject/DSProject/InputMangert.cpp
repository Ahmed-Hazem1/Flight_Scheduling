#include "InputMangert.h"
#include "Simulation.h"
#include "Lane.h"
#include "Area.h"
#include "Utilities.h"
#include "Event.h"
#include "Queue.h"

using namespace std;

void InputManger::ReadDataFromFile(string FileName, Simulation* sim)
{

	fstream File;
	File.open(FileName);
	int n, numAreas;
	File >> n; // number of areas
	numAreas = n; 
	std::cout << "Number of Areas " << numAreas << endl;
	sim->InstantiateAreas(n);
	File >> n;
	sim->SetTakeOffTime(n);
	File >> n;
	sim->SetLandingTime(n);
	File >> n;
	sim->SetBoardingTime(n);
	File >> n;
	sim->SetOffBoardingTime(n);
	for (int i = 0; i < numAreas; i++)
	{
		File >> n;
		cout << "Number of lanes is " << n << endl;
		sim->GetArea(i + 1)->SetLanesNum(n);
		sim->GetArea(i + 1)->SetAreaNumber(i + 1);
		for (int j = 0; j < numAreas - 1; j++)   // creating areas and their distances
		{
			int area1, area2;
			File >> n;
			cout << n << endl;
			area1 = i + 1;
			if (i == j)
			{
				if (j == numAreas)
				{
					area2 = j;

				}
				else
					area2 = j + 1;

			}
			else
			{
				area2 = j + 1;
			}
			sim->SetAreaDist(area1, area2, n);

		}
	}
		

		for (size_t i = 0; i < numAreas; i++)   // creating lanes
		{
			auto CurrentArea = sim->GetArea(i + 1);
			std::cout << "Number of lanes in area " << CurrentArea->GetlanesNumber() << endl;
			for (size_t j = 0; j < CurrentArea->GetlanesNumber(); j++)
			{
				int AreaNum, AvailabilityTime, MaintenanceTime, MaintenanceAfter;
				string LaneSpec;
				auto newlane = new Lane();
				File >> AreaNum;    // UNUSED
				File >> LaneSpec;
				File >> AvailabilityTime;
				File >> MaintenanceAfter;
				File >> MaintenanceTime;
				newlane->Type = (LaneSpec == "V") ? VIPL : NORMALL;
				newlane->AvailabilityTime = AvailabilityTime;
				newlane->MaintenanceAfter = MaintenanceAfter;
				newlane->MaintenanceTime = MaintenanceTime;
				CurrentArea->SetLaneByNumber(j + 1, newlane);
			}
		}
		int autoPromotion, numEvents;
		File >> autoPromotion;
		std::cout << "Number of autoPromotion " << autoPromotion << endl;
		sim->SetAutoPromotionTime(autoPromotion);
		File >> numEvents;     //creating events
		auto EventsQ = new Queue<Event*>();
		std::cout << "Number of events " << numEvents << endl;

		for (size_t i = 0; i < numEvents; i++)
		{
			auto newEvent = new Event();
			string eventType, FlightType;
			int TimeStep, ID, from, to, passengers;
			File >> eventType;

			
			
			if (eventType == "B")   // booking
			{
				cout << "Booking \n";
				File >> FlightType;
				File >> TimeStep;
				//cout << "TimeStep " << TimeStep << endl;
				File >> ID;
				//cout << "ID " << ID << endl;
				newEvent->EventTime = TimeStep;
				newEvent->ID = ID;
				newEvent->Type = BOOK;
				File >> from;
				File >> to;
				File >> passengers;
				newEvent->From = from;
				newEvent->To = to;
				newEvent->PassengersNumber = passengers;
				newEvent->FlightType = (FlightType == "V") ? VIPL : NORMALL;

			}
			else if (eventType == "X")
			{
				File >> TimeStep;
				//cout << "TimeStep " << TimeStep << endl;
				File >> ID;
				//cout << "ID " << ID << endl;
				newEvent->EventTime = TimeStep;
				newEvent->ID = ID;
				newEvent->Type = CANCEL;
				newEvent->EventTime = TimeStep;
				newEvent->ID = ID;
			}
			else
			{
				File >> TimeStep;
				File >> ID;
				//cout << "ID " << ID << endl;
				newEvent->EventTime = TimeStep;
				newEvent->ID = ID;
				newEvent->Type = PROMOTE;
				newEvent->EventTime = TimeStep;
				newEvent->ID = ID;
			}
				
			newEvent->Print();
			EventsQ->appendNode(newEvent);



		}
		sim->SetEventsQueue(EventsQ);
	









}

bool InputManger::CreateOutPutFile(string OutPutFileName)
{
	OutPutFile.open(OutPutFileName);	// Create and Open output file

	OutPutFile << "FT\t ID\t BT\t WT\t ST\t" << endl;

	//OutPutFile.close();
	return true;
	
}

//void InputManger::ExcuteOutputFile(string OutputFileName)
//{
//	/*OutPutFile<<GetF*/
//
//}
