//
// Created by Maciej Czech on 13.04.18.
//
#include<iostream>

#include "AdjacencyList.h"


AdjacencyList::AdjacencyList(std::fstream &file) {
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

    //alokowanie pamięci dla macierzy
    /* dynamically allocates memmory for the matrix */
    this->m_matrix = new int* [this->m_size + 1];
    for (int i = 0; i < this->m_size + 1; ++i) this->m_matrix[i] = new int [this->m_size + 1];

    /* setting seek on 5th line in the input file */
    file.seekg(std::ios::beg);
    for (int i = 0; i < 5; ++i) {
        file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    /* reading and writing the input in*/
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
            //y++;
            while (getline(elementstream, element, ' ')) {
                *(*(this->m_matrix + y) + x) = std::stoi(element, nullptr, 10);
                x++;

            }
        }
    }
    std::cout << "Adjacency list has been created. " << std::endl;
}


/* converting constructor that creates object of Adjacency List out of Adjacency Matrix */
AdjacencyList::AdjacencyList(AdjacencyMatrix &matrix) {
    int counter;
    this->m_size = matrix.getSize();
    this->m_matrix = new int* [this->m_size];
    for (int i = 0; i < this->m_size; ++i) this->m_matrix[i] = new int[this->m_size];
    for (int i = 0; i < matrix.getSize(); ++i) {
        counter = 0;
        for (int j = 0; j < matrix.getSize(); ++j) {
            int element = matrix.getElement(i, j);
            if(element) {this->m_matrix[i][counter] = j + 1; counter++;}
        }
    }
}


AdjacencyList::~AdjacencyList(){
    for (int i = 0; i < this->m_size; ++i) {
        delete[] this->m_matrix[i];
    }
    delete[] this->m_matrix;
}

void AdjacencyList::print(){
    for (int i = 0; i < m_size; i++){
        /* writes out vertex and it's neighbors in this way: "1: 2, 3" */
        std::cout << i + 1 << ": ";
        for (int j = 0; j < m_size; j++){
            if(m_matrix[i][j] != 0) std::cout << m_matrix[i][j] << " ";
        }
        std::cout << std::endl;
    }
}



