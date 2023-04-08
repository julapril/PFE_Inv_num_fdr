/**
* \file generation_aleatoire.cpp
* \brief Définition de fonctions générant des nombres aléatoires à partir d'une interpolation
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

#include "generation_aleatoire.h"
#include "interpolation_hermite.h"

/**
 * @fn est_dans_intervalle
 * @breif Vérifie si une valeur de u donnée est dans un triplet-intervalle.
 * @param u_genere La valeur de u générée.
 * @param tIntervalle Un triplet-intervalle.
 * @return true si u_genere est dans le tIntervalle et false sinon.
 */
bool est_dans_intervalle (double u_genere, std::tuple<Intervalle *, Intervalle *, double *>& tIntervalle)
{
    return *std::get<1>(tIntervalle) == u_genere;
}

/**
 * @fn recherche_intervalle
 * @brief Recherche le triplet-intervalle contenant un u donné parmi une liste.
 * @param debut itérateur pour le début de la recherche.
 * @param fin itérateur pour la fin de la recherche.
 * @param u_genere La valeur de u générée.
 * @return Un pointeur vers le triplet-intervalle contenant le u_genere. Si le u_genere n'est pas trouvé, on retourne fin.
 */
std::list<std::tuple<Intervalle *, Intervalle *, double *>>::iterator recherche_intervalle
        (std::list<std::tuple<Intervalle *, Intervalle *, double *>>::iterator debut,
         std::list<std::tuple<Intervalle *, Intervalle *, double *>>::iterator fin, double u_genere){
    for( ; debut != fin; debut++)
        if(est_dans_intervalle(u_genere, *debut))
            return debut;
    return fin;
}

/**
 * @fn initialisation_index
 * @brief Initialisation d'un index liant C valeurs équidistantes de u entre 0 et 1 à
 * C itérateurs pointant vers des triplets-intervalles.
 * @param itr Un itérateur de la liste des triplets-intervalles.
 * @param C La taille de l'index.
 * @return Un index d'itérateurs.
 */
std::vector<std::list<std::tuple<Intervalle *, Intervalle *, double *>>::iterator> *initialisation_index
        (std::list<std::tuple<Intervalle *, Intervalle *, double *>>::iterator itr, int C){

    auto index = new std::vector<std::list<std::tuple<Intervalle *, Intervalle *, double *>>::iterator> (C);
    (*index)[0] = itr;
    for (size_t i = 1; i<C; i++){
        double u = ((double)i)/C;
        while (!est_dans_intervalle(u,*itr)) itr++;
        (*index)[i] = itr;
    }
    return index;
}

/**
 * @fn generation_aleatoire_index
 * @brief Génération de nombre aléatoire selon l'interpolation donnée. On effectue une recherche par index.
 * @param interpolations Liste chaînée des triplet-intervalles contenant intervalle en p, intervalle en u, et coefficients d'Hermite.
 * @param nb_generations Nombre de générations aléatoires.
 * @param ordre Ordre de l'interpolation d'Hermite utilisée.
 * @param seed Seed utilisée pour la gnération aléatoire uniforme.
 * @param affichage1 Détermine si on affiche les nombres générés ou non.
 * @return Un vecteur de nombres aléatoires selon l'interpolation.
 */
std::vector<double>* generation_aleatoire_index(std::list<std::tuple<Intervalle*, Intervalle*, double*>>& interpolations,
                                               const size_t nb_generations, const size_t ordre, int seed,
                                               bool affichage1){

    std::vector<double>* generations = new std::vector<double>(nb_generations);
    //Initialisation du générateur de nombre uniforme.
    std::default_random_engine generator;
    generator.seed(seed);
    std::uniform_real_distribution<double> distribution(0.0,1.0);

    //Initialisation de l'index
    int C = (int)(interpolations.size());
    auto debut = interpolations.begin();
    auto index = initialisation_index(debut, C);

    if (affichage1) std::cout << std::endl << "NOMBRES G" << (char)144 << "N" << (char)144 << "R" << (char)144 << "S"<<std::endl;

    for (size_t i = 0; i < nb_generations; i++){
        //Génération d'un u de loi uniforme sur (0,1)
        double u_genere = distribution(generator);

        //Recherche du triplet-intervalle correspondant au u généré. On utilise l'index, puis une recherche linéaire.
        auto itr = (*index)[(int)(u_genere*C)];
        std::list<std::tuple<Intervalle *, Intervalle *, double *>>::iterator tIntervalle;
        tIntervalle = recherche_intervalle(itr,interpolations.end(), u_genere);

        //Utilisation des coefficients d'Hermite pour calculer H(u) et l'ajouter au vecteur qui sera retourné.
        double H_u = evaluation_hermite(std::get<2>(*tIntervalle), u_genere, std::get<1>(*tIntervalle), ordre);
        (*generations)[i] = H_u;
        if (affichage1)
            printf("u = %.10f, H(u) = %+.10f \n", u_genere,H_u);
    }

    //Suppression du contenu de l'index
    delete index;

    return generations;
}

/**
 * @fn generation_aleatoire_recherche
 * @brief Génération de nombre aléatoire selon l'interpolation donnée. On effectue une recherche linéaire.
 * @param interpolations Liste chaînée des triplet-intervalles contenant intervalle en p, intervalle en u, et coefficients d'Hermite.
 * @param nb_generations Nombre de générations aléatoires.
 * @param ordre Ordre de l'interpolation d'Hermite utilisée.
 * @param seed Seed utilisée pour la gnération aléatoire uniforme.
 * @param affichage1 Détermine si on affiche les nombres générés ou non.
 * @return Un vecteur de nombres aléatoires selon l'interpolation.
 */
std::vector<double>* generation_aleatoire_recherche(std::list<std::tuple<Intervalle*, Intervalle*, double*>>& interpolations,
                                               const size_t nb_generations, const size_t ordre, int seed,
                                               bool affichage1){

    std::vector<double>* generations = new std::vector<double>(nb_generations);
    std::default_random_engine generator;
    generator.seed(seed);
    std::uniform_real_distribution<double> distribution(0.0,1.0);

    for (size_t i = 0; i < nb_generations; i++){
        double u_genere = distribution(generator);
        std::list<std::tuple<Intervalle *, Intervalle *, double *>>::iterator tIntervalle;

       tIntervalle =recherche_intervalle(interpolations.begin(),interpolations.end(), u_genere);

        double H_u = evaluation_hermite(std::get<2>(*tIntervalle), u_genere, std::get<1>(*tIntervalle), ordre);
        (*generations)[i] = H_u;
        if (affichage1)
            printf("u = %.10f, H(u) = %+.10f \n", u_genere,H_u);

    }

    return generations;
}