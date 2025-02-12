/*Project id: Group 1 Project A   
      Project Name: Person and Friends`
      Programmer: Ben Sprankle
      Tester: Ben Sprankle
      Date: Febuary 5, 2025
      Version: 4.3  (Final Version)
      Description: This program defines a Person class where each person has a name and a list of friends.
      Which can be added or subtracted from the total
      */

// These are my libraries that I used to create the program
#include <iostream>
#include <string>
#include <sstream>
#include <ostream>
#include <vector>
using namespace std;

// This is my class of person
class Person
{
private:
// These are the variables that I used in the class
    string name;
// I actually made this a vector originally because it made it simpler then realized that it was part of the assignment
    vector<string> friend_names;
    double fc;
public:
// These are the functions that I used in the class
    Person(string name, double fc, vector<string> freind_names);
    void befriend(string p);
    void unfriend(string p);
    vector<string> get_friend_names();
    double get_fc();
};

// This is the main constructor for the class that creates the person and inizializes the variables
Person::Person(string name, double fc, vector<string> friend_names)
{
    cout << "Person created" << endl;
    cout << endl;
}

// This is the function that adds a friend of your choice
void Person::befriend(string p)
{
    friend_names.push_back(p);
    cout << "Person befriended" << endl;
    cout << endl;
}

// This is the function that removes friends which I had alot of trouble with
void Person::unfriend(string p)
{
// After researching I found using auto in this format allows the eaiest way to remove a specific friend
    for (auto i = friend_names.begin(); i != friend_names.end(); i++)
    {
        if (*i == p)
        {
        // The return is used to stop the loop so that it doesnt accidentaly remove the wrong friend, which it was doing before
            friend_names.erase(i);
            cout << "Person unfriended" << endl;
            cout << endl;
            return;
            // I could've used break however I do not fully understand the difference between the two
        }
    }
    cout << "Person not found" << endl;
    cout << endl;
}

// This is the vector that returns the friends names vector which we have built with the rest of the functions
vector<string> Person::get_friend_names()
{   
    return friend_names;
    // Pretty simple function that returns the vector
}

// This just counts all the names in the vector and returns the number of friends
double Person::get_fc()
{
    fc = friend_names.size();
    return fc;
    // Again very simple just uses .size() to count the number of friends
}



int main()
{
    // These are the variables that I used in the main function
    string name;
    string operation;
    string fname;
    vector<string> friend_names = vector<string>();
    double fc;
    int i = 0;
    int fnum = 0;
    // This is for my ease it clears the screen so that the user can't see the previous inputs but if I scroll up I can see them. It helps with me knowing which thing is the most recent
    cout << "\033[2J\033[1;1H";
    cout << "What is your name? ";
    cin >> name;
    cout << endl;
    // This sets how many times the loop will run
    cout << "How many friends do we need to evaluate? ";
    cin >> fnum;
    // creates the person
    Person person(name, 0, vector<string>());
    // loop that runs the amount of times the user inputed
    while (i < fnum){
        // helps you know where you are in the loop
        cout << "#" << i+1 << " Befriend or Unfriend? ";
        cin >> operation;
        // makes it all lowercase so that the user can input it in any way they want
        transform(operation.begin(), operation.end(), operation.begin(), ::tolower);
        
        // This is the befriend function
        if (operation == "befriend"){
            cout << "What is the friends name? ";
            cin >> fname;
            person.befriend(fname);
        }
        
        // This is the unfriend function
        else if (operation == "unfriend"){
            cout << "What is the friends name? ";
            cin >> fname;
            person.unfriend(fname);
        }
        
        // incase they dont spell it right or do the wrong thing
        else if (operation != "unfriend" || operation != "befriend"){
            cout << "Don't understand" << endl;
            cout << endl;
            i--;
        }
        i++;
    }
    cout << endl;
    cout << name + " you have " << person.get_fc() << " friends. They are: " << endl;
    // This is the loop that prints out all the friends
    for (int i = 0; i < person.get_friend_names().size(); i++)
    {
        // Prints them all out with a space seperating them
        cout << person.get_friend_names()[i] << " ";
    }

    // Return 0 because thats how you end the int main.
    return 0;
}
