/*Project id: Group 1 Project A   
      Project Name: Cash Register
      Programmer: Ben Sprankle
      Tester: Ben Sprankle
      Date: Febuary 10, 2025
      Version: 5.1  (Final Version)
      Description: This program defines a Cash Register class that runs manages and closes the store.
      */

// These are my libraries that I used to create the program
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <cctype>

using namespace std;

//This is the class that I created for the cash register
class CashRegister
{
private:
    //These are the variables that I used in the class
    vector<double> prices;
    vector<string> items;
    double total_price;
    double total_sales;
    double total_scount;
    double total_tax;
    double tax;
    double subtotal;
    double tax_rate;
public:
    //This is my constructor for the class
    CashRegister(vector<double> prices, vector<string> items, double total_price, double total_sales, double total_scount, double total_tax, double tax, double subtotal, double tax_rate);
    //These are my function
    void add_item(string item, double price, double tax_rate);
    void clear();
    int get_count();
    void display_all();
    void add_taxable_item(string item, double price, double tax_rate);
    double get_total_tax();
    double get_sales_total();
    double get_sales_count();
    void reset_sales();
};

CashRegister::CashRegister(vector<double> prices, vector<string> items, double total_price, double total_sales, double total_scount, double total_tax, double tax, double subtotal, double tax_rate)
{
    //Reinitializes the variables helps them work
    this->prices = prices;
    this->items = items;
    this->total_price = total_price;
    this->total_sales = total_sales;
    this->total_scount = total_scount;
    this->total_tax = total_tax;
    this->tax = tax;
    this->subtotal = subtotal;
    this->tax_rate = tax_rate;
    cout << "Cash Register Created" << endl;
    cout << endl;
}

//This is the function that adds an item to the cash register
void CashRegister::add_item(string item, double price, double tax_rate){
    string d;
    //This limits which items are taxable
    cout << "Is this item taxable?: ";
    cin >> d;
    //lowercase for ease of use
    transform(d.begin(), d.end(), d.begin(), ::tolower);
    if (d == "yes" || d == "yep" || d == "sure"){
        add_taxable_item(item, price, tax_rate);
    } 
    //adds to vectors
    items.push_back(item);
    subtotal += price;
    prices.push_back(price);
}

void CashRegister::clear(){
    //clears the vectors
    items.clear();
    prices.clear();
}

int CashRegister::get_count(){
    //returns the size of the vector
    return items.size();
}

void CashRegister::display_all(){
    //displays all the items in the vector
    cout << "\n\n\nThere are " << get_count() << " items" << endl;
    for (int i = 0; i < items.size(); i++){
        cout << items[i] << " " << prices[i] << endl;
    }
    cout << "\n\n Subtotal: " << subtotal << endl;
    cout << "Tax: " << tax << endl;
    //Keeps it only in cents not hundreths place
    cout << fixed << setprecision(2);
    cout << "Total: " << subtotal + tax << endl;
    cout << endl << endl << endl;
    total_sales += subtotal;
    total_scount++;
}

void CashRegister::add_taxable_item(string item, double price, double tax_rate){
    //adds tax to the total
    tax += price * (tax_rate / 100);
    total_tax += tax;
}

double CashRegister::get_total_tax(){
    //returns the total tax
    return total_tax;
}

double CashRegister::get_sales_total(){
    //returns the total sales
    return total_sales;
}

double CashRegister::get_sales_count(){
    //returns the total sales count
    return total_scount;
}

void CashRegister::reset_sales(){
    //resets the sales
    total_sales = 0;
    total_scount = 0;
    total_tax = 0;
}

int main(){
    //These are the variables that I used in the main function
    vector<double> prices;
    vector<string> items;
    double item_count = 0;
    double price = 0;
    double total_price = 0;
    double total_sales = 0;
    double total_scount = 0;
    double total_tax = 0;
    double tax = 0;
    double subtotal = 0;
    double tax_rate = 0;
    string choice = "";
    string choice2 = "";
    string choice3 = "";
    string item = "";
    
    //This clears the screen for ease of use
    cout << "\033[2J\033[1;1H";
    cout << "Welcome to the Cash Register" << endl;

    //This is the input for the tax rate
    cout << "What is the Tax Rate?: ";
    cin >> tax_rate;

    //This is the creation of the cash register
    CashRegister cashRegister(prices, items, total_price, total_sales, total_scount, total_tax, tax, subtotal, tax_rate);
    cout << endl;

    //This is the loop that runs the program
    while (choice != "Close")
    {
        cout << "What would you like to do today?" << endl;
        //This is the input for the user
        cout << "(Close, Manage, Run): ";
        cin >> choice;
        if (choice == "Run"){
            tax = 0;
            //This is the loop that runs the program
            while (choice2 != "charge"){
                cout << "Add or Charge?: ";
                cin >> choice2;
                //lowercase for ease of use
                transform(choice2.begin(), choice2.end(), choice2.begin(), ::tolower);
                cout << endl;
                if (choice2 == "add"){
                    cout << "Item Name: ";
                    cin >> item;
                    cout << "Item Cost: ";
                    cin >> price;
                    cashRegister.add_item(item, price, tax_rate);
                }
                else if (choice2 == "charge"){
                    cashRegister.display_all();
                }
                else if (choice2 != "charge" || choice2 != "add"){
                    cout << "Don't understand" << endl;
                }
            }
        }
        //This is the manage function
        else if (choice == "Manage"){
            cout << "Here's what we have so far today: " << endl;
            cout << "Sales Count: " << cashRegister.get_sales_count() << endl;
            cout << "Sales Total: " << cashRegister.get_sales_total() << endl;
            cout << "Total Tax: " << cashRegister.get_total_tax() << endl;
            cout << "\n\nWould you like to restart the day?: ";
            cin >> choice3;
            //lowercase for ease of use
            transform(choice3.begin(), choice3.end(), choice3.begin(), ::tolower);
            if (choice3 == "yes"){
                cashRegister.reset_sales();
            }
        }
    }
    //This is the closing line
    cout << "Thank you!\nGoodbye" << endl;
    return 0;
}
