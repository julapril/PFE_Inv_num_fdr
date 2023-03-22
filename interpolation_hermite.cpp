/**
* \file interpolation_hermite.cpp
* \brief Définition de fonctions liées à l'interpolation d'hermite d'ordre 1, 3 et 5.
* \author Julien April
* \version 0.1
* \date mars 2023
*
* Dans le cadre du cours MAT-3600 Projet de fin d'études
* Sous la supervision de Philippe-Adnré Luneau et Jean Deteix
*
*/

#include <cmath>
#include <tuple>

#include "interpolation_hermite.h"

/**
 * @fn double evaluation_hermite
 * @brief Fonction permettant d'évaluer le polynôme d'Hermite selon ses coefficients.
 * Puisque les coefficients sont donnés pour un u_tilde entre 0 et 1, on doit ajuster la valeur de u.
 * @param coeff Les coefficients du polynome d'Hermite
 * @param u La valeur de u pour laquelle on évalue le polynome d'Hermite.
 * @param inter_u L'intervalle dans lequel se situe le u.
 * @param ordre L'ordre d'interpolation
 * @return double La valeur de l'évaluation du polynôme d'Hermite en u.
 */
double evaluation_hermite(double* coeff, double u, Intervalle* inter_u, const size_t ordre){
    double evaluation = 0;
    double u_tilde = (u - inter_u->getInf()) / (inter_u->getSup() - inter_u->getInf());
    for (size_t i = 0; i <= ordre; i++)
        evaluation += *(coeff + i) * pow(u_tilde,i);
    return evaluation;
}

/**
 * @fn double* hermite_lineaire
 * @brief Fonction calculant les coefficients du polynome d'Hermite pour l'ordre 1.
 * @param inter_p L'intervalle en p où l'interpolation est effectuée.
 * @return double* Un tableau contenant les coefficients de l'interpolation d'ordre 1.
 */
double* hermite_lineaire(Intervalle* inter_p){
    double p1 = inter_p->getInf();
    double p2 = inter_p->getSup();
    double* L = new double [2];
    L[0] = p1;
    L[1] = p2-p1;
    return L;
}

/**
 * @fn double* hermite_cubique
 * @brief Fonction calculant les coefficients du polynome cubique d'Hermite.
 * @param inter_p L'intervalle en p où l'interpolation est effectuée.
 * @param inter_u L'intervalle en u où l'interpolation est effectuée.
 * @param densite La densité de la variable aléatoire.
 * @return double* Un tableau contenant les coefficients de l'interpolation d'ordre 3.
 */
double* hermite_cubique(Intervalle* inter_p, Intervalle* inter_u, double (*densite)(double)){
    double p1 = inter_p->getInf();
    double p2 = inter_p->getSup();
    double u1 = inter_u->getInf();
    double u2 = inter_u->getSup();

    double f1 = densite(p1);
    double f2 = densite(p2);

    double* C = new double[4];
    C[0] = p1;
    C[1] = (u2-u1)/f1;
    C[2] = 3*(p2-p1) - (u2-u1)*(2/f1 + 1/f2);
    C[3] = 2*(p1-p2) + (u2-u1)*(1/f1 + 1/f2);
    return C;
}

/**
 * @fn double* hermite_quintique
 * @brief Fonction calculant les coefficients du polynome quintique d'Hermite.
 * @param inter_p L'intervalle en p où l'interpolation est effectuée.
 * @param inter_u L'intervalle en u où l'interpolation est effectuée.
 * @param densite La densité de la variable aléatoire.
 * @param deriveedensite La dérivée de la densité de la variable aléatoire.
 * @return double* Un tableau contenant les coefficients de l'interpolation d'ordre 5.
 */
double* hermite_quintique(Intervalle* inter_p, Intervalle* inter_u,
                          double (*densite)(double), double (*deriveedensite)(double)){
    double p1 = inter_p->getInf();
    double p2 = inter_p->getSup();
    double u1 = inter_u->getInf();
    double u2 = inter_u->getSup();

    double f1 = densite(p1);
    double df1 = deriveedensite(p1);
    double f2 = densite(p2);
    double df2 = deriveedensite(p2);
    double du = u2 - u1;
    double dp = p2 - p1;

    double* Q = new double[6];
    Q[0] = p1;
    Q[1] = du/f1;
    Q[2] = -du*du*df1/2/pow(f1,3);
    Q[5] = -du*du*df2/2/pow(f2,3) - 3*du/f2 + 6*dp - 3*Q[1] - Q[2];
    Q[4] = du/f2 -3*dp +2*Q[1] + Q[2] - 2*Q[5];
    Q[3] = dp - Q[1] - Q[2] - Q[4] - Q[5];
    return Q;
}

/**
 * @fn  initialisation_interpolations
 * @brief Fonction initialisant une liste contenant toute l'information sur l'interpolation.
 * @param p La liste des intervalles en p.
 * @param fdr La fonction de répartition de la variable aléatoire.
 * @param densite La fonction densité de la variable aléatoire.
 * @param deriveedensite La dérivée de la densité de la variable aléatoire.
 * @param ordre L'ordre d'interpolation
 * @return list<tuple<Intervalle*, Intervalle*, double*>>* une liste contenant toute l'information sur l'interpolation.
 * Pour chaque noeud de la liste, la première entrée donne l'intervalle en p, la deuxième l'intervalle en u,
 * et la troisième les coefficients de l'interpolation d'Hermite correspondante.
 */
std::list<std::tuple<Intervalle*, Intervalle*, double*>>* initialisation_interpolations
(std::list<Intervalle*> p, double (*fdr)(double),  double (*densite)(double), double (*deriveedensite)(double), const size_t ordre){

    std::list<std::tuple<Intervalle*, Intervalle*, double*>>* interpolations;
    for(auto& inter_p: p) {
        double p1 = inter_p->getInf();
        double p2 = inter_p->getSup();
        //Initialisation de l'intervalle en u
        double u1 = fdr(p1);
        double u2 = fdr(p2);
        Intervalle* inter_u = new Intervalle(u1,u2);

        //Initialisation des coefficients d'Hermite
        double* hermite_coeff;
        switch(ordre) {
            case 1:
                hermite_coeff = hermite_lineaire(inter_p);
                break;
            case 3:
                hermite_coeff = hermite_cubique(inter_p, inter_u, densite);
                break;
            case 5:
                hermite_coeff = hermite_quintique(inter_p, inter_u, densite, deriveedensite);
                break;
            default:
                throw std::logic_error("L'ordre de l'interpolation d'Hermite doit etre 1,3, ou 5.");
        }
        //Initialisation du tuple inter_p, inter_u, hermite_coefficient et ajout à la liste interpolations
        std::tuple<Intervalle *, Intervalle *, double *> triplet_p_u_interpo = std::make_tuple (inter_p,inter_u, hermite_coeff);
        interpolations->push_back(triplet_p_u_interpo);
    }
    return interpolations;
}

