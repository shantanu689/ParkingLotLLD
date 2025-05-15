#include <vector>
#include <unordered_map>
#include "ParkingSpot.cpp"
#include "./Vehicles/Vehicle.hpp"

using namespace std;

class ParkingLot
{
    private:
        vector<vector<ParkingSpot*>> grid;
        unordered_map<string, ParkingSpot*> vehicleToSpotMapping;
        int gridRows;
        int gridCols;

    public:
        ParkingLot(int rows, int cols, int bikeSpots, int carSpots)
        {
            gridRows = rows;
            gridCols = cols;
            grid.resize(rows);
            for(int i=0;i<rows;i++)
            {
                grid[i].resize(cols);
                for(int j=0;j<cols;j++)
                {
                    VehicleType vehicleType;

                    if(bikeSpots > 0)
                    {
                        vehicleType = VehicleType::Bike;
                        bikeSpots--;
                    }
                    else if(carSpots > 0)
                    {
                        vehicleType = VehicleType::Car;
                        carSpots--;
                    }
                    else
                    {
                        vehicleType = VehicleType::Truck;
                    }

                    grid[i][j] = new ParkingSpot(vehicleType, i*cols + j);
                }
            }
        } 

        ~ParkingLot()
        {
            for(int i=0;i<gridRows;i++)
            {
                for(int j=0;j<gridCols;j++)
                {
                    delete grid[i][j];
                }
            }
        }
        
        //Expose a method to allow user selection of parking spot
        vector<int> GetVacantSpots(VehicleType vehicleType, int limitResults = -1)
        {
            vector<int> res;
            if(limitResults == -1)
            {
                limitResults = gridRows*gridCols;
            }

            for(int i=0;i<gridRows && limitResults>0;i++)
            {
                for(int j=0;j<gridCols && limitResults>0;j++)
                {
                    if(grid[i][j]->type == vehicleType && !(grid[i][j]->vehicle))
                    {
                        res.push_back(grid[i][j]->spotNumber);
                        limitResults--;
                    }
                }
            }

            return res;
        }

        // Returns the spot number if vehicle is parked, else -1
        int FindVehicle(Vehicle* vehicle)
        {
            string licensePlate = vehicle->getLicensePlate();
            if(vehicleToSpotMapping.count(licensePlate) == 0)
            {                
                return -1;
            }
            
            return vehicleToSpotMapping[licensePlate]->spotNumber;
        }

        bool ParkVehicle(Vehicle* vehicle, int spotNumber = -1)
        {
            if(spotNumber == -1)
            {
                vector<int> availableSpot = GetVacantSpots(vehicle->getType(), 1);
                if(availableSpot.size() == 0)
                {
                    cout << "Parking Lot is full now. Please come back later." << endl;
                    return false;
                }
                
                spotNumber = availableSpot[0];
            }

            if(FindVehicle(vehicle) != -1)
            {
                cout << "Vehicle is already parked in the parking lot. Cannot assign a new spot." << endl;
                return false;
            }

            int spotRow = spotNumber/gridCols;
            int spotCol = spotNumber%gridCols;
            grid[spotRow][spotCol]->vehicle = vehicle;
            auto currTime = chrono::system_clock::now();
            grid[spotRow][spotCol]->startTime = currTime;
            vehicleToSpotMapping[vehicle->getLicensePlate()] = grid[spotRow][spotCol];
            cout << "Park vehicle: " << vehicle->getLicensePlate() << " on spot: " << spotNumber << endl;
            return true;
        }

        double GetParkingCharges(Vehicle* vehicle, ParkingSpot* spot)
        {
            auto currTime = chrono::system_clock::now();
            auto duration = chrono::duration_cast<chrono::minutes>(currTime - spot->startTime);
            return vehicle->calculateParkingFees(duration.count());
        }

        bool RemoveVehicle(Vehicle* vehicle)
        {
            int spotNumber = FindVehicle(vehicle);
            if(spotNumber == -1)
            {
                cout << "Vehicle is not parked in the parking lot, cannot remove it" << endl;
                return false;
            }

            int spotRow = spotNumber/gridCols;
            int spotCol = spotNumber%gridCols;
            ParkingSpot* spot = grid[spotRow][spotCol];
    
            double parkingCharges = GetParkingCharges(vehicle, spot);
            cout << "Process payment of Rs." << parkingCharges << endl;

            //start payment process
            spot->vehicle = nullptr;
            vehicleToSpotMapping.erase(vehicle->getLicensePlate());

            cout << "Removed vehicle: " << vehicle->getLicensePlate() << " from parking lot." << endl;
            return true;
        }

        void DisplayParkingStatus()
        {
            cout << "-------------- Parking Status ------------------------------" << endl;
            cout << "VehicleType \t LicensePlate \t SpotNumber \t ParkingCost" << endl;
            for(auto it=vehicleToSpotMapping.begin();it!=vehicleToSpotMapping.end();it++)
            {
                string licensePlate = it->first;
                ParkingSpot* spot = it->second;
                cout << ((spot->vehicle)->getTypeAsString()) << " \t\t " << licensePlate << " \t\t " << spot->spotNumber << " \t\t " << GetParkingCharges(spot->vehicle, spot) << endl;
            }
            cout << "-------------------------------------------------------------------------" << endl;
        }
};