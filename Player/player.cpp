#include "player.hpp"
#include <cmath>

player::player(bool isIA,int id,std::string name,std::string pathToFile,int FrameLimit,sf::Vector2f positionCase,TileMap *mapGen)
    : m_id(0)
    , m_isIA(isIA)
    , m_life(INITIAL_LIFE)
    , m_bombAmmo(INITIAL_AMMO)
    , m_playerSpeed(INITIAL_SPEED)
    , m_playerName("empty")
    , m_pathFile("Media/Image/lol.png")
    , m_anim(1,Down)
    , m_bombPower(1)
{
    m_id=id;
    m_playerName=name;
    m_bombAmmo=1;
    m_bombUse=0;
    canMove=true;
    m_getFocusPos=true;
    m_visitedList.push_back(new sf::Vector2f(0,0));
    m_tTimeIA = sf::seconds(DELAY_EXPLOSION+DELAY_DISPLAY+1);
    if(m_isIA==true)
        m_playerSpeed=100;
    if(!m_playerTexture.loadFromFile(pathToFile))
        std::cout << "error" << std::endl;

    m_playerSprite.setTexture(m_playerTexture);
    m_animSpeed=FrameLimit/4;
    m_playerBomb.push_back(bomb());
    m_xPos=positionCase.x;
    m_BefMovement=sf::Vector2f(0,0);
    m_yPos=positionCase.y;
    m_playerSprite.setPosition(sf::Vector2f(m_xPos*TILE_SIZE,m_yPos*TILE_SIZE));
    m_focusPos=mapGen->getPointPosition(WIDTH_MAP/2,HEIGHT_MAP/2);

}

void player::resetPlayer()
{
    m_playerSprite.setPosition(sf::Vector2f(TILE_SIZE,TILE_SIZE));
    m_life=INITIAL_LIFE;
    m_start=true;
    m_bombAmmo=INITIAL_AMMO;
    m_getFocusPos=true;
    if(m_isIA==true)
        m_playerSpeed=100;
    m_bombPower=1;
    if(m_id==0)
    {
        m_xPos=1;
        m_yPos=1;
        m_visitedList.clear();
        m_visitedList.push_back(new sf::Vector2f(1,1));
        m_visitedList.push_back(new sf::Vector2f(2,1));
        m_visitedList.push_back(new sf::Vector2f(1,2));
    }
    else if(m_id==1)
    {
        m_xPos=WIDTH_MAP;
        m_yPos=HEIGHT_MAP;
        m_visitedList.clear();
        m_visitedList.push_back(new sf::Vector2f(WIDTH_MAP,HEIGHT_MAP));
        m_visitedList.push_back(new sf::Vector2f(WIDTH_MAP-1,HEIGHT_MAP));
        m_visitedList.push_back(new sf::Vector2f(WIDTH_MAP,HEIGHT_MAP-1));
    }
    else if(m_id==2)
    {
        m_xPos=1;
        m_yPos=HEIGHT_MAP;
        m_visitedList.clear();
        m_visitedList.push_back(new sf::Vector2f(1,HEIGHT_MAP));
        m_visitedList.push_back(new sf::Vector2f(2,HEIGHT_MAP));
        m_visitedList.push_back(new sf::Vector2f(1,HEIGHT_MAP-1));
    }
    else if(m_id==3)
    {
        m_xPos=WIDTH_MAP;
        m_yPos=1;
        m_visitedList.clear();
        m_visitedList.push_back(new sf::Vector2f(WIDTH_MAP,1));
        m_visitedList.push_back(new sf::Vector2f(WIDTH_MAP-1,1));
        m_visitedList.push_back(new sf::Vector2f(WIDTH_MAP,2));
    }

    m_playerBomb.clear();
    m_playerBomb.push_back(bomb());
    m_playerSprite.setPosition(sf::Vector2f(m_xPos*TILE_SIZE,m_yPos*TILE_SIZE));
}

void player::addEnnemi(player* ennemies)
{
    m_ennemi.push_back(ennemies);
}

void player::setPosition(sf::Vector2f positionCase)
{
    m_playerSprite.setPosition(sf::Vector2f(positionCase.x*TILE_SIZE,positionCase.y*TILE_SIZE));
}

