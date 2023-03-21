//
// Created by julap on 2023-03-01.
//
#include <tuple>
#include <list>
#include <vector>

#include "Intervalle.h"

#ifndef PROGRAMMATION_UTILITAIRES_H
#define PROGRAMMATION_UTILITAIRES_H

bool est_dans_intervalle (double u_genere, std::tuple<Intervalle *, Intervalle *, double *>& tIntervalle);

std::list<std::tuple<Intervalle *, Intervalle *, double *>>::iterator  recherche_intervalle
    (std::list<std::tuple<Intervalle *, Intervalle *, double *>>::iterator debut, std::list<std::tuple<Intervalle *, Intervalle *, double *>>::iterator fin, double u_genere);

std::vector<std::list<std::tuple<Intervalle *, Intervalle *, double *>>::iterator> initialisation_index (std::list<std::tuple<Intervalle *, Intervalle *, double *>>::iterator itr, int C);
#endif //PROGRAMMATION_UTILITAIRES_H
