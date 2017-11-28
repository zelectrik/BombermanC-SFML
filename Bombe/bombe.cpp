#include "bombe.hpp"

bomb::bomb()
    :   m_bombTexture(PATH_TO_BOMB_TEXTURE)
    ,   m_explosionTexture(PATH_TO_EXPLOSION_TEXTURE)
{
    m_isUse=false;
    m_Destruct=false;
    m_isSolid=false;
    m_launch=false;
    m_makeDamage=false;
}

void bomb::launchBomb()
{
    m_launch=true;
}

bool bomb::damagePlayer(sf::Vector2f playerPos)
{
    bool isTouch=false;
    if(m_makeDamage == true)
    {
        if(m_caseBomb==playerPos)
        {
            isTouch=true;
        }
        for(int i=0; i<m_explosionSprite.size() && isTouch==false; i++)
        {
            if(sf::Vector2f(m_explosionSprite[i].getPosition().x/TILE_SIZE,m_explosionSprite[i].getPosition().y/TILE_SIZE)==playerPos)
            {
                isTouch=true;
            }
        }
    }
    return isTouch;
}

sf::Vector2f bomb::getBombPosition()
{
    return m_caseBomb;
}

bool bomb::damageBomb(bomb *bombs)
{
    for(int i=0; i<m_caseExplosion.size(); i++)
    {
        if(bombs->getBombPosition()==m_caseExplosion[i])
        {
            bombs->launchBomb();
        }
    }

}

bool bomb::getLaunch()
{
    return m_launch;
}

