#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <iomanip>

using namespace std;
string manager_password = "manager123";
string manager_username = "manager";

// files name : employee.csv, customer.csv, car.csv

// CSV files format ::
// cars database : carId(string), car_name(string), price(int), isAvailable(boolean), returnDate(string), username(string)
// customers database : username(string), name(string), password(string), customer_record(int), no_car_rented(int), car1_id(string/null), car2_id(string/null), car3_id(string/null), car4_id(string/null), car5_id(string/null), dues(int)
// employees database : username(string), name(string), password(string), employee_record(int), no_car_rented(int), car1_id(string/null), car2_id(string/null), car3_id(string/null), car4_id(string/null), car5_id(string/null), dues(int)
int getDaysDifference(string returnDate, string todaysDate)
{
    int dd1 = stoi(returnDate.substr(0, 2));
    int mm1 = stoi(returnDate.substr(3, 2));
    int yyyy1 = stoi(returnDate.substr(6, 4));
    int dd2 = stoi(todaysDate.substr(0, 2));
    int mm2 = stoi(todaysDate.substr(3, 2));
    int yyyy2 = stoi(todaysDate.substr(6, 4));
    int daysDifference = (dd1 - dd2) + (mm1 - mm2) * 30 + (yyyy1 - yyyy2) * 365;
    return (daysDifference);
}
class Car
{
public:
    string carId;
    string car_name;
    int price;
    bool isAvailable;
    string returnDate;
    string username;
    Car(string carId, string car_name, int price, bool isAvailable, string returnDate, string username)
    {
        this->carId = carId;
        this->car_name = car_name;
        this->price = price;
        this->isAvailable = isAvailable;
        this->returnDate = returnDate;
        this->username = username;
    }
};

class User
{
public:
    string username;
    string name;
    string password;
    User(string username, string name, string password)
    {
        this->username = username;
        this->name = name;
        this->password = password;
    }
};

class Customer : public User
{
public:
    string username;
    string name;
    string password;

    Customer(string username, string name, string password) : User(username, name, password)
    {
        this->username = username;
        this->name = name;
        this->password = password;
    }

    void display()
    {
        cout << "Welcome " << this->name << endl;
        cout << "1. Rent a car" << endl;
        cout << "2. Return a car" << endl;
        cout << "3. View rented cars" << endl;
        cout << "4. View dues" << endl;
        cout << "5. Clear dues" << endl;
        int choice;
        cin >> choice;
        if (choice == 1)
        {
            // rent a car
            viewAvailableCars();
            rentCar();
        }
        else if (choice == 2)
        {
            // return a car
            viewRentedCars();
            returnCar();
        }
        else if (choice == 3)
        {
            // view rented cars
            viewRentedCars();
        }
        else if (choice == 4)
        {
            // view dues
            viewDues();
        }
        else if (choice == 5)
        {
            // clear dues
            clearDues();
        }
        else
        {
            cout << "Invalid choice" << endl;
        }

        cout << "Do you want to continue? (y/n): ";
        char ch;
        cin >> ch;
        if (ch == 'y')
        {
            display();
        }
        else
        {
            exit(0);
        }
    }

    // view
    void viewDues()
    {
        ifstream file;
        file.open("customer.csv");
        string line;
        while (getline(file, line))
        {
            stringstream ss(line);
            string username, name, password, customer_record, no_car_rented, car1_id, car2_id, car3_id, car4_id, car5_id, dues;
            getline(ss, username, ',');
            getline(ss, name, ',');
            getline(ss, password, ',');
            getline(ss, customer_record, ',');
            getline(ss, no_car_rented, ',');
            getline(ss, car1_id, ',');
            getline(ss, car2_id, ',');
            getline(ss, car3_id, ',');
            getline(ss, car4_id, ',');
            getline(ss, car5_id, ',');
            getline(ss, dues, ',');
            if (username == this->username)
            {
                cout << "Your dues are: " << dues << endl;
            }
        }
    }

    // clear dues
    void clearDues()
    {
        ifstream file;
        file.open("customer.csv");
        ofstream file1;
        file1.open("temp.csv");
        string line;
        while (getline(file, line))
        {
            stringstream ss(line);
            string username, name, password, customer_record, no_car_rented, car1_id, car2_id, car3_id, car4_id, car5_id, dues;
            getline(ss, username, ',');
            getline(ss, name, ',');
            getline(ss, password, ',');
            getline(ss, customer_record, ',');
            getline(ss, no_car_rented, ',');
            getline(ss, car1_id, ',');
            getline(ss, car2_id, ',');
            getline(ss, car3_id, ',');
            getline(ss, car4_id, ',');
            getline(ss, car5_id, ',');
            getline(ss, dues, ',');
            if (username == this->username)
            {
                file1 << username << "," << name << "," << password << "," << customer_record << "," << no_car_rented << "," << car1_id << "," << car2_id << "," << car3_id << "," << car4_id << "," << car5_id << ",0" << endl;
            }
            else
            {
                file1 << line << endl;
            }
        }
        file.close();
        file1.close();
        remove("customer.csv");
        rename("temp.csv", "customer.csv");
        cout << "Dues cleared successfully" << endl;
    }

    void viewAvailableCars()
    {
        cout << "Available cars are: " << endl;
        ifstream file;
        file.open("car.csv");
        string line;
        while (getline(file, line))
        {
            stringstream ss(line);
            string carId, car_name, price, isAvailable, returnDate, username;
            getline(ss, carId, ',');
            getline(ss, car_name, ',');
            getline(ss, price, ',');
            getline(ss, isAvailable, ',');
            getline(ss, returnDate, ',');
            getline(ss, username, ',');
            if (isAvailable == "1")
            {
                cout << carId << " " << car_name << " " << price << endl;
            }
        }
    }

