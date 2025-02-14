/*
Project id: Group 9 Project A
Project name:Clock w/ added appointment
programmer: Martin, Ben Sprankle
Tester: Ben Sprankle
Date:2-12-2025
Version: 2.4
Description: This program implements the use of an alarm clock feature to clock class program.
*/

#include <iostream>
#include <vector>
#include <memory>
#include <ctime>
#include <string>
#include <iomanip>
#include <stdexcept>
#include <sstream>
using namespace std;

// Base class
class Appointment {
protected:
    string description;
    int year, month, day, hour, minute;

public:
    Appointment(const string& desc, int y, int m, int d, int h, int min)
        : description(desc), year(y), month(m), day(d), hour(h), minute(min) {}

    virtual bool occurs_on(int y, int m, int d) const = 0;
    virtual void print() const {
        cout << description << " at " << hour << ":" << (minute < 10 ? "0" : "") << minute << endl;
    }
    virtual ~Appointment() {}
};

// Derived classes
class Onetime : public Appointment {
public:
    Onetime(const string& desc, int y, int m, int d, int h, int min)
        : Appointment(desc, y, m, d, h, min) {}

    bool occurs_on(int y, int m, int d) const override {
        return (year == y && month == m && day == d);
    }
};

class Daily : public Appointment {
public:
    Daily(const string& desc, int h, int min)
        : Appointment(desc, 0, 0, 0, h, min) {}

    bool occurs_on(int, int, int) const override {
        return true; // Happens every day
    }
};

class Weekly : public Appointment {
    int weekday; // 0 = Sunday, 1 = Monday, ..., 6 = Saturday
public:
    Weekly(const string& desc, int wd, int h, int min)
        : Appointment(desc, 0, 0, 0, h, min), weekday(wd) {}

    bool occurs_on(int y, int m, int d) const override {
        struct tm timeinfo = {};
        timeinfo.tm_year = y - 1900;
        timeinfo.tm_mon = m - 1;
        timeinfo.tm_mday = d;
        mktime(&timeinfo);
        return (timeinfo.tm_wday == weekday);
    }
};

class Monthly : public Appointment {
public:
    Monthly(const string& desc, int d, int h, int min)
        : Appointment(desc, 0, 0, d, h, min) {}

    bool occurs_on(int, int, int d) const override {
        return day == d; // Happens on the same day every month
    }
};

int main() {
    vector<shared_ptr<Appointment>> appointments;

    // Sample appointments
    appointments.push_back(make_shared<Onetime>("Doctor Appointment", 2025, 2, 20, 10, 30));
    appointments.push_back(make_shared<Daily>("Morning Exercise", 6, 0));
    appointments.push_back(make_shared<Weekly>("Team Meeting", 3, 14, 0)); // Every Wednesday
    appointments.push_back(make_shared<Monthly>("Pay Rent", 1, 12, 0));

    int y, m, d;
    cout << "Enter a date (YYYY MM DD): ";
    cin >> y >> m >> d;

    cout << "Appointments on " << y << "-" << m << "-" << d << ":\n";
    for (const auto& appt : appointments) {
        if (appt->occurs_on(y, m, d)) {
            appt->print();
        }
    }

    return 0;
}
