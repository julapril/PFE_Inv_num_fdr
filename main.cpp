#include <iostream>
#include <cmath>
#include <chrono>
#include <random>

#include "generation_inversion.h"
#include "distributions_statistiques.h"

int main() {
/*
  //COMPARAISON AVEC LE PACKAGE DE C++
    auto start1 = std::chrono::steady_clock::now();

    const int nrolls = 1000000;  // number of experiments
    std::default_random_engine generator;
    std::normal_distribution<double> distribution(0.0, 1.0);
    std::vector<double> generations_random(nrolls);
    for (int i = 0; i < nrolls; ++i) {
        generations_random[i] = distribution(generator);
    }
    auto end1 = std::chrono::steady_clock::now();

    std::chrono::duration<double> secondes_ecoulees1 = end1 - start1;
    std::cout << "Temps total c++: " << secondes_ecoulees1.count() << "s\n";
*/
    char quit = 'r';
    while(quit != 'q'){

    int distr;
    int nb_generations;
    int seed;
    int ordre = 3;
    char r1;
    int nb_pts_particuliers;
    std::vector<double> pts_particuliers;
    bool test_monoticite = false;
    double tol = 1e-12;
    double delta = 0.05;
    bool affichage_generations = true;
    bool affichage = true;

    std::cout << "*******************************************************************************" << std::endl;
    std::cout << "*  G" << (char) 130 << "n" << (char) 130 << "rateur al" << (char) 130 << "atoire par inversion num"
              << (char) 130 << "rique des fonctions de r" << (char) 130 << "partition  *" << std::endl;
    std::cout << "*  Par Julien April                                                           *" << std::endl;
    std::cout << "*  Dans le cadre de: MAT-3600 Projet de fin d'" << (char) 130 << "tudes                          *"
              << std::endl;
    std::cout << "*  Sous la supervision de Philippe-Andr" << (char) 130 << " Luneau et Jean Deteix                *"
              << std::endl;
    std::cout << "*******************************************************************************" << std::endl
              << std::endl;

    std::cout << "PARTIE 1: G" << (char)130 << "n" << (char)130 << "ration al" << (char)130 << "atoire manuelle" << std::endl;
    std::cout << "Distributions statistiques" << std::endl;
    std::cout << "1. Loi normale" << std::endl;
    std::cout << "2. Loi de Cauchy" << std::endl;
    std::cout << "3. Loi exponentielle" << std::endl;
    std::cout << "4. Loi Gamma(5)" << std::endl;
    std::cout << "5. Loi Gamma(1/2)" << std::endl;
    std::cout << "6. Loi Beta(2,2)" << std::endl;
    std::cout << "7. Loi Beta(0.3,3)" << std::endl;
    std::cout << "Veuillez entrer une distribution statistique pour laquelle vous souhaiter g" << (char) 130 << "n"
              << (char) 130 << "rer des nombres al" << (char) 130 << "atoires:" << std::endl;
    std::cin >> distr;
    std::cout << "Combien de nombres voulez-vous g" << (char) 130 << "n" << (char) 130 << "rer?:" << std::endl;
    std::cin >> nb_generations;
    if (nb_generations > 50) affichage_generations = false;
    std::cout << "Entrez une racine pour le g" << (char) 130 << "n" << (char) 130
              << "rateur uniforme (n'importe quel nombre) :" << std::endl;
    std::cin >> seed;
    std::cout << "Voulez-vous utiliser les param" << (char) 138 << "tres par d" << (char) 130
              << "faut pour l'algorithme?(o/n)" << std::endl;
    std::cin >> r1;
    if (r1 == 'n') {
        std::cout << "Quel ordre de l'interpolation d'Hermite (1,3 ou 5):" << std::endl;
        std::cin >> ordre;
        if (ordre == 3) {
            std::cout << "Voulez-vous que l'interpolation soit monotone? (o/n)" << std::endl;
            std::cout
                    << "(Si oui, un test de monoticit" << (char) 130 << " sera effectu" << (char) 130
                    << ", et les intervalles non monotones" <<std::endl <<"seront divis" << (char) 130 << "s jusqu'" << (char) 133
                    << " respecter toutes les conditions)."
                    << std::endl;
            std::cin >> r1;
            if (r1 == 'o')
                test_monoticite = true;
            else
                test_monoticite = false;
        }
        std::cout << "Voulez-vous ajouter des points particuliers pour l'interpolation? (o/n)" << std::endl;
        std::cout
                << "(Il est sugg" << (char) 130 << "r" << (char) 130
                << " d'ajouter les extremums locaux et discontinuit" << (char) 130 << "s de la densit" << (char) 130
                << " et de ses d" << (char) 130 << "riv" << (char) 130 << "es.)"
                << std::endl;
        std::cin >> r1;
        if (r1 == 'o') {
            std::cout << "Combien?" << std::endl;
            std::cin >> nb_pts_particuliers;
            pts_particuliers.reserve(nb_pts_particuliers);
            std::cout << "Entrez les " << nb_pts_particuliers
                      << " points particuliers en appuyant sur enter entre chacun." << std::endl;
            for (int i = 0; i < nb_pts_particuliers; i++)
                std::cin >> pts_particuliers[i];
        }
        std::cout << "Entrez l'erreur-u maximale tol" << (char) 130 << "r" << (char) 130
                  << "e (exemple de format: 1e-12): " << std::endl;
        std::cin >> tol;
        std::cout << "Souhaitez-vous que les nombres g" << (char) 130 << "n" << (char) 130 << "r" << (char) 130
                  << "es soient affich" << (char) 130 << "s? (o/n):" << std::endl;
        std::cin >> r1;
        affichage_generations = (r1 == 'o') ? true : false;

        std::cout << "Souhaitez-vous que les statistiques (temps et nombres d'intervalles) soient affich" << (char) 130
                  << "es? (o/n):"
                  << std::endl;
        std::cin >> r1;
        affichage = (r1 == 'o') ? true : false;
    }


    switch (distr) {
        case 1: {
            Intervalle interNormale = Intervalle(-6, 6);
            generation_inversion(nb_generations, fdrNormale, densiteNormale, deriveedensiteNormale,
                                               interNormale, pts_particuliers, ordre, tol, delta, seed,
                                               test_monoticite, affichage, affichage_generations, false, false);
            break;
        }
        case 2: {
            Intervalle interCauchy = Intervalle(-1e12, 1e12);
            generation_inversion(nb_generations, fdrCauchy, densiteCauchy, deriveedensiteCauchy,
                                               interCauchy, pts_particuliers, ordre, tol, delta, seed,
                                               test_monoticite, affichage, affichage_generations, false, false);
            break;
        }
        case 3: {
            Intervalle interExponentielle = Intervalle(0, 30);
            generation_inversion(nb_generations, fdrExponentielle, densiteExponentielle, deriveedensiteExponentielle,
                                               interExponentielle, pts_particuliers, ordre, tol, delta, seed,
                                               test_monoticite, affichage, affichage_generations, false, false);
            break;
        }

        case 4: {
            Intervalle interGamma5 = Intervalle(.005, 35);
            generation_inversion(nb_generations, fdrGamma5, densiteGamma5, deriveedensiteGamma5,
                                               interGamma5, pts_particuliers, ordre, tol, delta, seed,
                                               test_monoticite, affichage, affichage_generations, false, false);
            break;
        }
        case 5: {
            Intervalle interGamma1_2 = Intervalle(1e-14, 20);
            generation_inversion(nb_generations, fdrGamma1_2, densiteGamma1_2, deriveedensiteGamma1_2,
                                               interGamma1_2, pts_particuliers, ordre, tol, delta, seed,
                                               test_monoticite, affichage, affichage_generations, false, false);
            break;
        }
        case 6: {
            Intervalle interBeta2_2 = Intervalle(1e-6,1-1e-6);
            generation_inversion(nb_generations, fdrBeta2_2, densiteBeta2_2, deriveedensiteBeta2_2,
                                               interBeta2_2, pts_particuliers, ordre, tol, delta, seed,
                                               test_monoticite, affichage, affichage_generations, false, false);
            break;
        }
        case 7: {
            Intervalle interBeta_0p3_3 = Intervalle(1e-16,0.9);
            if (ordre == 1) interBeta_0p3_3 = Intervalle(0, 0.999);
            else interBeta_0p3_3 = Intervalle(1e-16, 0.9);
            generation_inversion(nb_generations, fdrBeta_0p3_3, densiteBeta_0p3_3, deriveedensiteBeta_0p3_3,
                                               interBeta_0p3_3, pts_particuliers, ordre, tol, delta, seed,
                                               test_monoticite, affichage, affichage_generations, false, false);
            break;
        }
        default:
            throw std::logic_error("La distribution entree n'est pas valide.");
    }

    std::cout << std::endl << "Quitter (q) ou Recommencer(r)?" << std::endl;
    std::cin >> quit;
    }



    int distr;
    int nb_generations = 1;
    int seed = 123;
    int ordre;
    bool test_monoticite = true;
    double tol;
    double delta = 0.05;
    std::vector<double> pts_particuliers;
    bool affichage_generations = false;
    bool affichage = false;
    bool affichage_nbintervalles = true;

    std::cout << std::endl << "PARTIE 2: Calcul du nombres d'intervalles utilis" << (char)130 << "es lors de l'interpolation pour chaque ordre,"
    << std::endl <<"          pour quelques valeurs d'erreur-u et pour toutes les distributions" << std::endl;
    for(ordre = 1; ordre < 6; ordre = ordre+2) {
        switch(ordre){
            case 1:
                std::cout << "INTERPOLATION LIN" << (char)144 << "AIRE"<<std::endl;
                break;
            case 3:
                std::cout << "INTERPOLATION CUBIQUE"<<std::endl;
                break;
            case 5:
                std::cout << "INTERPOLATION QUINTIQUE"<<std::endl;
                break;
        }
        for (tol = 1e-6; tol > 1e-13; tol = tol / 100) {
            std::cout << "(Erreur-u = " << tol << " )" << std::endl;
            for (distr = 1; distr < 8; distr++) {
                std::cout << distr <<": ";
                switch (distr) {
                    case 1: {
                        Intervalle interNormale = Intervalle(-6, 6);
                        generation_inversion(nb_generations, fdrNormale, densiteNormale, deriveedensiteNormale,
                                             interNormale, pts_particuliers, ordre, tol, delta, seed,
                                             test_monoticite, affichage, affichage_generations, false,
                                             affichage_nbintervalles);
                        break;
                    }
                    case 2: {
                        Intervalle interCauchy = Intervalle(-1e12, 1e12);
                        generation_inversion(nb_generations, fdrCauchy, densiteCauchy, deriveedensiteCauchy,
                                             interCauchy, pts_particuliers, ordre, tol, delta, seed,
                                             test_monoticite, affichage, affichage_generations, false,
                                             affichage_nbintervalles);
                        break;
                    }
                    case 3: {
                        Intervalle interExponentielle = Intervalle(0, 30);
                        generation_inversion(nb_generations, fdrExponentielle, densiteExponentielle,
                                             deriveedensiteExponentielle,
                                             interExponentielle, pts_particuliers, ordre, tol, delta, seed,
                                             test_monoticite, affichage, affichage_generations, false,
                                             affichage_nbintervalles);
                        break;
                    }

                    case 4: {
                        Intervalle interGamma5 = Intervalle(.005, 35);
                        generation_inversion(nb_generations, fdrGamma5, densiteGamma5, deriveedensiteGamma5,
                                             interGamma5, pts_particuliers, ordre, tol, delta, seed,
                                             test_monoticite, affichage, affichage_generations, false,
                                             affichage_nbintervalles);
                        break;
                    }
                    case 5: {
                        Intervalle interGamma1_2 = Intervalle(1e-14, 20);
                        generation_inversion(nb_generations, fdrGamma1_2, densiteGamma1_2, deriveedensiteGamma1_2,
                                             interGamma1_2, pts_particuliers, ordre, tol, delta, seed,
                                             test_monoticite, affichage, affichage_generations, false,
                                             affichage_nbintervalles);
                        break;
                    }
                    case 6: {
                        Intervalle interBeta2_2 = Intervalle(1e-6, 1 - 1e-6);
                        generation_inversion(nb_generations, fdrBeta2_2, densiteBeta2_2, deriveedensiteBeta2_2,
                                             interBeta2_2, pts_particuliers, ordre, tol, delta, seed,
                                             test_monoticite, affichage, affichage_generations, false,
                                             affichage_nbintervalles);
                        break;
                    }
                    case 7: {
                        Intervalle interBeta_0p3_3 = Intervalle(0,1);
                        if (ordre == 1) interBeta_0p3_3 = Intervalle(0, 0.999);
                        else interBeta_0p3_3 = Intervalle(1e-16, 0.9);
                        generation_inversion(nb_generations, fdrBeta_0p3_3, densiteBeta_0p3_3, deriveedensiteBeta_0p3_3,
                                             interBeta_0p3_3, pts_particuliers, ordre, tol, delta, seed,
                                             test_monoticite, affichage, affichage_generations, false,
                                             affichage_nbintervalles);
                        break;
                    }
                    default:
                        throw std::logic_error("La distribution entree n'est pas valide.");
                }
            }
        }
    }

    char r;
    std::cin >> r;

    return 0;
}
