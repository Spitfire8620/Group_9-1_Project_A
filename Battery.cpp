/*Project id: Group 1 Project A  
      Project Name: Battery
      Programmer: Ben Sprankle
      Tester: Ben Sprankle
      Date: Febuary 6, 2025
      Version: 4.3  (Final Version)
      Description: This program creates a battery that can be charged and drained
      */

// These are my libraries that I used to create the program
#include <iostream>
#include <cmath>
#include <iomanip>
#include <string>
#include <algorithm>
#include <cctype>
using namespace std;

//This is my class for the battery
class Battery
{
private:
//These are the variables that I used in the class
    double amount;
    double rcharge;
    double capacity;
public:
//This is my constructor and functions
    Battery(double capacity, double rcharge, double amount);
    void drain(double amount);
    void charge();
    double get_remaining_capacity();
};
//This is my constructor
Battery::Battery(double capacity, double rcharge, double amount)
{
    //My code was getting stuck in an infinite loop using this initializer I was able to fix it.
    this->capacity = capacity;
    this->rcharge = rcharge;
    //Amount was starting at like 2356E-31 or something crazy so I set it to 0
    this->amount = amount;
}
//This is my drain function
void Battery::drain(double amount)
{
    //This makes sure you dont drain to much
    if (amount > rcharge){
        cout << "Not enough power in the battery" << endl;
        cout << endl;
    }
    //This is the drain function
    else if (amount < rcharge){
        rcharge -= amount;
        cout << "Battery drained by " << amount << " mAh" << endl;
        cout << endl;
    }
    //This is just to let you know its empty
    else if (amount == rcharge){
        rcharge -= amount;
        cout << "Battery has been drained completely" << endl;
        cout << endl;
    }
}
//This was a quick one it just resets the battary to capacity using the private variables in the class
void Battery::charge()
{
    rcharge = capacity;
    cout << "Battery has been charged to full capacity" << endl;
    cout << endl;
}
//This is my get remaining capacity function
double Battery::get_remaining_capacity()
{
    //This just returns the variable remaining charge or rcharge which is being changed throughout the program
    return rcharge;
}

int main() {
    //These are my variables
    double amount;
    double capacity;
    string choice;
    int inputs;
    int i = 0;
    //Again here are some custom text that allow your screen to be cleared without removing the last output I find it helpful when coding
    cout << "\033[2J\033[1;1H";
    cout << "What is the capacity of your battery in mAh?" << endl;
    //Allowes you to set your own capacity I did 2000-3000 in my tests because that was requested
    cout << "Capacity: ";
    cin >> capacity;
    cout << "\n\nHow many inputs would you like to make?" << endl;
    //This sets the loop
    cout << "Inputs: ";
    cin >> inputs;
    //This initalizes the variables and resets there values
    Battery Battery(capacity, capacity, 0);
    //This is the loop that runs the program
    while (i < inputs){
        cout << "Would you like to drain or charge the battery?" << endl;
        cout << "Choice: ";
        cin >> choice;
        //Makes everything lowercase for user simplicity
        transform(choice.begin(), choice.end(), choice.begin(), ::tolower);
        //This is the drain function
        if (choice == "drain"){
            cout << "How much power would you like to drain from the battery in milliampere hours?" << endl;
            cout << "Amount: ";
            cin >> amount;
            Battery.drain(amount);
        }
        //This is the charge function
        else if (choice == "charge"){
            //Goes to the function pretty straight forward
            Battery.charge();
        }
        else {
            //This is just for user error becasuse I'm not expecting them to be perfect
            cout << "Don't understand" << endl;
            cout << endl;
            i--;
        }
        i++;
        cout << "Remaining Charge: " << Battery.get_remaining_capacity() << " mAh" << endl;
    }
    //Ends telling you your remaining capacity
        cout << "\n\nYour batter has " << Battery.get_remaining_capacity() << " mAh remaining after being used." << endl;

    return 0;
}
