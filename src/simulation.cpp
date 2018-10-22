#include "random.h"
#include "simulation.h"
#include "network.h"
#include <iostream>

Simulation::Simulation(Network *_net) : _network(_net), stepnum(10) {}

void Simulation::initialize(int argc, char **argv) {
    TCLAP::CmdLine cmd("Network simulation");
    TCLAP::ValueArg<int> argNode("n", "nodes", "Number of nodes", false, 0, "int");
    cmd.add(argNode);
    TCLAP::ValueArg<long> argSeed("S", "seed", "Random seed", false, 0, "long");
    cmd.add(argSeed);
    TCLAP::ValueArg<double> argDegree("d", "degree", "Mean node degree", false, 4, "double");
    cmd.add(argDegree);
    TCLAP::ValueArg<int> argTime("t", "time", "Number of steps to simulate", false, 10, "int");
    cmd.add(argTime);

    cmd.parse(argc, argv);

    RNG.initialize(argSeed.getValue());     //affecte à l'attribut rng une seed aléatoire ou pas si on l'a rentrée nous meme
    int nodes(argNode.getValue());          //Nombre de noeuds
    if (nodes < 1) nodes = RNG.poisson(50); //si on a pas rentrer un nombre de noeud, affecte un noeuds suivant la loi de Poisson
    _network->resize(nodes);                // Que veut dire "Resize" ?
    double degree(argDegree.getValue());
    if (degree < 1) degree = RNG.uniform_double(1, std::sqrt(nodes)); //la moyenne des degree est choisi aléatoirement si non donné
    size_t nlink = _network->random_connect(degree);        //nlink contient le nombre de lien entre les nodes
    std::cout << _network->size() << " nodes, " << nlink << " links\n";
    maxtime = argTime.getValue();
}


void Simulation::run() {
    for (int time=0; time<maxtime; time++) {
        if ((time % stepnum) == 0) print(time); //affiche le temps quand le nombre de steps entre chaque affichage est atteint
        step();     //Effectue un step dans le programme, donc met à jour le réseau, jusqu'à qu'on ait atteint maxtime
    }
    print(maxtime); //affiche le dernier time
}

void Simulation::print(const int &time) const {
    std::cout << time << ": ";
    std::vector<double> vals = _network->sorted_values();
    for (auto I : vals) std::cout << I << " ";
    std::cout << std::endl;
}

void Simulation::step() const {
    std::vector<double> next_values(_network->size()); //next_values = tableau du nombre de noeuds
    std::vector<double> epsilon(_network->size());// epsilon = tableau du nombre de noeuds
    RNG.uniform_double(epsilon); //à chaque noeuds on attriubue une valeur aléatoire (uniformed-distributed)
    for (size_t node=0; node<next_values.size(); node++) {  //on parcourt le tableau de noeuds
        double cumul_neighbs = 0;
        for (auto I : _network->neighbors(node)) cumul_neighbs += _network->value(I); //parcourt les voisins de chaque noeud et on cumule les valeurs des voisins
        double ddeg(_network->degree(node)); //ddeg porte le nombre de lien du noeuds courant
        next_values[node] = epsilon[node]*cumul_neighbs/ddeg+(1-epsilon[node])*_network->value(node); //on construit le prochain tableau de noeufs pour la prochaine étape
                                                                                                        // valeur du noeuds*cumul des noeuds des voisins / nombre lien +...
    }
    _network->set_values(next_values);          //attribue au network ses nouvelles valeurs
}
