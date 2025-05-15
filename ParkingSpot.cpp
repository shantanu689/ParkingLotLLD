#include "./Vehicles/Vehicle.hpp"
#include <chrono>

class ParkingSpot
{
    public:
        VehicleType type;
        int spotNumber;
        Vehicle* vehicle;
        chrono::time_point<chrono::system_clock> startTime;
        
        ParkingSpot(VehicleType type, int spotNumber)
        {
            this->type = type;
            this->spotNumber = spotNumber;
            this->vehicle = nullptr;
        }
};