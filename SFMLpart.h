#pragma once
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <cmath>
#include "IncidencyMatrix.h"
#include "font.h"
#include <string>

#define PI 3.14159265

//Pierdolnałem tylko jeden header odpowiedzialny za rysowanie, najebane jak w cygańskim tobołku, ale działa.

void Draw(IncidencyMatrix* matrix){
	const int radius = 40;	/*radius of a circle shaped node*/
    const int r = 320;		/*radius used to calcute posistions of a nodes, it is basically
    						*the distance between the center of a window and every single node*/
	
	float* angles;			/*pointer, that I will allocate memmory to, later on
							*will be used as an array that stores angles used to calculate positions*/

	const int verticiesToDraw = matrix->getVerticies();

	/*vectors used to store information of the beggining and the end of a lines that connect nodes*/
	std::vector < int > from;
	std::vector < int > to;

	/*deviding whole entire circle into equal seperate pieces*/
	float alphaOffset = 360./verticiesToDraw;
	
	/*allocating memory for angles*/
	angles = new float[verticiesToDraw];
	angles[0] = 0;

	/*adding consecutive angles in a simple way
	*I'm using pointer, because it's supposed to be faster this way*/
	for (int i = 1; i < verticiesToDraw; ++i) *(angles + i) = *(angles + i - 1) + alphaOffset;

	/*more less middle of a screen*/
	int Sx = 500 - radius/2, Sy = 500 - radius/2;
	srand (time(NULL));

    // create the window
    sf::RenderWindow window(sf::VideoMode(1000, 1000), "Malowanko");

    //SFML objects
    sf::Font font;
    font.loadFromMemory(font_data, font_data_size);

 	sf::Text* text[verticiesToDraw];
    sf::CircleShape* shapes[verticiesToDraw];

    //setting parameters of the verticies 
    for (int i = 0; i < verticiesToDraw ; ++i)
    {
    	shapes[i] = new sf::CircleShape(static_cast<int>(radius - verticiesToDraw*0.3));
    	shapes[i]->setFillColor(sf::Color(74, 175, 226));
    	shapes[i]->setPosition(r * cos(angles[i] * PI/180.) + Sx, r * sin(angles[i] * PI/180.) + Sy);
    	shapes[i]->setOutlineThickness(2);
		shapes[i]->setOutlineColor(sf::Color::Red);

    	text[i] = new sf::Text;
    	text[i]->setFont(font);
    	text[i]->setCharacterSize(30);
    	text[i]->setColor(sf::Color::Black);
    	if(i < 9) text[i]->setPosition(r * cos(angles[i] * PI/180.) + Sx + 27, r * sin(angles[i] * PI/180.) + Sy + 14);
    	else text[i]->setPosition(r * cos(angles[i] * PI/180.) + Sx + 17, r * sin(angles[i] * PI/180.) + Sy + 14);
   		text[i]->setString(std::to_string(i + 1));
    }

    /*im iretating though incidence martix to find points where to start and end lines that connect verticies
    *each column has two "1" inside, which determine start and end of the egde
    *then I collect indexes into the vector, so that I can read them easier later on*/

    for (int edge = 0; edge < matrix->getEdges(); edge++){
    	for (int vertex = 0; vertex < matrix->getVerticies(); vertex++){
            /*first it finds first "1" in a particular column
            *then it looks for the second one in the same column*/
    		if(matrix->getElement(vertex, edge)){
    			for (int i = vertex + 1; i < matrix->getVerticies(); i++){
    				if(matrix->getElement(i, edge)){
    					from.push_back(vertex);
    					to.push_back(i);
    					break;
    				}
    			}
    		}
    	}
    }

    //vector that holds lines as sf::VertexArray which is SFML class
    std::vector <sf::VertexArray> line;
	for (unsigned int i = 0; i < to.size(); ++i){
		line.resize(i + 1);
		line[i] = sf::VertexArray(sf::LinesStrip, 2);
		line[i][0].position = text[from.at(i)]->getPosition();
		line[i][0].position.x += 5; line[i][0].position.y += 0;
		line[i][0].color = sf::Color::Red;
		line[i][1].position = text[to.at(i)]->getPosition();
		line[i][1].position.x += 5; line[i][0].position.y += 0;
		line[i][1].color = sf::Color::Red;
	}


    /* run the program as long as the window is open */
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        /* clear the window with black color */
        window.clear(sf::Color(216, 214, 208));

        /* draw lines */
        for (unsigned int i = 0; i < to.size(); ++i){
        	window.draw(line[i]);
        }
        /* draw verticies */
        for (int i = 0; i < verticiesToDraw; ++i)
        {
        	window.draw(*shapes[i]);
        	window.draw(*text[i]);
        }
        
        window.display();
    }

}
