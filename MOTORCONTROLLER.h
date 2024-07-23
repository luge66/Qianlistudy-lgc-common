#ifndef MOTORCONTROLLER_H
#define MOTORCONTROLLER_H
#include <cstring>
#include <string>
#include <iostream>

using namespace std;

class MotorController
{
    private:
        bool motorPower;
        double motorSpeed;
        string motorDirect;

    public:
        MotorController();
        MotorController(const bool &, const double &, const string &);
        void turnOn();
        void turnOff();
        void getSpeed();
        void setSpeed(double speed);

        void getDirect();
        void setDirect(string direct);
};

#endif