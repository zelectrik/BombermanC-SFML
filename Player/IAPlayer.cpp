#include "IAPlayer.hpp"
#include "player.hpp"
#include <cmath>

IAPlayer::IAPlayer(int id,std::string name,std::string pathToFile,int FrameLimit,sf::Vector2f positionCase)
    : m_id(0)
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
    if(!m_playerTexture.loadFromFile(pathToFile))
        std::cout << "error" << std::endl;
    m_playerSprite.setTexture(m_playerTexture);
    m_animSpeed=FrameLimit/4;
    m_playerBomb.push_back(bomb());
    m_xPos=positionCase.x;
    m_yPos=positionCase.y;
    m_playerSprite.setPosition(sf::Vector2f(m_xPos*TILE_SIZE,m_yPos*TILE_SIZE));
}

void IAPlayer::resetPlayer()
{
    m_playerSprite.setPosition(sf::Vector2f(TILE_SIZE,TILE_SIZE));
    m_life=INITIAL_LIFE;
    m_bombAmmo=INITIAL_AMMO;
    m_playerSpeed=INITIAL_SPEED;
    m_bombPower=1;
    if(m_id==0)
    {
        m_xPos=1;
        m_yPos=1;
    }
    else if(m_id==1)
    {
        m_xPos=WIDTH_MAP;
        m_yPos=HEIGHT_MAP;
    }
    else if(m_id==2)
    {
        m_xPos=1;
        m_yPos=HEIGHT_MAP;
    }
    else if(m_id==3)
    {
        m_xPos=WIDTH_MAP;
        m_yPos=1;
    }

    m_playerBomb.clear();
    m_playerBomb.push_back(bomb());
    m_playerSprite.setPosition(sf::Vector2f(m_xPos*TILE_SIZE,m_yPos*TILE_SIZE));
}

void IAPlayer::setPosition(sf::Vector2f positionCase)
{
    m_playerSprite.setPosition(sf::Vector2f(positionCase.x*TILE_SIZE,positionCase.y*TILE_SIZE));
}

void IAPlayer::drawPlayer(sf::RenderWindow &fenetre)
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

void IAPlayer::eventPlayerInput(sf::Keyboard::Key key,TileMap &mapGen)
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
                std::cout<<"x : "<<m_xPos<<" y : "<<m_yPos<<std::endl;
                m_playerBomb[i].createBomb(mapGen.getPointPosition(m_xPos,m_yPos),sf::Vector2f(m_xPos,m_yPos),m_bombPower,mapGen);

            }
        }
        m_bombUse++;
    }
    if(key == sf::Keyboard::E)
        m_playerBomb.push_back(bomb());
    if(key == sf::Keyboard::R)
    {
        m_bombPower++;
        std::cout<<m_bombPower<<std::endl;
    }

}


void IAPlayer::handlePlayer(TileMap mapGen)
{
    sf::Vector2f movement(0.f,0.f);
    if(m_yPos>ennemiFocus->getPosition().y)
        movement.y=-1;
    else if(m_yPos<ennemiFocus->getPosition().y)
        movement.y=+1;
    else if(m_xPos>ennemiFocus->getPosition().x)
        movement.x=-1;
    else if(m_yPos<ennemiFocus->getPosition().y)
        movement.x=+1;

    if(mapGen.getTileNumber(m_yPos+movement.y,m_xPos+movement.x) == TYPE_GROUND
            && (abs(m_playerSprite.getPosition().x-mapGen.getPointPosition(m_xPos+movement.x,m_yPos+movement.y).x)
                +abs(m_playerSprite.getPosition().y-mapGen.getPointPosition(m_xPos+movement.x,m_yPos+movement.y).y) <= TILE_SIZE+5))
    {
        m_xPos+=movement.x;
        m_yPos+=movement.y;
    }

    m_focusPos=mapGen.getPointPosition(m_xPos,m_yPos);

}

void IAPlayer::movePlayer(sf::Time deltatime)
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

bomb IAPlayer::getbomb(int nb)
{
    return m_playerBomb[nb];
}

bomb* IAPlayer::getbombAdress(int nb)
{
    return &m_playerBomb[nb];
}

void IAPlayer::killPlayer()
{
    m_life=0;
}

int IAPlayer::getnbBomb()
{
    return m_playerBomb.size();
}

void IAPlayer::chooseFocus(player *ennemi)
{/*
    float bestDistance=1000;
    int focus;
    float distance;
    for(int n=0;n<ennemi.size();n++)
    {
        distance=sqrt(pow((m_xPos-ennemi->getPosition().x),2)+pow((m_yPos-ennemi->getPosition().y),2));
        if(bestDistance>distance)
        {
            bestDistance=distance;
            focus=n;
        }
    }*/
    m_ennemiFocus=ennemi;
}

void IAPlayer::chooseFocus(IAPlayer *ennemi)
{/*
    float bestDistance=1000;
    int focus;
    float distance;
    for(int n=0;n<ennemi.size();n++)
    {
        distance=sqrt(pow((m_xPos-ennemi->getPosition().x),2)+pow((m_yPos-ennemi->getPosition().y),2));
        if(bestDistance>distance)
        {
            bestDistance=distance;
            focus=n;
        }
    }*/
    oEnnemiFocus=ennemi;
}



//return true if player is alive else return fals if player is dead
bool IAPlayer::updatePlayer(sf::Time deltatime,TileMap &mapGen,IAPlayer &otherPlayer1,int tour)
{
    IAPlayer::handlePlayer(mapGen);
    if((m_id==0 && tour == 1)||(m_id!=0 && tour == 0))
        IAPlayer::movePlayer(deltatime);



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
            if(m_playerBomb[i].damagePlayer(sf::Vector2f(round(m_playerSprite.getPosition().x/TILE_SIZE),round(m_playerSprite.getPosition().y/TILE_SIZE)))==true
                    || otherPlayer1.getPlayerBomb(i).damagePlayer(sf::Vector2f(round(m_playerSprite.getPosition().x/TILE_SIZE),round(m_playerSprite.getPosition().y/TILE_SIZE)))==true)
            {
                std::cout<<"error"<<std::endl;
                return false;
            }
        }
        /*if(bombExplose==sf::Vector2f(0,0))
        {

        }
        else
        {

        }*/
    }
    return true;
}

bomb IAPlayer::getPlayerBomb(int i)
{
    return m_playerBomb[i];
}



IAPlayer::~IAPlayer()
{

}
