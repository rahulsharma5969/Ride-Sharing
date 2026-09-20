#ifndef DRIVER_H
#define DRIVER_H

#include "User.h"
#include <vector>
#include <iostream>

/**
 * @brief Derived class representing a driver on the platform.
 * Demonstrates Inheritance, Encapsulation, and Polymorphism.
 */
class Driver : public User {
private:
    std::string vehicleMake;
    std::string vehicleModel;
    std::string licensePlate;
    int vehicleCapacity;
    bool isAvailable;
    std::string currentLocation;
    double totalEarnings;
    std::vector<int> rideHistory;

public:
    Driver(int id, const std::string& name, const std::string& phone,
           const std::string& make, const std::string& model,
           const std::string& plate, int capacity, const std::string& location = "Downtown")
        : User(id, name, phone), vehicleMake(make), vehicleModel(model),
          licensePlate(plate), vehicleCapacity(capacity), isAvailable(true),
          currentLocation(location), totalEarnings(0.0) {}

    // Getters & Setters
    std::string getVehicleMake() const { return vehicleMake; }
    std::string getVehicleModel() const { return vehicleModel; }
    std::string getLicensePlate() const { return licensePlate; }
    int getVehicleCapacity() const { return vehicleCapacity; }
    bool getIsAvailable() const { return isAvailable; }
    std::string getCurrentLocation() const { return currentLocation; }
    double getTotalEarnings() const { return totalEarnings; }
    const std::vector<int>& getRideHistory() const { return rideHistory; }

    void setAvailable(bool status) { isAvailable = status; }
    void setCurrentLocation(const std::string& loc) { currentLocation = loc; }

    void toggleAvailability() {
        isAvailable = !isAvailable;
        std::cout << "[Driver System] Driver " << name << " is now "
                  << (isAvailable ? "AVAILABLE" : "OFFLINE") << ".\n";
    }

    void addEarnings(double amount) {
        if (amount > 0) {
            totalEarnings += amount;
        }
    }

    void addRideToHistory(int rideId) {
        rideHistory.push_back(rideId);
    }

    // Overridden Virtual Functions (Polymorphism)
    void displayProfile() const override {
        std::cout << "========================================\n";
        std::cout << " DRIVER PROFILE (ID: #" << id << ")\n";
        std::cout << "========================================\n";
        std::cout << " Name           : " << name << "\n";
        std::cout << " Phone          : " << phone << "\n";
        std::cout << " Vehicle        : " << vehicleMake << " " << vehicleModel << " (" << licensePlate << ")\n";
        std::cout << " Capacity       : " << vehicleCapacity << " seats\n";
        std::cout << " Location       : " << currentLocation << "\n";
        std::cout << " Status         : " << (isAvailable ? "ONLINE / AVAILABLE" : "OFFLINE") << "\n";
        std::cout << " Rating         : " << std::fixed << std::setprecision(1) << rating << " / 5.0 (" << totalRatings << " ratings)\n";
        std::cout << " Total Earnings : $" << std::fixed << std::setprecision(2) << totalEarnings << "\n";
        std::cout << " Completed Rides: " << rideHistory.size() << "\n";
        std::cout << "========================================\n";
    }

    std::string getRole() const override {
        return "Driver";
    }
};

#endif // DRIVER_H
