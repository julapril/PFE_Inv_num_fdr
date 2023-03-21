/**
* \file interpolation_hermite.h
* \brief Déclaration de fonctions liées à l'interpolation d'hermite d'ordre 1, 3 et 5.
* \author Julien April
* \version 0.1
* \date mars 2023
*
* Dans le cadre du cours MAT-3600 Projet de fin d'études
* Sous la supervision de Philippe-Adnré Luneau et Jean Deteix
*
*/

#ifndef PROGRAMMATION_HERMITE_LINEAIRE_H
#define PROGRAMMATION_HERMITE_LINEAIRE_H

#include <list>

#include "Intervalle.h"

double evaluation_hermite(double* coeff, double u, Intervalle* inter_u, const size_t ordre);

double* hermite_lineaire(Intervalle* inter_p);
double* hermite_cubique(Intervalle* inter_p, Intervalle* inter_u, double (*densite)(double));
double* hermite_quintique(Intervalle* inter_p, Intervalle* inter_u,
                          double (*densite)(double),  double (*deriveedensite)(double));

std::list<std::tuple<Intervalle*, Intervalle*, double*>>* initialisation_interpolations
(std::list<Intervalle*> p, double (*fdr)(double),  double (*densite)(double),
 double (*deriveedensite)(double), const size_t ordre);

#endif //PROGRAMMATION_HERMITE_LINEAIRE_H
