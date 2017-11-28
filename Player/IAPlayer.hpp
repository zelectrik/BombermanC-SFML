#ifndef IAPLAYER_HPP_INCLUDED
#define IAPLAYER_HPP_INCLUDED


#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include <memory>
#include <cmath>
#include "../TileMap/tileMap.hpp"
#include "../Bombe/bombe.hpp"
#include "player.hpp"


#define INITIAL_LIFE 2
#define INITIAL_AMMO 1
#define INITIAL_SPEED 85
#define SPRITE_PLAYER_SIZE 32
#define HEIGHT_MAP 15
#define WIDTH_MAP 19



class IAPlayer
{
public:
    IAPlayer(int id,std::string name,std::string pathToFile,int FrameLimit,sf::Vector2f positionCase);
    void setPosition(sf::Vector2f positionCase);
    void resetPlayer();
    void drawPlayer(sf::RenderWindow &fentre);
    void handlePlayer(TileMap mapGen);
    void eventPlayerInput(sf::Keyboard::Key,TileMap &mapGen);
    void chooseFocus(player *ennemi);
    void chooseFocus(IAPlayer *ennemi);
    void movePlayer(sf::Time deltatime);
    bomb getPlayerBomb(int i);
    bomb getbomb(int nb);
    bomb* getbombAdress(int nb);
    bool updatePlayer(sf::Time deltatime,TileMap &mapGen,IAPlayer &otherPlayer1,int tour);
    int getnbBomb();
    void killPlayer();
    ~IAPlayer();

private:
    sf::Texture m_playerTexture;
    sf::Sprite m_playerSprite;


    int m_xPos,m_yPos;
    int m_id;
    int m_life;
    int m_bombAmmo;
    int m_bombUse;
    int m_bombPower;
    float m_playerSpeed;
    bool m_updateAnim=false;
    sf::Vector2f m_focusPos;
    std::string m_playerName;
    std::string m_pathFile;
    sf::Vector2i m_anim;
    int m_animSpeed;
    int m_animFrame;
    std::vector<bomb> m_playerBomb;
    std::vector<bool> m_bombDestroy;

    player* ennemiFocus;
    IAPlayer* oEnnemiFocus;



};


#endif // IAPLAYER_HPP_INCLUDED
