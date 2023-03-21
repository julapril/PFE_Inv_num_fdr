/**
* \file division.cpp
* \brief Définition de fonctions liées à la division et la division récursive des intervalles
 * lors de l'interpolation d'Hermite d'ordre 1, 3 et 5.
* \author Julien April
* \version 0.1
* \date mars 2023
*
* Dans le cadre du cours MAT-3600 Projet de fin d'études
* Sous la supervision de Philippe-Adnré Luneau et Jean Deteix
*
*/

#include <cmath>
#include <algorithm>

#include "division.h"
#include "interpolation_hermite.h"

/**
 * @fn division_0(std::list<Intervalle*>& p, std::vector<double>&  ptsparticuliers, Intervalle& inter)
 * @brief Initialisation du vecteur d'intervalles p, selon les pts particuliers.
 * @param p Le vecteur d'intervalles en p.
 * @param ptsparticuliers Les extremums locaux et discontinuités de la densité et de ses dérivées.
 * @param inter Le support de la variable aléatoire, l'intervalle de départ.
 */
void division_0(std::list<Intervalle*>& p, std::vector<double>&  ptsparticuliers, Intervalle& inter){

    if (ptsparticuliers.empty())
        p.emplace_front(&inter);
    else{
        std::sort(ptsparticuliers.begin(), ptsparticuliers.end());
        size_t lg = ptsparticuliers.size();

        if (!(inter == ptsparticuliers[0]) || !(inter == ptsparticuliers[lg-1]))
            throw std::logic_error("Au moins un point particulier n'est pas dans le support de la variable aléaoitre");

        p.push_back( new Intervalle(inter.getInf(),ptsparticuliers[0]));
        for(auto itr = ptsparticuliers.end() - 1; itr != ptsparticuliers.begin();)
            p.push_back(new Intervalle(*(--itr),*(itr)));
        p.push_back(new Intervalle(ptsparticuliers[lg-1],inter.getSup()));
    }
}

/**
 * @fn respecte_condition_1(Intervalle* inter, double (*fdr)(double), double delta)
 * @brief Vérifie si la condition F(p_{i+1}) - F(p_i) < delta est respectée pour un intervalle en p donné.
 * @param inter Un intervalle en p.
 * @param fdr La fonction de répartition.
 * @param delta La tolérance pour la première division.
 * @return true si la condition est respectée, et false sinon
 */
bool respecte_condition_1(Intervalle* inter, double (*fdr)(double), double delta) {
    return ( (fdr(inter->getSup()) - fdr(inter->getInf())) < delta );
}

void division_1(std::list<Intervalle*>& p, double (*fdr)(double), double delta){
    for(auto itr = p.begin(); itr != p.end(); itr++)
        if(! respecte_condition_1(*itr,fdr, delta))
            division_1_recursif(p,itr, fdr, delta);
}
void division_1_recursif(std::list<Intervalle*>& p, std::list<Intervalle*>::iterator itr,
                         double (*fdr)(double), double delta){

    if(! respecte_condition_1(*itr,fdr, delta)){
        double b = (*itr)->getSup();
        double m = (*itr)->milieu();
        (*itr)->setSup(m);
        Intervalle* inter = new Intervalle(m,b);
        //Insérer inter dans la liste
        itr++;
        p.insert(itr,inter);
        itr--;
        itr--;
        //Récursivité
        division_1_recursif(p,itr,fdr,delta);
        itr++;
        division_1_recursif(p,itr,fdr,delta);
    }
}


 /**
  * @fn respecte_condition_2( std::tuple<Intervalle*, Intervalle*, double*>& tIntervalle,
  * double (*fdr)(double), const size_t ordre, double tol)
  * @brief Vérifie si l'erreur au point milieu de d'un u-intervalle donné est plus petit que la tolérance tol.
  * @param tIntervalle Un triplet-intervalle contenant intervalle en p, intervalle en u, et coefficients d'Hermite.
  * @param fdr La fonction de répartition.
  * @param ordre L'ordre de l'interpolation d'Hermite.
  * @param tol La tolérence sur l'erreur pour la division_2.
  * @return true si la condition est respectée, et false sinon
  */
