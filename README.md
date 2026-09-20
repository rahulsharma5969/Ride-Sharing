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
- `RideManager`: Serves as the central manager orchestrating rider registration, driver matching, ride lifecycle (`REQUESTED` $\rightarrow$ `ACCEPTED` $\rightarrow$ `IN_PROGRESS` $\rightarrow$ `COMPLETED`), wallet payouts, platform fees (20%), and analytics.
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