    // return car : inputs : carId of the car to be returned, and then inputs the date of return
    // then it opens the car.csv file and updates the isAvailable, returnDate, username fields
    // then it opens the customer.csv file and updates the no_car_rented, car1_id, car2_id, car3_id, car4_id, car5_id and dues fields
    void rentCar()
    {
        string carId;
        cout << "Enter carId of the car you want to rent: ";
        cin >> carId;
        cout << "Enter the date of return in dd/mm/yyyy format: ";
        string returnDate_input;
        cin >> returnDate_input;
        string todaysDate;
        cout << "Enter todays date in dd/mm/yyyy format: ";
        cin >> todaysDate;
        ifstream file;

        file.open("car.csv");
        // getting the price and id of the car to be rented
        string line;
        string price;
        string car_id;
        while (getline(file, line))
        {
            stringstream ss(line);
            string carId1, car_name1, price1, isAvailable1, returnDate1, username1;
            getline(ss, carId1, ',');
            getline(ss, car_name1, ',');
            getline(ss, price1, ',');
            getline(ss, isAvailable1, ',');
            getline(ss, returnDate1, ',');
            getline(ss, username1, ',');
            if (carId1 == carId && isAvailable1 == "1")
            {
                price = price1;
                car_id = carId1;
                break;
            }
        }

        // updating the car.csv file
        ifstream file1;
        file1.open("car.csv");
        ofstream file2;
        file2.open("temp.csv");
        string line1;
        while (getline(file1, line1))
        {
            stringstream ss(line1);
            string carId1, car_name1, price1, isAvailable1, returnDate1, username1;
            getline(ss, carId1, ',');
            getline(ss, car_name1, ',');
            getline(ss, price1, ',');
            getline(ss, isAvailable1, ',');
            getline(ss, returnDate1, ',');
            getline(ss, username1, ',');
            if (carId1 == carId)
            {
                isAvailable1 = "0";
                file2 << carId1 << "," << car_name1 << "," << price1 << "," << isAvailable1 << "," << returnDate_input << "," << this->username << endl;
            }
            else
            {
                file2 << line1 << endl;
            }
        }
        file1.close();
        file2.close();
        remove("car.csv");
        rename("temp1.csv", "car.csv");

        // updating the customer.csv file
        ifstream file3;
        file3.open("customer.csv");
        ofstream file4;
        file4.open("temp.csv");
        string line2;
        while (getline(file3, line2))
        {
            stringstream ss(line2);
            string username, name, password, customer_record, no_car_rented, car1_id, car2_id, car3_id, car4_id, car5_id, dues;
            getline(ss, username, ',');
            getline(ss, name, ',');
            getline(ss, password, ',');
            getline(ss, customer_record, ',');
            getline(ss, no_car_rented, ',');
            getline(ss, car1_id, ',');
            getline(ss, car2_id, ',');
            getline(ss, car3_id, ',');
            getline(ss, car4_id, ',');
            getline(ss, car5_id, ',');
            getline(ss, dues, ',');
            if (username == this->username)
            {
                // updating the no_car_rented, car1_id, car2_id, car3_id, car4_id, car5_id and and dues bases on price of the car
                int no_car_rented_int = stoi(no_car_rented);
                no_car_rented_int++;
                if (no_car_rented_int == 1)
                {
                    cout << "hi" << endl;
                    file4 << username << "," << name << "," << password << "," << customer_record << "," << no_car_rented_int << "," << car_id << ",null,null,null,null," << stoi(dues) + stoi(price) * getDaysDifference(returnDate_input, todaysDate) << endl;
                }
                else if (no_car_rented_int == 2)
                {
                    file4 << username << "," << name << "," << password << "," << customer_record << "," << no_car_rented_int << "," << car1_id << "," << car_id << ",null,null,null," << stoi(dues) + stoi(price) * getDaysDifference(returnDate_input, todaysDate) << endl;
                }
                else if (no_car_rented_int == 3)
                {
                    file4 << username << "," << name << "," << password << "," << customer_record << "," << no_car_rented_int << "," << car1_id << "," << car2_id << "," << car_id << ",null,null," << stoi(dues) + stoi(price) * getDaysDifference(returnDate_input, todaysDate) << endl;
                }
                else if (no_car_rented_int == 4)
                {
                    file4 << username << "," << name << "," << password << "," << customer_record << "," << no_car_rented_int << "," << car1_id << "," << car2_id << "," << car3_id << "," << car_id << ",null," << stoi(dues) + stoi(price) * getDaysDifference(returnDate_input, todaysDate) << endl;
                }
                else if (no_car_rented_int == 5)
                {
                    file4 << username << "," << name << "," << password << "," << customer_record << "," << no_car_rented_int << "," << car1_id << "," << car2_id << "," << car3_id << "," << car4_id << "," << car_id << "," << stoi(dues) + stoi(price) * getDaysDifference(returnDate_input, todaysDate) << endl;
                }
            }
            else
            {
                file4 << line2 << endl;
            }
        }
        file3.close();
        file4.close();
        remove("customer.csv");
        rename("temp.csv", "customer.csv");
        cout << "Car rented successfully" << endl;
    }

    // lists down the id, name and price and return date of the cars that are rented by the customer from cars.csv file
    void viewRentedCars()
    {
        ifstream file;
        file.open("car.csv");
        string line;
        while (getline(file, line))
        {
            stringstream ss(line);
            string carId, car_name, price, isAvailable, returnDate, username;
            getline(ss, carId, ',');
            getline(ss, car_name, ',');
            getline(ss, price, ',');
            getline(ss, isAvailable, ',');
            getline(ss, returnDate, ',');
            getline(ss, username, ',');
            if (username == this->username)
            {
                cout << carId << " " << car_name << " " << price << " " << returnDate << endl;
            }
        }
    }

    // getting the days difference between two dates
    int getDaysDifference(string returnDate, string todaysDate)
    {
        int dd1 = stoi(returnDate.substr(0, 2));
        int mm1 = stoi(returnDate.substr(3, 2));
        int yyyy1 = stoi(returnDate.substr(6, 4));
        int dd2 = stoi(todaysDate.substr(0, 2));
        int mm2 = stoi(todaysDate.substr(3, 2));
        int yyyy2 = stoi(todaysDate.substr(6, 4));
        int daysDifference = (dd1 - dd2) + (mm1 - mm2) * 30 + (yyyy1 - yyyy2) * 365;
        return (daysDifference);
    }

