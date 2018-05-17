//
// Created by maciek on 13.04.18.
//

#include "Representation.h"


void Representation::print(){
    for (int i = 0; i < this->m_size; i++){
        for (int j = 0; j < this->m_size; j++){
            std::cout << this->m_matrix[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

int Representation::getElement(int i, int j) const {
    if(m_matrix) return this->m_matrix[i][j];
}

void Representation::setElement(int i, int j, int element) {
    if(m_matrix) this->m_matrix[i][j] = element;
}
