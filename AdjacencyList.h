//
// Created by maciek on 13.04.18.
//

#ifndef PROJEKT_1_VOL2_ADJACENCYLIST_H
#define PROJEKT_1_VOL2_ADJACENCYLIST_H


#include "Representation.h"
#include "AdjacencyMatrix.h"

class AdjacencyMatrix;

class AdjacencyList : public Representation{
public:

    AdjacencyList(){}
    AdjacencyList(std::fstream& file);
    AdjacencyList(AdjacencyMatrix& matrix);


    virtual ~AdjacencyList();
    virtual void print();

private:


};


#endif //PROJEKT_1_VOL2_ADJACENCYLIST_H
