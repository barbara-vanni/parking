#ifndef STOCKCAR_HPP
#define STOCKCAR_HPP

#include "Car.hpp"
#include <vector>

// StockCar class declaration

class StockCar {
public:
    void addCar(const Car& car);
    void moveCar(int carIndex, int distance);
    std::vector<Car>& getStockCar() { 
        return cars; 
        }
    void resetCars();
    ~StockCar();
private:
    std::vector<Car> cars;
};

#endif