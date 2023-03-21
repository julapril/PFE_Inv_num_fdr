//
// Created by julap on 2023-02-28.
//
#include <vector>
#include <list>
#include "Intervalle.h"

#ifndef PROGRAMMATION_GENERATION_INVERSION_H
#define PROGRAMMATION_GENERATION_INVERSION_H

std::vector<double> generation_inversion(const size_t nb_generations, double (*fdr)(double),  double (*densite)(double),
                             double (*deriveedensite)(double), Intervalle inter, std::vector<double>&  ptsparticuliers,
                             const size_t ordre=1, double tol = 1e-10, double delta = 0.05, int seed = 1234,
                             bool test_monoticite = true, bool affichage = false,  bool affichage1 = false);
#endif //PROGRAMMATION_GENERATION_INVERSION_H
