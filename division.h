/**
* \file division.h
* \brief Déclaration de fonctions liées à la division et la division récursive des intervalles
 * lors de l'interpolation d'Hermite d'ordre 1, 3 et 5.
* \author Julien April
* \version 0.1
* \date mars 2023
*
* Dans le cadre du cours MAT-3600 Projet de fin d'études
* Sous la supervision de Philippe-Adnré Luneau et Jean Deteix
*
*/

#include <list>
#include <tuple>
#include <vector>

#include "Intervalle.h"

#ifndef PROGRAMMATION_DIVISION_H
#define PROGRAMMATION_DIVISION_H

void division_0(std::list<Intervalle*>& p, std::vector<double>&  ptsparticuliers, Intervalle& inter);

bool respecte_condition_1(Intervalle* inter, double (*fdr)(double), double delta);
void division_1(std::list<Intervalle*>& p, double (*fdr)(double), double delta);
void division_1_recursif(std::list<Intervalle*>& p, std::list<Intervalle*>::iterator itr,
                         double (*fdr)(double), double delta);

bool respecte_condition_2( std::tuple<Intervalle*, Intervalle*, double*>& tIntervalle,
                           double (*fdr)(double), const size_t ordre, double delta);
bool est_monotone (std::tuple<Intervalle*, Intervalle*, double*>& tIntervalle,
                   double (*densite)(double), const size_t ordre, bool test_monoticite);
void division_2(std::list<std::tuple<Intervalle*, Intervalle*, double*>>& interpolations,
                double (*fdr)(double),double (*densite)(double), double (*deriveedensite)(double),
                const size_t ordre, double tol, bool test_monoticite);
void division_2_recursif(std::list<std::tuple<Intervalle*, Intervalle*, double*>>& interpolations,
                         std::list<std::tuple<Intervalle*, Intervalle*, double*>>::iterator itr,
                         double (*fdr)(double), double (*densite)(double), double (*deriveedensite)(double),
                         const size_t ordre, double tol, bool test_monoticite);
#endif //PROGRAMMATION_DIVISION_H
