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
