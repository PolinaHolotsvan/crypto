#include <iostream>
#include "Lab2.h"
#include "Tests.h"


using namespace std;


void lab1Tests() {
    bailliePSWTest(97); //prime
    bailliePSWTest(150); //composite
    bailliePSWTest(977); //prime
    bailliePSWTest(4951); //prime
    bailliePSWTest(5000); //composite


    millerRabinTest(97, 10); //prime
    millerRabinTest(150, 20); //composite
    millerRabinTest(977, 20); //prime
    millerRabinTest(4951, 40); //prime
    millerRabinTest(5000, 40); //composite

    convertorTest(4951, 16, 5);
}


int main() {
    int64_t message = 34567890;
    RSATest(message, 16);
    RSATest(message, 18);
    RSATest(message, 20);
}