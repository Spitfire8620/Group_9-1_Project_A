
/*Project id: Group 1 Project A   
      Project Name: Clock
      Programmer: Ben Sprankle
      Tester: Ben Sprankle
      Date: Febuary 10, 2025
      Version: 5.1  (Final Version)
      Description: This program is a clock with a world clock option .
      */

// These are my libraries that I used to create the program
#include <iostream>
#include <string>
#include <algorithm>
#include <iomanip>
#include <cctype>
#include <ctime>

using namespace std;

class Clock
{
private:
    //These are the variables that I used in the class
    time_t current_time = time(0);
    tm* local_time = localtime(&current_time);
    int hours = local_time->tm_hour;
    int minutes = local_time->tm_min;
    string time_str;
public:
    //This is my constructor for the class
    Clock(int hours, int minutes, int seconds, string time_str = "");
    //These are my functions
    string get_time();
    int get_hours();
    int get_minutes();
};

class WorldClock : public Clock
{
private:
    //These are the variables that I used in the class
    string time_zone;

public:
    WorldClock(int hours, int minutes, int seconds, string time_str, string time_zone);
    string get_time_zone();
    string get_world_time();
    int get_world_hours();
};

//This is my constructor for the class
Clock::Clock(int hours, int minutes, int seconds, string time_str)
{
    this->hours = hours;
    this->minutes = minutes;
    this->time_str = time_str;
}
//This is my function that gets the time
string Clock::get_time()
{
    string time_str;
    if (hours > 12)
    {
        time_str = to_string(hours - 12) + ":" + to_string(minutes) + " PM";
    }
    else
    {
        time_str = to_string(hours) + ":" + to_string(minutes) + " AM";
    }
    return time_str;
}
//This is my function that gets the hours
int Clock::get_hours()
{
    return hours;
}
//This is my function that gets the minutes
int Clock::get_minutes()
{
    return minutes;
}
//This is my constructor for the class
WorldClock::WorldClock(int hours, int minutes, int seconds, string time_str, string time_zone)
    : Clock(hours, minutes, seconds, time_str)
{
    this->time_zone = time_zone;
}
//This is my function that gets the time zone
string WorldClock::get_time_zone()
{
    return time_zone;
}
//This is my function that gets the world time
string WorldClock::get_world_time()
{
    int hours = get_world_hours();
    int minutes = get_minutes();
    string time_str;
    if (hours > 12)
    {
        time_str = to_string(hours - 12) + ":" + to_string(minutes) + " PM";
    }
    else
    {
        time_str = to_string(hours) + ":" + to_string(minutes) + " AM";
    }
    return time_str;
}
//This is my function that gets the world hours
int WorldClock::get_world_hours()
{
    int offset = stoi(time_zone); // Assuming time_zone is a string representing the offset
    return (get_hours() + offset) % 24;
}

int main() {
    string world = "";
    cout << "\033[2J\033[1;1H";
    cout << "Enter timezone: ";
    cin >> world;
    cout << endl;
    Clock clock(10, 30, 0, "");
    WorldClock worldClock(10, 30, 0, "", world); // Assuming time zone offset is +2 hours

    cout << "Local Time: " << clock.get_time() << endl;
    cout << "World Time: " << worldClock.get_world_time() << endl;

    return 0;
}
