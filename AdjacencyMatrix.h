//
// Created by maciek on 14.04.18.
//

#ifndef PROJEKT_1_VOL2_ADJACENCYMATRIX_H
#define PROJEKT_1_VOL2_ADJACENCYMATRIX_H


#include "Representation.h"
#include "AdjacencyList.h"
#include "IncidenceMatrix.h"

class AdjacencyList;
class IncidenceMatrix;

class AdjacencyMatrix : public Representation{
public:
    AdjacencyMatrix(){}
    AdjacencyMatrix(int verticies, int edges);
    AdjacencyMatrix(int verticies, double probability);
    AdjacencyMatrix(std::fstream& file);
    AdjacencyMatrix(AdjacencyList& list);
    AdjacencyMatrix(IncidenceMatrix& IncidenceMatrix);

    virtual ~AdjacencyMatrix();
    virtual void print();

private:
};


#endif //PROJEKT_1_VOL2_ADJACENCYMATRIX_H
