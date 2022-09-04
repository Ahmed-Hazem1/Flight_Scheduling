#pragma once
#define _Simulation
#include "Area.h"
#include "Queue.h"
#include "Flight.h"
#include "Queue.h"
#include "Graph.h"
#include "PriorityQueue.h"
#include "InputMangert.h"
#include "LinkedList.h"
#include "Event.h"

class Simulation
{
private :
	int MaxTime;   // you will need to know it with the file
	int NumAreas=0;
	int TakeOffTime=0;
	int LandingTime=0;
	int BoardingTime=0;
	int OffBoardingTime=0;
	int AutoPromotionTime=0;
	int CurrentTime = 0;
	int FinishTime=0;
	int VIPFlightCount = 0;
	int NormalFlightCount = 0;
	int AverageWatingTime;
	int AverageServicingTime;
	Graph* AreaWeights;
	Queue<Event*>* EventsQueue;
	Area** Areas;
	Queue<Flight*> VipFlightsQueue;
	Queue<Flight*> FlyingFlightsQueue;
	LinkedList<Flight*> TakingOffFlightsList;
	LinkedList<Flight*> FlyingFlightsList;
	LinkedList<Flight*> FinishedFlights;
	LinkedList<Flight*> WatingToLandFlightsList;
	LinkedList<Flight*> landingFlightsList;

	

	PriorityQueue<Flight*> NormalFlightsPQueue;   //need to be changed to pq
	
	void EnterMainLoop();
	void GetInputData(string s);
	void EvaluateEvent(Event* event);
	void DeleteFLightWithId(int ID);
	void PromoteFLightWithId(int ID);

	InputManger* Input;
	ofstream OutPutFile;
	
public :
	Area* CurrentAreas;
	
	void StartSimulation(string );
	void InstantiateAreas(int n);
	void SetTakeOffTime(int);
	void SetLandingTime(int);
	void SetBoardingTime(int);
	void SetOffBoardingTime(int);
	void SetEventsQueue(Queue<Event*>* q) { EventsQueue = q; }
	Area* GetArea(int index);
	void SetAreaDist(int area1, int area2, int dist);
	int GetAreaDist(int area1, int area2);
	void SetAutoPromotionTime(int t) { AutoPromotionTime = t; }
	int GetAutoPromotionTime() { return AutoPromotionTime; }
	//int GetFinishTime(){return  }

	Simulation();

};

