#ifndef VEHICLE_HPP
#define VEHICLE_HPP

#include <iostream>

using namespace std;

// enum names should not be same to class name else it will implicitly assume enum instead of a class object at places
// Use enum class to have a scoped enum
enum class VehicleType
{
    Car,
    Bike,
    Truck
};

class Vehicle
{
    private:
        string licensePlate;
        VehicleType type;
        double parkingRate;
    
    public:
    // We define only the method definition in .hpp as it will be included across multiple cpps
    // So to avoid linking errors we could also use inline if we want here
        Vehicle(string licensePlate, VehicleType type, double parkingRate);
        VehicleType getType();
        string getTypeAsString();
        string getLicensePlate();
        double getParkingRate();
        virtual double calculateParkingFees(int minutes) = 0;
};


class Bike : public Vehicle
{
    public:
        Bike(string licensePlate);
        double calculateParkingFees(int minutes) override;
};

class Car : public Vehicle
{
    public:
        Car(string licensePlate);
        double calculateParkingFees(int minutes) override;
};

class Truck : public Vehicle
{
    public:
        Truck(string licensePlate);
        double calculateParkingFees(int minutes) override;
};

#endif