#include <gtest/gtest.h>
#include "Reseau.h"
#include <fstream>

// Test de Dijkstra avec trace.txt
TEST(ReseauTest, TestDijkstra) {
    std::ifstream fichier("trace.txt");
    ASSERT_TRUE(fichier.is_open()) << "Impossible d'ouvrir le fichier trace.txt";

    Reseau reseau(fichier);

    Routeur r1("port-theud", "132.203.120.179", "Quebec");
    Routeur r2("sl-gw31-nyc-4-0.sprintlink.net8", "160.81.43.177", "New York");

    int tempsTransmission = 0;
    auto chemin = reseau.determinerMinParcours(r1, r2, tempsTransmission);

    ASSERT_GT(chemin.size(), 0) << "Le chemin ne devrait pas être vide";
    ASSERT_EQ(tempsTransmission, 35) << "Le temps de transmission attendu est de 35.";
}

// Test de Routeur Accessible avec trace.txt
TEST(ReseauTest, TestRouteursAccessibles) {
    std::ifstream fichier("trace.txt");
    ASSERT_TRUE(fichier.is_open()) << "Impossible d'ouvrir le fichier trace.txt";

    Reseau reseau(fichier);

    ASSERT_FALSE(reseau.routeursAccessibles()) << "Le graphe n'est pas fortement connexe.";
}

// Test pour les routeurs critiques (traceFC.txt)
TEST(ReseauTest, TestRouteursCritiques) {
    std::ifstream fichier("traceFC.txt");
    ASSERT_TRUE(fichier.is_open()) << "Impossible d'ouvrir le fichier traceFC.txt";

    Reseau reseau(fichier);
    auto critiques = reseau.routeursCritiques();


    ASSERT_EQ(critiques.size(), 3) << "Le graphe devrait contenir exactement 3 routeurs critiques.";


    std::vector<std::string> attendus = {
        "sl-gw31-nyc-4-0.sprintlink.net8",
        "gw541a.n.ulaval.ca4",
        "port-theud"
    };

    for (const auto& routeur : critiques) {
        ASSERT_NE(std::find(attendus.begin(), attendus.end(), routeur.reqNom()), attendus.end())
            << "Routeur critique inattendu : " << routeur.reqNom();
    }
}
