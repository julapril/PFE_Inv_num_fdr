//
// Created by julap on 2023-03-06.
//
#include <random>
#include <chrono>

#include "generation_aleatoire.h"
#include "utilitaires.h"
#include "interpolation_hermite.h"

std::vector<double> generation_aleatoire_index(std::list<std::tuple<Intervalle*, Intervalle*, double*>>& interpolations,
                                               const size_t nb_generations, const size_t ordre, int seed,
                                               bool affichage1){

    auto start2 = std::chrono::steady_clock::now();

    std::vector<double> generations (nb_generations);
    std::default_random_engine generator;
    generator.seed(seed);
    std::uniform_real_distribution<double> distribution(0.0,1.0);

    int C = (int)(interpolations.size()/2);
    auto debut = interpolations.begin();
    auto index = initialisation_index(debut, C);

    for (size_t i = 0; i < nb_generations; i++){
        double u_genere = distribution(generator);
        std::list<std::tuple<Intervalle *, Intervalle *, double *>>::iterator tIntervalle;

        auto itr = index[(int)(u_genere*C)];
        tIntervalle = recherche_intervalle(itr,interpolations.end(), u_genere);

        //tIntervalle =recherche_intervalle(interpolations.begin(),interpolations.end(), u_genere);

        double H_u = evaluation_hermite(std::get<2>(*tIntervalle), u_genere, std::get<1>(*tIntervalle), ordre);
        generations[i] = H_u;
        if (affichage1)
            std::cout << "u = " << u_genere << ",  H(u) = " << H_u << std::endl;

    }
    auto end2 = std::chrono::steady_clock::now();
    std::chrono::duration<double> secondes_ecoulees2 = end2-start2;
    std::cout << "generation aleatoire index: " << secondes_ecoulees2.count() << "s\n";

    return generations;
}

std::vector<double> generation_aleatoire_recherche(std::list<std::tuple<Intervalle*, Intervalle*, double*>>& interpolations,
                                               const size_t nb_generations, const size_t ordre, int seed,
                                               bool affichage1){

    auto start2 = std::chrono::steady_clock::now();

    std::vector<double> generations (nb_generations);
    std::default_random_engine generator;
    generator.seed(seed);
    std::uniform_real_distribution<double> distribution(0.0,1.0);

    for (size_t i = 0; i < nb_generations; i++){
        double u_genere = distribution(generator);
        std::list<std::tuple<Intervalle *, Intervalle *, double *>>::iterator tIntervalle;

       tIntervalle =recherche_intervalle(interpolations.begin(),interpolations.end(), u_genere);

        double H_u = evaluation_hermite(std::get<2>(*tIntervalle), u_genere, std::get<1>(*tIntervalle), ordre);
        generations[i] = H_u;
        if (affichage1)
            std::cout << "u = " << u_genere << ",  H(u) = " << H_u << std::endl;

    }
    auto end2 = std::chrono::steady_clock::now();
    std::chrono::duration<double> secondes_ecoulees2 = end2-start2;
    std::cout << "generation aleatoire recherche: " << secondes_ecoulees2.count() << "s\n";

    return generations;
}