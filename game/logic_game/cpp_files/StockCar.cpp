#include "../hpp_files/StockCar.hpp"

void StockCar::addCar(const Car& car) {
    cars.push_back(car);
}

void StockCar::moveCar(int carIndex, int distance) {
    if (carIndex >= 0 && carIndex < cars.size()) {
        cars[carIndex].move(distance);
    }
}

StockCar::~StockCar() {}