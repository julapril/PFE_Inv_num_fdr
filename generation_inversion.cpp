//
// Created by julap on 2023-02-28.
//
#include <list>
#include <tuple>
#include <random>
#include <iostream>

#include "generation_inversion.h"
#include "division.h"
#include "interpolation_hermite.h"
#include "generation_aleatoire.h"


std::vector<double> generation_inversion(const size_t nb_generations, double (*fdr)(double),  double (*densite)(double),
                             double (*deriveedensite)(double), Intervalle inter,std::vector<double>&  ptsparticuliers,
                             const size_t ordre, double tol, double delta, int seed,
                             bool test_monoticite, bool affichage, bool affichage1){

    /* INITIALISATION */
    // Division_0: on initialise le vecteur d'intervalles p, selon les pts particuliers.
    // Les points particuliers sont les extremums locaux et discontinuités de la densité et de ses dérivées.
    std::list<Intervalle*> p;
    division_0(p, ptsparticuliers, inter);


    /* PREMIÈRE DIVISION */
    // Division_1: on divise les intervalles en s'assurant que la condition F(p_{i+1}) - F(p_i) < delta
    // pour chaque intervalle de p.
    division_1(p,fdr,delta);

    if (affichage){
        std::cout << "Nombres d'intervalles (division 1) = " << p.size()  <<  std::endl;}
    if (affichage1){
        for (auto& pIntervalle: p) std::cout << *pIntervalle << std::endl;}

    /* DEUXIÈME DIVISION */
    //Initialisation interpolations. On initialise une liste qui contiendra toute l'information sur l'interpolation,
    // soient les intervalles en p, les intervalles en u, et les coefficients du polynome d'Hermite correspondant.
    std::list<std::tuple<Intervalle*, Intervalle*, double*>> interpolations;
    interpolations = *initialisation_interpolations(p, fdr, densite, deriveedensite, ordre);
    if (affichage1) {
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
    if (affichage){
        std::cout << "Nombres d'intervalles (division 2) = " << interpolations.size()  <<  std::endl; }


    /* GÉNÉRATION ALÉATOIRE */
    //Génération de nombres aléatoires et évaluation de H
    std::vector<double> generations_recherche = generation_aleatoire_recherche(interpolations, nb_generations, ordre, seed,
                                                                 affichage1);
    std::vector<double> generations_index = generation_aleatoire_index(interpolations, nb_generations, ordre, seed,
                                                                     affichage1);

    if (affichage)
        std::cout << "Generation de " << nb_generations << " nombres aleatoires completee." <<  std::endl;

    return generations_recherche;
}