bool respecte_condition_2 (std::tuple<Intervalle*, Intervalle*, double*>& tIntervalle,
                           double (*fdr)(double), const size_t ordre, double tol){
    double m_u = (*std::get<1>(tIntervalle)).milieu();
    double* coeff = std::get<2> (tIntervalle);
    Intervalle* inter_u = std::get<1>(tIntervalle);
    double H_u = evaluation_hermite(coeff,m_u,inter_u, ordre);
    double err_estimee = std::abs(fdr(H_u) - m_u);
    return err_estimee < tol;
}

bool est_monotone (std::tuple<Intervalle*, Intervalle*, double*>& tIntervalle,
                   double (*densite)(double), const size_t ordre, bool test_monoticite){
    if(!test_monoticite) return true;
    else {
        switch (ordre) {
            case 1:
                return true;
            case 3: {
                double p1 = std::get<0>(tIntervalle)->getInf();
                double p2 = std::get<0>(tIntervalle)->getSup();
                double u1 = std::get<1>(tIntervalle)->getInf();
                double u2 = std::get<1>(tIntervalle)->getSup();
                double f1 = densite(p1);
                double f2 = densite(p2);
                double pente = (u2 - u1) / (p2 - p1) / 3;
                return (f1 >= pente && f2 >= pente);
            }
            case 5:
                return true;
            default:
                throw std::logic_error("L'ordre de l'interpolation d'Hermite doit etre 1,3, ou 5.");
        }
    }
}

void division_2(std::list<std::tuple<Intervalle*, Intervalle*, double*>>& interpolations,
                double (*fdr)(double), double (*densite)(double), double (*deriveedensite)(double),
                const size_t ordre, double tol, bool test_monoticite){
    for(auto itr = interpolations.begin(); itr != interpolations.end(); itr++)
        if(! respecte_condition_2(*itr,fdr, ordre, tol) || !est_monotone(*itr, densite, ordre, test_monoticite))
            division_2_recursif(interpolations,itr, fdr, densite, deriveedensite, ordre, tol, test_monoticite);
}

void division_2_recursif(std::list<std::tuple<Intervalle*, Intervalle*, double*>>& interpolations,
                         std::list<std::tuple<Intervalle*, Intervalle*, double*>>::iterator itr,
                         double (*fdr)(double), double (*densite)(double), double (*deriveedensite)(double),
                         const size_t ordre, double tol, bool test_monoticite){
    if(! respecte_condition_2(*itr,fdr,ordre, tol) || !est_monotone(*itr, densite, ordre, test_monoticite)){
        double b = std::get<0>(*itr)->getSup();
        double m = std::get<0>(*itr)->milieu();
        double F_b = std::get<1>(*itr)->getSup();
        double F_m = fdr(m);
        std::get<0>(*itr)->setSup(m);
        std::get<1>(*itr)->setSup(F_m);
        delete[] std::get<2>(*itr);

        Intervalle* inter_p = new Intervalle(m,b);
        Intervalle* inter_u = new Intervalle(F_m, F_b);

        double* hermite_coeff;
        switch(ordre) {
            case 1:
                hermite_coeff = hermite_lineaire(inter_p);
                std::get<2>(*itr) = hermite_lineaire(std::get<0>(*itr));
                break;
            case 3:
                hermite_coeff = hermite_cubique(inter_p, inter_u, densite);
                std::get<2>(*itr) =
                        hermite_cubique(std::get<0>(*itr), std::get<1>(*itr), densite);
                break;
            case 5:
                hermite_coeff = hermite_quintique(inter_p, inter_u, densite, deriveedensite);
                std::get<2>(*itr) =
                        hermite_quintique(std::get<0>(*itr), std::get<1>(*itr), densite, deriveedensite);
                break;
            default:
                throw std::logic_error("L'ordre de l'interpolation d'Hermite doit etre 1,3, ou 5.");
        }
        std::tuple<Intervalle*, Intervalle*, double*> tIntervalle = std::make_tuple (inter_p, inter_u, hermite_coeff);
        //Insérer inter dans la liste
        itr++;
        interpolations.insert(itr,tIntervalle);
        itr--;
        itr--;
        //Récursivité
        division_2_recursif(interpolations,itr,fdr, densite, deriveedensite, ordre, tol, test_monoticite);
        itr++;
        division_2_recursif(interpolations, itr, fdr, densite, deriveedensite, ordre, tol, test_monoticite);
    }
}
