//
// Created by maciek on 14.04.18.
//

#include "IncidenceMatrix.h"

/* default constructors */
IncidenceMatrix::IncidenceMatrix(){}

IncidenceMatrix::IncidenceMatrix(int verticies, int edges){
    this->m_matrix = new int* [verticies];
    for (int i = 0; i < verticies; ++i) this->m_matrix[i] = new int [edges];
}


IncidenceMatrix::IncidenceMatrix(std::fstream &file) {
    /* setting seek "pointer" at the beggining of the file */
    file.seekg(std::ios::beg);
    /* third line in the input file determines type of the representation that is being processed */
    for (int i = 0; i < 2; ++i) {
        file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    /*setting size of the matrix to zero to prevent it from keeping any weird value at the beggining*/
    file >> this->m_type;

    /* evaluating size of NxM matrix given in the input file */
    file.seekg(std::ios::beg);
    for (int i = 0; i < 5; ++i) {
        file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    std::string value;
    int verticies = 0;
    int edges = 0;

    std::string line1;
    while(file.good()){
        while(getline(file, line1, ';')){
            std::istringstream stream1(line1);
            edges = 0;
            while(stream1 >> value){
                edges++;
            }
            verticies++;
        }
    }

    this->m_verticies = verticies;
    this->m_edges = edges;


	/* dynamically allocates memmory for the matrix */
    this->m_matrix = new int* [this->m_verticies + 1];
    for (int i = 0; i < this->m_verticies + 1; ++i) this->m_matrix[i] = new int [this->m_edges + 1];

    /* clear so I can read the same file again */
    file.clear();

    file.seekg(std::ios::beg);
    for (int i = 0; i < 5; ++i) {
        file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    /* reading and writing the input in */
    int x = 0, y = 0;
    std::string line;
    while(file.good()){
        while(getline(file, line1, ';')){
            std::istringstream stream1(line1);
            y = 0;
            while(stream1 >> value){
                *(*(this->m_matrix + x) + y) = std::stoi(value, NULL, 10);
                y++;
            }
            x++;
        }
    }
    std::cout << "Utworzono macierz incydencji." << std::endl;
}

/* converting constructor that creates object of Incidence out of Adjacency Matrix */
IncidenceMatrix::IncidenceMatrix(AdjacencyMatrix &adjacencyMatrix) {
    this->m_verticies = adjacencyMatrix.getSize();
    this->m_edges = 0;
    int edge = 0;
    for (int i = 0; i < adjacencyMatrix.getSize() ; ++i) {
        for (int j = i; j < adjacencyMatrix.getSize() ; ++j) {
            if(adjacencyMatrix.getElement(i, j)) this->m_edges++;
        }
    }
    this->m_matrix = new int* [this->m_verticies];
    for (int l = 0; l < this->m_verticies; ++l) this->m_matrix[l] = new int [this->m_edges];
    for (int col = 0; col < adjacencyMatrix.getSize(); ++col) {
        for (int row = 0; row <= col; ++row) {
            if(adjacencyMatrix.getElement(col, row)){
                this->m_matrix[row][edge] = this->m_matrix[col][edge] = 1;
                ++edge;
            }
        }
    }
}

/* copy constructor that is never used :) */
IncidenceMatrix::IncidenceMatrix(const IncidenceMatrix& obj){
    IncidenceMatrix temp(obj.getVerticies(), obj.getEdges());
    for (int i = 0; i < this->m_verticies; ++i){
        for (int j = 0; i < this->m_edges; ++j){
            this->m_matrix[i][j] = obj.getElement(i, j);
        }
    }
}



void IncidenceMatrix::print(){
    for (int i = 0; i < this->m_verticies; i++){
        for (int j = 0; j < this->m_edges; j++){
            std::cout << this->m_matrix[i][j] << " ";
        }
        std::cout << std::endl;
    }
}


IncidenceMatrix::~IncidenceMatrix() {
    if(this->m_matrix){
        for (int i = 0; i < this->m_verticies; ++i) {
            delete[] this->m_matrix[i];
        }
        delete[] this->m_matrix;
    }
}
