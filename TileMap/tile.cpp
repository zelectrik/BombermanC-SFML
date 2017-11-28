#include "tile.hpp"

tile::tile(int type,sf::Vector2f position,int tileNumberInMap)
{
    m_type=type;
    m_isFree=true;
    switch(m_type)
    {
    case TYPE_WALL:
        m_probability=0.2;
        m_life=1;
        m_isColision=true;
        m_isDestructible=false;
        m_position=position;
        break;
    case TYPE_GROUND:
        m_probability=0.6;
        m_life=1;
        m_isColision=false;
        m_isDestructible=false;
        m_position=position;
        break;
    case TYPE_BRICS:
        m_probability=0.1;
        m_life=2;
        m_isColision=true;
        m_isDestructible=true;
        m_position=position;
        break;
    case TYPE_WOOD:
        m_probability=0.1;
        m_life=1;
        m_isColision=true;
        m_isDestructible=true;
        m_position=position;
        break;
    }
    m_hitBox.setPosition(m_position);
    m_hitBox.setSize(sf::Vector2f(TILE_SIZE,TILE_SIZE));
    m_hitBox.setFillColor(sf::Color::Transparent);
    m_numberInMap=tileNumberInMap;
}

bool tile::getIsSolide()
{
    return m_isColision;
}

sf::Vector2f tile::getPosition()
{
    return m_position;
}

sf::RectangleShape tile::getHitBox()
{
    return m_hitBox;
}

bool tile::getIsDestructible()
{
    return m_isDestructible;
}

bool tile::DestructTile()
{
    m_life--;
    return (m_life<=0);
}

void tile::damageTile()
{
    m_life--;
}

bool tile::getIsDestruct()
{
    if(m_life<=0)
        return true;
    else
        return false;
}

bool tile::getIsFree()
{
    return m_isFree;
}

void tile::setIsFree(bool active)
{
    m_isFree=active;
}

void tile::setType(int type)
{
    m_type=type;
}
