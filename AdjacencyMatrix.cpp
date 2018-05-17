//
// Created by Maciek Czech on 14.04.18.
//

#include "AdjacencyMatrix.h"
#include "AdjacencyList.h"
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

AdjacencyMatrix::AdjacencyMatrix(std::fstream &file){
    /* setting seek "pointer" at the beggining of the file */
    file.seekg(std::ios::beg);
	/* third line in the input file determines type of the representation that is being processed */ 
    for (int i = 0; i < 2; ++i) {
        file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    /* putting char from input file into this variable
    * it is actually never used, but I decided to leave it as it is */
    file >> this->m_type;

    /*setting size of the matrix to zero to prevent it from keeping any weird value at the beggining*/
    this->m_size = 0;
    for (int i = 0; i < 3; ++i) {
        file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    /* evaluating size of a matrix given in the input file */
    while (!file.eof()) {
        this->m_size++;
        file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    /* dynamically allocates memmory for the matrix */
    this->m_matrix = new int* [this->m_size + 1];
    for (int i = 0; i < this->m_size + 1; ++i) this->m_matrix[i] = new int [this->m_size + 1];

    /* setting seek on 5th line in the input file */
    file.seekg(std::ios::beg);
    for (int i = 0; i < 5; ++i) {
        file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    /* reading and writing the input in */
    int x = 0, y = -1;
    std::string line;
    while (getline(file, line, ';')) {
        std::stringstream rowstream(line);
        std::string row;
        y++;
        while (getline(rowstream, row)) {
            std::stringstream elementstream(row);
            std::string element;
            x = 0;
            while (getline(elementstream, element, ' ')) {
                *(*(this->m_matrix + x) + y) = std::stoi(element, NULL, 10);
                x++;

            }
        }
    }
    std::cout << "Adjacency Matrix has been created." << std::endl;
}

/* constructor used to create random graph with particular amount of verticies and egdes */
AdjacencyMatrix::AdjacencyMatrix(int verticies, int edges){
    int v1 = 0, v2 = 0;
    srand (time(NULL));

    /* size of the matrix is equal to verticies number */
    this->m_size = verticies;
    this->m_matrix = new int* [this->m_size];
    for (int i = 0; i < this->m_size; ++i) this->m_matrix[i] = new int[this->m_size];
    
    for (int i = 0; i < this->m_size; i++){
        for (int j = 0; j < this->m_size; j++) this->m_matrix[i][j] = 0;
    }
    for(int i = 0; i < edges; i++){
        while(v1 == v2 || this->m_matrix[v1][v2] == 1){
            v1 = rand()%this->m_size;
            v2 = rand()%this->m_size;
        }
        this->m_matrix[v1][v2] = 1;
        this->m_matrix[v2][v1] = 1;
    }
}

/*
* constructor used to create random graph with given amount of verticies
* and probability that determines whether there will be an egde between two verticies 
*/
AdjacencyMatrix::AdjacencyMatrix(int verticies, double probability){
    int v1, v2;
    srand (time(NULL));

    this->m_size = verticies;
    this->m_matrix = new int* [this->m_size];
    for (int i = 0; i < this->m_size; ++i) this->m_matrix[i] = new int[this->m_size];
    
    for (int i = 0; i < this->m_size; i++){
        for (int j = 0; j < this->m_size; j++) this->m_matrix[i][j] = 0;
    }
    
    for(v1 = 0; v1 < this->m_size; v1++){
        for(v2 = 0; v2 < this->m_size; v2++){
            if(v1 == v2) this->m_matrix[v1][v2] = 0;
            else{
                int prob = rand()%101;
                if(prob <= (probability * 100)){
                    this->m_matrix[v1][v2] = this->m_matrix[v2][v1] = 1;
                }
            }
        }
    }
}


/* converting constructor that creates object of Adjacency Matrix out of Adjacency List */
AdjacencyMatrix::AdjacencyMatrix(AdjacencyList& list){
    this->m_size = list.getSize();
    this->m_matrix = new int* [this->m_size];
    for (int i = 0; i < this->m_size; ++i) this->m_matrix[i] = new int[this->m_size];
    for (int i = 0; i < list.getSize(); ++i) {
        for (int j = 0; j < list.getSize(); ++j) {
            int element = list.getElement(i, j);
            if(element)
                this->m_matrix[i][element - 1] = 1;
            else
                this->m_matrix[i][element - 1] = 0;
        }
    }
}

/* converting constructor that creates object of Adjacency List out of Adjacency Matrix */
AdjacencyMatrix::AdjacencyMatrix(IncidenceMatrix& IncidenceMatrix) {
    this->m_size = IncidenceMatrix.getVerticies();
    this->m_matrix = new int *[this->m_size];
    for (int i = 0; i < this->m_size; ++i) this->m_matrix[i] = new int[this->m_size];
    for (int edge = 0; edge < IncidenceMatrix.getEdges(); ++edge) {
        int a = -1, b = -1, vertex = 0;
        for (; vertex < IncidenceMatrix.getVerticies() && a == -1; ++vertex) {
            if (IncidenceMatrix.getElement(vertex, edge)) a = vertex;
        }
        for (; vertex < IncidenceMatrix.getVerticies() && b == -1; ++vertex) {
            if (IncidenceMatrix.getElement(vertex, edge)) b = vertex;
        }
        if (b == -1) b = a;
        this->m_matrix[a][b] = this->m_matrix[b][a] = 1;
    }
}

void AdjacencyMatrix::print(){
    for (int i = 0; i < this->m_size; i++){
        for (int j = 0; j < this->m_size; j++){
            std::cout << this->m_matrix[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

AdjacencyMatrix::~AdjacencyMatrix(){
    for (int i = 0; i < this->m_size; ++i) {
        delete[] this->m_matrix[i];
    }
    delete[] this->m_matrix;
}


