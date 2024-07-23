#include "MOTORCONTROLLER.h"
#include <locale>

int menuOp(MotorController &motor)
{
    int choice;
    cout << "----------------------------------------------" << endl;
    cout << "请输入数字来选择你的模式" << endl;
    cout << "0.关闭电机" << endl;
    cout << "1.开启电机" << endl;
    cout << "2.修改电机速度" << endl;
    cout << "3.查看电机速度" << endl;
    cout << "4.改变电机旋转方向(顺时针's' || 逆时针'n')" << endl;
    cout << "5.查看当前电机旋转方向(顺时针 || 逆时针)" << endl;
    cout << "----------------------------------------------" << endl;
    cin >> choice;
    if(choice != 0 && choice != 1 && choice != 2 && choice != 3 && choice != 4 && choice != 5)
    {
        cout << "重新输入数字" << endl;
        cin >> choice;
    }
    switch(choice)
    {
        case 0:
        {
            motor.turnOff();
            break;
        }

        case 1:
        {
            motor.turnOn();
            break;
        }

        case 2:
        {
            double speed;
            cout << "请输入新的电机速度" << endl;
            cin >> speed;
            motor.setSpeed(speed);
            break;
        }

        case 3:
        {
            motor.getSpeed();
            break;
        }

        case 4:
        {
            string direct;
            cin.ignore();
            cout << "请输入新的电机方向" << endl;
            getline(cin, direct);
            motor.setDirect(direct);
            break;
        }

        case 5:
        {
            motor.getDirect();
            break;
        }
    }

    return choice;
}

int main()
{
    int choice;
    MotorController motor;
    choice = 0;
    while(choice == 0 || choice == 1 || choice == 2 || choice == 3 || choice == 4 || choice == 5)
    {
        choice = menuOp(motor);
        cout << endl;
    }
    return 0;
}