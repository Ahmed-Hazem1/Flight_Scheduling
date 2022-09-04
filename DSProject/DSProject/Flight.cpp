#include "Flight.h"
#include "Utilities.h"
unsigned int Flight::GetPassengersNumber() const
{
    return PassengersNumber;
}

unsigned  int Flight::GetBookingTime() const
{
    return BookingTime;
}

unsigned int Flight::GetDepartureArea() const
{
    return DepartureArea;
}

unsigned int Flight::GetArrivalArea() const
{
    return ArrivalArea;
}

unsigned int Flight::GetFlightType() const
{
    return FlightType;
}

bool Flight::UpdateState()
{
    if (!RemainingTimeToNextState--)
    {
        return false;
    }
    return true;
}
