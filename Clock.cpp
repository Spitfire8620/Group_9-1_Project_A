
/*
Project id: Group 9 Project A
Project name:Clock w/ added alarm feature
programmer: Ben Sprankle, Jacob Huerta
Tester: Ben Sprankle, Martin Aguilar
Date:2-12-2025
Version: 7.6
Description: This program implements the use of an alarm clock feature to clock class program.
*/

#include <iostream>
#include <string>
#include <algorithm>
#include <iomanip>
#include <cctype>
#include <ctime>
#include <sstream> // Included this header for std::ostringstream

using namespace std;

class Clock
{
protected:
    // Variables used in the class
    time_t current_time = time(0);
    tm* local_time = localtime(&current_time);
    int hours = local_time->tm_hour;
    int minutes = local_time->tm_min;
    string time_str;
    bool alarm_set;
    int alarm_hours;
    int alarm_minutes;

public:
    // Constructor for the class
    Clock(int hours, int minutes, int seconds, string time_str = "")
        : hours(hours), minutes(minutes), time_str(time_str), alarm_set(false), alarm_hours(0), alarm_minutes(0) {}

    // Functions
    string get_time();
    int get_hours();
    int get_minutes();
    void set_alarm(int hours, int minutes, string m);
    void clear_alarm();
};

class WorldClock : public Clock
{
private:
    // Variables used in the class
    string time_zone;

public:
    WorldClock(int hours, int minutes, int seconds, string time_str, string time_zone)
        : Clock(hours, minutes, seconds, time_str), time_zone(time_zone) {}

    string get_time_zone();
    string get_world_time();
    int get_world_hours();
};

// Function to get the time
string Clock::get_time()
{
    string time_str;
    int display_hours = hours > 12 ? hours - 12 : hours;
    string am_pm = hours >= 12 ? " PM" : " AM";

    ostringstream oss;
    oss << setw(2) << setfill('0') << display_hours << ":"
        << setw(2) << setfill('0') << minutes << am_pm;

    // Check if the alarm time has been reached or exceeded
    if (alarm_set && (hours > alarm_hours || (hours == alarm_hours && minutes >= alarm_minutes))) {
        oss << " Alarm"; // Display alarm text
        clear_alarm(); // Clear the alarm after it goes off
    }

    return oss.str();
}

// Function to get the hours
int Clock::get_hours()
{
    return hours;
}

// Function to get the minutes
int Clock::get_minutes()
{
    return minutes;
}

// Function to set the alarm
void Clock::set_alarm(int hours, int minutes, string m)
{
    alarm_set = true;
    if (m == "am"){
        alarm_hours = hours;
    }
    else if (m == "pm"){
        alarm_hours = hours + 12;
    }
    alarm_minutes = minutes;
    transform(m.begin(),m.end(),m.begin(), ::toupper);
    cout << "Alarm set for -> " << alarm_hours << ":" << alarm_minutes << m << endl;
}

// Function to clear the alarm
void Clock::clear_alarm()
{
    alarm_set = false;
    alarm_hours = 0;
    alarm_minutes = 0;
}

// Function to get the time zone
string WorldClock::get_time_zone()
{
    return time_zone;
}

// Function to get the world time
string WorldClock::get_world_time()
{
    int hours = get_world_hours();
    int minutes = get_minutes();
    int display_hours = hours > 12 ? hours - 12 : hours;
    string am_pm = hours >= 12 ? " PM" : " AM";

    ostringstream oss;
    oss << setw(2) << setfill('0') << display_hours << ":" << setw(2) << setfill('0') << minutes << am_pm;

    // Check if the alarm time has been reached or exceeded
    if (alarm_set && (hours > alarm_hours || (hours == alarm_hours && minutes >= alarm_minutes))) {
        oss << " Alarm"; // Display alarm text
        clear_alarm(); // Clear the alarm after it goes off
    }

    return oss.str();
}

// Function to get the world hours
int WorldClock::get_world_hours()
{
    int offset = stoi(time_zone); // Assuming time_zone is a string representing the offset
    int adjusted_hours = (get_hours() + offset) % 24;
    if (adjusted_hours < 0) adjusted_hours += 24;
    return adjusted_hours;
}

int main() {
    string world;
    string m;
    int alarmh;
    int alarmm;
    time_t now = time(0);
    tm *ltm = localtime(&now);
    Clock clear_alarm();
    cout << "\033[2J,\033[1;1H";
    cout << "Enter timezone offset (e.g., +3, -5): ";
    cin >> world;
    cout << endl;
    cout << "Enter the alarm hour: ";
    cin >> alarmh;
    cout << endl;
    cout << "Enter the alarm minutes: ";
    cin >> alarmm;
    cout << "Am or Pm: ";
    cin >> m;
    transform(m.begin(),m.end(),m.begin(), ::tolower);
    cout << endl;

    Clock local_clock(ltm->tm_hour, ltm->tm_min, ltm->tm_sec, "");
    local_clock.set_alarm(alarmh, alarmm, m);

    WorldClock world_clock(ltm->tm_hour, ltm->tm_min, ltm->tm_sec, "", world);
    world_clock.set_alarm((alarmh + stoi(world)) % 24, alarmm, m);
    Clock get_alarm();
    cout << endl;

    cout << "Local Time: " << local_clock.get_time() << endl;
    cout << "World Time: " << world_clock.get_world_time() << endl;

    return 0;
}
