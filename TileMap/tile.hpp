#ifndef TILE_HPP_INCLUDED
#define TILE_HPP_INCLUDED

#include <SFML/Graphics.hpp>
#include <iostream>
#define TILE_SIZE 32

#define TYPE_WALL 0
#define TYPE_GROUND 1
#define TYPE_BRICS 2
#define TYPE_WOOD 3
#define BONUS_ADD_BOMB 4
#define BONUS_BOOST_EXPLOSION 5
#define BONUS_BOOST_SPEED 6
#define TYPE_BOMB 7


class tile
{
public:
    tile(int type,sf::Vector2f position,int tileNumberInMap);
    ///constructeur
    bool getIsSolide();
    /****return si le tile est solide
    ****/
    bool getIsDestructible();
    /*** return si le tile est destructible
    ***/
    sf::Vector2f getPosition();
    /*** return la position du tile
    ***/
    bool DestructTile();
    /*** return si le tile est detruit apres avoir recu des degats
    ***/
    bool getIsFree();
    /*** return si le tile est free
    ***/
    void damageTile();
    /*** infige des degats au tile
    ***/
    bool getIsDestruct();
    /*** return si le tile est detruit
    ***/
    void setType(int type);
    /*** met le type de tile (mur,brique,bois etc...)
    ***/
    void setIsFree(bool active);
    /*** gere la boucle principale du joueur et vefifie si celui-ci
    est encore en vie
    ***/
    sf::RectangleShape getHitBox();
    /*** return la hit box du tile
    ***/




private:
    int m_type; // different type to manage texture
    float m_probability; // The probability to spawn
    int m_life;
    bool m_isColision;
    bool m_isDestructible;
    int m_numberInMap;
    bool m_isFree;
    sf::RectangleShape m_hitBox;
    sf::Vector2f m_position;

};



#endif // TILE_HPP_INCLUDED