    // getting the customer record deductions based on the return date, todays date and the condition of the car
    int getCustomerRecordDeductions(string returnDate, string todaysDate, int choice)
    {

        int daysDifference = getDaysDifference(returnDate, todaysDate);
        int customer_record_deductions = 0;
        if (choice == 1)
        {
            customer_record_deductions += 0;
        }
        else if (choice == 2)
        {
            customer_record_deductions += 1;
        }
        else if (choice == 3)
        {
            customer_record_deductions += 2;
        }

        if (daysDifference > 7)
        {
            customer_record_deductions += 2;
        }
        else if (daysDifference > 3)
        {
            customer_record_deductions += 1;
        }
    }

    // get choice
    int getChoice()
    {
        cout << "Enter your choice: ";
        int choice;
        cin >> choice;
        return choice;
    }

    // return car
    void returnCar()
    {
        string carId;
        cout << "Enter carId of the car you want to return: ";
        cin >> carId;
        cout << "Enter the condition of the car: ";
        cout << "1. Good" << endl;
        cout << "2. Bad" << endl;
        cout << "3. Very Bad" << endl;
        int choice = getChoice();
        cout << "Enter todays date in dd/mm/yyyy format: ";
        string todaysDate;
        cin >> todaysDate;

        // now we will uspdate the car.csv file and make the car available an also get the price of the car and exptected return date
        ifstream file;
        file.open("car.csv");
        string line;
        string price;
        string returnDate;
        while (getline(file, line))
        {
            stringstream ss(line);
            string carId1, car_name1, price1, isAvailable1, returnDate1, username1;
            getline(ss, carId1, ',');
            getline(ss, car_name1, ',');
            getline(ss, price1, ',');
            getline(ss, isAvailable1, ',');
            getline(ss, returnDate1, ',');
            getline(ss, username1, ',');
            if (carId1 == carId)
            {

                price = price1;
                returnDate = returnDate1;
                break;
            }
        }

        // updating the car.csv file
        ifstream file1;
        file1.open("car.csv");
        ofstream file2;
        file2.open("temp.csv");
        string line1;
        while (getline(file1, line1))
        {
            stringstream ss(line1);
            string carId1, car_name1, price1, isAvailable1, returnDate1, username1;
            getline(ss, carId1, ',');
            getline(ss, car_name1, ',');
            getline(ss, price1, ',');
            getline(ss, isAvailable1, ',');
            getline(ss, returnDate1, ',');
            getline(ss, username1, ',');
            if (carId1 == carId)
            {
                file2 << carId1 << "," << car_name1 << "," << price1 << ",1,null,null" << endl;
            }
            else
            {
                file2 << line1 << endl;
            }
        }
        file1.close();
        file2.close();
        remove("car.csv");
        rename("temp.csv", "car.csv");

        int customer_record_deductions = getCustomerRecordDeductions(returnDate, todaysDate, choice);

        // now updating the customer.csv file by updating the no_car_rented, car1_id, car2_id, car3_id, car4_id, car5_id and dues customer_record
        ifstream file3;
        file3.open("customer.csv");
        ofstream file4;
        file4.open("temp.csv");
        string line2;
        while (getline(file3, line2))
        {
            stringstream ss(line2);
            string username, name, password, customer_record, no_car_rented, car1_id, car2_id, car3_id, car4_id, car5_id, dues;
            getline(ss, username, ',');
            getline(ss, name, ',');
            getline(ss, password, ',');
            getline(ss, customer_record, ',');
            getline(ss, no_car_rented, ',');
            getline(ss, car1_id, ',');
            getline(ss, car2_id, ',');
            getline(ss, car3_id, ',');
            getline(ss, car4_id, ',');
            getline(ss, car5_id, ',');
            getline(ss, dues, ',');
            if (username == this->username)
            {
                // updating the no_car_rented, car1_id, car2_id, car3_id, car4_id, car5_id , the customer_record with the deductions and the dues by adding 1000 for minor damages and 2000 for major damages and double price for every extra day
                int no_car_rented_int = stoi(no_car_rented);
                no_car_rented_int--;
                if (no_car_rented_int == 0)
                {
                    file4 << username << "," << name << "," << password << "," << customer_record << "," << no_car_rented_int << ",null,null,null,null,null," << stoi(dues) + 1000 + stoi(price) * getDaysDifference(returnDate, todaysDate) << endl;
                }
                else if (no_car_rented_int == 1)
                {
                    file4 << username << "," << name << "," << password << "," << customer_record << "," << no_car_rented_int << "," << car2_id << ",null,null,null,null," << stoi(dues) + 1000 + stoi(price) * getDaysDifference(returnDate, todaysDate) << endl;
                }
                else if (no_car_rented_int == 2)
                {
                    file4 << username << "," << name << "," << password << "," << customer_record << "," << no_car_rented_int << "," << car2_id << "," << car3_id << ",null,null,null," << stoi(dues) + 1000 + stoi(price) * getDaysDifference(returnDate, todaysDate) << endl;
                }
                else if (no_car_rented_int == 3)
                {
                    file4 << username << "," << name << "," << password << "," << customer_record << "," << no_car_rented_int << "," << car2_id << "," << car3_id << "," << car4_id << ",null,null," << stoi(dues) + 1000 + stoi(price) * getDaysDifference(returnDate, todaysDate) << endl;
                }
                else if (no_car_rented_int == 4)
                {
                    file4 << username << "," << name << "," << password << "," << customer_record << "," << no_car_rented_int << "," << car2_id << "," << car3_id << "," << car4_id << "," << car5_id << ",null," << stoi(dues) + 1000 + stoi(price) * getDaysDifference(returnDate, todaysDate) << endl;
                }
            }
            else
            {
                file4 << line2 << endl;
            }
        }
        file3.close();
        file4.close();
        remove("customer.csv");
        rename("temp.csv", "customer.csv");
        cout << "Car returned successfully" << endl;
    }
};

class Employee : public User
{
public:
    string username;
    string name;
    string password;
    Employee(string username, string name, string password) : User(username, name, password)
    {
        this->username = username;
        this->name = name;
        this->password = password;
    }

