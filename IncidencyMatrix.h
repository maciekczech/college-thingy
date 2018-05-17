//
// Created by maciek on 14.04.18.
//

#ifndef PROJEKT_1_VOL2_INCIDENCYMATRIX_H
#define PROJEKT_1_VOL2_INCIDENCYMATRIX_H


#include "Representation.h"
#include "AdjacencyMatrix.h"

class AdjacencyMatrix;

class IncidencyMatrix : public Representation{
public:
    IncidencyMatrix();
    IncidencyMatrix(int verticies, int edges);
    IncidencyMatrix(std::fstream& file);
	IncidencyMatrix(const IncidencyMatrix& obj);
    IncidencyMatrix(AdjacencyMatrix& adjacencyMatrix);
    virtual ~IncidencyMatrix();

    //w sumie to okazal sie niepotrzebny, ale nie usuwam, bo moze kiedys sie przydać
    IncidencyMatrix& operator=(IncidencyMatrix obj){
		std::cout << "Przypisane wierzcholki: " << m_verticies << std::endl;
		std::cout << "Przypisane kraw: " << m_edges << std::endl;
		this->setVerticies(obj.getVerticies());
		this->setEdges(obj.getVerticies());
		this->m_matrix = new int* [this->m_verticies + 1];
    	for (int i = 0; i < this->m_verticies + 1; ++i) this->m_matrix[i] = new int [this->m_edges + 1];
   		for (int i = 0; i < this->m_verticies; ++i){
        	for (int j = 0; i < this->m_edges; ++j){
            	this->m_matrix[i][j] = obj.getElement(i, j);
       		}
    	}
    	return *this;
    }

    virtual void print();

    int getVerticies() const {return m_verticies;}
    int getEdges() const {return m_edges;}

    void setVerticies(int verticies){ m_verticies = verticies;}
    void setEdges(int edges){ m_edges = edges;}

private:
    int m_verticies;
    int m_edges;

};


#endif //PROJEKT_1_VOL2_INCIDENCYMATRIX_H
