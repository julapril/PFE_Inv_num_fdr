//
// Created by julap on 2023-03-09.
//

#ifndef PROGRAMMATION_DISTRIBUTIONS_STATISTIQUES_H
#define PROGRAMMATION_DISTRIBUTIONS_STATISTIQUES_H

#include "Intervalle.h"
#include <vector>

//Constantes pour le calcul de fdrNormale
static const double RT2PI = sqrt(4.0*acos(0.0));

static const double SPLIT = 7.07106781186547;

static const double N0 = 220.206867912376;
static const double N1 = 221.213596169931;
static const double N2 = 112.079291497871;
static const double N3 = 33.912866078383;
static const double N4 = 6.37396220353165;
static const double N5 = 0.700383064443688;
static const double N6 = 3.52624965998911e-02;
static const double M0 = 440.413735824752;
static const double M1 = 793.826512519948;
static const double M2 = 637.333633378831;
static const double M3 = 296.564248779674;
static const double M4 = 86.7807322029461;
static const double M5 = 16.064177579207;
static const double M6 = 1.75566716318264;
static const double M7 = 8.83883476483184e-02;

//constante pour le calcul de beta(0.3,3)
static const double beta_0p3_3 = 2.229654403567447045707915;


double fdrNormale(double x);
double densiteNormale(double x);
double deriveedensiteNormale(double x);

double fdrCauchy(double x);
double densiteCauchy(double x);
double deriveedensiteCauchy(double x);

double fdrExponentielle(double x);
double densiteExponentielle(double x);
double deriveedensiteExponentielle(double x);

double gammad ( double x, double p);

double fdrGamma5(double x);
double densiteGamma5(double x);
double deriveedensiteGamma5(double x);

double fdrGamma1_2(double x);
double densiteGamma1_2(double x);
double deriveedensiteGamma1_2(double x);

double fdrBeta2_2(double x);
double densiteBeta2_2(double x);
double deriveedensiteBeta2_2(double x);

double fdrBeta_0p3_3(double x);
double densiteBeta_0p3_3(double x);
double deriveedensiteBeta_0p3_3(double x);

void initialisation_distribution(int distr,
                                 double (*fdr)(double),  double (*densite)(double), double (*deriveedensite)(double));

#endif //PROGRAMMATION_DISTRIBUTIONS_STATISTIQUES_H