    // the employee functions will be same as the customer functions just that here we will open the employees.csv file instead of the customers.csv file and provide extra 15% discount to the employees

    void display()
    {
        cout << "Welcome " << endl;
        cout << "1. Rent a car" << endl;
        cout << "2. Return a car" << endl;
        cout << "3. View rented cars" << endl;
        cout << "4. View dues" << endl;
        cout << "5. Clear dues" << endl;
        int choice;
        cin >> choice;
        if (choice == 1)
        {
            // rent a car
            viewAvailableCars();
            rentCar();
        }
        else if (choice == 2)
        {
            // return a car
            viewRentedCars();
            returnCar();
        }
        else if (choice == 3)
        {
            // view rented cars
            viewRentedCars();
        }
        else if (choice == 4)
        {
            // view dues
            viewDues();
        }
        else if (choice == 5)
        {
            // clear dues
            clearDues();
        }
        else
        {
            cout << "Invalid choice" << endl;
        }

        cout << "Do you want to continue? (y/n): ";
        char ch;
        cin >> ch;
        if (ch == 'y')
        {
            display();
        }
        else
        {
            exit(0);
        }
    }

    void viewDues()
    {
        ifstream file;
        file.open("employee.csv");
        string line;
        while (getline(file, line))
        {
            stringstream ss(line);
            string username, name, password, employee_record, no_car_rented, car1_id, car2_id, car3_id, car4_id, car5_id, dues;
            getline(ss, username, ',');
            getline(ss, name, ',');
            getline(ss, password, ',');
            getline(ss, employee_record, ',');
            getline(ss, no_car_rented, ',');
            getline(ss, car1_id, ',');
            getline(ss, car2_id, ',');
            getline(ss, car3_id, ',');
            getline(ss, car4_id, ',');
            getline(ss, car5_id, ',');
            getline(ss, dues, ',');
            if (username == this->username)
            {
                cout << "Your dues are: " << dues << endl;
            }
        }
    }

    void clearDues()
    {
        ifstream file;
        file.open("employee.csv");
        ofstream file1;
        file1.open("temp.csv");
        string line;
        while (getline(file, line))
        {
            stringstream ss(line);
            string username, name, password, employee_record, no_car_rented, car1_id, car2_id, car3_id, car4_id, car5_id, dues;
            getline(ss, username, ',');
            getline(ss, name, ',');
            getline(ss, password, ',');
            getline(ss, employee_record, ',');
            getline(ss, no_car_rented, ',');
            getline(ss, car1_id, ',');
            getline(ss, car2_id, ',');
            getline(ss, car3_id, ',');
            getline(ss, car4_id, ',');
            getline(ss, car5_id, ',');
            getline(ss, dues, ',');
            if (username == this->username)
            {
                file1 << username << "," << name << "," << password << "," << employee_record << "," << no_car_rented << "," << car1_id << "," << car2_id << "," << car3_id << "," << car4_id << "," << car5_id << ",0" << endl;
            }
            else
            {
                file1 << line << endl;
            }
        }
        file.close();
        file1.close();
        remove("employee.csv");
        rename("temp.csv", "employee.csv");
        cout << "Dues cleared successfully" << endl;
    }

    void viewAvailableCars()
    {
        cout << "Available cars are: " << endl;
        ifstream file;
        file.open("car.csv");
        string line;
        while (getline(file, line))
        {
            stringstream ss(line);
            string carId, car_name, price, isAvailable, returnDate, username;
            getline(ss, carId, ',');
            getline(ss, car_name, ',');
            getline(ss, price, ',');
            getline(ss, isAvailable, ',');
            getline(ss, returnDate, ',');
            getline(ss, username, ',');
            if (isAvailable == "1")
            {
                cout << carId << " " << car_name << " " << price << endl;
            }
        }
    }

    void rentCar()
    {
        string carId;
        cout << "Enter carId of the car you want to rent: ";
        cin >> carId;
        cout << "Enter the date of return in dd/mm/yyyy format: ";
        string returnDate_input;
        cin >> returnDate_input;
        string todaysDate;
        cout << "Enter todays date in dd/mm/yyyy format: ";
        cin >> todaysDate;
        ifstream file;

        file.open("car.csv");
        string line;
        string price;
        string car_id;
        while (getline(file, line))
        {
            stringstream ss(line);
            string carId1, car_name1, price1, isAvailable1, returnDate1, username1;
            getline(ss, carId1, ',');
            getline(ss, car_name1, ',');
            getline(ss, price1, ',');
            getline(ss, isAvailable1, ',');
            getline(ss, returnDate1, ',');
            getline(ss, username1, ',');
            if (carId1 == carId)
            {
                price = price1;
                car_id = carId1;
                break;
            }
        }

        ifstream file1;
        file1.open("car.csv");
        ofstream file2;
        file2.open("temp.csv");
        string line1;
        while (getline(file1, line1))
        {
            stringstream ss(line1);
            string carId1, car_name1, price1, isAvailable1, returnDate1, username1;
            getline(ss, carId1, ',');
            getline(ss, car_name1, ',');
            getline(ss, price1, ',');
            getline(ss, isAvailable1, ',');
            getline(ss, returnDate1, ',');
            getline(ss, username1, ',');
            if (carId1 == carId)
            {
                file2 << carId1 << "," << car_name1 << "," << price1 << ",0," << returnDate_input << "," << this->username << endl;
            }
            else
            {
                file2 << line1 << endl;
            }
        }
        file1.close();
        file2.close();
        remove("car.csv");
        rename("temp.csv", "car.csv");

        ifstream file3;
        file3.open("employee.csv");
        ofstream file4;
        file4.open("temp.csv");
        string line2;
        while (getline(file3, line2))
        {
            stringstream ss(line2);
            string username, name, password, employee_record, no_car_rented, car1_id, car2_id, car3_id, car4_id, car5_id, dues;
            getline(ss, username, ',');
            getline(ss, name, ',');
            getline(ss, password, ',');
            getline(ss, employee_record, ',');
            getline(ss, no_car_rented, ',');
            getline(ss, car1_id, ',');
            getline(ss, car2_id, ',');
            getline(ss, car3_id, ',');
            getline(ss, car4_id, ',');
            getline(ss, car5_id, ',');
            getline(ss, dues, ',');
            if (username == this->username)
            {
                int no_car_rented_int = stoi(no_car_rented);
                no_car_rented_int++;
                if (no_car_rented_int == 1)
                {
                    file4 << username << "," << name << "," << password << "," << employee_record << "," << no_car_rented_int << "," << car_id << ",null,null,null,null," << stoi(dues) + stoi(price) * getDaysDifference(returnDate_input, todaysDate) * 0.85 << endl;
                }
                else if (no_car_rented_int == 2)
                {
                    file4 << username << "," << name << "," << password << "," << employee_record << "," << no_car_rented_int << "," << car1_id << "," << car_id << ",null,null,null," << stoi(dues) + stoi(price) * getDaysDifference(returnDate_input, todaysDate) * 0.85 << endl;
                }
                else if (no_car_rented_int == 3)
                {
                    file4 << username << "," << name << "," << password << "," << employee_record << "," << no_car_rented_int << "," << car1_id << "," << car2_id << "," << car_id << ",null,null," << stoi(dues) + stoi(price) * getDaysDifference(returnDate_input, todaysDate) * 0.85 << endl;
                }
                else if (no_car_rented_int == 4)
                {
                    file4 << username << "," << name << "," << password << "," << employee_record << "," << no_car_rented_int << "," << car1_id << "," << car2_id << "," << car3_id << "," << car_id << ",null," << stoi(dues) + stoi(price) * getDaysDifference(returnDate_input, todaysDate) * 0.85 << endl;
                }
                else if (no_car_rented_int == 5)
                {
                    file4 << username << "," << name << "," << password << "," << employee_record << "," << no_car_rented_int << "," << car1_id << "," << car2_id << "," << car3_id << "," << car4_id << "," << car_id << "," << stoi(dues) + stoi(price) * getDaysDifference(returnDate_input, todaysDate) * 0.85 << endl;
                }
            }
            else
            {
                file4 << line2 << endl;
            }
        }
        file3.close();
        file4.close();
        remove("employee.csv");
        rename("temp.csv", "employee.csv");
        cout << "Car rented successfully" << endl;
    }

