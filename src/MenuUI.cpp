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
