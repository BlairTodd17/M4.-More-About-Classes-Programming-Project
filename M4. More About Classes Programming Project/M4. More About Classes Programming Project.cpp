#include <iostream>
#include <string>
using namespace std;

class ParkedCar {
private:
    string make, model, color, licenseNumber;
    int minutesParked;

public:
    ParkedCar(string mk = "", string mdl = "", string clr = "", string lic = "", int mins = 0)
        : make(mk), model(mdl), color(clr), licenseNumber(lic), minutesParked(mins) {}

    int getMinutesParked() const { return minutesParked; }
    string getMake() const { return make; }
    string getModel() const { return model; }
    string getColor() const { return color; }
    string getLicenseNumber() const { return licenseNumber; }
};

class ParkingMeter {
private:
    int minutesPurchased;

public:
    ParkingMeter(int mins = 0) : minutesPurchased(mins) {}

    int getMinutesPurchased() const { return minutesPurchased; }
};

class ParkingTicket {
private:
    string officerName, badgeNumber;
    string carMake, carModel, carColor, licenseNumber;
    int fine;
    int minutesOver;

public:
    ParkingTicket(const ParkedCar& car, int overMinutes, const string& name, const string& badge) {
        carMake = car.getMake();
        carModel = car.getModel();
        carColor = car.getColor();
        licenseNumber = car.getLicenseNumber();
        minutesOver = overMinutes;
        officerName = name;
        badgeNumber = badge;

        fine = 25;
        if (overMinutes > 60) {
            int additionalHours = (overMinutes - 1) / 60;
            fine += additionalHours * 10;
        }
    }

    void printTicket() const {
        cout << "\n*** Parking Ticket ***\n";
        cout << "Officer: " << officerName << "  Badge: " << badgeNumber << "\n";
        cout << "Car - License: " << licenseNumber << ", Make: " << carMake << ", Model: " << carModel << ", Color: " << carColor << "\n";
        cout << "Minutes Over: " << minutesOver << "\n";
        cout << "Fine: $" << fine << "\n";
    }
};

class PoliceOfficer {
private:
    string name;
    string badgeNumber;

public:
    PoliceOfficer(string n = "", string b = "") : name(n), badgeNumber(b) {}

    void inspectCar(const ParkedCar& car, const ParkingMeter& meter) {
        int parked = car.getMinutesParked();
        int purchased = meter.getMinutesPurchased();
        if (parked > purchased) {
            int minutesOver = parked - purchased;
            ParkingTicket ticket(car, minutesOver, name, badgeNumber);
            ticket.printTicket();
        }
        else {
            cout << "\nNo violation. Car is legally parked.\n";
        }
    }
};

int main() {
    ParkedCar car1("Toyota", "Camry", "Red", "XYZ123", 30);
    ParkingMeter meter1(40);
    PoliceOfficer officer1("John Doe", "5678");
    officer1.inspectCar(car1, meter1);

    ParkedCar car2("Honda", "Accord", "Blue", "ABC987", 70);
    ParkingMeter meter2(60);
    PoliceOfficer officer2("Jane Smith", "1234");
    officer2.inspectCar(car2, meter2);

    ParkedCar car3("Ford", "Mustang", "Black", "LMN456", 190);
    ParkingMeter meter3(60);
    PoliceOfficer officer3("James Brown", "4321");
    officer3.inspectCar(car3, meter3);

    return 0;
}
