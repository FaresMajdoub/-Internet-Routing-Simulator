
/** \file Reseau.cpp
 * \brief Définition de l'interface pour un reseau informatique
 * \author TE
*/
#include <algorithm>
#include "Reseau.h"
#include "ContratException.h"

using namespace std;

/**
 * \brief Constructeur par d�faut
 * \post Un r�seau vide est instanci�.
 */
Reseau::Reseau () { };

/**
 * \brief Constructeur à partir d'un fichier en entrée.
 * \param[in, out] p_fichierEntree fichierEntree un flux sur un fichier d'entrée
 * \pre Il y a assez de mémoire pour charger tous les routeur de la liste.
 * \pre	Le fichier p_fichierEntree est ouvert corectement.
 * \post Le fichier p_fichierEntree n'est pas fermé par la fonction.
 * Si les préconditions sont respectées, les données du réseau contenu
 * dans le fichier en entrée sont organis�es dans un graphe en m�moire.

 */
Reseau::Reseau(std::ifstream& p_fichierEntree)
{
    //Lecture des données sur les routeurs
    string nom; //Pour le nom des routeurs
    string adresseIP;
    string localisation;
    int numero = 1;
    vector<string> tabNomRouteurs;

    bool sentinelle = false;

    while (!p_fichierEntree.eof () && sentinelle == false)
    {
        getline(p_fichierEntree, nom);
        cout << nom << endl;
        if (nom == "$")//limite de la première partie du fichier
        {
            sentinelle = true;
        }
        else
        {
            getline(p_fichierEntree, adresseIP);
            getline(p_fichierEntree, localisation);
            Routeur lRouteur (nom, adresseIP, localisation);
            m_graphe.ajouterSommet(numero, lRouteur);
            ++numero;
            tabNomRouteurs.push_back(nom);
        }
    }

    int tempsTransmission;
    string nomD; //nom du routuer de destination
    int indiceSource;
    int indiceDestination;
    char buff[255];
    vector<string>::iterator location;
    while (!p_fichierEntree.eof())
    {
        p_fichierEntree.getline(buff, 100);
        nom = buff;
        location = find(tabNomRouteurs.begin (), tabNomRouteurs.end (), nom);
        indiceSource = location - tabNomRouteurs.begin ();
        p_fichierEntree.getline(buff, 100);
        nomD = buff;
        location = find(tabNomRouteurs.begin (), tabNomRouteurs.end (), nomD);
        indiceDestination = location - tabNomRouteurs.begin ();
        p_fichierEntree >> tempsTransmission;
        p_fichierEntree.ignore();

        m_graphe.ajouterArc(indiceSource + 1, indiceDestination + 1,
                             tempsTransmission);
    }

    cout << "********Graphe lu: ********" << std::endl;
    cout << m_graphe;
    cout << "***************************" << std::endl;

}

/**
 * \brief Affiche une liste de routeurs du réseau � l'ecran.
 * @param p_vRouteurs Une liste de routeurs dans un vector.
 * \post Le contenu de la liste v est affiché.
 */
void
Reseau::afficherRouteurs (std::vector<Routeur> & p_vRouteurs)
{
    if (p_vRouteurs.size () == 0)
    {
        std::cout << "La liste est vide\n";
        return;
    }

    for (unsigned int i = p_vRouteurs.size (); i > 0; i--)
    {
        std::cout << p_vRouteurs[i - 1] << std::endl;
    }
}

/**
 * \brief Affiche la liste de tous les routeurs du réseau � l'écran
 * \pre	Le reseau est non vide
 * \post La liste de tous les routeurs du r�seau sont affich�es.
 */
void
Reseau::afficherRouteurs()
{
    PRECONDITION(!m_graphe.estVide());
    std::vector<Routeur> lListeRouteur = m_graphe.listerEtiquetteSommets ();
    afficherRouteurs (lListeRouteur);
}

/**
 *
 * @param p_vRouteurs liste des routeurs enregistrés dans le réseau
 */
void
Reseau::getRouteurs (std::vector<Routeur>& p_vRouteurs) const
{
    p_vRouteurs = m_graphe.listerEtiquetteSommets ();
}

/**
 * \brief Vérifie si tous les routeurs du réseau sont accessibles.
 * \pre Le réseau est non vide.
 * \return Vrai si tout routeur est accessible depuis n'importe où, sinon faux.
 */

