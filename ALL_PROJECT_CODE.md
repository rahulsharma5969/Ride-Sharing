# Ride-Sharing Application — All Project Files Consolidated

This document contains the complete source code, configuration, and documentation of the entire Ride-Sharing Application C++ project in a single file.

---

## Table of Contents
1. [CMakeLists.txt](file:///c:/Users/devso/oop/CMakeLists.txt)
2. [README.md](file:///c:/Users/devso/oop/README.md)
3. [include/User.h](file:///c:/Users/devso/oop/include/User.h)
4. [include/Rider.h](file:///c:/Users/devso/oop/include/Rider.h)
5. [include/Driver.h](file:///c:/Users/devso/oop/include/Driver.h)
6. [include/RideType.h](file:///c:/Users/devso/oop/include/RideType.h)
7. [include/Ride.h](file:///c:/Users/devso/oop/include/Ride.h)
8. [include/RideManager.h](file:///c:/Users/devso/oop/include/RideManager.h)
9. [include/MenuUI.h](file:///c:/Users/devso/oop/include/MenuUI.h)
10. [src/main.cpp](file:///c:/Users/devso/oop/src/main.cpp)
11. [src/RideManager.cpp](file:///c:/Users/devso/oop/src/RideManager.cpp)
12. [src/MenuUI.cpp](file:///c:/Users/devso/oop/src/MenuUI.cpp)

---

## 1. CMakeLists.txt

```cmake
cmake_minimum_required(VERSION 3.10)
project(RideSharingApp VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

file(GLOB SOURCES
    "src/*.cpp"
)

add_executable(ride_sharing_app ${SOURCES})
```

---

## 2. README.md

```markdown
# Ride-Sharing Platform Simulator (C++ & Object-Oriented Programming)

A modular, extensible C++ application simulating a modern ride-sharing platform (akin to Uber / Lyft). Built using Object-Oriented Design principles including **Inheritance**, **Polymorphism**, **Encapsulation**, and **Abstraction**.

---

## 🌟 Key Features & OOP Architecture

### 1. **Inheritance & Hierarchy**
- **User Base Class (`User`)**: Abstract base class representing any platform participant. Extended by:
  - `Rider`: Holds passenger profile, wallet balance, transaction logic, and trip history.
  - `Driver`: Holds driver profile, vehicle details, seating capacity, availability toggle, and total earnings.
- **Ride Category Base Class (`RideType`)**: Abstract pricing strategy base class. Extended by:
  - `EconomyRide`: Standard fare structure ($3.00 base, $1.20/km, $0.25/min).
  - `LuxuryRide`: Premium luxury experience ($7.50 base + $5.00 luxury fee, $2.50/km, $0.60/min).
  - `BikeRide`: Fast single-rider urban transport ($1.50 base, $0.80/km, 10% eco-discount).
  - `XLRide`: Extra capacity 6-seater ($5.00 base, $1.80/km, $0.40/min).

### 2. **Polymorphism & Dynamic Dispatch**
- **Fare Engine**: `RideType::calculateFare(distance, duration, surge)` is pure virtual, enabling custom pricing algorithms per ride category (e.g., eco-discounts for bikes, flat luxury fees, capacity adjustments).
- **User Display**: Overridden `displayProfile()` and `getRole()` functions for dynamic runtime behavior.

### 3. **Encapsulation & Data Protection**
- Internal state variables (wallets, earnings, trip statuses, average ratings) are strictly private or protected.
- Controlled transactions: Funds deduction validates sufficient balance before confirming rides; dynamic average rating recalculations ensure numerical boundaries ($1.0 - 5.0$).

### 4. **Abstraction & System Controller Facade**
- `RideManager`: Serves as the central manager orchestrating rider registration, driver matching, ride lifecycle (`REQUESTED` -> `ACCEPTED` -> `IN_PROGRESS` -> `COMPLETED`), wallet payouts, platform fees (20%), and analytics.
- `MenuUI`: High-level CLI interface isolating user input/output from domain business logic.

---

## 📁 Repository Directory Layout

```
c:\Users\devso\oop\
├── CMakeLists.txt         # CMake build configuration script
├── README.md              # Project documentation and guide
├── include/               # C++ Header files
│   ├── User.h             # Abstract Base User class
│   ├── Rider.h            # Rider (Passenger) derived class
│   ├── Driver.h           # Driver derived class
│   ├── RideType.h         # Polymorphic Ride Category hierarchy
│   ├── Ride.h             # Ride Session & Receipt management
│   ├── RideManager.h      # System Controller / Platform Manager
│   └── MenuUI.h           # Menu-driven CLI Interface header
└── src/                   # C++ Implementation source files
    ├── RideManager.cpp    # Platform management implementation
    ├── MenuUI.cpp         # Menu interface implementation
    └── main.cpp           # Main application entry point
```

---

## 🚀 How to Build and Run

### Option 1: Direct g++ / clang++ Compilation
```bash
g++ -std=c++17 -Iinclude src/RideManager.cpp src/MenuUI.cpp src/main.cpp -o ride_sharing_app
./ride_sharing_app
```

### Option 2: Using CMake
```bash
mkdir build
cd build
cmake ..
cmake --build .
./ride_sharing_app
```

---

## 🎮 Interactive Menu Options

1. **Rider Portal**:
   - Register new riders with custom initial deposits.
   - View profile, ratings, and wallet balance.
   - Add funds to wallet.
   - View available ride options & live pricing tiers.
   - Book rides with custom pickup/dropoff, distance, duration, and surge multiplier.
   - Rate drivers after trip completion.
   - View complete ride history receipts.

2. **Driver Portal**:
   - Register new drivers with vehicle details & seat capacity.
   - View earnings, rating, and location.
   - Toggle online / offline availability.
   - Accept ride requests, progress trip states, and collect payouts.
   - Rate riders.

3. **Admin Dashboard**:
   - View overall platform revenue, commission earnings, and ride status breakdown.
   - Inspect all registered riders, drivers, and ride receipts.
   - Run custom fare calculator / estimator.

4. **Automated End-to-End Simulation**:
   - One-click showcase demonstrating registration, fare calculation, surge pricing, driver matching, trip completion, payment distribution, and rating exchange.
```

---

## 3. include/User.h

```cpp
#ifndef USER_H
#define USER_H

#include <string>
#include <iostream>
#include <iomanip>

/**
 * @brief Abstract Base Class representing a general User in the Ride Sharing Platform.
 * Demonstrates Abstraction and Encapsulation.
 */
class User {
protected:
    int id;
    std::string name;
    std::string phone;
    double rating;
    int totalRatings;

public:
    User(int id, const std::string& name, const std::string& phone)
        : id(id), name(name), phone(phone), rating(5.0), totalRatings(1) {}

    virtual ~User() = default;

    // Getters
    int getId() const { return id; }
    std::string getName() const { return name; }
    std::string getPhone() const { return phone; }
    double getRating() const { return rating; }
    int getTotalRatings() const { return totalRatings; }

    // Setters
    void setName(const std::string& newName) { name = newName; }
    void setPhone(const std::string& newPhone) { phone = newPhone; }

    /**
     * @brief Updates the user's average rating dynamically.
     */
    void addRating(double newRating) {
        if (newRating < 1.0) newRating = 1.0;
        if (newRating > 5.0) newRating = 5.0;
        
        double totalScore = (rating * totalRatings) + newRating;
        totalRatings++;
        rating = totalScore / totalRatings;
    }

    // Pure Virtual Functions (Polymorphism & Abstraction)
    virtual void displayProfile() const = 0;
    virtual std::string getRole() const = 0;
};

#endif // USER_H
```

---

## 4. include/Rider.h

```cpp
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
```

---

## 5. include/Driver.h

```cpp
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
```

---

## 6. include/RideType.h

```cpp
#ifndef RIDE_TYPE_H
#define RIDE_TYPE_H

#include <string>
#include <iostream>
#include <iomanip>

/**
 * @brief Abstract Base Class for Fare Calculation Strategy and Ride Categories.
 * Demonstrates Polymorphism and Strategy Pattern via inheritance.
 */
class RideType {
protected:
    std::string typeName;
    double baseFare;
    double perKmRate;
    double perMinuteRate;
    int maxCapacity;

public:
    RideType(const std::string& name, double base, double perKm, double perMin, int capacity)
        : typeName(name), baseFare(base), perKmRate(perKm), perMinuteRate(perMin), maxCapacity(capacity) {}

    virtual ~RideType() = default;

    // Getters
    std::string getTypeName() const { return typeName; }
    double getBaseFare() const { return baseFare; }
    double getPerKmRate() const { return perKmRate; }
    double getPerMinuteRate() const { return perMinuteRate; }
    int getMaxCapacity() const { return maxCapacity; }

    /**
     * @brief Pure Virtual Function calculating fare dynamically.
     * Overridden in derived classes for custom pricing rules (surges, luxury fees, discounts).
     */
    virtual double calculateFare(double distanceKm, double durationMin, double surgeMultiplier = 1.0) const = 0;

    virtual void displayInfo() const {
        std::cout << std::left << std::setw(12) << typeName
                  << " | Base: $" << std::setw(5) << std::fixed << std::setprecision(2) << baseFare
                  << " | $" << std::setw(4) << perKmRate << "/km"
                  << " | $" << std::setw(4) << perMinuteRate << "/min"
                  << " | Seats: " << maxCapacity << "\n";
    }
};

/**
 * @brief Economy Ride - standard affordable option.
 */
class EconomyRide : public RideType {
public:
    EconomyRide() : RideType("Economy", 3.00, 1.20, 0.25, 4) {}

    double calculateFare(double distanceKm, double durationMin, double surgeMultiplier = 1.0) const override {
        double rawFare = baseFare + (distanceKm * perKmRate) + (durationMin * perMinuteRate);
        return rawFare * surgeMultiplier;
    }
};

/**
 * @brief Luxury Ride - premium vehicle with high comfort & complimentary amenities.
 */
class LuxuryRide : public RideType {
private:
    double luxuryFee;

public:
    LuxuryRide() : RideType("Luxury", 7.50, 2.50, 0.60, 4), luxuryFee(5.00) {}

    double calculateFare(double distanceKm, double durationMin, double surgeMultiplier = 1.0) const override {
        double rawFare = baseFare + luxuryFee + (distanceKm * perKmRate) + (durationMin * perMinuteRate);
        return rawFare * surgeMultiplier;
    }

    void displayInfo() const override {
        std::cout << std::left << std::setw(12) << typeName
                  << " | Base: $" << std::setw(5) << std::fixed << std::setprecision(2) << baseFare
                  << " (+$" << luxuryFee << " Lux Fee)"
                  << " | $" << std::setw(4) << perKmRate << "/km"
                  << " | $" << std::setw(4) << perMinuteRate << "/min"
                  << " | Seats: " << maxCapacity << "\n";
    }
};

/**
 * @brief Bike Ride - fast single rider option for urban traffic.
 */
class BikeRide : public RideType {
public:
    BikeRide() : RideType("Bike", 1.50, 0.80, 0.15, 1) {}

    double calculateFare(double distanceKm, double durationMin, double surgeMultiplier = 1.0) const override {
        double rawFare = baseFare + (distanceKm * perKmRate) + (durationMin * perMinuteRate);
        // Bikes get 10% eco-discount
        return (rawFare * 0.90) * surgeMultiplier;
    }
};

/**
 * @brief XL Ride - large vehicle for up to 6 passengers or heavy luggage.
 */
class XLRide : public RideType {
public:
    XLRide() : RideType("Ride XL", 5.00, 1.80, 0.40, 6) {}

    double calculateFare(double distanceKm, double durationMin, double surgeMultiplier = 1.0) const override {
        double rawFare = baseFare + (distanceKm * perKmRate) + (durationMin * perMinuteRate);
        return rawFare * surgeMultiplier;
    }
};

#endif // RIDE_TYPE_H
```

---

## 7. include/Ride.h

```cpp
#ifndef RIDE_H
#define RIDE_H

#include <string>
#include <iostream>
#include <iomanip>

enum class RideStatus {
    REQUESTED,
    ACCEPTED,
    IN_PROGRESS,
    COMPLETED,
    CANCELLED
};

inline std::string statusToString(RideStatus status) {
    switch (status) {
        case RideStatus::REQUESTED:   return "REQUESTED";
        case RideStatus::ACCEPTED:    return "ACCEPTED";
        case RideStatus::IN_PROGRESS: return "IN_PROGRESS";
        case RideStatus::COMPLETED:   return "COMPLETED";
        case RideStatus::CANCELLED:   return "CANCELLED";
    }
    return "UNKNOWN";
}

/**
 * @brief Class representing a Ride transaction and lifecycle on the platform.
 * Encapsulates ride state, location data, timing, fare, and rating feedback.
 */
class Ride {
private:
    int rideId;
    int riderId;
    int driverId; // -1 if unassigned
    std::string riderName;
    std::string driverName;
    std::string rideTypeName;
    std::string pickupLocation;
    std::string dropoffLocation;
    double distanceKm;
    double durationMin;
    double fare;
    RideStatus status;
    double riderRatingGiven;  // Rating given by driver to rider
    double driverRatingGiven; // Rating given by rider to driver

public:
    Ride(int rideId, int riderId, const std::string& riderName,
         const std::string& typeName, const std::string& pickup,
         const std::string& dropoff, double distance, double duration, double fare)
        : rideId(rideId), riderId(riderId), driverId(-1), riderName(riderName),
          driverName("Unassigned"), rideTypeName(typeName), pickupLocation(pickup),
          dropoffLocation(dropoff), distanceKm(distance), durationMin(duration),
          fare(fare), status(RideStatus::REQUESTED), riderRatingGiven(0.0), driverRatingGiven(0.0) {}

    // Getters
    int getRideId() const { return rideId; }
    int getRiderId() const { return riderId; }
    int getDriverId() const { return driverId; }
    std::string getRiderName() const { return riderName; }
    std::string getDriverName() const { return driverName; }
    std::string getRideTypeName() const { return rideTypeName; }
    std::string getPickupLocation() const { return pickupLocation; }
    std::string getDropoffLocation() const { return dropoffLocation; }
    double getDistanceKm() const { return distanceKm; }
    double getDurationMin() const { return durationMin; }
    double getFare() const { return fare; }
    RideStatus getStatus() const { return status; }
    double getRiderRatingGiven() const { return riderRatingGiven; }
    double getDriverRatingGiven() const { return driverRatingGiven; }

    // State Transitions
    void assignDriver(int dId, const std::string& dName) {
        driverId = dId;
        driverName = dName;
        status = RideStatus::ACCEPTED;
    }

    void startTrip() {
        if (status == RideStatus::ACCEPTED) {
            status = RideStatus::IN_PROGRESS;
        }
    }

    void completeTrip() {
        if (status == RideStatus::IN_PROGRESS || status == RideStatus::ACCEPTED) {
            status = RideStatus::COMPLETED;
        }
    }

    void cancelTrip() {
        status = RideStatus::CANCELLED;
    }

    void setDriverRatingGiven(double rating) { driverRatingGiven = rating; }
    void setRiderRatingGiven(double rating) { riderRatingGiven = rating; }

    void displayReceipt() const {
        std::cout << "=====================================================\n";
        std::cout << "               RIDE RECEIPT / SUMMARY                \n";
        std::cout << "=====================================================\n";
        std::cout << " Ride ID          : #" << rideId << "\n";
        std::cout << " Status           : " << statusToString(status) << "\n";
        std::cout << " Ride Category    : " << rideTypeName << "\n";
        std::cout << " Rider            : " << riderName << " (ID: #" << riderId << ")\n";
        std::cout << " Driver           : " << driverName << " (ID: #" << (driverId == -1 ? 0 : driverId) << ")\n";
        std::cout << " Route            : " << pickupLocation << " -> " << dropoffLocation << "\n";
        std::cout << " Distance / Time  : " << std::fixed << std::setprecision(1)
                  << distanceKm << " km / " << durationMin << " mins\n";
        std::cout << " Total Fare       : $" << std::fixed << std::setprecision(2) << fare << "\n";
        if (driverRatingGiven > 0) {
            std::cout << " Rider's Rating   : " << std::fixed << std::setprecision(1) << driverRatingGiven << " Stars\n";
        }
        if (riderRatingGiven > 0) {
            std::cout << " Driver's Rating  : " << std::fixed << std::setprecision(1) << riderRatingGiven << " Stars\n";
        }
        std::cout << "=====================================================\n";
    }
};

#endif // RIDE_H
```

---

## 8. include/RideManager.h

```cpp
#ifndef RIDE_MANAGER_H
#define RIDE_MANAGER_H

#include "Rider.h"
#include "Driver.h"
#include "RideType.h"
#include "Ride.h"

#include <unordered_map>
#include <vector>
#include <memory>
#include <string>

/**
 * @brief System Controller/Facade managing overall platform operations.
 * Coordinates ride creation, driver matching, transaction processing, and system analytics.
 */
class RideManager {
private:
    std::unordered_map<int, std::shared_ptr<Rider>> riders;
    std::unordered_map<int, std::shared_ptr<Driver>> drivers;
    std::unordered_map<std::string, std::shared_ptr<RideType>> rideTypes;
    std::vector<std::shared_ptr<Ride>> rides;

    int nextRiderId;
    int nextDriverId;
    int nextRideId;

    double platformCommissionRate; // e.g. 0.20 (20%)
    double totalPlatformRevenue;

public:
    RideManager();

    // Seeding & Setup
    void seedDemoData();

    // User Registration
    std::shared_ptr<Rider> registerRider(const std::string& name, const std::string& phone, double initialDeposit = 50.0);
    std::shared_ptr<Driver> registerDriver(const std::string& name, const std::string& phone,
                                            const std::string& make, const std::string& model,
                                            const std::string& plate, int capacity, const std::string& location = "Downtown");

    // Lookups
    std::shared_ptr<Rider> getRider(int riderId);
    std::shared_ptr<Driver> getDriver(int driverId);
    std::shared_ptr<Ride> getRide(int rideId);
    std::shared_ptr<RideType> getRideType(const std::string& typeName);

    const std::unordered_map<int, std::shared_ptr<Rider>>& getAllRiders() const { return riders; }
    const std::unordered_map<int, std::shared_ptr<Driver>>& getAllDrivers() const { return drivers; }
    const std::vector<std::shared_ptr<Ride>>& getAllRides() const { return rides; }

    // Fare Estimation & Ride Types Display
    void displayAvailableRideTypes() const;
    double estimateFare(const std::string& typeName, double distanceKm, double durationMin, double surge = 1.0) const;

    // Driver Matching Algorithm
    std::shared_ptr<Driver> findMatchingDriver(const std::string& location, int requiredCapacity);

    // Ride Lifecycle Management
    std::shared_ptr<Ride> requestRide(int riderId, const std::string& typeName,
                                      const std::string& pickup, const std::string& dropoff,
                                      double distanceKm, double durationMin, double surge = 1.0);

    bool acceptRide(int rideId, int driverId);
    bool startTrip(int rideId);
    bool completeTrip(int rideId);
    bool cancelRide(int rideId);

    // Feedback & Ratings
    bool rateDriver(int rideId, double stars);
    bool rateRider(int rideId, double stars);

    // Platform Analytics
    void displaySystemStats() const;
};

#endif // RIDE_MANAGER_H
```

---

## 9. include/MenuUI.h

```cpp
#ifndef MENU_UI_H
#define MENU_UI_H

#include "RideManager.h"
#include <iostream>
#include <limits>

/**
 * @brief Menu-driven Console UI for interacting with the Ride Sharing Platform.
 */
class MenuUI {
private:
    RideManager manager;

    // Helper functions for user input
    int getIntInput(const std::string& prompt);
    double getDoubleInput(const std::string& prompt);
    std::string getStringInput(const std::string& prompt);

    // Sub-menus
    void riderMenu();
    void driverMenu();
    void adminMenu();
    void runAutomatedDemo();

public:
    MenuUI();
    void start();
};

#endif // MENU_UI_H
```

---

## 10. src/main.cpp

```cpp
#include "../include/MenuUI.h"
#include <iostream>

int main() {
    try {
        MenuUI ui;
        ui.start();
    } catch (const std::exception& e) {
        std::cerr << "[Fatal Error] Exception caught in main: " << e.what() << std::endl;
        return 1;
    } catch (...) {
        std::cerr << "[Fatal Error] Unknown error occurred." << std::endl;
        return 1;
    }
    return 0;
}
```

---

## 11. src/RideManager.cpp

```cpp
#include "../include/RideManager.h"
#include <iostream>
#include <algorithm>

RideManager::RideManager()
    : nextRiderId(101), nextDriverId(201), nextRideId(1001),
      platformCommissionRate(0.20), totalPlatformRevenue(0.0) {
    
    // Register polymorphic ride types
    rideTypes["Economy"] = std::make_shared<EconomyRide>();
    rideTypes["Luxury"]  = std::make_shared<LuxuryRide>();
    rideTypes["Bike"]    = std::make_shared<BikeRide>();
    rideTypes["XL"]      = std::make_shared<XLRide>();
}

void RideManager::seedDemoData() {
    // Register Demo Riders
    auto r1 = registerRider("Alice Smith", "+1-555-0101", 120.00);
    auto r2 = registerRider("Bob Jones", "+1-555-0102", 75.50);
    auto r3 = registerRider("Charlie Brown", "+1-555-0103", 200.00);

    // Register Demo Drivers
    auto d1 = registerDriver("David Miller", "+1-555-0201", "Toyota", "Camry", "XYZ-1234", 4, "Downtown");
    auto d2 = registerDriver("Emma Watson", "+1-555-0202", "Tesla", "Model S", "ELEC-777", 4, "Downtown");
    auto d3 = registerDriver("Frank Castle", "+1-555-0203", "Honda", "Civic", "PUN-9900", 4, "Uptown");
    auto d4 = registerDriver("Grace Hopper", "+1-555-0204", "Ford", "Explorer", "SUV-8800", 6, "Airport");
    auto d5 = registerDriver("Hank Pym", "+1-555-0205", "Yamaha", "R15 Bike", "MTR-1122", 1, "Suburbs");

    // Add rating history for realism
    d1->addRating(4.8); d1->addRating(5.0);
    d2->addRating(5.0); d2->addRating(4.9);
    d3->addRating(4.5);
    d4->addRating(4.9);
    d5->addRating(4.7);

    // Simulate completed demo rides
    auto ride1 = requestRide(r1->getId(), "Economy", "Downtown", "Uptown", 8.5, 18.0, 1.0);
    if (ride1) {
        acceptRide(ride1->getRideId(), d1->getId());
        startTrip(ride1->getRideId());
        completeTrip(ride1->getRideId());
        rateDriver(ride1->getRideId(), 5.0);
        rateRider(ride1->getRideId(), 5.0);
    }

    auto ride2 = requestRide(r2->getId(), "Luxury", "Downtown", "Airport", 22.0, 35.0, 1.25);
    if (ride2) {
        acceptRide(ride2->getRideId(), d2->getId());
        startTrip(ride2->getRideId());
        completeTrip(ride2->getRideId());
        rateDriver(ride2->getRideId(), 5.0);
        rateRider(ride2->getRideId(), 4.8);
    }

    std::cout << "[System Setup] Demo data successfully initialized with Riders, Drivers, and Historical Rides.\n";
}

std::shared_ptr<Rider> RideManager::registerRider(const std::string& name, const std::string& phone, double initialDeposit) {
    int id = nextRiderId++;
    auto rider = std::make_shared<Rider>(id, name, phone, initialDeposit);
    riders[id] = rider;
    return rider;
}

std::shared_ptr<Driver> RideManager::registerDriver(const std::string& name, const std::string& phone,
                                                     const std::string& make, const std::string& model,
                                                     const std::string& plate, int capacity, const std::string& location) {
    int id = nextDriverId++;
    auto driver = std::make_shared<Driver>(id, name, phone, make, model, plate, capacity, location);
    drivers[id] = driver;
    return driver;
}

std::shared_ptr<Rider> RideManager::getRider(int riderId) {
    auto it = riders.find(riderId);
    return (it != riders.end()) ? it->second : nullptr;
}

std::shared_ptr<Driver> RideManager::getDriver(int driverId) {
    auto it = drivers.find(driverId);
    return (it != drivers.end()) ? it->second : nullptr;
}

std::shared_ptr<Ride> RideManager::getRide(int rideId) {
    for (auto& ride : rides) {
        if (ride->getRideId() == rideId) return ride;
    }
    return nullptr;
}

std::shared_ptr<RideType> RideManager::getRideType(const std::string& typeName) {
    auto it = rideTypes.find(typeName);
    return (it != rideTypes.end()) ? it->second : nullptr;
}

void RideManager::displayAvailableRideTypes() const {
    std::cout << "\n---------------------------------------------------------------\n";
    std::cout << " AVAILABLE RIDE CATEGORIES & FARE STRUCTURE                    \n";
    std::cout << "---------------------------------------------------------------\n";
    for (const auto& pair : rideTypes) {
        pair.second->displayInfo();
    }
    std::cout << "---------------------------------------------------------------\n";
}

double RideManager::estimateFare(const std::string& typeName, double distanceKm, double durationMin, double surge) const {
    auto it = rideTypes.find(typeName);
    if (it != rideTypes.end()) {
        return it->second->calculateFare(distanceKm, durationMin, surge);
    }
    return 0.0;
}

std::shared_ptr<Driver> RideManager::findMatchingDriver(const std::string& location, int requiredCapacity) {
    // 1. Try to match location & capacity first
    for (auto& pair : drivers) {
        auto driver = pair.second;
        if (driver->getIsAvailable() && 
            driver->getVehicleCapacity() >= requiredCapacity && 
            driver->getCurrentLocation() == location) {
            return driver;
        }
    }
    // 2. Fallback: Any available driver with suitable capacity
    for (auto& pair : drivers) {
        auto driver = pair.second;
        if (driver->getIsAvailable() && driver->getVehicleCapacity() >= requiredCapacity) {
            return driver;
        }
    }
    return nullptr;
}

std::shared_ptr<Ride> RideManager::requestRide(int riderId, const std::string& typeName,
                                               const std::string& pickup, const std::string& dropoff,
                                               double distanceKm, double durationMin, double surge) {
    auto rider = getRider(riderId);
    if (!rider) {
        std::cout << "[Error] Rider ID #" << riderId << " not found.\n";
        return nullptr;
    }

    auto rideType = getRideType(typeName);
    if (!rideType) {
        std::cout << "[Error] Invalid Ride Category: " << typeName << "\n";
        return nullptr;
    }

    double fare = rideType->calculateFare(distanceKm, durationMin, surge);
    if (rider->getWalletBalance() < fare) {
        std::cout << "[Error] Insufficient wallet balance ($" << std::fixed << std::setprecision(2)
                  << rider->getWalletBalance() << "). Fare estimate: $" << fare << ".\n";
        return nullptr;
    }

    int rideId = nextRideId++;
    auto ride = std::make_shared<Ride>(rideId, riderId, rider->getName(), typeName, pickup, dropoff, distanceKm, durationMin, fare);
    rides.push_back(ride);
    rider->addRideToHistory(rideId);

    std::cout << "[Ride Requested] Ride #" << rideId << " created! Pickup: " << pickup
              << " -> Dropoff: " << dropoff << " | Estimated Fare: $" << std::fixed << std::setprecision(2) << fare << "\n";

    // Automatic matching attempt
    auto driver = findMatchingDriver(pickup, rideType->getMaxCapacity());
    if (driver) {
        acceptRide(rideId, driver->getId());
    } else {
        std::cout << "[Driver Dispatch] Searching for nearby drivers... Currently pending acceptance.\n";
    }

    return ride;
}

bool RideManager::acceptRide(int rideId, int driverId) {
    auto ride = getRide(rideId);
    auto driver = getDriver(driverId);

    if (!ride || !driver) return false;
    if (!driver->getIsAvailable()) {
        std::cout << "[Match Error] Driver #" << driverId << " is currently offline or busy.\n";
        return false;
    }

    ride->assignDriver(driverId, driver->getName());
    driver->setAvailable(false);

    std::cout << "[Ride Match] Driver " << driver->getName() << " (Vehicle: "
              << driver->getVehicleMake() << " " << driver->getVehicleModel() << ", Plate: "
              << driver->getLicensePlate() << ") accepted Ride #" << rideId << "!\n";
    return true;
}

bool RideManager::startTrip(int rideId) {
    auto ride = getRide(rideId);
    if (ride && ride->getStatus() == RideStatus::ACCEPTED) {
        ride->startTrip();
        std::cout << "[Trip Status] Ride #" << rideId << " is now IN PROGRESS.\n";
        return true;
    }
    return false;
}

bool RideManager::completeTrip(int rideId) {
    auto ride = getRide(rideId);
    if (!ride) return false;

    if (ride->getStatus() != RideStatus::IN_PROGRESS && ride->getStatus() != RideStatus::ACCEPTED) {
        std::cout << "[Error] Cannot complete ride #" << rideId << " because it is not active.\n";
        return false;
    }

    auto rider = getRider(ride->getRiderId());
    auto driver = getDriver(ride->getDriverId());

    if (!rider || !driver) return false;

    double fare = ride->getFare();
    if (!rider->deductFunds(fare)) {
        std::cout << "[Payment Error] Payment deduction failed for Rider #" << rider->getId() << ".\n";
        return false;
    }

    double platformFee = fare * platformCommissionRate;
    double driverPayout = fare - platformFee;

    driver->addEarnings(driverPayout);
    driver->addRideToHistory(rideId);
    driver->setAvailable(true);
    driver->setCurrentLocation(ride->getDropoffLocation());

    totalPlatformRevenue += platformFee;

    ride->completeTrip();

    std::cout << "[Trip Completed] Ride #" << rideId << " finished successfully!\n";
    std::cout << "                 Payment Processed: $" << std::fixed << std::setprecision(2) << fare << "\n";
    std::cout << "                 Driver Payout    : $" << driverPayout << "\n";
    std::cout << "                 Platform Fee     : $" << platformFee << "\n";

    return true;
}

bool RideManager::cancelRide(int rideId) {
    auto ride = getRide(rideId);
    if (!ride) return false;

    if (ride->getStatus() == RideStatus::COMPLETED || ride->getStatus() == RideStatus::CANCELLED) {
        std::cout << "[Error] Cannot cancel Ride #" << rideId << " in its current status.\n";
        return false;
    }

    if (ride->getDriverId() != -1) {
        auto driver = getDriver(ride->getDriverId());
        if (driver) {
            driver->setAvailable(true);
        }
    }

    ride->cancelTrip();
    std::cout << "[Trip Status] Ride #" << rideId << " has been CANCELLED.\n";
    return true;
}

bool RideManager::rateDriver(int rideId, double stars) {
    auto ride = getRide(rideId);
    if (!ride || ride->getStatus() != RideStatus::COMPLETED) return false;

    auto driver = getDriver(ride->getDriverId());
    if (driver) {
        driver->addRating(stars);
        ride->setDriverRatingGiven(stars);
        std::cout << "[Feedback] Rating of " << stars << " stars submitted for Driver " << driver->getName() << ".\n";
        return true;
    }
    return false;
}

bool RideManager::rateRider(int rideId, double stars) {
    auto ride = getRide(rideId);
    if (!ride || ride->getStatus() != RideStatus::COMPLETED) return false;

    auto rider = getRider(ride->getRiderId());
    if (rider) {
        rider->addRating(stars);
        ride->setRiderRatingGiven(stars);
        std::cout << "[Feedback] Rating of " << stars << " stars submitted for Rider " << rider->getName() << ".\n";
        return true;
    }
    return false;
}

void RideManager::displaySystemStats() const {
    std::cout << "=====================================================\n";
    std::cout << "          PLATFORM DASHBOARD & SYSTEM ANALYTICS       \n";
    std::cout << "=====================================================\n";
    std::cout << " Total Registered Riders : " << riders.size() << "\n";
    std::cout << " Total Registered Drivers: " << drivers.size() << "\n";
    std::cout << " Total Rides Processed   : " << rides.size() << "\n";
    std::cout << " Total Platform Revenue  : $" << std::fixed << std::setprecision(2) << totalPlatformRevenue << "\n";
    
    int completedCount = 0;
    int cancelledCount = 0;
    int activeCount = 0;

    for (const auto& r : rides) {
        if (r->getStatus() == RideStatus::COMPLETED) completedCount++;
        else if (r->getStatus() == RideStatus::CANCELLED) cancelledCount++;
        else activeCount++;
    }

    std::cout << " Completed Rides        : " << completedCount << "\n";
    std::cout << " Active Rides           : " << activeCount << "\n";
    std::cout << " Cancelled Rides        : " << cancelledCount << "\n";
    std::cout << "=====================================================\n";
}
```

---

## 12. src/MenuUI.cpp

```cpp
#include "../include/MenuUI.h"
#include <iostream>
#include <iomanip>

MenuUI::MenuUI() {
    manager.seedDemoData();
}

int MenuUI::getIntInput(const std::string& prompt) {
    int val;
    while (true) {
        std::cout << prompt;
        if (std::cin >> val) {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return val;
        }
        std::cout << "[Input Error] Please enter a valid number.\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}

double MenuUI::getDoubleInput(const std::string& prompt) {
    double val;
    while (true) {
        std::cout << prompt;
        if (std::cin >> val) {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return val;
        }
        std::cout << "[Input Error] Please enter a valid decimal number.\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}

std::string MenuUI::getStringInput(const std::string& prompt) {
    std::string val;
    std::cout << prompt;
    std::getline(std::cin, val);
    return val;
}

void MenuUI::start() {
    int choice = -1;
    while (choice != 0) {
        std::cout << "\n===========================================================\n";
        std::cout << "        RIDE SHARING PLATFORM SIMULATOR (C++ OOP)          \n";
        std::cout << "===========================================================\n";
        std::cout << " 1. Rider Portal\n";
        std::cout << " 2. Driver Portal\n";
        std::cout << " 3. Admin Dashboard & Analytics\n";
        std::cout << " 4. Run Automated End-to-End Demo Simulation\n";
        std::cout << " 0. Exit Application\n";
        std::cout << "===========================================================\n";

        choice = getIntInput("Select an option (0-4): ");

        switch (choice) {
            case 1: riderMenu(); break;
            case 2: driverMenu(); break;
            case 3: adminMenu(); break;
            case 4: runAutomatedDemo(); break;
            case 0:
                std::cout << "\nThank you for using the Ride Sharing Platform! Goodbye.\n";
                break;
            default:
                std::cout << "\n[Invalid Option] Please enter a choice between 0 and 4.\n";
                break;
        }
    }
}

void MenuUI::riderMenu() {
    int option = -1;
    while (option != 0) {
        std::cout << "\n-----------------------------------------------------------\n";
        std::cout << "                      RIDER PORTAL                         \n";
        std::cout << "-----------------------------------------------------------\n";
        std::cout << " 1. Register New Rider\n";
        std::cout << " 2. View Rider Profile & Balance\n";
        std::cout << " 3. Add Funds to Wallet\n";
        std::cout << " 4. View Available Ride Types & Fare Rates\n";
        std::cout << " 5. Book / Request a Ride\n";
        std::cout << " 6. Rate Driver for Completed Ride\n";
        std::cout << " 7. View Ride History\n";
        std::cout << " 0. Back to Main Menu\n";
        std::cout << "-----------------------------------------------------------\n";

        option = getIntInput("Rider Portal Choice: ");

        switch (option) {
            case 1: {
                std::string name = getStringInput("Enter Rider Name: ");
                std::string phone = getStringInput("Enter Phone Number: ");
                double deposit = getDoubleInput("Enter Initial Wallet Balance ($): ");
                auto rider = manager.registerRider(name, phone, deposit);
                std::cout << "\n[Success] Rider registered successfully! Your Rider ID is #" << rider->getId() << "\n";
                break;
            }
            case 2: {
                int rId = getIntInput("Enter Rider ID: ");
                auto rider = manager.getRider(rId);
                if (rider) {
                    rider->displayProfile();
                } else {
                    std::cout << "[Error] Rider not found.\n";
                }
                break;
            }
            case 3: {
                int rId = getIntInput("Enter Rider ID: ");
                auto rider = manager.getRider(rId);
                if (rider) {
                    double amount = getDoubleInput("Enter amount to add ($): ");
                    rider->addFunds(amount);
                } else {
                    std::cout << "[Error] Rider not found.\n";
                }
                break;
            }
            case 4: {
                manager.displayAvailableRideTypes();
                break;
            }
            case 5: {
                int rId = getIntInput("Enter your Rider ID: ");
                auto rider = manager.getRider(rId);
                if (!rider) {
                    std::cout << "[Error] Rider not found.\n";
                    break;
                }

                manager.displayAvailableRideTypes();
                std::string typeName = getStringInput("Enter Ride Category (Economy / Luxury / Bike / XL): ");
                std::string pickup = getStringInput("Enter Pickup Location: ");
                std::string dropoff = getStringInput("Enter Dropoff Location: ");
                double dist = getDoubleInput("Estimated Distance in km: ");
                double dur = getDoubleInput("Estimated Time in mins: ");
                double surge = getDoubleInput("Surge Multiplier (1.0 = Normal, 1.5 = Surge): ");

                manager.requestRide(rId, typeName, pickup, dropoff, dist, dur, surge);
                break;
            }
            case 6: {
                int rideId = getIntInput("Enter Ride ID to rate: ");
                double stars = getDoubleInput("Enter rating for driver (1.0 to 5.0): ");
                manager.rateDriver(rideId, stars);
                break;
            }
            case 7: {
                int rId = getIntInput("Enter Rider ID: ");
                auto rider = manager.getRider(rId);
                if (rider) {
                    const auto& history = rider->getRideHistory();
                    std::cout << "\nRide History for Rider " << rider->getName() << " (" << history.size() << " rides):\n";
                    for (int rideId : history) {
                        auto ride = manager.getRide(rideId);
                        if (ride) ride->displayReceipt();
                    }
                } else {
                    std::cout << "[Error] Rider not found.\n";
                }
                break;
            }
            case 0:
                break;
            default:
                std::cout << "[Invalid Option]\n";
                break;
        }
    }
}

void MenuUI::driverMenu() {
    int option = -1;
    while (option != 0) {
        std::cout << "\n-----------------------------------------------------------\n";
        std::cout << "                      DRIVER PORTAL                        \n";
        std::cout << "-----------------------------------------------------------\n";
        std::cout << " 1. Register New Driver\n";
        std::cout << " 2. View Driver Profile & Earnings\n";
        std::cout << " 3. Toggle Online / Offline Availability\n";
        std::cout << " 4. Accept a Pending Ride\n";
        std::cout << " 5. Start / Progress Active Ride\n";
        std::cout << " 6. Complete Ride & Collect Payment\n";
        std::cout << " 7. Rate Rider for Completed Ride\n";
        std::cout << " 0. Back to Main Menu\n";
        std::cout << "-----------------------------------------------------------\n";

        option = getIntInput("Driver Portal Choice: ");

        switch (option) {
            case 1: {
                std::string name = getStringInput("Enter Driver Name: ");
                std::string phone = getStringInput("Enter Phone Number: ");
                std::string make = getStringInput("Vehicle Make (e.g. Toyota): ");
                std::string model = getStringInput("Vehicle Model (e.g. Camry): ");
                std::string plate = getStringInput("License Plate: ");
                int cap = getIntInput("Seat Capacity (excluding driver): ");
                std::string loc = getStringInput("Current Location: ");

                auto driver = manager.registerDriver(name, phone, make, model, plate, cap, loc);
                std::cout << "\n[Success] Driver registered! Your Driver ID is #" << driver->getId() << "\n";
                break;
            }
            case 2: {
                int dId = getIntInput("Enter Driver ID: ");
                auto driver = manager.getDriver(dId);
                if (driver) {
                    driver->displayProfile();
                } else {
                    std::cout << "[Error] Driver not found.\n";
                }
                break;
            }
            case 3: {
                int dId = getIntInput("Enter Driver ID: ");
                auto driver = manager.getDriver(dId);
                if (driver) {
                    driver->toggleAvailability();
                } else {
                    std::cout << "[Error] Driver not found.\n";
                }
                break;
            }
            case 4: {
                int dId = getIntInput("Enter Driver ID: ");
                int rideId = getIntInput("Enter Ride ID to Accept: ");
                manager.acceptRide(rideId, dId);
                break;
            }
            case 5: {
                int rideId = getIntInput("Enter Ride ID to Start: ");
                manager.startTrip(rideId);
                break;
            }
            case 6: {
                int rideId = getIntInput("Enter Ride ID to Complete: ");
                manager.completeTrip(rideId);
                break;
            }
            case 7: {
                int rideId = getIntInput("Enter Ride ID: ");
                double stars = getDoubleInput("Enter rating for rider (1.0 to 5.0): ");
                manager.rateRider(rideId, stars);
                break;
            }
            case 0:
                break;
            default:
                std::cout << "[Invalid Option]\n";
                break;
        }
    }
}

void MenuUI::adminMenu() {
    int option = -1;
    while (option != 0) {
        std::cout << "\n-----------------------------------------------------------\n";
        std::cout << "                 ADMIN & PLATFORM DASHBOARD                \n";
        std::cout << "-----------------------------------------------------------\n";
        std::cout << " 1. Display Platform Metrics & Financial Summary\n";
        std::cout << " 2. List All Registered Riders\n";
        std::cout << " 3. List All Registered Drivers\n";
        std::cout << " 4. View All System Rides\n";
        std::cout << " 5. Run Ride Fare Calculator / Estimator\n";
        std::cout << " 0. Back to Main Menu\n";
        std::cout << "-----------------------------------------------------------\n";

        option = getIntInput("Admin Choice: ");

        switch (option) {
            case 1:
                manager.displaySystemStats();
                break;
            case 2:
                std::cout << "\n--- REGISTERED RIDERS ---\n";
                for (const auto& pair : manager.getAllRiders()) {
                    pair.second->displayProfile();
                }
                break;
            case 3:
                std::cout << "\n--- REGISTERED DRIVERS ---\n";
                for (const auto& pair : manager.getAllDrivers()) {
                    pair.second->displayProfile();
                }
                break;
            case 4:
                std::cout << "\n--- ALL PLATFORM RIDES ---\n";
                for (const auto& ride : manager.getAllRides()) {
                    ride->displayReceipt();
                }
                break;
            case 5: {
                manager.displayAvailableRideTypes();
                std::string cat = getStringInput("Enter Category (Economy/Luxury/Bike/XL): ");
                double dist = getDoubleInput("Distance (km): ");
                double time = getDoubleInput("Duration (mins): ");
                double surge = getDoubleInput("Surge multiplier (e.g. 1.0, 1.5): ");

                double fare = manager.estimateFare(cat, dist, time, surge);
                std::cout << "\n>>> Calculated Fare for " << cat << " (" << dist << " km, " << time << " mins, " << surge << "x surge): $"
                          << std::fixed << std::setprecision(2) << fare << " <<<\n";
                break;
            }
            case 0:
                break;
            default:
                std::cout << "[Invalid Option]\n";
                break;
        }
    }
}

void MenuUI::runAutomatedDemo() {
    std::cout << "\n========================================================================\n";
    std::cout << "         AUTOMATED SIMULATION SHOWCASE (OOP C++ PLATFORM)               \n";
    std::cout << "========================================================================\n";

    std::cout << "\nStep 1: Registering a new Rider 'Diana Prince' with $150.00 wallet...\n";
    auto rider = manager.registerRider("Diana Prince", "+1-555-0999", 150.00);

    std::cout << "\nStep 2: Registering a new Driver 'Bruce Wayne' with a Luxury SUV...\n";
    auto driver = manager.registerDriver("Bruce Wayne", "+1-555-0888", "Batmobile", "V8", "GOTHAM-1", 4, "Downtown");

    std::cout << "\nStep 3: Calculating fare estimates for a 15 km, 25 minute journey with 1.5x surge pricing...\n";
    std::cout << " Economy Fare Estimate : $" << std::fixed << std::setprecision(2) << manager.estimateFare("Economy", 15.0, 25.0, 1.5) << "\n";
    std::cout << " Luxury Fare Estimate  : $" << manager.estimateFare("Luxury", 15.0, 25.0, 1.5) << "\n";
    std::cout << " Bike Fare Estimate    : $" << manager.estimateFare("Bike", 15.0, 25.0, 1.5) << "\n";
    std::cout << " XL Fare Estimate      : $" << manager.estimateFare("XL", 15.0, 25.0, 1.5) << "\n";

    std::cout << "\nStep 4: Diana requests a Luxury Ride from Downtown to Metro Station...\n";
    auto ride = manager.requestRide(rider->getId(), "Luxury", "Downtown", "Metro Station", 15.0, 25.0, 1.5);

    if (ride) {
        std::cout << "\nStep 5: Bruce accepts the ride request...\n";
        manager.acceptRide(ride->getRideId(), driver->getId());

        std::cout << "\nStep 6: Driver starts the trip...\n";
        manager.startTrip(ride->getRideId());

        std::cout << "\nStep 7: Driver completes the trip & platform settles payment automatically...\n";
        manager.completeTrip(ride->getRideId());

        std::cout << "\nStep 8: Exchanging ratings...\n";
        manager.rateDriver(ride->getRideId(), 5.0);
        manager.rateRider(ride->getRideId(), 5.0);

        std::cout << "\nStep 9: Displaying final Ride Receipt:\n";
        ride->displayReceipt();
    }

    std::cout << "\nStep 10: Updated Platform Dashboard:\n";
    manager.displaySystemStats();

    std::cout << "========================================================================\n";
    std::cout << "                END OF AUTOMATED DEMO SIMULATION                       \n";
    std::cout << "========================================================================\n";
}
```
