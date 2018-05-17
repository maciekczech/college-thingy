#include <iostream>

#include <fstream>
#include <sstream>
#include <limits>
#include "AdjacencyList.h"
#include "AdjacencyMatrix.h"
#include "IncidenceMatrix.h"
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "SFMLpart.h"



char readChar(std::fstream& file, int number);
int main(void){


    char choice; 		/* char used to keep a letter that is read from input file 
    					* It determines a way of interpreting input data
    					 */ 
    std::fstream file;	


    /* opening file */
    file.open("input.dat");
    if(file.good())	{std::cout << "File was open successfully. " << std::endl;}
    else 			{std::cout << "Couldn't open the file. " << std::endl; return 0;}

    choice = readChar(file, 3);



    switch(choice){
        case 'L': {
            AdjacencyList adjacencyList(file);
            adjacencyList.print();
            std::cout << "\nMacierz sąsiedztwa dla zadanej listy sąsiedztwa: " << std::endl;
            AdjacencyMatrix adjacencyMatrixFromList(adjacencyList);
            adjacencyMatrixFromList.print();
            std::cout << "\nMacierz incydencji dla zadanej macierzy sąsiedztwa: " << std::endl;
            IncidenceMatrix incidenceMatrixFromAdjacencyMatrix(adjacencyMatrixFromList);
            incidenceMatrixFromAdjacencyMatrix.print();
            Draw(&incidenceMatrixFromAdjacencyMatrix);
            break;
        }
        case 'I': {
            IncidenceMatrix IncidenceMatrix(file);
            IncidenceMatrix.print();
            std::cout << "\nMacierz sąsiedztwa dla zadanej macierzy incydencji: " << std::endl;
            AdjacencyMatrix adjacencyMatrixFromIncidenceMatrix(IncidenceMatrix);
            adjacencyMatrixFromIncidenceMatrix.print();
            std::cout << "\nLista sąsiedztwa dla zadanej macierzy incydencji: " << std::endl;
            AdjacencyList adjacencyListFromIncidencyMatrix(adjacencyMatrixFromIncidenceMatrix);
            adjacencyListFromIncidencyMatrix.print();
            Draw(&IncidenceMatrix);
            break;
        }
        case 'S': {
            AdjacencyMatrix adjacencyMatrix(file);
            adjacencyMatrix.print();
            std::cout << "\nLista sąsiedztwa dla zadanej macierzy sąsiedztwa: " << std::endl;
            AdjacencyList adjacencyListFromMartix(adjacencyMatrix);
            adjacencyListFromMartix.print();
            std::cout << "\nMacierz incydencji dla zadanej macierzy sąsiedztwa: " << std::endl;
            IncidenceMatrix incidenceMatrixFromAdjacencyMatrix(adjacencyMatrix);
            incidenceMatrixFromAdjacencyMatrix.print();
            Draw(&incidenceMatrixFromAdjacencyMatrix);
            break;
        }
        case 'X': {
            AdjacencyMatrix randomAdjacencyMatrix(10, 5);
            randomAdjacencyMatrix.print();
            std::cout << "\nLista sąsiedztwa dla zadanej macierzy sąsiedztwa: " << std::endl;
            AdjacencyList adjacencyListFromMartix(randomAdjacencyMatrix);
            adjacencyListFromMartix.print();
            std::cout << "\nMacierz incydencji dla zadanej macierzy sąsiedztwa: " << std::endl;
            IncidenceMatrix incidenceMatrixFromAdjacencyMatrix(randomAdjacencyMatrix);
            incidenceMatrixFromAdjacencyMatrix.print();
            Draw(&incidenceMatrixFromAdjacencyMatrix);
            break;
        }

        case 'P': {
            AdjacencyMatrix randomAdjacencyMatrix(18, 0.3);
            randomAdjacencyMatrix.print();
            std::cout << "\nLista sąsiedztwa dla zadanej macierzy sąsiedztwa: " << std::endl;
            AdjacencyList adjacencyListFromMartix(randomAdjacencyMatrix);
            adjacencyListFromMartix.print();
            std::cout << "\nMacierz incydencji dla zadanej macierzy sąsiedztwa: " << std::endl;
            IncidenceMatrix incidenceMatrixFromAdjacencyMatrix(randomAdjacencyMatrix);
            incidenceMatrixFromAdjacencyMatrix.print();
            Draw(&incidenceMatrixFromAdjacencyMatrix);
            break;
        }

        default:	std::cout << "Podaj jedną z liter z listy" << std::endl;\

    }

    return 0;
}

char readChar(std::fstream& file, int number){
    file.seekg(std::ios::beg);
    for (int i = 0; i < number - 1; ++i){
        file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    char letter;
    file >> letter;
    return letter;
}