void player::drawPlayer(sf::RenderWindow &fenetre)
{
    for(int i=0; i<m_playerBomb.size(); i++)
    {
        if(m_playerBomb[i].getBombIsUse()==true)
            fenetre.draw(m_playerBomb[i]);
    }
    if(m_life!=0)
    {
        fenetre.draw(m_playerSprite);
    }
}

void player::eventPlayerInput(sf::Keyboard::Key key,TileMap &mapGen)
{
    if(m_isIA==false)
    {
        bool canUseLower=false;
        if((m_id==0 && key == sf::Keyboard::A)||(m_id==1 && key == sf::Keyboard::Numpad4)
                ||(m_id==2 && key == sf::Keyboard::RControl)||(m_id==3 && key == sf::Keyboard::I))
        {
            for(int i=0; i<m_playerBomb.size() && canUseLower==false; i++)
            {
                if(m_playerBomb[i].getBombIsUse()==false)
                {
                    canUseLower=true;
                    m_playerBomb[i].createBomb(mapGen.getPointPosition(m_xPos,m_yPos),sf::Vector2f(m_xPos,m_yPos),m_bombPower,mapGen);

                }
            }
            m_bombUse++;
        }
    }

}

sf::Vector2f player::getPosition()
{
    return sf::Vector2f(m_xPos,m_yPos);
}


