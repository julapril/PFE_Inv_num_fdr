/**
* \file Intervalle.cpp
* \brief Implémentation de la classe Intervalle
* \author Julien April
* \version 0.1
* \date mars 2023
*
* Dans le cadre du cours MAT-3600 Projet de fin d'études
* Sous la supervision de Philippe-Adnré Luneau et Jean Deteix
*
*/

#include "Intervalle.h"

/**
 * @fn Intervalle::Intervalle(double inf, double sup)
 * @brief Constructeur de la classe Intervalle
 *
 * @param inf représente la borne inférieure de l'intervalle
 * @param sup représente la borne supérieure de l'intervalle
 *
 * @exception logic_error si inf est plus petite que sup
 */
Intervalle::Intervalle(double inf, double sup){
    if (inf > sup)
        throw std::logic_error("La borne inferieure de l'intervalle est plus grande que la borne superieure.");
    a = inf;
    b = sup;
}

/**
 * @fn Intervalle::~Intervalle()
 * @brief Destructeur de la classe Intervalle
 *
 * @post Une instance de la classe est détruite
 */
Intervalle::~Intervalle(){}

/**
 *@fn Intervalle::getInf() const
 * @return double La borne inférieure de l'intervalle
 */
double Intervalle::getInf() const{
    return a;
}

/**
 * @fn Intervalle::getSup() const
 * @return double La borne supérieure de l'intervalle
 */
double Intervalle::getSup() const{
    return b;
}

/**
 * @fn Intervalle::operator<(Intervalle inter) const
 * @brief Surcharge de l'opérateur "plus petit que" avec un intervalle
 *
 * @param inter Intervalle avec lequel on compare l'instance.
 * @return true si la borne supérieure de l'instance est plus petite
 * que la borne inférieure de l'intervalle inter et false sinon
 */
bool Intervalle::operator<(Intervalle inter) const{
    return getSup() < inter.getInf();
}

/**
 * @fn Intervalle::operator>(Intervalle inter) const
 * @brief Surcharge de l'opérateur "plus grand que" avec un intervalle
 *
 * @param inter Intervalle avec lequel on compare l'instance.
 * @return true si la borne inférieure de l'instance est plus grande
 * que la borne supérieure de l'intervalle inter et false sinon
 */
bool Intervalle::operator>(Intervalle inter) const{
    return getInf() > inter.getSup();
}

/**
 * @fn Intervalle::operator==(Intervalle inter) const
 * @brief Surcharge de l'opérateur "égal à" avec un intervalle
 *
 * @param inter Intervalle avec lequel on compare l'instance.
 * @return true si les bornes inférieures et supérieures des
 * intervalles sont égales et false sinon
 */
bool Intervalle::operator==(Intervalle inter) const{
    return getInf() == inter.getInf() && b == inter.getSup();
}

/**
 * @fn Intervalle::operator<(double x) const
 * @brief Surcharge de l'opérateur "plus petit que" avec un nombre de type double
 *
 * @param double Nombre avec lequel on compare l'intervalle.
 * @return true si le nombre est plus grand que la borne supérieure
 * de l'intervalle et false sinon
 */
bool Intervalle::operator<(double x) const{
    return getSup() < x;
}

/**
 * @fn Intervalle::operator>(double x) const
 * @brief Surcharge de l'opérateur "plus grand que" avec un nombre de type double
 *
 * @param double Nombre avec lequel on compare l'intervalle.
 * @return true si le nombre est plus petit que la borne inférieure
 * de l'intervalle et false sinon
 */
bool Intervalle::operator>(double x) const {
    return getInf() > x;
}

/**
 * @fn Intervalle::operator==(double x) const
 * @brief Surcharge de l'opérateur "égal" avec un nombre de type double
 *
 * @param double Nombre avec lequel on compare l'intervalle.
 * @return true si le nombre est dans l'intervalle et false sinon
 */
bool Intervalle::operator==(double x) const{
    return getInf() <= x && x <= getSup();
}

/**
 * @fn Intervalle::milieu() const
 * @return double Le point milieu de l'intervalle
 */
double Intervalle::milieu() const{
    return (a+b)/2;
}

/**
 * @fn Intervalle::setInf(double inf)
 * @brief Mutateur pour l'attribut de borne inférieure
 * @param inf La nouvelle valeur de borne inférieure
 * @exception logic_error si la nouvelle borne inférieure est plus grande que la borne supérieure
 */
void Intervalle::setInf(double inf) {
    if(inf > getSup())
        throw std::logic_error("La borne inférieure de l'intervalle est plus grande que la borne supérieure.");
    a = inf;
}

/**
 * @fn Intervalle::setSup(double sup)
 * @brief Mutateur pour l'attribut de borne supérieure
 * @param inf La nouvelle valeur de borne supérieure
 * @exception logic_error si la nouvelle borne supérieure est plus petite que la borne inférieure
 */
void Intervalle::setSup(double sup) {
    if(sup < getInf())
        throw std::logic_error("La borne inférieure de l'intervalle est plus grande que la borne supérieure.");
    b = sup;
}

/**
 * @fn operator<<(std::ostream& out, const Intervalle& inter)
 * @brief Surcharge de l'opérateur d'affichage "<<"
 * @param out ostream
 * @param inter Intervalle à afficher
 * @return std::ostream& out
 */
std::ostream& operator<<(std::ostream& out, const Intervalle& inter){
    out << "[" << inter.getInf() << ", " << inter.getSup() << "]";
    return out;
}


