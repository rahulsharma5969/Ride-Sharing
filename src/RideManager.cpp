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