void player::handlePlayerInput(TileMap &mapGen)
{
    sf::Vector2f movement(0.f,0.f);
    if(m_isIA==false)
    {
        if((m_id==0 && sf::Keyboard::isKeyPressed(sf::Keyboard::Z))||(m_id==1 && sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad5))
                ||(m_id==2 && sf::Keyboard::isKeyPressed(sf::Keyboard::Up))||(m_id==3 && sf::Keyboard::isKeyPressed(sf::Keyboard::O)))
            movement.y=-1;
        else if((m_id==0 && sf::Keyboard::isKeyPressed(sf::Keyboard::S))||(m_id==1 && sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad2))
                ||(m_id==2 && sf::Keyboard::isKeyPressed(sf::Keyboard::Down))||(m_id==3 && sf::Keyboard::isKeyPressed(sf::Keyboard::L)))
            movement.y=+1;
        else if((m_id==0 && sf::Keyboard::isKeyPressed(sf::Keyboard::Q))||(m_id==1 && sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad1))
                ||(m_id==2 && sf::Keyboard::isKeyPressed(sf::Keyboard::Left))||(m_id==3 && sf::Keyboard::isKeyPressed(sf::Keyboard::K)))
            movement.x=-1;
        else if((m_id==0 && sf::Keyboard::isKeyPressed(sf::Keyboard::D))||(m_id==1 && sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad3))
                ||(m_id==2 && sf::Keyboard::isKeyPressed(sf::Keyboard::Right))||(m_id==3 && sf::Keyboard::isKeyPressed(sf::Keyboard::M)))
            movement.x=+1;

        if((mapGen.getTileNumber(m_yPos+movement.y,m_xPos+movement.x) == TYPE_GROUND
                || mapGen.getTileNumber(m_yPos+movement.y,m_xPos+movement.x) == BONUS_ADD_BOMB
                || mapGen.getTileNumber(m_yPos+movement.y,m_xPos+movement.x) == BONUS_BOOST_EXPLOSION
                || mapGen.getTileNumber(m_yPos+movement.y,m_xPos+movement.x) == BONUS_BOOST_SPEED)
                && (abs(m_playerSprite.getPosition().x-mapGen.getPointPosition(m_xPos+movement.x,m_yPos+movement.y).x)
                    +abs(m_playerSprite.getPosition().y-mapGen.getPointPosition(m_xPos+movement.x,m_yPos+movement.y).y) <= TILE_SIZE+5))
        {
            m_xPos+=movement.x;
            m_yPos+=movement.y;
        }
    }
    if(m_isIA==true)
    {

        if(m_ennemi.size()==0 && m_start==true)
        {

            canMove=true;
            m_getFocusPos=true;
            m_choosePos=mapGen.getPointPosition(WIDTH_MAP/2,HEIGHT_MAP/2);
        }
        else if(m_ennemi.size()!=0 && m_start==true)
        {

            canMove=true;
            m_getFocusPos=true;
            chooseFocus();
            m_start=false;
            m_choosePos=sf::Vector2f(abs(m_ennemiFocus->getPosition().x),abs(m_ennemiFocus->getPosition().y));
        }

        if(m_cTimeIA.getElapsedTime()>m_tTimeIA)
        {
            canMove=true;
            m_getFocusPos=true;
            m_choosePos=sf::Vector2f(abs(m_ennemiFocus->getPosition().x),abs(m_ennemiFocus->getPosition().y));
        }

        if(canMove==false)
        {
            int n=m_visitedList.size();
            while(m_getFocusPos==false && n>0)
            {
                n--;
                for(int i=0; i<m_playerBomb.size() && m_getFocusPos==false; i++)
                {

                    if(m_playerBomb[i].getBombIsUse())
                    {
                        if((m_playerBomb[i].getBombPosition().x!=m_visitedList[n]->x && m_playerBomb[i].getBombPosition().y!=m_visitedList[n]->y)||(getVectorLength(m_playerBomb[i].getBombPosition(),*m_visitedList[n])>m_bombPower))
                        {
                            m_getFocusPos=true;
                            m_choosePos=sf::Vector2f(m_visitedList[n]->x,m_visitedList[n]->y);
                        }
                    }

                }

            }
        }
        chooseFocus();
        if(m_xPos>m_choosePos.x && (mapGen.getTileNumber(m_yPos,m_xPos-1)==TYPE_GROUND
                                    || mapGen.getTileNumber(m_yPos,m_xPos-1)==BONUS_ADD_BOMB
                                    || mapGen.getTileNumber(m_yPos,m_xPos-1)==BONUS_BOOST_EXPLOSION
                                    || mapGen.getTileNumber(m_yPos,m_xPos-1)==BONUS_BOOST_SPEED)
                && mapGen.getTileNumber(m_yPos,m_xPos-1)!=TYPE_BOMB)
            movement.x=-1;
        else if(m_xPos<m_choosePos.x &&( mapGen.getTileNumber(m_yPos,m_xPos+1)==TYPE_GROUND
                                         ||  mapGen.getTileNumber(m_yPos,m_xPos+1)==BONUS_ADD_BOMB
                                         ||  mapGen.getTileNumber(m_yPos,m_xPos+1)==BONUS_BOOST_EXPLOSION
                                         ||  mapGen.getTileNumber(m_yPos,m_xPos+1)==BONUS_BOOST_SPEED)
                && mapGen.getTileNumber(m_yPos,m_xPos+1)!=TYPE_BOMB)
            movement.x=+1;
        else if(m_yPos>m_choosePos.y && (mapGen.getTileNumber(m_yPos-1,m_xPos)==TYPE_GROUND
                                         || mapGen.getTileNumber(m_yPos-1,m_xPos)==BONUS_ADD_BOMB
                                         || mapGen.getTileNumber(m_yPos-1,m_xPos)==BONUS_BOOST_EXPLOSION
                                         || mapGen.getTileNumber(m_yPos-1,m_xPos)==BONUS_BOOST_SPEED)
                && mapGen.getTileNumber(m_yPos-1,m_xPos)!=TYPE_BOMB)
            movement.y=-1;
        else if(m_yPos<m_choosePos.y && (mapGen.getTileNumber(m_yPos+1,m_xPos)==TYPE_GROUND
                                         || mapGen.getTileNumber(m_yPos+1,m_xPos)==BONUS_ADD_BOMB
                                         || mapGen.getTileNumber(m_yPos+1,m_xPos)==BONUS_BOOST_EXPLOSION
                                         || mapGen.getTileNumber(m_yPos+1,m_xPos)==BONUS_BOOST_SPEED)
                && mapGen.getTileNumber(m_yPos+1,m_xPos)!=TYPE_BOMB)
            movement.y=+1;

        else if ((m_xPos!=m_choosePos.x || m_yPos!=m_choosePos.y) && canMove==true && m_start==false &&
                 ((m_id==0 && (m_xPos!=1 || m_yPos!=1))||(m_id==1 && (m_xPos!=WIDTH_MAP || m_yPos!=HEIGHT_MAP))||(m_id==2 && (m_xPos!=1 || m_yPos!=HEIGHT_MAP-1))||(m_id==3 && (m_xPos!=WIDTH_MAP-1 || m_yPos!=1))))
        {
                bool canPos=true;
                for(int i=0; i<m_playerBomb.size(); i++)
                {
                    if(m_playerBomb[i].getBombIsUse())
                        canPos==false;
                }
                if(canPos)
                {
                    canMove=false;
                    bool canUseLower=false;
                    m_getFocusPos=false;
                    for(int i=0; i<m_playerBomb.size() && canUseLower==false; i++)
                    {
                        if(m_playerBomb[i].getBombIsUse()==false)
                        {
                            canUseLower=true;
                            m_playerBomb[i].createBomb(mapGen.getPointPosition(m_xPos,m_yPos),sf::Vector2f(m_xPos,m_yPos),m_bombPower,mapGen);

                        }
                    }
                    m_bombUse++;
                    m_cTimeIA.restart();
                }
        }
        if ((m_xPos==m_choosePos.x && m_yPos==m_choosePos.y) && canMove==true && m_start==false)
        {

            bool canPos=true;
            for(int i=0; i<m_playerBomb.size(); i++)
            {
                if(m_playerBomb[i].getBombIsUse())
                    canPos==false;
            }
            if(canPos)
            {
                canMove=false;
                chooseFocus();
                bool canUseLower=false;
                m_getFocusPos=false;
                for(int i=0; i<m_playerBomb.size() && canUseLower==false; i++)
                {
                    if(m_playerBomb[i].getBombIsUse()==false)
                    {
                        canUseLower=true;
                        m_playerBomb[i].createBomb(mapGen.getPointPosition(m_xPos,m_yPos),sf::Vector2f(m_xPos,m_yPos),m_bombPower,mapGen);

                    }
                }
                m_bombUse++;
                m_cTimeIA.restart();
            }
        }


        if((abs(m_playerSprite.getPosition().x-mapGen.getPointPosition(m_xPos+movement.x,m_yPos+movement.y).x)
                +abs(m_playerSprite.getPosition().y-mapGen.getPointPosition(m_xPos+movement.x,m_yPos+movement.y).y)) <= TILE_SIZE+5)
        {
            m_xPos+=movement.x;
            m_yPos+=movement.y;
        }
    }

    if(mapGen.getTileNumber(m_yPos,m_xPos)==BONUS_ADD_BOMB)
    {
        mapGen.change(m_yPos,m_xPos,TYPE_GROUND,false);
        m_playerBomb.push_back(bomb());
    }
    else if(mapGen.getTileNumber(m_yPos,m_xPos)==BONUS_BOOST_EXPLOSION)
    {
        mapGen.change(m_yPos,m_xPos,TYPE_GROUND,false);
        m_bombPower++;
    }
    else if(mapGen.getTileNumber(m_yPos,m_xPos)==BONUS_BOOST_SPEED)
    {
        mapGen.change(m_yPos,m_xPos,TYPE_GROUND,false);
        m_playerSpeed+=ADD_SPEED;
    }
    m_focusPos=mapGen.getPointPosition(m_xPos,m_yPos);


}

