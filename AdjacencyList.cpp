//
// Created by maciek on 13.04.18.
//
#include<iostream>

#include "AdjacencyList.h"

//ogólnie wszystkie te konstruktory są troche nieprzemyślane i podejrzewam, że mogłyby być przynajmniej dwa razy krótsze
//ale it is what it is

AdjacencyList::AdjacencyList(std::fstream &file) {
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
                *(*(this->m_matrix + y) + x) = std::stoi(element, nullptr, 10);
                x++;

            }
        }
    }
    std::cout << "Zczytano i utworzono liste sasiedztwa: " << std::endl;
}


//konstruktor konwertujący macierz sąsiedztwa na listę sąsiedztwa
AdjacencyList::AdjacencyList(AdjacencyMatrix &matrix) {
    // counter potrzebny do dodawania kolejnych elementow listy we wlasciwe miejsce
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
        //wskazuje wierzchołek, który sąsiaduje z kolejno wypisanymi, np.: "1: 2 3"
        std::cout << i + 1 << ": ";
        for (int j = 0; j < m_size; j++){
            if(m_matrix[i][j] != 0) std::cout << m_matrix[i][j] << " ";
        }
        std::cout << std::endl;
    }
}



