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

    virtual double estimateTripCost(double km) const = 0;

    virtual void displayInfo() const {
        cout << "Brand: " << brand
             << ", Model: " << model
             << ", Year: " << year
             << ", Mileage: " << mileage << " km";
    }

    string getBrand() const { return brand; }
};

class ElectricCar : public Vehicle {
private:
    double batteryCapacityKWh;
    double pricePerKWh;

public:
    ElectricCar(string b, string m, int y, double mil, double battery, double priceKWh = 0.25)
        : Vehicle(b, m, y, mil), batteryCapacityKWh(battery), pricePerKWh(priceKWh) {}

    double estimateTripCost(double km) const override {
        double kWhPer100Km = 18.0;
        return (km / 100.0) * kWhPer100Km * pricePerKWh;
    }

    void displayInfo() const override {
        cout << "[Electric] ";
        Vehicle::displayInfo();
        cout << ", Battery: " << batteryCapacityKWh << " kWh" << endl;
    }
};

class GasCar : public Vehicle {
private:
    double fuelConsumption;
    double fuelPricePerLiter;

public:
    GasCar(string b, string m, int y, double mil, double cons, double priceL = 1.4)
        : Vehicle(b, m, y, mil), fuelConsumption(cons), fuelPricePerLiter(priceL) {}

    double estimateTripCost(double km) const override {
        return (km / 100.0) * fuelConsumption * fuelPricePerLiter;
    }

    void displayInfo() const override {
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
        cout << "\n=== FLEET ===" << endl;
        if (vehicles.empty()) {
            cout << "Fleet is empty." << endl;
            return;
        }
        for (size_t i = 0; i < vehicles.size(); ++i) {
            cout << i + 1 << ". ";
            vehicles[i]->displayInfo();
        }
    }

    void calculateAllTrips(double km) const {
        cout << "\n=== TRIP COST FOR " << km << " KM ===" << endl;
        for (size_t i = 0; i < vehicles.size(); ++i) {
            cout << i + 1 << ". " << vehicles[i]->getBrand()
                 << " -> $" << vehicles[i]->estimateTripCost(km) << endl;
        }
    }
};

int main() {
    Fleet myFleet;
    myFleet.addVehicle(make_shared<ElectricCar>("Tesla", "Model Y", 2023, 15000, 75));
    myFleet.addVehicle(make_shared<GasCar>("BMW", "X5", 2021, 45000, 11.5));
    myFleet.addVehicle(make_shared<ElectricCar>("Nissan", "Leaf", 2020, 60000, 40));

    int choice = -1;
    while (choice != 0) {
        cout << "\n1 - Show fleet\n2 - Calculate trip cost\n3 - Add electric car\n0 - Exit\nChoice: ";
        cin >> choice;

        if (choice == 1) {
            myFleet.showFleet();
        } else if (choice == 2) {
            double km;
            cout << "Enter distance (km): ";
            cin >> km;
            myFleet.calculateAllTrips(km);
        } else if (choice == 3) {
            string brand, model;
            int year;
            double mil, bat;
            cout << "Brand Model Year Mileage Battery: ";
            cin >> brand >> model >> year >> mil >> bat;
            myFleet.addVehicle(make_shared<ElectricCar>(brand, model, year, mil, bat));
            cout << "Added!" << endl;
        }
    }

    return 0;
}
