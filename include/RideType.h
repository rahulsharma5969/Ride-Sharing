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