    void viewRentedCars()
    {
        ifstream file;
        file.open("car.csv");
        string line;
        while (getline(file, line))
        {
            stringstream ss(line);
            string carId, car_name, price, isAvailable, returnDate, username;
            getline(ss, carId, ',');
            getline(ss, car_name, ',');
            getline(ss, price, ',');
            getline(ss, isAvailable, ',');
            getline(ss, returnDate, ',');
            getline(ss, username, ',');
            if (username == this->username)
            {
                cout << carId << " " << car_name << " " << price << " " << returnDate << endl;
            }
        }
    }

    int getEmployeeRecordDeductions(string returnDate, string todaysDate, int choice)
    {

        int daysDifference = getDaysDifference(returnDate, todaysDate);
        int employee_record_deductions = 0;
        if (choice == 1)
        {
            employee_record_deductions += 0;
        }
        else if (choice == 2)
        {
            employee_record_deductions += 1;
        }
        else if (choice == 3)
        {
            employee_record_deductions += 2;
        }

        if (daysDifference > 7)
        {
            employee_record_deductions += 2;
        }
        else if (daysDifference > 3)
        {
            employee_record_deductions += 1;
        }

        return employee_record_deductions;
    }

    int getChoice()
    {
        cout << "Enter your choice: ";
        int choice;
        cin >> choice;
        return choice;
    }

    void returnCar()
    {
        string carId;
        cout << "Enter carId of the car you want to return: ";
        cin >> carId;
        cout << "Enter the condition of the car: ";
        cout << "1. Good" << endl;
        cout << "2. Bad" << endl;
        cout << "3. Very Bad" << endl;
        int choice = getChoice();
        cout << "Enter todays date in dd/mm/yyyy format: ";
        string todaysDate;
        cin >> todaysDate;

        ifstream file;
        file.open("car.csv");
        string line;
        string price;
        string returnDate;
        while (getline(file, line))
        {
            stringstream ss(line);
            string carId1, car_name1, price1, isAvailable1, returnDate1, username1;
            getline(ss, carId1, ',');
            getline(ss, car_name1, ',');
            getline(ss, price1, ',');
            getline(ss, isAvailable1, ',');
            getline(ss, returnDate1, ',');
            getline(ss, username1, ',');
            if (carId1 == carId)
            {
                price = price1;
                returnDate = returnDate1;
                break;
            }
        }

        ifstream file1;
        file1.open("car.csv");
        ofstream file2;
        file2.open("temp.csv");
        string line1;
        while (getline(file1, line1))
        {
            stringstream ss(line1);
            string carId1, car_name1, price1, isAvailable1, returnDate1, username1;
            getline(ss, carId1, ',');
            getline(ss, car_name1, ',');
            getline(ss, price1, ',');
            getline(ss, isAvailable1, ',');
            getline(ss, returnDate1, ',');
            getline(ss, username1, ',');
            if (carId1 == carId)
            {
                file2 << carId1 << "," << car_name1 << "," << price1 << ",1,null,null" << endl;
            }
            else
            {
                file2 << line1 << endl;
            }
        }
        file1.close();
        file2.close();
        remove("car.csv");
        rename("temp.csv", "car.csv");

        int employee_record_deductions = getEmployeeRecordDeductions(returnDate, todaysDate, choice);

        ifstream file3;
        file3.open("employee.csv");
        ofstream file4;
        file4.open("temp.csv");
        string line2;
        while (getline(file3, line2))
        {
            stringstream ss(line2);
            string username, name, password, employee_record, no_car_rented, car1_id, car2_id, car3_id, car4_id, car5_id, dues;
            getline(ss, username, ',');
            getline(ss, name, ',');
            getline(ss, password, ',');
            getline(ss, employee_record, ',');
            getline(ss, no_car_rented, ',');
            getline(ss, car1_id, ',');
            getline(ss, car2_id, ',');
            getline(ss, car3_id, ',');
            getline(ss, car4_id, ',');
            getline(ss, car5_id, ',');
            getline(ss, dues, ',');
            if (username == this->username)
            {
                int no_car_rented_int = stoi(no_car_rented);
                no_car_rented_int--;
                if (no_car_rented_int == 0)
                {
                    file4 << username << "," << name << "," << password << "," << employee_record << "," << no_car_rented_int << ",null,null,null,null,null," << stoi(dues) + 1000 + stoi(price) * getDaysDifference(returnDate, todaysDate) * 0.85 << endl;
                }
                else if (no_car_rented_int == 1)
                {
                    file4 << username << "," << name << "," << password << "," << employee_record << "," << no_car_rented_int << "," << car2_id << ",null,null,null,null," << stoi(dues) + 1000 + stoi(price) * getDaysDifference(returnDate, todaysDate) * 0.85 << endl;
                }
                else if (no_car_rented_int == 2)
                {
                    file4 << username << "," << name << "," << password << "," << employee_record << "," << no_car_rented_int << "," << car2_id << "," << car3_id << ",null,null,null," << stoi(dues) + 1000 + stoi(price) * getDaysDifference(returnDate, todaysDate) * 0.85 << endl;
                }
                else if (no_car_rented_int == 3)
                {
                    file4 << username << "," << name << "," << password << "," << employee_record << "," << no_car_rented_int << "," << car2_id << "," << car3_id << "," << car4_id << ",null,null," << stoi(dues) + 1000 + stoi(price) * getDaysDifference(returnDate, todaysDate) * 0.85 << endl;
                }
                else if (no_car_rented_int == 4)
                {
                    file4 << username << "," << name << "," << password << "," << employee_record << "," << no_car_rented_int << "," << car2_id << "," << car3_id << "," << car4_id << "," << car5_id << ",null," << stoi(dues) + 1000 + stoi(price) * getDaysDifference(returnDate, todaysDate) * 0.85 << endl;
                }
            }
            else
            {
                file4 << line2 << endl;
            }
        }
        file3.close();
        file4.close();
        remove("employee.csv");
        rename("temp.csv", "employee.csv");
        cout << "Car returned successfully" << endl;
    }
};

