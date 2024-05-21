#include <iostream>
#include "../hpp_files/StockCar.hpp"

// StockCar class implementation
// Methods to add a car to the stock, move a car, and reset all cars

void StockCar::addCar(const Car& car) {
    cars.push_back(car);
}

void StockCar::moveCar(int carIndex, int distance) {
    if (carIndex >= 0 && carIndex < cars.size()) {
        cars[carIndex].move(distance);
    }
}

void StockCar::resetCars() {
    for (Car& car : cars) {
        car.resetPosition();
    }
    std::cout << "All cars have been reset to their initial positions." << std::endl;
}

StockCar::~StockCar() {}