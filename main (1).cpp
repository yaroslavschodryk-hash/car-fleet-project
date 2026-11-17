#include <iostream>
#include <vector>
#include <string>
#include <memory>

using namespace std;

class Vehicle {
protected:
    string brand;
    string model;
    int year;
    double mileage;

public:
    Vehicle(string b, string m, int y, double mil) 
        : brand(b), model(m), year(y), mileage(mil) {}

    virtual ~Vehicle() {}

    virtual void displayInfo() const {
        cout << "Brand: " << brand << ", Model: " << model 
             << ", Year: " << year << ", Mileage: " << mileage << " km";
    }
};

class ElectricCar : public Vehicle {
private:
    double batteryCapacityKWh;

public:
    ElectricCar(string b, string m, int y, double mil, double battery)
        : Vehicle(b, m, y, mil), batteryCapacityKWh(battery) {}

    virtual void displayInfo() const override {
        cout << "[Electric] ";
        Vehicle::displayInfo();
        cout << ", Battery: " << batteryCapacityKWh << " kWh" << endl;
    }
};

class GasCar : public Vehicle {
private:
    double fuelConsumption;

public:
    GasCar(string b, string m, int y, double mil, double cons)
        : Vehicle(b, m, y, mil), fuelConsumption(cons) {}

    virtual void displayInfo() const override {
        cout << "[Gas] ";
        Vehicle::displayInfo();
        cout << ", Fuel: " << fuelConsumption << " L/100km" << endl;
    }
};

class Fleet {
private:
    vector<shared_ptr<Vehicle>> vehicles;

public:
    void addVehicle(shared_ptr<Vehicle> v) {
        vehicles.push_back(v);
    }

    void showFleet() const {
        cout << "--- FLEET ---" << endl;
        for (size_t i = 0; i < vehicles.size(); ++i) {
            cout << i + 1 << ". ";
            vehicles[i]->displayInfo();
        }
    }
};

int main() {
    Fleet myFleet;

    myFleet.addVehicle(make_shared<ElectricCar>("Tesla", "Model Y", 2023, 15000, 75));
    myFleet.addVehicle(make_shared<GasCar>("BMW", "X5", 2021, 45000, 11.5));

    myFleet.showFleet();

    return 0;
}