bool Reseau::routeursAccessibles() {
    PRECONDITION(!m_graphe.estVide());
    return m_graphe.estFortementConnexe();
}
/**
 * \brief Renvoie une liste des routeurs critiques du réseau.
 * \pre Le réseau est non vide.
 * \post Le réseau original reste inchangé.
 * \throws std::bad_alloc si la mémoire est insuffisante pour retourner la liste des routeurs critiques.
 * \return Un vecteur contenant les routeurs critiques, ou une liste vide si aucun n'est critique.
 */

std::vector<Routeur> Reseau::routeursCritiques() {
    PRECONDITION(!m_graphe.estVide()); // Verifier que le graphe n'est pas vide.

    try {
        // Sauvegarder l'etat initial pour la postcondition
        // Sauvegarde des proprietes initiales du graphe pour les postconditions
        int nbSommetsInitial = m_graphe.nombreSommets();
        std::vector<int> sommetsInitials = m_graphe.listerSommets();
        std::vector<Routeur> etiquettesInitiales = m_graphe.listerEtiquetteSommets();

        std::vector<Routeur> pointsCritiques;
        m_graphe.getPointsArticulation(pointsCritiques);

        POSTCONDITION(m_graphe.nombreSommets() == nbSommetsInitial);
        POSTCONDITION(m_graphe.listerSommets() == sommetsInitials);
        POSTCONDITION(m_graphe.listerEtiquetteSommets() == etiquettesInitiales);

        return pointsCritiques;
    } catch (const std::bad_alloc&) {
        std::cerr << "Erreur : mémoire insuffisante pour calculer les routeurs critiques." << std::endl;
        throw;
    }
}
/**
 * \brief Détermine le chemin minimal entre deux routeurs.
 * \pre Les sommets d'origine et de destination existent.
 * \post Le graphe reste inchangé. Le nombre de sommets, les sommets eux-mêmes, et leurs étiquettes ne changent pas.
 * \post Le temps de transmission total est retourné dans \a p_nbSecondes (ou -1 s'il n'y a pas de chemin).
 * \post La liste des routeurs à parcourir est retournée dans le vecteur résultat.
 * \throws std::bad_alloc s'il n'y a pas assez de mémoire pour retourner le chemin.
 * @param[in] p_routeurOrigine Le routeur d'origine.
 * @param[in] p_routeurDestination Le routeur de destination.
 * @param[out] p_nbSecondes Le temps de transmission total.
 * @return Un vecteur contenant le parcours.
 */
std::vector<Routeur> Reseau::determinerMinParcours(const Routeur& p_routeurOrigine,
                                                   const Routeur& p_routeurDestination,
                                                   int& p_nbSecondes) {

    PRECONDITION(m_graphe.sommetExiste(m_graphe.getNumeroSommet(p_routeurOrigine)));
    PRECONDITION(m_graphe.sommetExiste(m_graphe.getNumeroSommet(p_routeurDestination)));

    try {

        int nbSommetsInitial = m_graphe.nombreSommets();
        std::vector<int> sommetsInitials = m_graphe.listerSommets();
        std::vector<Routeur> etiquettesInitiales = m_graphe.listerEtiquetteSommets();


        std::vector<Routeur> cheminRouteurs;
        p_nbSecondes = m_graphe.dijkstra(p_routeurOrigine, p_routeurDestination, cheminRouteurs);



        POSTCONDITION(m_graphe.nombreSommets() == nbSommetsInitial);
        POSTCONDITION(m_graphe.listerSommets() == sommetsInitials);
        POSTCONDITION(m_graphe.listerEtiquetteSommets() == etiquettesInitiales);


        POSTCONDITION((p_nbSecondes >= 0 && !cheminRouteurs.empty()) || (p_nbSecondes == -1 && cheminRouteurs.empty()));


        POSTCONDITION(cheminRouteurs.empty() || (cheminRouteurs.front() == p_routeurOrigine && cheminRouteurs.back() == p_routeurDestination));

        // Si aucun chemin n'existe on definit explicitement p_nbSecondes
        if (cheminRouteurs.empty()) {
            p_nbSecondes = -1;  // Aucun chemin trouvé
        }

        return cheminRouteurs;
    } catch (const std::bad_alloc&) {
        std::cerr << "Erreur : mémoire insuffisante pour déterminer le chemin minimal." << std::endl;
        throw;
    }
}
