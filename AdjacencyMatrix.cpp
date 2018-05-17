//
// Created by maciek on 14.04.18.
//

#include "AdjacencyMatrix.h"
#include "AdjacencyList.h"
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

AdjacencyMatrix::AdjacencyMatrix(std::fstream &file){
    //ustawiam wskaźnik seek na początek pliku
    file.seekg(std::ios::beg);
    //trzecia linijka okresla typ danych wejsciowych
    for (int i = 0; i < 2; ++i) {
        //pierwszy argument fstream::ignore() to najdłuższy możliwy wiersz,
        // drugi to znak nowej lini przy którym funkcja przechodzi do kolejnego wiersza
        file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    //tworzenie tymczasowej zmiennej i przypisanie jej wartości spod wskaźnika seek
    file >> this->m_type;

    /*część odpowiedzialna za zczytanie rozmiaru*/
    this->m_size = 0;
    for (int i = 0; i < 3; ++i) {
        file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    //liczy wielkość macierzy zliczając linijki w pliku
    while (!file.eof()) {
        this->m_size++;
        file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    //alokowanie pamięci dla macierzy
    this->m_matrix = new int* [this->m_size + 1];
    for (int i = 0; i < this->m_size + 1; ++i) this->m_matrix[i] = new int [this->m_size + 1];

    //ustawiam wskaźnik seek na początek pliku
    file.seekg(std::ios::beg);
    for (int i = 0; i < 5; ++i) {
        //pierwszy argument fstream::ignore() to najdłuższy możliwy wiersz,
        // drugi to znak nowej lini przy którym funkcja przechodzi do kolejnego wiersza
        file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
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
                *(*(this->m_matrix + x) + y) = std::stoi(element, NULL, 10);
                x++;

            }
        }
    }
    std::cout << "Utworzono macierz sasiedztwa." << std::endl;
}

AdjacencyMatrix::AdjacencyMatrix(int verticies, int edges){
    int v1 = 0, v2 = 0;
    srand (time(NULL));

    this->m_size = verticies;
    this->m_matrix = new int* [this->m_size];
    for (int i = 0; i < this->m_size; ++i) this->m_matrix[i] = new int[this->m_size];
    
    //zerowanie macierzy
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


AdjacencyMatrix::AdjacencyMatrix(int verticies, double probability){
    int v1, v2;
    srand (time(NULL));

    this->m_size = verticies;
    this->m_matrix = new int* [this->m_size];
    for (int i = 0; i < this->m_size; ++i) this->m_matrix[i] = new int[this->m_size];
    
    //zerowanie macierzy
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




//konstruktor konwertujący liste sasiedztwa na macierz sasiedztwa
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
//konstruktor konwertujacy macierz incydencji na macierz sasiedztwa
AdjacencyMatrix::AdjacencyMatrix(IncidencyMatrix &incidencyMatrix) {
    this->m_size = incidencyMatrix.getVerticies();
    this->m_matrix = new int *[this->m_size];
    for (int i = 0; i < this->m_size; ++i) this->m_matrix[i] = new int[this->m_size];
    for (int edge = 0; edge < incidencyMatrix.getEdges(); ++edge) {
        int a = -1, b = -1, vertex = 0;
        for (; vertex < incidencyMatrix.getVerticies() && a == -1; ++vertex) {
            if (incidencyMatrix.getElement(vertex, edge)) a = vertex;
        }
        for (; vertex < incidencyMatrix.getVerticies() && b == -1; ++vertex) {
            if (incidencyMatrix.getElement(vertex, edge)) b = vertex;
        }
        if (b == -1) b = a;
        this->m_matrix[a][b] = this->m_matrix[b][a] = 1;
    }
}

AdjacencyMatrix::~AdjacencyMatrix(){
    for (int i = 0; i < this->m_size; ++i) {
        delete[] this->m_matrix[i];
    }
    delete[] this->m_matrix;
}


