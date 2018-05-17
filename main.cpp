#include <iostream>

//biblioteka do obsługi plików
#include <fstream>
//biblioteka do parsowania danych
#include <sstream>
#include <limits>
#include "AdjacencyList.h"
#include "AdjacencyMatrix.h"
#include "IncidencyMatrix.h"
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "SFMLpart.h"



char readChar(std::fstream& file, int number);
int main(void){


    char choice; 		//char zczytywany z pliku określający sposób interpretacji danych wejściowych
    std::fstream file;	//uchwyt do obsługi pliku


    //Otwieranie pliku
    file.open("input.dat");
    if(file.good())	{std::cout << "Pomyślnie otwarto plik" << std::endl;}
    else 			{std::cout << "Nie udało się otworzyć pliku" << std::endl; return 0;}

    //zczytywanie literki
    choice = readChar(file, 3);



    switch(choice){
        case 'L': {
            AdjacencyList adjacencyList(file);
            adjacencyList.print();
            std::cout << "\nMacierz sąsiedztwa dla zadanej listy sąsiedztwa: " << std::endl;
            AdjacencyMatrix adjacencyMatrixFromList(adjacencyList);
            adjacencyMatrixFromList.print();
            std::cout << "\nMacierz incydencji dla zadanej macierzy sąsiedztwa: " << std::endl;
            IncidencyMatrix incidencyMatrixFromAdjacencyMatrix(adjacencyMatrixFromList);
            incidencyMatrixFromAdjacencyMatrix.print();
            Draw(&incidencyMatrixFromAdjacencyMatrix);
            break;
        }
        case 'I': {
            IncidencyMatrix incidencyMatrix(file);
            incidencyMatrix.print();
            std::cout << "\nMacierz sąsiedztwa dla zadanej macierzy incydencji: " << std::endl;
            AdjacencyMatrix adjacencyMatrixFromIncidencyMatrix(incidencyMatrix);
            adjacencyMatrixFromIncidencyMatrix.print();
            std::cout << "\nLista sąsiedztwa dla zadanej macierzy incydencji: " << std::endl;
            AdjacencyList adjacencyListFromIncidencyMatrix(adjacencyMatrixFromIncidencyMatrix);
            adjacencyListFromIncidencyMatrix.print();
            Draw(&incidencyMatrix);
            break;
        }
        case 'S': {
            AdjacencyMatrix adjacencyMatrix(file);
            adjacencyMatrix.print();
            std::cout << "\nLista sąsiedztwa dla zadanej macierzy sąsiedztwa: " << std::endl;
            AdjacencyList adjacencyListFromMartix(adjacencyMatrix);
            adjacencyListFromMartix.print();
            std::cout << "\nMacierz incydencji dla zadanej macierzy sąsiedztwa: " << std::endl;
            IncidencyMatrix incidencyMatrixFromAdjacencyMatrix(adjacencyMatrix);
            incidencyMatrixFromAdjacencyMatrix.print();
            Draw(&incidencyMatrixFromAdjacencyMatrix);
            break;
        }
        case 'X': {
            AdjacencyMatrix randomAdjacencyMatrix(10, 5);
            randomAdjacencyMatrix.print();
            std::cout << "\nLista sąsiedztwa dla zadanej macierzy sąsiedztwa: " << std::endl;
            AdjacencyList adjacencyListFromMartix(randomAdjacencyMatrix);
            adjacencyListFromMartix.print();
            std::cout << "\nMacierz incydencji dla zadanej macierzy sąsiedztwa: " << std::endl;
            IncidencyMatrix incidencyMatrixFromAdjacencyMatrix(randomAdjacencyMatrix);
            incidencyMatrixFromAdjacencyMatrix.print();
            Draw(&incidencyMatrixFromAdjacencyMatrix);
            break;
        }

        case 'P': {
            AdjacencyMatrix randomAdjacencyMatrix(40, 1.);
            randomAdjacencyMatrix.print();
            std::cout << "\nLista sąsiedztwa dla zadanej macierzy sąsiedztwa: " << std::endl;
            AdjacencyList adjacencyListFromMartix(randomAdjacencyMatrix);
            adjacencyListFromMartix.print();
            std::cout << "\nMacierz incydencji dla zadanej macierzy sąsiedztwa: " << std::endl;
            IncidencyMatrix incidencyMatrixFromAdjacencyMatrix(randomAdjacencyMatrix);
            incidencyMatrixFromAdjacencyMatrix.print();
            Draw(&incidencyMatrixFromAdjacencyMatrix);
            break;
        }

        default:	std::cout << "Podaj jedną z liter z listy" << std::endl;\

    }

    return 0;
}

char readChar(std::fstream& file, int number){
    //ustawiam wskaźnik seek na początek pliku
    file.seekg(std::ios::beg);
    for (int i = 0; i < number - 1; ++i){
        //pierwszy argument fstream::ignore() to najdłuższy możliwy wiersz,
        // drugi to znak nowej lini przy którym funkcja przechodzi do kolejnego wiersza
        file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    //tworzenie tymczasowej zmiennej i przypisanie jej wartości spod wskaźnika seek
    char letter;
    file >> letter;
    return letter;
}