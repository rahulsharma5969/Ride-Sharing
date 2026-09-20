#ifndef RIDER_H
#define RIDER_H

#include "User.h"
#include <vector>
#include <iostream>

/**
 * @brief Derived class representing a passenger/rider on the platform.
 * Demonstrates Inheritance and Encapsulation.
 */
class Rider : public User {
private:
    double walletBalance;
    std::vector<int> rideHistory; // List of Ride IDs

public:
    Rider(int id, const std::string& name, const std::string& phone, double initialBalance = 0.0)
        : User(id, name, phone), walletBalance(initialBalance) {}

    // Wallet Operations
    double getWalletBalance() const { return walletBalance; }

    void addFunds(double amount) {
        if (amount > 0) {
            walletBalance += amount;
            std::cout << "[Wallet] Successfully added $" << std::fixed << std::setprecision(2)
                      << amount << ". New balance: $" << walletBalance << "\n";
        }
    }

    bool deductFunds(double amount) {
        if (amount <= 0) return false;
        if (walletBalance >= amount) {
            walletBalance -= amount;
            return true;
        }
        return false;
    }

    // Ride History
    void addRideToHistory(int rideId) {
        rideHistory.push_back(rideId);
    }

    const std::vector<int>& getRideHistory() const {
        return rideHistory;
    }

    // Overridden Virtual Functions (Polymorphism)
    void displayProfile() const override {
        std::cout << "========================================\n";
        std::cout << " RIDER PROFILE (ID: #" << id << ")\n";
        std::cout << "========================================\n";
        std::cout << " Name           : " << name << "\n";
        std::cout << " Phone          : " << phone << "\n";
        std::cout << " Rating         : " << std::fixed << std::setprecision(1) << rating << " / 5.0 (" << totalRatings << " ratings)\n";
        std::cout << " Wallet Balance : $" << std::fixed << std::setprecision(2) << walletBalance << "\n";
        std::cout << " Total Rides    : " << rideHistory.size() << "\n";
        std::cout << "========================================\n";
    }

    std::string getRole() const override {
        return "Rider";
    }
};

#endif // RIDER_H
