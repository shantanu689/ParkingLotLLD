#include <bits/stdc++.h>
#include "ParkingLot.cpp"
#include "Vehicles/Vehicle.hpp"

using namespace std;

int main()
{
    
    int rows = 3;
    int cols = 2;
    int bikeSpots = 2;
    int carSpots = 3;
    
    ParkingLot parkingLot(rows, cols, bikeSpots, carSpots);
    parkingLot.DisplayParkingStatus();
    Vehicle* bike1 = new Bike("MHBK001");
    parkingLot.ParkVehicle(bike1);
    parkingLot.DisplayParkingStatus();

    Vehicle* bike2 = new Bike("MHBK002");
    Vehicle* bike3 = new Bike("MHBK003");
    Vehicle* car1 = new Car("MHCR001");
    Vehicle* car2 = new Car("MHCR002");
    Vehicle* truck1 = new Truck("MHTR001");

    this_thread::sleep_for(chrono::seconds(30));

    parkingLot.ParkVehicle(car1);
    parkingLot.ParkVehicle(bike2);
    parkingLot.DisplayParkingStatus();
    
    this_thread::sleep_for(chrono::seconds(30));
    vector<int> availableSpots = parkingLot.GetVacantSpots(VehicleType::Car);
    cout << "Available parking spots for CAR: ";
    for(int i=0;i<availableSpots.size();i++)
    {
        cout << availableSpots[i] << ", ";
    }
    cout << "Select a spot:" << endl;
    int carSpot;
    cin >> carSpot;

    this_thread::sleep_for(chrono::seconds(30));
    parkingLot.ParkVehicle(car2, carSpot);
    parkingLot.ParkVehicle(truck1);
    parkingLot.DisplayParkingStatus();

    parkingLot.ParkVehicle(bike3);
    parkingLot.RemoveVehicle(bike1);
    parkingLot.ParkVehicle(bike3);
    parkingLot.DisplayParkingStatus();

    delete bike1;
    delete bike2;
    delete bike3;
    delete car1;
    delete car2;
    delete truck1;
}