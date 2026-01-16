#include <iostream>
#include <ctime>
#include <cstdlib>
#include "mathlib.h"

using namespace std;

int main(){
    srand((unsigned) time(NULL)); // 랜덤 시드 초기화
    unsigned long i;
    unsigned long nrand = 1000000;

    cout << "=============== 정규분포 적합성 검증 Start ===============" <<endl;
    double* randnum = new double[nrand];
    for(i = 0 ; i < nrand ; i++){
        randnum[i] = normdistrand();    // 정규분포형 난수 생성
    }
    normal_distribution_goodness_fit_test(nrand, randnum); 
    delete[] randnum;
    cout << "=============== 정규분포 적합성 검증 End ===============" <<endl;

    cout << "=============== 표준정규누적분포의 역함수 적합성 검증 Start ===============" <<endl;
    double* inverse_randnum = new double[nrand];
    double urn;
    for(i = 0 ; i < nrand ; i++){
        urn = rand() / ((double)RAND_MAX);  // [0, 1] 범위의 균등분포형 난수 생성
        inverse_randnum[i] = inverse_normal_cumulative_distribution_function(urn);
    }
    normal_distribution_goodness_fit_test(nrand, inverse_randnum); 
    delete[] inverse_randnum;
    cout << "=============== 표준정규누적분포의 역함수 적합성 검증 End ===============" <<endl;
}