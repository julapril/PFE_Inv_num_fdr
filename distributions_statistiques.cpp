//
// Created by julap on 2023-03-09.
//
#include <cmath>

#include "distributions_statistiques.h"

double fdrNormale(double x)
{
    const double z = fabs(x);
    double c = 0.0;

    if(z<=37.0)
    {
        const double e = exp(-z*z/2.0);
        if(z<SPLIT)
        {
            const double n = (((((N6*z + N5)*z + N4)*z + N3)*z + N2)*z + N1)*z + N0;
            const double d = ((((((M7*z + M6)*z + M5)*z + M4)*z + M3)*z + M2)*z + M1)*z + M0;
            c = e*n/d;
        }
        else
        {
            const double f = z + 1.0/(z + 2.0/(z + 3.0/(z + 4.0/(z + 13.0/20.0))));
            c = e/(RT2PI*f);
        }
    }
    return x<=0.0 ? c : 1-c;
}

double densiteNormale(double x){
    double f = exp(-.5*x*x)/sqrt(2*M_PI);
    return f;
}

double deriveedensiteNormale(double x){
    double ff = -x*exp(-.5*x*x)/sqrt(2*M_PI);
    return ff;
}

double fdrCauchy(double x){
    double F = atan(x)/M_PI + .5;
    return F;
}

double densiteCauchy(double x){
    double f = 1/(M_PI * (1+x*x));
    return f;
}

double deriveedensiteCauchy(double x){
    double ff = -2*x/(M_PI * pow(1+x*x,2));
    return ff;
}

double fdrExponentielle(double x){
    double F = 1 - exp(-x);
    return F;
}

double densiteExponentielle(double x){
    double f = exp(-x);
    return f;
}

double deriveedensiteExponentielle(double x){
    double ff = -exp(-x);
    return ff;
}

double gammad ( double x, double p)
{
    double a;
    double an;
    double arg;
    double b;
    double c;
    double elimit = - 88.0;
    double oflo = 1.0E+37;
    double plimit = 1000.0;
    double pn1;
    double pn2;
    double pn3;
    double pn4;
    double pn5;
    double pn6;
    double rn;
    double tol = 1.0E-14;
    double value;
    double xbig = 1.0E+08;

    value = 0.0;

    if ( x == 0.0 )
    {
        value = 0.0;
        return value;
    }

    if ( plimit < p )
    {
        pn1 = 3.0 * sqrt ( p ) * ( pow ( x / p, 1.0 / 3.0 )
                                   + 1.0 / ( 9.0 * p ) - 1.0 );

        value = fdrNormale( pn1);
        return value;
    }

    if ( xbig < x )
    {
        value = 1.0;
        return value;
    }

    if ( x <= 1.0 || x < p )
    {
        arg = p * log ( x ) - x - lgamma ( p + 1.0 );
        c = 1.0;
        value = 1.0;
        a = p;

        for ( ; ; )
        {
            a = a + 1.0;
            c = c * x / a;
            value = value + c;

            if ( c <= tol )
            {
                break;
            }
        }

        arg = arg + log ( value );

        if ( elimit <= arg )
        {
            value = exp ( arg );
        }
        else
        {
            value = 0.0;
        }
    }

    else
    {
        arg = p * log ( x ) - x - lgamma ( p );
        a = 1.0 - p;
        b = a + x + 1.0;
        c = 0.0;
        pn1 = 1.0;
        pn2 = x;
        pn3 = x + 1.0;
        pn4 = x * b;
        value = pn3 / pn4;

        for ( ; ; )
        {
            a = a + 1.0;
            b = b + 2.0;
            c = c + 1.0;
            an = a * c;
            pn5 = b * pn3 - an * pn1;
            pn6 = b * pn4 - an * pn2;

            if ( pn6 != 0.0 )
            {
                rn = pn5 / pn6;

                double r8_min;
                if ( tol*rn < tol ) r8_min = tol*rn;
                else r8_min = tol;

                if ( fabs ( value - rn ) <= r8_min )
                {
                    break;
                }
                value = rn;
            }

            pn1 = pn3;
            pn2 = pn4;
            pn3 = pn5;
            pn4 = pn6;

            if ( oflo <= abs ( pn5 ) )
            {
                pn1 = pn1 / oflo;
                pn2 = pn2 / oflo;
                pn3 = pn3 / oflo;
                pn4 = pn4 / oflo;
            }
        }

        arg = arg + log ( value );

        if ( elimit <= arg )
        {
            value = 1.0 - exp ( arg );
        }
        else
        {
            value = 1.0;
        }
    }

    return value;
}

double fdrGamma5(double x){
    double fdr = gammad(x,5);
    return fdr;
}
double densiteGamma5(double x){
    double f = pow(x,4)*exp(-x)/24;
    return f;
}
double deriveedensiteGamma5(double x){
    double ff = pow(x,3)*(4-x)*exp(-x)/24;
    return ff;
}

double fdrGamma1_2(double x){
    double fdr = gammad(x,.5);
    return fdr;
}
double densiteGamma1_2(double x){
    double f = exp(-x)*M_2_SQRTPI/2/sqrt(x);
    return f;
}
double deriveedensiteGamma1_2(double x){
    double ff = -exp(-x)*M_2_SQRTPI/4*(1+2*x)/sqrt(pow(x,3));
    return ff;
}

double fdrBeta2_2(double x){
    double fdr = pow(x,2)*(3-2*x);
    return fdr;
}
double densiteBeta2_2(double x){
    double f = 6*x*(1-x);
    return f;
}
double deriveedensiteBeta2_2(double x){
    double ff = 6-12*x;
    return ff;
}

double fdrBeta_0p3_3(double x){
    double fdr = pow(x,0.3)*(1/0.3 - 2*x/1.3 + pow(x, 2)/2.3)/beta_0p3_3;
    return fdr;
}
double densiteBeta_0p3_3(double x){
    double f = pow(1-x,2)*pow(x, -0.7)/beta_0p3_3;
    return f;
}
double deriveedensiteBeta_0p3_3(double x){
    double ff = - (0.7 + 0.6*x - 1.3*pow(x,2))*pow(x, -1.7)/beta_0p3_3;
    return ff;
}



