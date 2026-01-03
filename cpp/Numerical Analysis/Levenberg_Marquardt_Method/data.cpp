#include <iostream>
#include <fstream>

using namespace std;

#include "data.h"

void read_market_vol(char* filename, int n_strike, double* v_strike, int n_maturity, double* v_maturity, double** m_vol){
    
    ifstream inf(filename, ios::in);
    if(!inf.is_open()){ // 파일을 open 할 수 없을 때
        cout << filename << " 파일을 열 수 없습니다." << endl;
        inf.clear();
        exit(0);
    }

    int i, j;
    char text[20];

    inf>>text; // "만기:" 읽기
    for(i = 0 ; i < n_maturity; i++){
        inf>>text;
        v_maturity[i] = atof(text);
    }


    inf>>text; // "행사가격:" 읽기
    for(i = 0 ; i < n_strike; i++){
        inf>>text;
        v_strike[i] = atof(text);
    }
    
    inf>>text; // "변동성:" 읽기
    for(i = 0 ; i < n_strike ; i++){
        for(j = 0; j < n_maturity ; j++){
            inf >> text;
            m_vol[i][j] = atof(text)/100.0;
        }
    }
    inf.close();
}

void save_vol(char* filename, int n_strike, double* v_strike, int n_maturity, double* v_maturity, double** vol){

    ofstream outf(filename, ios::out | ios::trunc);
    // ios::trunc 사용시 기존 데이터 삭제 후 추가
    // ios:app 사용시 데이터 추가 기능
    if(!outf.is_open()){
        cout << filename << " 파일을 열 수 없습니다." << endl;
        outf.clear();
        exit(0);
    }

    int i, j;
    outf << "만기:" << " ";
    for(j = 0 ; j < n_maturity ; j++){
        outf << v_maturity[j] << " ";
    }
    outf << endl;
   
    outf << "행사가격:" << " ";
    for(i = 0 ; i < n_strike ; i++){
        outf << v_strike[i] << " ";
    }
    outf << endl;

    outf << "변동성 : " << "   ";
    for(i = 0 ; i < n_strike; i++){
        for(j = 0 ; j < n_maturity ; j++){
            outf << vol[i][j] * 100.0 << " ";
        }
        outf << endl;
        outf << "  " << "";
    }
    outf.close();
}
