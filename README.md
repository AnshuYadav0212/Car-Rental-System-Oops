# Car-Rental-System-Oops
This is the repository for the Car Rental System using Object Oriented Programming Concepts in Course Cs253

## Overview
This program is a car rental system that allows customers and employees to rent and return cars, view and clear dues, and manage rental records. The manager has additional capabilities to add, delete, and update cars, customers, and employees, as well as view their records.

## Classes
### Car
- **Fields**: `carId`, `car_name`, `price`, `isAvailable`, `returnDate`, `username`

### User
- **Fields**: `username`, `name`, `password`

### Customer (inherits from User)
- **Fields**: `username`, `name`, `password`
- **Functions**:
  - `display()`
  - `viewDues()`
  - `clearDues()`
  - `viewAvailableCars()`
  - `rentCar()`
  - `viewRentedCars()`
  - `getDaysDifference()`
  - `getCustomerRecordDeductions()`
  - `getChoice()`
  - `returnCar()`

### Employee (inherits from User)
- **Fields**: `username`, `name`, `password`
- **Functions**:
  - `display()`
  - `viewDues()`
  - `clearDues()`
  - `viewAvailableCars()`
  - `rentCar()`
  - `viewRentedCars()`
  - `getDaysDifference()`
  - `getEmployeeRecordDeductions()`
  - `getChoice()`
  - `returnCar()`

## CSV Files
- **car.csv**: `carId (string)`, `car_name (string)`, `price (int)`, `isAvailable (boolean)`, `returnDate (string)`, `username (string)`
- **customer.csv**: `username (string)`, `name (string)`, `password (string)`, `customer_record (int)`, `no_car_rented (int)`, `car1_id (string/null)`, `car2_id (string/null)`, `car3_id (string/null)`, `car4_id (string/null)`, `car5_id (string/null)`, `dues (int)`
- **employee.csv**: `username (string)`, `name (string)`, `password (string)`, `employee_record (int)`, `no_car_rented (int)`, `car1_id (string/null)`, `car2_id (string/null)`, `car3_id (string/null)`, `car4_id (string/null)`, `car5_id (string/null)`, `dues (int)`

## User Types
### Manager
- **Username**: `manager`
- **Password**: `manager123`

### Customer
- **Functions**:
  - Rent a car
  - Return a car
  - View rented cars
  - View dues
  - Clear dues

### Employee
- **Functions**:
  - Rent a car
  - Return a car
  - View rented cars
  - View dues
  - Clear dues

### Manager Functions
- Add a car
- Delete a car
- Update a car
- Add a customer
- Delete a customer
- Update a customer
- Add an employee
- Delete an employee
- Update an employee

## Data Handling
- The system uses CSV files to store and update data for cars, customers, and employees.
- Data is updated in the CSV files after every operation.

## Program Workflow
### Login/Signup
1. **Manager**: Login with the manager username and password.
2. **Customer**: Login with their username and password.
3. **Employee**: Login with their username and password.
4. **New Customer**: Signup with a username, name, and password.
5. **New Employee**: Signup with a username, name, and password.

### Employee Display
1. Rent a car
2. Return a car
3. View rented cars
4. View dues
5. Clear dues

### Customer Display
1. Rent a car
2. Return a car
3. View rented cars
4. View dues
5. Clear dues

### Manager Display
1. Add a car
2. Delete a car
3. Update a car
4. Add a customer
5. Delete a customer
6. Update a customer
7. Add an employee
8. Delete an employee
9. Update an employee

## Dues and Records
- Dues and records of customers and employees are updated after every operation.
- Cars are made available again after being returned.
- Dues are cleared by customers and employees, updating the dues to 0 in the CSV files.
