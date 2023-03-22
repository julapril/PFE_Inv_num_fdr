/**
* \file generation_aleatoire.h
* \brief Déclaration de fonctions générant des nombres aléatoires à partir d'une interpolation
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

#include "Intervalle.h"

#ifndef PROGRAMMATION_GENERATION_ALEATOIRE_H
#define PROGRAMMATION_GENERATION_ALEATOIRE_H

bool est_dans_intervalle (double u_genere, std::tuple<Intervalle *, Intervalle *, double *>& tIntervalle);

std::list<std::tuple<Intervalle *, Intervalle *, double *>>::iterator  recherche_intervalle
        (std::list<std::tuple<Intervalle *, Intervalle *, double *>>::iterator debut, std::list<std::tuple<Intervalle *,
         Intervalle *, double *>>::iterator fin, double u_genere);

std::vector<std::list<std::tuple<Intervalle *, Intervalle *, double *>>::iterator> *initialisation_index
        (std::list<std::tuple<Intervalle *, Intervalle *, double *>>::iterator itr, int C);

std::vector<double>* generation_aleatoire_index(std::list<std::tuple<Intervalle*, Intervalle*, double*>>& interpolations,
                                               const size_t nb_generations, const size_t ordre, int seed,
                                               bool affichage1);

std::vector<double>* generation_aleatoire_recherche(std::list<std::tuple<Intervalle*, Intervalle*, double*>>& interpolations,
                                                   const size_t nb_generations, const size_t ordre, int seed,
                                                   bool affichage1);

#endif //PROGRAMMATION_GENERATION_ALEATOIRE_H
