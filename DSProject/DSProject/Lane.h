#pragma once
#include "Utilities.h"
class Lane
{
public:
	LaneFlightType Type;
	int MaintenanceTime;
	int MaintenanceAfter;
	int AvailabilityTime;
	bool IsFree;
};

