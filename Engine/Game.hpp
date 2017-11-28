#ifndef GAME_HPP_INCLUDED
#define GAME_HPP_INCLUDED

#include <SFML/Graphics.hpp>
#include "../Player/player.hpp"
#include "../Player/IAPlayer.hpp"7
#include <iostream>
#include "../TileMap/tileMap.hpp"
#define TEXTURE_TILE_PATH "Media/Image/tile.png"
#include "../Menu/text.hpp"
#include "fonction.hpp"
#include <memory>
#include <string>

#define UI_HEIGHT 496
#define UI_WIDTH 724




class Game
{
public:
    Game(); ///Constructeur
    void run(sf::RenderWindow &m_window);
    /**** run est la boucle principale du jeu, elle permet d'update
    tout les joueurs les bombes la map. Elle permet de reguler les fps.
    ***/
    void reloadGame(sf::RenderWindow &m_window,int nbIa, int nbPlayer);
    /***  Rétabli tout les paramètres à l'origin et ajoute les joueurs
    necessaire.
    ***/

private:
    void processEvents(sf::RenderWindow &m_window);
    /*** Gere les input des joueurs
    ***/
    void update(sf::Time deltaTime);
    /*** update tout les joueurs les bombes la map
    ***/

    void render(sf::RenderWindow& m_window);
    /*** Gere tout ce qui est affichage
    ***/

    bool m_isPause=false;

private:
    //sf::RenderWindow m_window;
    sf::View m_gameView;

    sf::Time TimePerFrame;
    sf::Clock timer;
    sf::Clock c_ShowFPS;
    sf::Time t_ShowFPS;

    int m_FramePerSecond;
    sf::Texture m_BackgroundTexture;
    sf::Sprite m_BackgroundSprite;
    int m_FrameLimitSelect;
    bool m_gameFinish;
    bool m_stopGame=false;
    bool m_returnMenu;

    bool m_goMenu=false;


    text m_FramePerSecondText;

    std::vector<bool> m_playerIsAlive;
    std::vector<player*> m_player;


    int m_nbPlayer;
    int m_nbPlayerDead;

    /*player m_playerListe;
    player m_playerListe2;
    player m_playerListe3;
    player m_playerListe4;*/

    TileMap map;

    /******Temp*****/
};

#endif // GAME_HPP_INCLUDED
