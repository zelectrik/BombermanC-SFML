#ifndef PLAYER_HPP_INCLUDED
#define PLAYER_HPP_INCLUDED

#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include <memory>
#include <cmath>
#include "../TileMap/tileMap.hpp"
#include "../Bombe/bombe.hpp"
#include "../Engine/SearchCell.hpp"
#include "../Engine/fonction.hpp"





#define INITIAL_LIFE 2
#define INITIAL_AMMO 1
#define INITIAL_SPEED 140
#define ADD_SPEED 10
#define SPRITE_PLAYER_SIZE 32

#define IA_TRUE true
#define IA_FALSE false


enum Direction{Down,Right,Up,Left};


class player
{
public:
    player(bool isIA,int id,std::string name,std::string pathToFile,int FrameLimit,sf::Vector2f positionCase,TileMap *mapGen);
    ///constructeur
    void setPosition(sf::Vector2f positionCase);
    sf::Vector2f getPosition();
    void resetPlayer();
    /*** Remet tous les paramètres d'origine(vie,degats...)
    ***/
    void drawPlayer(sf::RenderWindow &fentre);
    /*** Permet de dessiner le personnage et ces bombes
    ***/
    void handlePlayerInput(TileMap &mapGen);
    /*** Gere les input lié au mouvement et gere les mouvement des ia
    ***/
    void eventPlayerInput(sf::Keyboard::Key,TileMap &mapGen);
    /*** Gere les input lié au action (poser une bombe)
    ***/
    void movePlayer(sf::Time deltatime);
    /*** update les movement du joueur en fonction de ces input
    ***/
    bomb getPlayerBomb(int i);
    /*** return la bomb avec l'identifiant i
    ***/
    bomb getbomb(int nb);
    /*** return la bomb avec l'identifiant nb
    ***/
    bomb* getbombAdress(int nb);
    /*** return l'adresse de la bomb avec l'identifiant nb
    ***/
    void chooseFocus();
    /*** Permet de choisir un focus au départ par défault ensuite si le focus est mort alors en choisit un autre
    ***/
    bool updatePlayer(sf::Time deltatime,TileMap &mapGen,player &otherPlayer1,int tour);
    /*** gere la boucle principale du joueur et vefifie si celui-ci
    est encore en vie
    ***/
    int getnbBomb();
    /*** retourne le nombre de bombe a son actif
    ***/
    int getLife();
    /*** return la vie du joueur
    ***/
    std::string getName();
    /*** return le nom du jeu
    ***/
    void addEnnemi(player* ennemies);
    /*** ajoute un pointeur sur un player dans le vector m_ennemi
    ***/
    void killPlayer();
    /*** met la vie d'un joueur a 0
    ***/
    ~player();

private:
    sf::Texture m_playerTexture;
    sf::Sprite m_playerSprite;


    bool m_isIA;
    player* m_ennemiFocus;

    std::vector<player*> m_ennemi;

    //PathFinding m_path;


    int m_xPos,m_yPos;
    int m_id;
    int m_life;
    int m_bombAmmo;
    int m_bombUse;
    int m_bombPower;
    float m_playerSpeed;
    bool m_updateAnim=false;
    bool m_start=true;
    sf::Vector2f m_focusPos;
    std::string m_playerName;
    std::string m_pathFile;
    sf::Vector2i m_anim;
    int m_animSpeed;
    int m_animFrame;
    sf::Vector2f m_choosePos;
    std::vector<bomb> m_playerBomb;
    std::vector<bool> m_bombDestroy;

    sf::Vector2f m_BefMovement;

    std::vector<sf::Vector2f*> m_visitedList;

    sf::Clock m_cTimeIA;
    sf::Time m_tTimeIA;
    bool canMove;
    bool m_getFocusPos;



};

#endif // PLAYER_HPP_INCLUDED