void bomb::update(TileMap &mapGen)
{

    if(m_isUse==true)
    {
        if(m_timer.getElapsedTime().asSeconds()>=m_delayToExplosion.asSeconds() || (m_launch==true && m_makeDamage==false))
        {
            /***************Manage the position of the sprite of explosion*********************/

            int n=0;
            m_bombSprite.setTextureRect(sf::IntRect(SIZE_BOMB,0,SIZE_BOMB,SIZE_BOMB));
            bool can_continue=true;
            int cpt=0;
            int cptTour=0;
            sf::Vector2f bombTouch;
            m_makeDamage=true;
            /**********Left Explosion***************/
            for(int i=0; i<=m_bombPower-1 && can_continue==true; i++)
            {
                n++;
                if(mapGen.getTileNumber(m_caseBomb.y,m_caseBomb.x-n)==TYPE_WALL)
                    can_continue=false;
                else
                {

                    cpt++;
                    m_explosionSprite.push_back(sf::Sprite());
                    m_explosionSprite[i].setPosition(sf::Vector2f(m_positionBomb.x-n*SIZE_BOMB,m_positionBomb.y));
                    m_explosionSprite[i].setTexture(*m_explosionTexture.get());
                    m_explosionSprite[i].setTextureRect(sf::IntRect(SIZE_BOMB,0,SIZE_BOMB,SIZE_BOMB));
                    m_caseExplosion.push_back(sf::Vector2f(m_caseBomb.x-n,m_caseBomb.y));
                    if(mapGen.getTileNumber(m_caseBomb.y,m_caseBomb.x-n)!=TYPE_GROUND
                            && mapGen.getTileNumber(m_caseBomb.y,m_caseBomb.x-n)!=BONUS_ADD_BOMB
                            && mapGen.getTileNumber(m_caseBomb.y,m_caseBomb.x-n)!=BONUS_BOOST_EXPLOSION
                            && mapGen.getTileNumber(m_caseBomb.y,m_caseBomb.x-n)!=BONUS_BOOST_SPEED)
                        can_continue=false;
                }

            }
            n=0;
            can_continue=true;
            cptTour=cpt;
            /**********Right Explosion***************/
            for(int i=cpt; i<=cptTour+m_bombPower-1 && can_continue==true; i++)
            {
                n++;
                if(mapGen.getTileNumber(m_caseBomb.y,m_caseBomb.x+n)==TYPE_WALL)
                    can_continue=false;
                else
                {
                    cpt++;
                    m_explosionSprite.push_back(sf::Sprite());
                    m_explosionSprite[i].setTexture(*m_explosionTexture.get());
                    m_explosionSprite[i].setPosition(sf::Vector2f(m_positionBomb.x+n*SIZE_BOMB,m_positionBomb.y));
                    m_explosionSprite[i].setTextureRect(sf::IntRect(SIZE_BOMB,0,SIZE_BOMB,SIZE_BOMB));
                    m_caseExplosion.push_back(sf::Vector2f(m_caseBomb.x+n,m_caseBomb.y));
                    if(mapGen.getTileNumber(m_caseBomb.y,m_caseBomb.x+n)!=TYPE_GROUND
                            && mapGen.getTileNumber(m_caseBomb.y,m_caseBomb.x+n)!=BONUS_ADD_BOMB
                            && mapGen.getTileNumber(m_caseBomb.y,m_caseBomb.x+n)!=BONUS_BOOST_EXPLOSION
                            && mapGen.getTileNumber(m_caseBomb.y,m_caseBomb.x+n)!=BONUS_BOOST_SPEED)
                        can_continue=false;
                }


            }
            n=0;
            can_continue=true;
            cptTour=cpt;
            /**********Top Explosion***************/
            for(int i=cpt; i<=cptTour+m_bombPower-1 && can_continue==true; i++)
            {
                n++;
                if(mapGen.getTileNumber(m_caseBomb.y-n,m_caseBomb.x)==TYPE_WALL)
                    can_continue=false;
                else
                {
                    cpt++;
                    m_explosionSprite.push_back(sf::Sprite());
                    m_explosionSprite[i].setTexture(*m_explosionTexture.get());
                    m_explosionSprite[i].setPosition(sf::Vector2f(m_positionBomb.x,m_positionBomb.y-n*SIZE_BOMB));
                    m_explosionSprite[i].setTextureRect(sf::IntRect(0,0,SIZE_BOMB,SIZE_BOMB));
                    m_caseExplosion.push_back(sf::Vector2f(m_caseBomb.x,m_caseBomb.y-n));
                    if(mapGen.getTileNumber(m_caseBomb.y-n,m_caseBomb.x)!=TYPE_GROUND
                            && mapGen.getTileNumber(m_caseBomb.y-n,m_caseBomb.x)!=BONUS_ADD_BOMB
                            && mapGen.getTileNumber(m_caseBomb.y-n,m_caseBomb.x)!=BONUS_BOOST_EXPLOSION
                            && mapGen.getTileNumber(m_caseBomb.y-n,m_caseBomb.x)!=BONUS_BOOST_SPEED)
                        can_continue=false;
                }

            }
            n=0;
            can_continue=true;
            cptTour=cpt;
            /**********Bot Explosion***************/
            for(int i=cpt; i<=cptTour+m_bombPower-1 && can_continue==true; i++)
            {
                n++;
                bombTouch=sf::Vector2f(0,0);
                if(mapGen.getTileNumber(m_caseBomb.y+n,m_caseBomb.x)==TYPE_WALL)
                    can_continue=false;
                else if(mapGen.getTileNumber(m_caseBomb.y+n,m_caseBomb.x)==TYPE_BOMB)
                {
                    bombTouch=sf::Vector2f(m_caseBomb.y+n,m_caseBomb.x);
                    m_caseExplosion.push_back(sf::Vector2f(m_caseBomb.x,m_caseBomb.y+n));
                }
                else
                {

                    cpt++;
                    m_explosionSprite.push_back(sf::Sprite());
                    m_explosionSprite[i].setTexture(*m_explosionTexture.get());
                    m_explosionSprite[i].setPosition(sf::Vector2f(m_positionBomb.x,m_positionBomb.y+n*SIZE_BOMB));
                    m_explosionSprite[i].setTextureRect(sf::IntRect(0,0,SIZE_BOMB,SIZE_BOMB));
                    m_caseExplosion.push_back(sf::Vector2f(m_caseBomb.x,m_caseBomb.y+n));
                    if(mapGen.getTileNumber(m_caseBomb.y+n,m_caseBomb.x)!=TYPE_GROUND
                            && mapGen.getTileNumber(m_caseBomb.y+n,m_caseBomb.x)!=BONUS_ADD_BOMB
                            && mapGen.getTileNumber(m_caseBomb.y+n,m_caseBomb.x)!=BONUS_BOOST_EXPLOSION
                            && mapGen.getTileNumber(m_caseBomb.y+n,m_caseBomb.x)!=BONUS_BOOST_SPEED)
                        can_continue=false;
                }

            }

            m_isExplode=true;
            m_timer.restart();
            bomb::damageTile(mapGen);
            bomb::positionBombTouch(bombTouch);


        }

        if(m_timer.getElapsedTime().asSeconds()>=m_displayExplosion.asSeconds() && m_isExplode==true)
        {
            m_Destruct=true;
            m_isUse=false;
            m_isSolid=false;
            m_makeDamage=false;
            m_explosionSprite.clear();
            m_caseExplosion.clear();
            mapGen.setTileNumber(m_caseBomb.y,m_caseBomb.x,TYPE_GROUND);
        }
    }

}

