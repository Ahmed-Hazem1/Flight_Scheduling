#pragma once
#include"Utilities.h"
#include "Lane.h"

class Area
{
	
	int AreaNumber;
	int DFOtherArea;
	int NLanes;
	Lane** Lanes;

public:

	int GetAreaNumber() { return AreaNumber; }
	int GetlanesNumber() { return NLanes; }
	void SetLaneByNumber(int n, Lane* lane) { Lanes[n - 1] = lane; }
	void SetAreaNumber(int n) { AreaNumber = n; }
	
	void SetLanesNum(int num) { Lanes = new Lane*[num]; NLanes = num; }
	Lane* GetLane(int n) { return Lanes[n - 1]; }
	Lane* GetFreeLaneByType(LaneFlightType type) {
		for (size_t i = 0; i < NLanes; i++)
		{
			auto lane = Lanes[i];
			if (lane->IsFree && lane->Type == type)
			{
				return lane;
			}
		}
		return nullptr;
	}



};

