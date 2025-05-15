#include "Vehicle.hpp"

Vehicle::Vehicle(string licensePlate, VehicleType type, double parkingRate)
{
    this->licensePlate = licensePlate;
    this->type = type;
    this->parkingRate = parkingRate;
}
VehicleType Vehicle::getType()
{
    return this->type;
}
string Vehicle::getTypeAsString()
{
    string res;
    switch(this->type){
        case VehicleType::Bike:
            res = "Bike";
            break;
        case VehicleType::Car:
            res = "Car";
            break;
        default:
            res = "Truck";
    }

    return res;
}
string Vehicle::getLicensePlate()
{
    return this->licensePlate;
}
double Vehicle::getParkingRate()
{
    return this->parkingRate;
}


Bike::Bike(string licensePlate) : Vehicle(licensePlate, VehicleType::Bike, 1) {}
double Bike::calculateParkingFees(int minutes)
{
    return minutes*(this->getParkingRate());
}


Car::Car(string licensePlate) : Vehicle(licensePlate, VehicleType::Car, 2){}
double Car::calculateParkingFees(int minutes)
{
    return minutes*(this->getParkingRate());
}


Truck::Truck(string licensePlate) : Vehicle(licensePlate, VehicleType::Truck, 2){}
double Truck::calculateParkingFees(int minutes)
{
    return minutes*(this->getParkingRate());
}