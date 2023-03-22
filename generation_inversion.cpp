/**
* \file generation_inversion.cpp
* \brief Définition d'une fonction effectuant un algorithme d'inversion numérique de fonction de répartition par interpolation.
* \author Julien April
* \version 0.1
* \date mars 2023
*
* Dans le cadre du cours MAT-3600 Projet de fin d'études
* Sous la supervision de Philippe-Adnré Luneau et Jean Deteix
*
*/
#include <random>
#include <chrono>

#include "generation_inversion.h"
#include "division.h"
#include "interpolation_hermite.h"
#include "generation_aleatoire.h"


std::vector<double>* generation_inversion(const size_t nb_generations, double (*fdr)(double),  double (*densite)(double),
                             double (*deriveedensite)(double), Intervalle inter,std::vector<double>&  ptsparticuliers,
                             const size_t ordre, double tol, double delta, int seed,
                             bool test_monoticite, bool affichage, bool affichage_generations, bool affichage_division_0, bool affichage_nbintervalles){

    auto start = std::chrono::steady_clock::now();
    /* INITIALISATION */
    // Division_0: on initialise le vecteur d'intervalles p, selon les pts particuliers.
    // Les points particuliers sont les extremums locaux et discontinuités de la densité et de ses dérivées.
    std::list<Intervalle*> p;
    Intervalle inter_copie = inter;
    division_0(p, ptsparticuliers, inter);


    /* PREMIÈRE DIVISION */
    // Division_1: on divise les intervalles en s'assurant que la condition F(p_{i+1}) - F(p_i) < delta
    // pour chaque intervalle de p.
    division_1(p,fdr,delta);

    /* DEUXIÈME DIVISION */
    //Initialisation interpolations. On initialise une liste qui contiendra toute l'information sur l'interpolation,
    // soient les intervalles en p, les intervalles en u, et les coefficients du polynome d'Hermite correspondant.
    std::list<std::tuple<Intervalle*, Intervalle*, double*>> interpolations;
    interpolations = *initialisation_interpolations(p, fdr, densite, deriveedensite, ordre);
    if (affichage_division_0) {
        std::cout << "p-Intervalles, u-Intervalles, Coefficients Hermite" << std::endl;
        for (auto &tIntervalle: interpolations) {
            double *hermite_coeff = std::get<2>(tIntervalle);
            std::cout << *std::get<0>(tIntervalle) << "   " << *std::get<1>(tIntervalle) << "   ";
            for (size_t i = 0; i<= ordre; i++) std::cout << *(hermite_coeff + i) << " "  ;
            std::cout << std::endl;
        }
    }

    //Division_2: On redivise encore les intervalles tant que l'erreur au point milieu de chaque u-intervalle est
    // plus petit que la tolérance tol. Pour la division, on divise l'intervalle en p.
    // Puis, on recalcule les nouveaux u_intervalles et les nouveaux coefficients des polynômes d'Hermite correspondants.
    division_2(interpolations, fdr, densite, deriveedensite, ordre, tol, test_monoticite);

    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double> secondes_ecoulees = end-start;


    /* GÉNÉRATION ALÉATOIRE */
    //Génération de nombres aléatoires et évaluation de H
    //std::vector<double> generations_recherche = generation_aleatoire_recherche(interpolations, nb_generations, ordre, seed, affichage_generations);
    auto start2 = std::chrono::steady_clock::now();
    std::vector<double>* generations_index = generation_aleatoire_index(interpolations, nb_generations, ordre, seed,
                                                                       affichage_generations);
    auto end2 = std::chrono::steady_clock::now();
    std::chrono::duration<double> secondes_ecoulees2 = end2-start2;


    if (affichage) {
        std::cout << std::endl << "DONN" << (char)144 << "ES ET R" << (char)144 << "SULTATS" << std::endl;
        std::cout << "G" << (char)130 << "n" << (char)130 << "ration de nombres al" << (char)130 << "atoires complt" << (char)130 << "t" << (char)130 << "e" << std::endl;
        switch(ordre){
            case 1:
                std::cout << "Interpolation lin" << (char)130 << "aire d'Hermite"<<std::endl;
                break;
            case 3: {
                std::cout << "Interpolation cubique d'Hermite";
                if (test_monoticite) std::cout << " avec test de monoticit" << (char)130 << std::endl;
                else std::cout << std::endl;
                break;
            }
            case 5:
                std::cout << "Interpolation quintique d'Hermite"<<std::endl;
                break;
        }
        std::cout << "Erreur-u maximale tol" << (char)130 << "r" << (char)130 << "e: " << tol <<std::endl;
        std::cout << "Sur l'intervalle " << inter_copie << std::endl;
        std::cout << "Nombres d'intervalles pour l'interpolation = " << interpolations.size()  <<  std::endl;
        std::cout << "Temps interpolation: " << secondes_ecoulees.count() << "s\n";
        std::cout << "Temps g" << (char)130 << "n" << (char)130 << "ration al" << (char)130 << "atoire par index: " << secondes_ecoulees2.count() << "s\n";
    }

    if(affichage_nbintervalles){
        std::cout << interpolations.size()  <<  std::endl;
    }
    return generations_index;
}
