//
// Created by julap on 2023-03-06.
//
#include <list>
#include <tuple>

#include "Intervalle.h"

#ifndef PROGRAMMATION_GENERATION_ALEATOIRE_H
#define PROGRAMMATION_GENERATION_ALEATOIRE_H

std::vector<double> generation_aleatoire_index(std::list<std::tuple<Intervalle*, Intervalle*, double*>>& interpolations,
                                               const size_t nb_generations, const size_t ordre, int seed,
                                               bool affichage1);

std::vector<double> generation_aleatoire_recherche(std::list<std::tuple<Intervalle*, Intervalle*, double*>>& interpolations,
                                                   const size_t nb_generations, const size_t ordre, int seed,
                                                   bool affichage1);

#endif //PROGRAMMATION_GENERATION_ALEATOIRE_H
