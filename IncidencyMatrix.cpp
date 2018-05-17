//
// Created by maciek on 14.04.18.
//

#include "IncidencyMatrix.h"


IncidencyMatrix::IncidencyMatrix(){}

IncidencyMatrix::IncidencyMatrix(int verticies, int edges){
    this->m_matrix = new int* [verticies];
    for (int i = 0; i < verticies; ++i) this->m_matrix[i] = new int [edges];
}


IncidencyMatrix::IncidencyMatrix(std::fstream &file) {
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

    //ustawiam wskaźnik seek na początek pliku
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


    //alokowanie pamięci dla macierzy
    this->m_matrix = new int* [this->m_verticies + 1];
    for (int i = 0; i < this->m_verticies + 1; ++i) this->m_matrix[i] = new int [this->m_edges + 1];

    //bez clear nie da się czytać tego samego pliku dwa razy
    file.clear();
    //ustawiam wskaźnik seek na początek pliku
    file.seekg(std::ios::beg);
    for (int i = 0; i < 5; ++i) {
        file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
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

//konstruktor konwertujacy macierz sąsiedztwa na macierz incydencji
IncidencyMatrix::IncidencyMatrix(AdjacencyMatrix &adjacencyMatrix) {
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

IncidencyMatrix::IncidencyMatrix(const IncidencyMatrix& obj){
    IncidencyMatrix temp(obj.getVerticies(), obj.getEdges());
    for (int i = 0; i < this->m_verticies; ++i){
        for (int j = 0; i < this->m_edges; ++j){
            this->m_matrix[i][j] = obj.getElement(i, j);
        }
    }
}



void IncidencyMatrix::print(){
    for (int i = 0; i < this->m_verticies; i++){
        for (int j = 0; j < this->m_edges; j++){
            std::cout << this->m_matrix[i][j] << " ";
        }
        std::cout << std::endl;
    }
}


IncidencyMatrix::~IncidencyMatrix() {
    if(this->m_matrix){
        for (int i = 0; i < this->m_verticies; ++i) {
            delete[] this->m_matrix[i];
        }
        delete[] this->m_matrix;
    }
}
