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
