#include "network.h"


void Network::resize(const size_t &) {

   values.size()
}

bool Network::add_link(const size_t & first, const size_t & second) { //doit etre utiliser dans cette classe
    //créer le lien entre les 2 noeuds passés en paramètre
    // le first va créer un lien avec le second et le second va créer un autre lien le first -> bidirectionnel
    //return true si le lien a bien été inséré
    return false;
}

size_t Network::random_connect(const double & mean_deg) {

    //On clear tous les lien déja existants
    links.clear();

    //nombre de nodes voisins qu'on va lier au noeud courant
    int NodesNumber(RNG.poisson(mean_deg));

    //On parcout les noeuds et on lui affecte NodesNumber liens
    for(size_t node=0; node < values.size() ; node++) {

        //On vérifie qu'on peut add_link entre la node courante et NodesNumbers autres nodes
        for(int i(0); i < NodesNumber ; ++i) {
             if(add_link(node, //choisir une node aléatoire parmi le tableau de nodes ))
             //le faire "NodesNumber" fois

             //faire un tableau qui contient tous les indices des noeuds disponibles (en excluant le noeuds courant)
             //on tire au sort un nombre parmi les indices dispo
        }

    }

    return 0; //retourne le nombre de lien total créé -> soit compteur soit commande multimap
}

size_t Network::set_values(const std::vector<double> & new_values) {

    size_t count(0); //Est ce que j'ai bien compris ce qu'ils veulent dire par "number of nodes succesfully reset"
    for(size_t node=0; node < values.size() ; node++) {
        values[node] = new_values[node];
       ++count;
    }
    //attention à la taille du new_values -> on continue à affecter les nouvelles valeurs jusqu'à que l'un des 2 n'aies plus de valeurs dispo
    //on va parcourir les noeuds et remplacer sa valeur par la valeur correspondante de new_value
    //on met un compteur quand le noeuds est bien remplacé -> retourne une size_t
    return count;
}

size_t Network::size() const {
    return values.size();
}

double Network::value(const size_t &_n) const {
    return values[_n];
}

size_t Network::degree(const size_t &_n) const {
    //retourne le nombre de liens qu'à le node _n
    //utiliser la multimap
    return 0;
}

std::vector<double> Network::sorted_values() const {

    double tmp;
    std::vector<double> sorted_values;

    for(const auto& value : values) {
        //algorithme qui affecte à la premieère valeur du tableau la plus grande valeure etc
        //tmp = value;
    }

    return sorted_values;
}

std::vector<size_t> Network::neighbors(const size_t & node) const {
    std::vector<size_t> neighbors;
    //utiliser la multimap pour retourner un tableau contenant les nodes voisins de node
    return neighbors;
}