class Manager
{
public:
    string username;
    string name;
    string password;
    Manager(string username, string name, string password)
    {
        this->username = username;
        this->name = name;
        this->password = password;
    }

    void display()
    {
        cout << "Welcome " << endl;
        cout << "1. Add a car" << endl;
        cout << "2. Remove a car" << endl;
        cout << "3. View all cars" << endl;
        cout << "4. View all customers" << endl;
        cout << "5. View all employees" << endl;
        cout << "6. Remove a customer" << endl;
        cout << "7. Remove an employee" << endl;
        cout << " 8. Add an employee" << endl;
        cout << " 9. Add a customer" << endl;

        int choice;
        cin >> choice;
        if (choice == 1)
        {
            // add a car
            addCar();
        }
        else if (choice == 2)
        {
            // remove a car
            removeCar();
        }
        else if (choice == 3)
        {
            // view all cars
            viewAllCars();
        }
        else if (choice == 4)
        {
            // view all customers
            viewAllCustomers();
        }
        else if (choice == 5)
        {
            // view all employees
            viewAllEmployees();
        }
        else if (choice == 6)
        {
            // remove a customer
            removeCustomer();
        }
        else if (choice == 7)
        {
            // remove an employee
            removeEmployee();
        }
        else if (choice == 8)
        {
            // add an employee
            addEmployee();
        }
        else if (choice == 9)
        {
            // add a customer
            addCustomer();
        }
        else
        {
            cout << "Invalid choice" << endl;
        }
    }

    bool checkIfCustomerHasRentedCars(string username)
    {
        ifstream file;
        file.open("customer.csv");
        string line;
        while (getline(file, line))
        {
            stringstream ss(line);
            string username1, name, password, customer_record, no_car_rented, car1_id, car2_id, car3_id, car4_id, car5_id, dues;
            getline(ss, username1, ',');
            getline(ss, name, ',');
            getline(ss, password, ',');
            getline(ss, customer_record, ',');
            getline(ss, no_car_rented, ',');
            getline(ss, car1_id, ',');
            getline(ss, car2_id, ',');
            getline(ss, car3_id, ',');
            getline(ss, car4_id, ',');
            getline(ss, car5_id, ',');
            getline(ss, dues, ',');
            if (username1 == username && no_car_rented != "0")
            {
                return true;
            }
        }
        return false;
    }

    void addEmployee()
    {
        string username, name, password;
        cout << "Enter username: ";
        cin >> username;
        cout << "Enter name: ";
        cin >> name;
        cout << "Enter password: ";
        cin >> password;
        ofstream file;
        file.open("employee.csv", ios::app);
        file << username << "," << name << "," << password << ",0,0,null,null,null,null,null,0" << endl;
        file.close();
        cout << "Employee added successfully" << endl;
    }

    void addCustomer()
    {
        string username, name, password;
        cout << "Enter username: ";
        cin >> username;
        cout << "Enter name: ";
        cin >> name;
        cout << "Enter password: ";
        cin >> password;
        ofstream file;
        file.open("customer.csv", ios::app);
        file << username << "," << name << "," << password << ",0,0,null,null,null,null,null,0" << endl;
        file.close();
        cout << "Customer added successfully" << endl;
    }

    void removeCustomer()
    {
        string username;
        cout << "Enter username of the customer you want to remove: ";
        cin >> username;

        bool checkIfCustomerHasRentedCars_ = checkIfCustomerHasRentedCars(username);

        if (checkIfCustomerHasRentedCars_)
        {
            cout << "Customer has rented cars" << endl;
            return;
        }

        ifstream file;
        file.open("customer.csv");
        ofstream file1;
        file1.open("temp.csv");
        string line;
        while (getline(file, line))
        {
            stringstream ss(line);
            string username1, name, password, customer_record, no_car_rented, car1_id, car2_id, car3_id, car4_id, car5_id, dues;
            getline(ss, username1, ',');
            getline(ss, name, ',');
            getline(ss, password, ',');
            getline(ss, customer_record, ',');
            getline(ss, no_car_rented, ',');
            getline(ss, car1_id, ',');
            getline(ss, car2_id, ',');
            getline(ss, car3_id, ',');
            getline(ss, car4_id, ',');
            getline(ss, car5_id, ',');
            getline(ss, dues, ',');
            if (username1 != username)
            {
                file1 << line << endl;
            }
        }
        file.close();
        file1.close();
        remove("customer.csv");
        rename("temp.csv", "customer.csv");
        cout << "Customer removed successfully" << endl;
    }

