#include<iostream>
#include<stdlib.h>
#include <stdio.h>
#if defined(_WIN32) // 윈도우 환경일 경우
#include <Windows.h>
#else // 그 외 unix 호환 시스템일 경우
#include <unistd.h>
#endif
#include<cstdlib>

using namespace std;

// 책 예시를 그대로 써놓으려고 했으나 너무 길어서 포기

class accelerator;
const int dummy = 0;

class engin{
private :
    virtual void acceleration_output() = 0;
    virtual void reduce_output() = 0;
    friend class accelerator;
};

class ic_engine : public engin{
private :
    virtual void acceleration_output() = 0;
    virtual void reduce_output() = 0;
};

class gs_engine : public ic_engine{
    private :
        void acceleration_output() override { increasing_fuel(); };
        void reduce_output() override { decreasing_fuel(); };
        void increasing_fuel() { increasing_piston_speed(); };
        void decreasing_fuel() { decreasing_piston_speed(); };
        void increasing_piston_speed() { cout << "increasing_piston_speed" << endl; };
        void decreasing_piston_speed() { cout << "decreasing_piston_speed" << endl; };
};

class elec_engine : public ic_engine{
private :
    void acceleration_output() override { increasing_motor_speed(); };
    void reduce_output() override { decreasing_motor_speed(); };
    void increasing_motor_speed() { cout << "increasing_motor_speed" << endl; };
    void decreasing_motor_speed() { cout << "decreasing_motor_speed" << endl; };
};

class break_system
{
public:
    void pushing_break(accelerator &accelerator_obj);
};

class accelerator{
public:
    accelerator(engin &engin) : my_engin(engin){};
    void acceleration_output() {my_engin.acceleration_output(); };
    void set_engin(engin &engin) {my_engin = engin; };

private:
    engin &my_engin;

    void reduce_output();
    friend void break_system::pushing_break(accelerator &accelerator_obj);
};

void break_system::pushing_break(accelerator &accelerator_obj){
    accelerator_obj.reduce_output();
}