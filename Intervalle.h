/**
* \file Intervalle.h
* \brief Interface de la classe Intervalle
* \author Julien April
* \version 0.1
* \date mars 2023
*
* Dans le cadre du cours MAT-3600 Projet de fin d'études
* Sous la supervision de Philippe-Adnré Luneau et Jean Deteix
*
*/

#ifndef PROJET_INTERVALLE_H
#define PROJET_INTERVALLE_H

#include <iostream>

/**
 * @class Intervalle
 *
 * @brief Classe représentant un intervalle borné réel
 */
class Intervalle {
public:
    Intervalle(double, double);
    ~Intervalle();
    double getInf() const;
    double getSup() const;
    void setInf(double);
    void setSup(double);
    bool operator<(Intervalle) const;
    bool operator>(Intervalle) const;
    bool operator==(Intervalle) const;
    bool operator<(double) const;
    bool operator>(double) const;
    bool operator==(double) const;
    double milieu() const;
    friend std::ostream& operator<<(std::ostream&,const Intervalle&);
private:
    double a;
    double b;
};


#endif //PROJET_INTERVALLE_H