    bool checkIfEmployeeHasRentedCars(string username)
    {
        ifstream file;
        file.open("employee.csv");
        string line;
        while (getline(file, line))
        {
            stringstream ss(line);
            string username1, name, password, employee_record, no_car_rented, car1_id, car2_id, car3_id, car4_id, car5_id, dues;
            getline(ss, username1, ',');
            getline(ss, name, ',');
            getline(ss, password, ',');
            getline(ss, employee_record, ',');
            getline(ss, no_car_rented, ',');
            getline(ss, car1_id, ',');
            getline(ss, car2_id, ',');
            getline(ss, car3_id, ',');
            getline(ss, car4_id, ',');
            getline(ss, car5_id, ',');
            getline(ss, dues, ',');
            if (username1 == username && no_car_rented != "0")
            {
                return true;
            }
        }
        return false;
    }

    void removeEmployee()
    {
        string username;
        cout << "Enter username of the employee you want to remove: ";
        cin >> username;

        bool checkIfEmployeeHasRentedCars_ = checkIfEmployeeHasRentedCars(username);
        if (checkIfEmployeeHasRentedCars_)
        {
            cout << "Employee has rented cars" << endl;
            return;
        }

        ifstream file;
        file.open("employee.csv");
        ofstream file1;
        file1.open("temp.csv");
        string line;
        while (getline(file, line))
        {
            stringstream ss(line);
            string username1, name, password, employee_record, no_car_rented, car1_id, car2_id, car3_id, car4_id, car5_id, dues;
            getline(ss, username1, ',');
            getline(ss, name, ',');
            getline(ss, password, ',');
            getline(ss, employee_record, ',');
            getline(ss, no_car_rented, ',');
            getline(ss, car1_id, ',');
            getline(ss, car2_id, ',');
            getline(ss, car3_id, ',');
            getline(ss, car4_id, ',');
            getline(ss, car5_id, ',');
            getline(ss, dues, ',');
            if (username1 != username)
            {
                file1 << line << endl;
            }
        }
        file.close();
        file1.close();
        remove("employee.csv");
        rename("temp.csv", "employee.csv");
        cout << "Employee removed successfully" << endl;
    }

    bool checkIfUniqueId(string carId)
    {
        ifstream file;
        file.open("car.csv");
        string line;
        while (getline(file, line))
        {
            stringstream ss(line);
            string carId1, car_name1, price1, isAvailable1, returnDate1, username1;
            getline(ss, carId1, ',');
            getline(ss, car_name1, ',');
            getline(ss, price1, ',');
            getline(ss, isAvailable1, ',');
            getline(ss, returnDate1, ',');
            getline(ss, username1, ',');
            if (carId1 == carId)
            {
                return false;
            }
        }
        return true;
    }

    bool checkIfCarIsRented(string carId)
    {
        ifstream file;
        file.open("car.csv");
        string line;
        while (getline(file, line))
        {
            stringstream ss(line);
            string carId1, car_name1, price1, isAvailable1, returnDate1, username1;
            getline(ss, carId1, ',');
            getline(ss, car_name1, ',');
            getline(ss, price1, ',');
            getline(ss, isAvailable1, ',');
            getline(ss, returnDate1, ',');
            getline(ss, username1, ',');
            if (carId1 == carId && isAvailable1 == "0")
            {
                return true;
            }
        }
        return false;
    }

    void addCar()
    {
        string carId, car_name, price;
        cout << "Enter carId: ";
        cin >> carId;
        cout << "Enter car name: ";
        cin >> car_name;
        cout << "Enter price: ";
        cin >> price;

        bool checkIfUnique = checkIfUniqueId(carId);
        if (!checkIfUnique)
        {
            cout << "CarId already exists" << endl;
            return;
        }

        ofstream file;
        file.open("car.csv", ios::app);
        file << carId << "," << car_name << "," << price << ",1,null,null" << endl;
        file.close();
        cout << "Car added successfully" << endl;
    }

    void removeCar()
    {
        string carId;
        cout << "Enter carId of the car you want to remove: ";
        cin >> carId;
        ifstream file;
        file.open("car.csv");

        bool checkIfCarIsRented_ = checkIfCarIsRented(carId);
        if (checkIfCarIsRented_)
        {
            cout << "Car is rented" << endl;
            return;
        }

        ofstream file1;
        file1.open("temp.csv");
        string line;
        while (getline(file, line))
        {
            stringstream ss(line);
            string carId1, car_name1, price1, isAvailable1, returnDate1, username1;
            getline(ss, carId1, ',');
            getline(ss, car_name1, ',');
            getline(ss, price1, ',');
            getline(ss, isAvailable1, ',');
            getline(ss, returnDate1, ',');
            getline(ss, username1, ',');
            if (carId1 != carId)
            {
                file1 << line << endl;
            }
        }
        file.close();
        file1.close();
        remove("car.csv");
        rename("temp.csv", "car.csv");
        cout << "Car removed successfully" << endl;
    }

    void viewAllCars()
    {
        ifstream file;
        file.open("car.csv");
        string line;
        while (getline(file, line))
        {
            stringstream ss(line);
            string carId, car_name, price, isAvailable, returnDate, username;
            getline(ss, carId, ',');
            getline(ss, car_name, ',');
            getline(ss, price, ',');
            getline(ss, isAvailable, ',');
            getline(ss, returnDate, ',');
            getline(ss, username, ',');
            cout << carId << " " << car_name << " " << price << " " << isAvailable << " " << returnDate << " " << username << endl;
        }
    }

