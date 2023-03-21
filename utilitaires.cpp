//
// Created by julap on 2023-03-01.
//

#include "utilitaires.h"
bool est_dans_intervalle (double u_genere, std::tuple<Intervalle *, Intervalle *, double *>& tIntervalle)
{
    return *std::get<1>(tIntervalle) == u_genere;
}

std::list<std::tuple<Intervalle *, Intervalle *, double *>>::iterator recherche_intervalle
(std::list<std::tuple<Intervalle *, Intervalle *, double *>>::iterator debut,
 std::list<std::tuple<Intervalle *, Intervalle *, double *>>::iterator fin, double u_genere){
    for( ; debut != fin; debut++)
        if(est_dans_intervalle(u_genere, *debut))
            return debut;
    return fin;
}

std::vector<std::list<std::tuple<Intervalle *, Intervalle *, double *>>::iterator> initialisation_index
(std::list<std::tuple<Intervalle *, Intervalle *, double *>>::iterator itr, int C){

    std::vector<std::list<std::tuple<Intervalle *, Intervalle *, double *>>::iterator> index (C);
    index[0] = itr;
    for (size_t i = 1; i<C; i++){
        double u = ((double)i)/C;
        while (!est_dans_intervalle(u,*itr)) itr++;
        index[i] = itr;
    }
    return index;
}
