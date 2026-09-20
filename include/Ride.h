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
