//
// Created by maciek on 13.04.18.
//

#ifndef PROJEKT_1_VOL2_REPRESENTATION_H
#define PROJEKT_1_VOL2_REPRESENTATION_H

#include <iostream>
#include <fstream>
#include <limits>
#include <sstream>

//klasa bazowa zrobiona bardziej dla picu niż użyteczności.
//z drugiej strony dzięki niej nie trzeba za każdym razem pisać setterów i getterów
//jest git.

class Representation {
public:
    Representation(){}
    virtual ~Representation(){}

    /*settery*/
    void setType(char type){m_type = type;}
    void setSize(int size){m_size = size;}
    void setElement(int i, int j, int element);

    /*gettery*/
    int** getMatrix(){return m_matrix;}
    char getType(){return m_type;}
    int getSize(){return m_size;}
    int getElement(int i, int j) const;

    /*wypisuje macierz*/
    virtual void print();

protected:
    int ** m_matrix;

    /*  L - stands for adjacency list
    *   I - stands for incidency matrix
    *   S - stands for adjacency matrix
    */
    char m_type;

    /*size of matrix*/
    int m_size;

};


#endif //PROJEKT_1_VOL2_REPRESENTATION_H