    void viewAllCustomers()
    {
        ifstream file;
        file.open("customer.csv");
        string line;
        while (getline(file, line))
        {
            stringstream ss(line);
            string username, name, password, customer_record, no_car_rented, car1_id, car2_id, car3_id, car4_id, car5_id, dues;
            getline(ss, username, ',');
            getline(ss, name, ',');
            getline(ss, password, ',');
            getline(ss, customer_record, ',');
            getline(ss, no_car_rented, ',');
            getline(ss, car1_id, ',');
            getline(ss, car2_id, ',');
            getline(ss, car3_id, ',');
            getline(ss, car4_id, ',');
            getline(ss, car5_id, ',');
            getline(ss, dues, ',');
            cout << username << " " << name << " " << password << " " << customer_record << " " << no_car_rented << " " << car1_id << " " << car2_id << " " << car3_id << " " << car4_id << " " << car5_id << " " << dues << endl;
        }
    }

    void viewAllEmployees()
    {
        ifstream file;
        file.open("employee.csv");
        string line;
        while (getline(file, line))
        {
            stringstream ss(line);
            string username, name, password, employee_record, no_car_rented, car1_id, car2_id, car3_id, car4_id, car5_id, dues;
            getline(ss, username, ',');
            getline(ss, name, ',');
            getline(ss, password, ',');
            getline(ss, employee_record, ',');
            getline(ss, no_car_rented, ',');
            getline(ss, car1_id, ',');
            getline(ss, car2_id, ',');
            getline(ss, car3_id, ',');
            getline(ss, car4_id, ',');
            getline(ss, car5_id, ',');
            getline(ss, dues, ',');
            cout << username << " " << name << " " << password << " " << employee_record << " " << no_car_rented << " " << car1_id << " " << car2_id << " " << car3_id << " " << car4_id << " " << car5_id << " " << dues << endl;
        }
    }
};

int getChoice()
{
    cout << "Enter your choice: ";
    int choice;
    cin >> choice;
    return choice;
}

// signup as customer
// inputs : username, name, password and add to the customer.csv file
void signup_customer()
{
    string username, name, password;
    cout << "Enter username: ";
    cin >> username;
    cout << "Enter name: ";
    cin >> name;
    cout << "Enter password: ";
    cin >> password;

    ofstream file;
    file.open("customer.csv", ios::app);
    file << username << "," << name << "," << password << ",10,0,null,null,null,null,null,0" << endl;
    file.close();
    cout << "Signup successful" << endl;
}

// signup as employee
// inputs : username, name, password and add to the employee.csv file
void signup_employee()
{
    string username, name, password;
    cout << "Enter username: ";
    cin >> username;
    cout << "Enter name: ";
    cin >> name;
    cout << "Enter password: ";
    cin >> password;

    ofstream file;
    file.open("employee.csv", ios::app);
    file << username << "," << name << "," << password << ",10,0,null,null,null,null,null,0" << endl;
    file.close();
    cout << "Signup successful" << endl;
}

string getUsername()
{
    string name;
    cout << "Enter your username: ";
    cin >> name;
    return name;
}

string getPassword()
{
    string password;
    cout << "Enter your password: ";
    cin >> password;
    return password;
}

bool verifyCustomer(string username, string password)
{
    ifstream file;
    file.open("customer.csv");
    string line;
    while (getline(file, line))
    {
        stringstream ss(line);
        string username1, name1, password1;
        getline(ss, username1, ',');
        getline(ss, name1, ',');
        getline(ss, password1, ',');
        if (username1 == username && password1 == password)
        {
            return true;
        }
    }
    file.close();
    return false;
}

bool verifyEmployee(string username, string password)
{
    ifstream file;
    file.open("employee.csv");
    string line;
    while (getline(file, line))
    {
        stringstream ss(line);
        string username1, name1, password1;
        getline(ss, username1, ',');
        getline(ss, name1, ',');
        getline(ss, password1, ',');
        if (username1 == username && password1 == password)
        {
            return true;
        }
    }
    file.close();
    return false;
}

void login_signup_page()
{
    cout << "Welcome to the car rental system" << endl;
    cout << "1. Login as Employee" << endl;
    cout << "2. Login as Customer" << endl;
    cout << "3. Signup as Customer" << endl;
    cout << "4. Signup as Employee" << endl;
    cout << "5. Login as Manager" << endl;
    cout << "5. Exit" << endl;

    int choice = getChoice();
    if (choice == 1)
    {
        // login as employee
        string username = getUsername();
        string password = getPassword();
        if (verifyEmployee(username, password))
        {
            cout << "Login successful" << endl;
            Employee employee(username, "null", password);
            employee.display();
        }
        else
        {
            cout << "Login failed, Invalid details" << endl;
        }
        // login_employee();
    }
    else if (choice == 2)
    {
        // login as customer
        string username = getUsername();
        string password = getPassword();
        if (verifyCustomer(username, password))
        {
            cout << "Login successful" << endl;
            Customer customer(username, "null", password);
            customer.display();
        }
        else
        {
            cout << "Login failed, Invalid details" << endl;
        }
        // login_customer();
    }
    else if (choice == 3)
    {
        // signup as customer
        signup_customer();
    }
    else if (choice == 4)
    {
        // signup as employee
        signup_employee();
    }
    else if (choice == 5)
    {
        // login as manager
        string username = getUsername();
        string password = getPassword();

        if (username == manager_username && password == manager_password)
        {
            cout << "Login successful" << endl;
            Manager manager(username, "null", password);
            manager.display();
        }
        else
        {
            cout << "Login failed, Invalid details" << endl;
        }
    }
    else if (choice == 6)
    {
        // exit
        exit(0);
    }
    else
    {
        cout << "Invalid choice" << endl;
    }

    cout << "Do you want to continue? (y/n): ";
    char ch;
    cin >> ch;
    if (ch == 'y')
    {
        login_signup_page();
    }
    else
    {
        exit(0);
    }
}

// main function
int main()
{

    login_signup_page();
    // Your code for interacting with the database and implementing the system goes here

    return 0;
}
