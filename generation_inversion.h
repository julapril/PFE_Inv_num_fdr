/**
* \file generation_inversion.h
* \brief Déclaration d'une fonction effectuant un algorithme d'inversion numérique de fonction de répartition par interpolation.
* \author Julien April
* \version 0.1
* \date mars 2023
*
* Dans le cadre du cours MAT-3600 Projet de fin d'études
* Sous la supervision de Philippe-Adnré Luneau et Jean Deteix
*
*/
#include <vector>
#include <list>
#include "Intervalle.h"

#ifndef PROGRAMMATION_GENERATION_INVERSION_H
#define PROGRAMMATION_GENERATION_INVERSION_H

std::vector<double>* generation_inversion(const size_t nb_generations, double (*fdr)(double),  double (*densite)(double),
                             double (*deriveedensite)(double), Intervalle inter, std::vector<double>&  ptsparticuliers,
                             const size_t ordre=3, double tol = 1e-10, double delta = 0.05, int seed = 1234,
                             bool test_monoticite = true, bool affichage = false,  bool affichage_generations = false,
                             bool affichage_division_0 = false, bool affichage_nbintervalles = false);
#endif //PROGRAMMATION_GENERATION_INVERSION_H