sf::Vector2f bomb::positionBombTouch(sf::Vector2f position)
{
    return position;
}



int bomb::getNumberOfCaseExplode()
{
    return m_caseExplosion.size();
}

sf::Vector2f bomb::getCaseExplose(int number)
{
    return m_caseExplosion[number];
}

bool bomb::getBombIsUse()
{
    return m_isUse;
}

void bomb::damageTile(TileMap &mapGen)
{
    for(int i=0; i<m_caseExplosion.size(); i++)
    {
        if(mapGen.getTileNumber(m_caseExplosion[i].y,m_caseExplosion[i].x)==TYPE_BRICS
                || mapGen.getTileNumber(m_caseExplosion[i].y,m_caseExplosion[i].x)==TYPE_WOOD)
            mapGen.change(m_caseExplosion[i].y,m_caseExplosion[i].x,TYPE_GROUND,true);
        else if(mapGen.getTileNumber(m_caseExplosion[i].y,m_caseExplosion[i].x)==BONUS_ADD_BOMB
                || mapGen.getTileNumber(m_caseExplosion[i].y,m_caseExplosion[i].x)==BONUS_BOOST_EXPLOSION
                || mapGen.getTileNumber(m_caseExplosion[i].y,m_caseExplosion[i].x)==BONUS_BOOST_SPEED)
            mapGen.change(m_caseExplosion[i].y,m_caseExplosion[i].x,TYPE_GROUND,false);
    }
}

void bomb::createBomb(sf::Vector2f BombPosition
                      ,sf::Vector2f casePosition,int bombPower,TileMap &map)
{
    m_caseExplosion.clear();
    m_caseBomb=casePosition;
    if(map.getTileNumber(m_caseBomb.y,m_caseBomb.x)==TYPE_GROUND
            || map.getTileNumber(m_caseBomb.y,m_caseBomb.x)==BONUS_ADD_BOMB
            || map.getTileNumber(m_caseBomb.y,m_caseBomb.x)==BONUS_BOOST_EXPLOSION
            || map.getTileNumber(m_caseBomb.y,m_caseBomb.x)==BONUS_BOOST_SPEED)
    {
        map.setTileNumber(m_caseBomb.y,m_caseBomb.x,TYPE_BOMB);
        m_bombPower=bombPower;
        m_isExplode=false;
        m_Destruct=false;
        m_isUse=true;
        m_isSolid=true;
        m_launch=false;
        m_positionBomb=BombPosition;
        m_delayToExplosion=sf::seconds(DELAY_EXPLOSION);
        m_displayExplosion=sf::seconds(DELAY_DISPLAY);
        /************change if we add Texture Pack**********************/


        m_bombSprite.setTexture(*m_bombTexture.get());
        m_bombSprite.setTextureRect(sf::IntRect(0,0,SIZE_BOMB,SIZE_BOMB));
        m_bombSprite.setPosition(m_positionBomb);

        m_timer.restart();
    }

}
