#include <iostream>
#include <cmath>
#include <chrono>
#include <random>

#include "generation_inversion.h"

/*double densiteTest(double x){return 1/cbrt(pow(x-.125,2))/3;}
double fdrTest(double x){return cbrt(x-.125)+.5;}
double deriveedensiteTest(double x){return -2/cbrt(pow(x-.125,5))/9;}
Intervalle interTest = Intervalle(0.00000000001,.2499999999999);

double densiteTest(double x){return 1/x;}
double fdrTest(double x){return log(x);}
double deriveedensiteTest(double x){return -1/pow(x,2);}
Intervalle interTest = Intervalle(1,exp(1));
*/
double densiteTest(double x){return cos(x);}
double fdrTest(double x){return sin(x);}
double deriveedensiteTest(double x){return -sin(x);}
Intervalle interTest = Intervalle (0,3.141592/2);

 /*
double densiteTest(double x){return 3*x*x;}
double fdrTest(double x){return x*x*x;}
double deriveedensiteTest(double x){return 6*x;}
 Intervalle interTest = Intervalle (0,1);
*/
int main() {
    /*std::cout << "Hello, World!" << std::endl;
    Intervalle inter (0,1);
    Intervalle inter1 (1,2);
    Intervalle inter2 (0,1);

    std::cout << inter.getInf();
    std::cout << inter.getSup();
    std::cout << inter.milieu() << std::endl;
    std::cout << (inter == inter1);
    std::cout << (inter == inter2);
    std::cout << (inter > 3);
    std::cout << (inter > 0.5);
    std::cout << (inter > -1);
    std::cout << (inter > 0);
    std::cout << (inter == 0);
    std::cout << (inter > inter1);
    std::cout << (inter < inter1)<<std::endl;
    inter.setInf(0.5);
    std::cout << inter.getInf()<<std::endl;
*/
    /*
     auto start1 = std::chrono::steady_clock::now();
     int seed = 777;
    int nb_generations = 1000000;
     std::default_random_engine generator;
     generator.seed(seed);
     std::uniform_real_distribution<double> distribution(0.0,1.0);
     for (size_t i = 0; i < nb_generations; i++)
         double u_genere = distribution(generator);
     auto end1 = std::chrono::steady_clock::now();
     std::chrono::duration<double> secondes_ecoulees1 = end1-start1;
     std::cout << "generation uniforme: " << secondes_ecoulees1.count() << "s\n";
*/
    auto start = std::chrono::steady_clock::now();
    std::vector<double> pointsparticuliers = {};
    std::vector<double> generations = generation_inversion(1,fdrTest,densiteTest,deriveedensiteTest,
                                               interTest, pointsparticuliers,5, 1e-10, 0.05,777,
                                               true,true,false);
    auto end = std::chrono::steady_clock::now();

    std::chrono::duration<double> secondes_ecoulees = end-start;
    std::cout << "secondes ecoulees: " << secondes_ecoulees.count() << "s\n";
    return 0;
}
