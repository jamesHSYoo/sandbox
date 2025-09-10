#include<iostream>

using namespace std;


class character{
public: 
    character(){
        cout << "Character 클래스 생성자" << endl; 
    };
};

int main(){
    character player; 
    // 자바와 다르게 위 처럼 선언하면 생성자가 자동으로 호출됨
    return 0;
}