#ifndef FONCTION_HPP_INCLUDED
#define FONCTION_HPP_INCLUDED

#include <string>
#include <iostream>
#include <sstream>
#include <SFML/Graphics.hpp>
#include <math.h>

std::string toString(std::size_t mot);
/*** transform et retourne un size_t en string
***/
std::string toString(int mot);
/*** transform et retourne un int en string
***/
std::string toString(float mot);
/*** transform et retourne un float en string
***/
std::string toString(sf::Time mot);
/*** transform et retourne un time en string
***/

bool isCollide(sf::Vector2i point,sf::Sprite sprite,
               int WidthSprite,int HeightSprite);
/*** return true si le point est en collision avec un sprite
***/
float getVectorLength(sf::Vector2f vecteur1,sf::Vector2f vecteur2);
/*** return la longueur entre deux points
***/

#endif // FONCTION_HPP_INCLUDED
