#include "fonction.hpp"

std::string toString(int mot)
{
    std::stringstream ss;
    std::string result;
    ss << mot;
    ss >> result;
    return result;
}

std::string toString(std::size_t mot)
{
    std::stringstream ss;
    std::string result;
    ss << mot;
    ss >> result;
    return result;
}

std::string toString(float mot)
{
    std::stringstream ss;
    std::string result;
    ss << mot;
    ss >> result;
    return result;
}

bool isCollide(sf::Vector2i point,sf::Sprite sprite
               ,int WidthSprite,int HeightSprite)
{
    bool result=false;
    int x1,x2;
    int y1,y2;
    x1 = sprite.getGlobalBounds().left-sprite.getOrigin().x;
    x2 = sprite.getGlobalBounds().left-sprite.getOrigin().x+WidthSprite;
    y1 = sprite.getGlobalBounds().top-sprite.getOrigin().y;
    y2 = sprite.getGlobalBounds().top-sprite.getOrigin().y+HeightSprite;
    if(point.x > x1 && point.x < x2
       && point.y > y1 && point.y < y2)
    {
        result=true;
    }

    return result;
}

float getVectorLength(sf::Vector2f vecteur1,sf::Vector2f vecteur2)
{
    return abs(sqrt(pow((vecteur2.x-vecteur1.x),2)+pow((vecteur2.y-vecteur1.y),2)));
}

