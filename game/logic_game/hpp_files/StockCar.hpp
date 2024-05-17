#ifndef STOCKCAR_HPP
#define STOCKCAR_HPP

#include "Car.hpp"
#include <vector>

class StockCar {
public:
    void addCar(const Car& car);
    void moveCar(int carIndex, int distance);
    std::vector<Car>& getStockCar() { 
        return cars; 
        }
    ~StockCar();
private:
    std::vector<Car> cars;
};

#endif