#include "MOTORCONTROLLER.h"

MotorController::MotorController()
{
    motorPower = false;
    motorSpeed = 0.0;
    motorDirect = "无方向";
}

MotorController::MotorController(const bool &power, const double &speed, const string &direct)
{
    motorPower = power;
    motorSpeed = speed;
    motorDirect = direct;
}

void MotorController::turnOn()
{
    if(motorPower)
    {
        cout << "电机启动！" << endl;
    }
    else
    {
        motorPower = true;
        cout << "电机启动！" << endl;
    }
}

void MotorController::turnOff()
{
    if(motorPower)
    {
        motorPower = false;
        cout << "电机关闭！" << endl;
    }
    else
    {
        cout << "电机关闭！" << endl;
    }
}

void MotorController::getSpeed()
{
    if(motorPower)
    {
        cout << "电机的旋转速度是： " << motorSpeed << "rad/s"<< endl;
    }
    else
    {
        cout << "未开启电机" << endl;
    }
}

void MotorController::setSpeed(double s)
{
    if(motorPower)
    {
        motorSpeed = s;
    }
    else
    {
        cout << "未开启电机" << endl;
    }
}

void MotorController::getDirect()
{
    if(motorPower)
    {
        if(motorDirect == "s")
        {
            cout << "电机的旋转方向是:顺时针"<< endl;
        }
        else if(motorDirect == "n")
        {
            cout << "电机的旋转方向是:逆时针" << endl;
        }
        else
        {
            cout << "电机的旋转方向是： " << motorDirect << endl;
        }
    }
    else
    {
        cout << "未开启电机" << endl;
    }
}

void MotorController::setDirect(string s)
{
    if(motorPower)
    {
        motorDirect = s;
    }
    else
    {
        cout << "未开启电机" << endl;
    }
}