#include "network.h"
#include "random.h"
#include <iostream>


void Network::resize(const size_t & t) {
   values.resize(t);
   RNG.normal(values);
}


bool Network::add_link(const size_t & firstNode, const size_t & secondNode) { //doit etre utiliser dans cette classe

    if (firstNode == secondNode) {
        return false;
    }

    else if(firstNode >= values.size() or (secondNode >= values.size())) {
        return false;
    }

    for (std::multimap<size_t,size_t>::iterator it=links.begin(); it!=links.end(); ++it) {

        if ((it->first == firstNode and it->second == secondNode) or (it->first == secondNode and it->second == firstNode) ) {
            return false;
        }
    }

    links.insert(std::pair<size_t,size_t>(firstNode,secondNode));
    links.insert(std::pair<size_t,size_t>(secondNode,firstNode));
    return true;
}

size_t Network::random_connect(const double & mean_deg) {

    //On clear tous les lien déja existants
    links.clear();
    size_t count(0);
    std::vector<size_t> nodes;
    std::vector<int> poissons(size());

    for(size_t node=0; node < size() ; node++) {
        nodes.push_back(node);
    }

    RNG.poisson(poissons, mean_deg);

    for(size_t node=0; node < size() ; node++) {

        RNG.shuffle(nodes);
        size_t it(0);

        for(int i(0); it < poissons[node] and i < size() ; ++i) {

            if (add_link(node, nodes[i])) {
                ++it;
            }
        }
        count += it;
    }
    return count;
}

size_t Network::set_values(const std::vector<double> & new_values) {

    size_t count(0);

    if (values.size() < new_values.size()) {

        for(size_t node=0; node < values.size() ; node++) {
            values[node] = new_values[node];
            ++count;
        }
    }

    else {
        for(size_t node=0; node < new_values.size() ; node++) {
            values[node] = new_values[node];
            ++count;
        }

    }
    return count;
}

size_t Network::size() const {
    return values.size();
}


double Network::value(const size_t &_n) const {
    return values[_n];
}


size_t Network::degree(const size_t &_n) const {
    return links.count(_n);
}

std::vector<double> Network::sorted_values() const {

        std::vector<double> descending_values = values;
        sort(descending_values.begin() , descending_values.end() , std::greater<double>());

        return descending_values;
}


std::vector<size_t> Network::neighbors(const size_t & node) const {

    std::vector<size_t> neighbors;

    for (std::multimap<size_t,size_t>::const_iterator it=links.begin(); it!=links.end(); ++it) {
        if (it->first == node) {
            neighbors.push_back(it->second);
        }
    }
    return neighbors;
}