std::string player::getName()
{
    return m_playerName;
}


void player::chooseFocus()
{
    if(m_id!=0 && m_id!=1 && m_start==true)
    {
        if(m_ennemi[m_id-1]->getLife()>0)
            m_ennemiFocus=m_ennemi[m_id-1];
    }
    else if(m_id==1 && m_start==true)
    {

        if(m_ennemi[m_id-1]->getLife()>0)
        {
            m_ennemiFocus=m_ennemi[m_id-1];
        }
    }
    else if(m_id==0 && m_start==true)
    {
        if(m_ennemi[m_ennemi.size()-1]->getLife()>0)
            m_ennemiFocus=m_ennemi[m_ennemi.size()-1];
    }
    if(m_ennemiFocus->getLife()<=0)
    {
        for(int i=0; i<m_ennemi.size(); i++)
        {
            if(m_ennemi[i]->getLife()>0)
                m_ennemiFocus=m_ennemi[i];
        }
    }

}

void player::movePlayer(sf::Time deltatime)
{
    sf::Vector2f movement(0.f,0.f);
    if(abs(m_focusPos.x-m_playerSprite.getPosition().x)<2)
    {
        m_playerSprite.setPosition(m_focusPos.x,m_playerSprite.getPosition().y);
        m_updateAnim=false;
    }
    if(abs(m_focusPos.y-m_playerSprite.getPosition().y)<2)
    {
        m_playerSprite.setPosition(m_playerSprite.getPosition().x,m_focusPos.y);
        m_updateAnim=false;
    }
    if(m_focusPos.x>m_playerSprite.getPosition().x)
    {
        movement.x=m_playerSpeed;
        m_updateAnim=true;
        m_anim.y=Right;
    }
    if(m_focusPos.x<m_playerSprite.getPosition().x)
    {
        movement.x=-m_playerSpeed;
        m_updateAnim=true;
        m_anim.y=Left;
    }

    if(m_focusPos.y>m_playerSprite.getPosition().y)
    {
        movement.y=m_playerSpeed;
        m_updateAnim=true;
        m_anim.y=Down;
    }

    else if(m_focusPos.y<m_playerSprite.getPosition().y)
    {
        movement.y=-m_playerSpeed;
        m_updateAnim=true;
        m_anim.y=Up;
    }
    m_animFrame++;
    if(m_updateAnim&&m_animFrame>m_animSpeed)
    {
        m_anim.x++;
        m_animFrame=0;
    }

    if(m_anim.x*SPRITE_PLAYER_SIZE>=m_playerTexture.getSize().x)
    {
        m_anim.x=0;
    }

    m_playerSprite.setTextureRect(sf::IntRect
                                  (m_anim.x*SPRITE_PLAYER_SIZE
                                   ,m_anim.y*SPRITE_PLAYER_SIZE
                                   ,SPRITE_PLAYER_SIZE,SPRITE_PLAYER_SIZE));

    m_playerSprite.move(movement.x*deltatime.asSeconds()
                        ,movement.y*deltatime.asSeconds());
}

bomb player::getbomb(int nb)
{
    return m_playerBomb[nb];
}

bomb* player::getbombAdress(int nb)
{
    return &m_playerBomb[nb];
}

void player::killPlayer()
{
    m_life=0;
}

int player::getnbBomb()
{
    return m_playerBomb.size();
}

//return true if player is alive else return fals if player is dead
bool player::updatePlayer(sf::Time deltatime,TileMap &mapGen,player &otherPlayer1,int tour)
{

    if((m_id==0 && tour == 1)||(m_id!=0 && tour == 0))
        player::movePlayer(deltatime);

    if(m_isIA==true)
    {
        bool exist=false;
        if(m_ennemi.size()!=0)
            chooseFocus();
        for(int i=0; i<m_visitedList.size(); i++)
        {
            if(*m_visitedList[i]==sf::Vector2f(m_xPos,m_yPos))
                exist=true;

        }

        if(exist==false)
        {
            m_visitedList.push_back(new sf::Vector2f(m_xPos,m_yPos));
        }

    }



    for(int i=0; i<m_playerBomb.size(); i++)
    {

        for(int j=0; j<m_playerBomb.size(); j++)
        {
            if(j!=i)
            {
                m_playerBomb[i].damageBomb(&m_playerBomb[j]);
            }
        }
        for(int k=0; k<otherPlayer1.getnbBomb(); k++)
        {
            m_playerBomb[i].damageBomb(otherPlayer1.getbombAdress(k));
        }

        if(m_life>=0)
        {
            m_playerBomb[i].update(mapGen);
            if(m_playerBomb[i].damagePlayer(sf::Vector2f(round(m_playerSprite.getPosition().x/TILE_SIZE),round(m_playerSprite.getPosition().y/TILE_SIZE)))==true)
            {
                m_life=0;
                return false;
            }
            if(otherPlayer1.getnbBomb()>i)
            {
                if(otherPlayer1.getPlayerBomb(i).damagePlayer(sf::Vector2f(round(m_playerSprite.getPosition().x/TILE_SIZE),round(m_playerSprite.getPosition().y/TILE_SIZE)))==true)
                {
                    m_life=0;
                    return false;
                }
            }
        }
    }

    return true;
}

int player::getLife()
{
    return m_life;
}

bomb player::getPlayerBomb(int i)
{
    return m_playerBomb[i];
}



player::~player()
{

}
