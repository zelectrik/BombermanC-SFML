#include <SFML/Graphics.hpp>
#include <stdlib.h>
#include <stdio.h>
#include "Menu/MenuType.hpp"
#include "Engine/Game.hpp"



using namespace sf;
void displayHomeScreen(RenderWindow &fenetre, bool colorGame, bool colorSettings);
void displayOpponentType(RenderWindow &fenetre, bool a, bool b, bool c);
void displayPlayerScreen(RenderWindow &fenetre);
void setMode(int i, int i2);

MenuType menu;
Font menufont;
int playermode [4] = {0,1,2,2};

int main()
{
    menufont.loadFromFile("Media/Font/font.ttf");
    sf::Music m_theme;
    if(!m_theme.openFromFile("Media/Sound/Theme.wav"))
        std::cout<<"Error"<<std::endl;

    RenderWindow fenetre(VideoMode(UI_WIDTH, UI_HEIGHT), "Bomberman",Style::Close);
    Game game;

    displayHomeScreen(fenetre, false, false);
    m_theme.play();
    m_theme.setLoop(true);
    while (fenetre.isOpen())
    {
        Event evenement;
        while (fenetre.pollEvent(evenement))
        {

            switch (evenement.type)
            {
            case Event::Closed:
                fenetre.close();
                break;
            case Event::MouseMoved:
                if(menu == HOME) {
                    if(evenement.mouseMove.x >= 50 && evenement.mouseMove.x <= 300 && evenement.mouseMove.y >= 350 && evenement.mouseMove.y < 430)
                        displayHomeScreen(fenetre, true, false);
                    else if(evenement.mouseMove.x >= (UI_WIDTH - 300) && evenement.mouseMove.x <= (UI_WIDTH - 50) && evenement.mouseMove.y >= 350 && evenement.mouseMove.y < 430)
                        displayHomeScreen(fenetre, false, true);
                    else
                        displayHomeScreen(fenetre, false, false);
                }
                break;
            case Event::MouseButtonPressed:
                if(menu == HOME) {
                    if(evenement.mouseButton.x >= (UI_WIDTH - 300) && evenement.mouseButton.x <= (UI_WIDTH - 50) && evenement.mouseButton.y >= 350 && evenement.mouseButton.y < 430)
                        fenetre.close();
                    else if(evenement.mouseButton.x >= 50 && evenement.mouseButton.x <= 300 && evenement.mouseButton.y >= 350 && evenement.mouseButton.y < 430)
                        displayPlayerScreen(fenetre);

                }
                else if(menu == PLAYER_SELECTION) {
                    if(evenement.mouseButton.x >= 34 && evenement.mouseButton.x <= 180 && evenement.mouseButton.y >= 56 && evenement.mouseButton.y < 360) {
                        if(playermode[0] == 1)
                            setMode(0, 0);
                        else
                            setMode(0, playermode[0] + 1);
                        displayPlayerScreen(fenetre);
                    }
                    else if(evenement.mouseButton.x >= 204 && evenement.mouseButton.x <= 350 && evenement.mouseButton.y >= 56 && evenement.mouseButton.y < 360) {
                        if(playermode[1] == 1)
                            setMode(1, 0);
                        else
                            setMode(1, playermode[1] + 1);
                        displayPlayerScreen(fenetre);
                    }
                    else if(evenement.mouseButton.x >= 374 && evenement.mouseButton.x <= 520 && evenement.mouseButton.y >= 56 && evenement.mouseButton.y < 360) {
                        if(playermode[2] == 2)
                            setMode(2, 0);
                        else
                            setMode(2, playermode[2] + 1);
                        displayPlayerScreen(fenetre);
                    }
                    else if(evenement.mouseButton.x >= 544 && evenement.mouseButton.x <= 690 && evenement.mouseButton.y >= 56 && evenement.mouseButton.y < 360) {
                        if(playermode[3] == 2)
                            setMode(3, 0);
                        else
                            setMode(3, playermode[3] + 1);
                        displayPlayerScreen(fenetre);
                    }
                    else if(evenement.mouseButton.x >= 300 && evenement.mouseButton.x <= 425 && evenement.mouseButton.y >= 400 && evenement.mouseButton.y < 460) {
                        int IA=0;
                        int player=0;
                        for(int i=0;i<4;i++)
                        {
                            if(playermode[i]==0)
                                player++;
                            else if(playermode[i]==1)
                                IA++;
                        }
                        game.reloadGame(fenetre,IA,player);
                        game.run(fenetre);
                        displayPlayerScreen(fenetre);
                    }
                    else if(evenement.mouseButton.x >= 20 && evenement.mouseButton.x <= 130 && evenement.mouseButton.y >= 20 && evenement.mouseButton.y < 45) {
                        displayHomeScreen(fenetre, false, false);
                    }
                }
                break;
            case Event::KeyPressed:
                break;
            }
        }
    }
    m_theme.stop();

}

int alea()
{
}

/*
Affiche l'écran de selection avec le nombre de joueur + IA
*/
void displayPlayerScreen(RenderWindow &fenetre) {
    menu = PLAYER_SELECTION;


    fenetre.setSize(Vector2u(UI_WIDTH, UI_HEIGHT));
    fenetre.clear(Color::Black);

    //Chargement du fond
    sf::Texture background;
    !background.loadFromFile("Media/Image/background_Menu.png");

    sf::Texture iaselector;
    !iaselector.loadFromFile("Media/Image/iaselector.png");
    sf::Texture playerselector;
    !playerselector.loadFromFile("Media/Image/playerselector.png");
    sf::Texture noneselector;
    !noneselector.loadFromFile("Media/Image/noneselector.png");

    Sprite re;
    re.setTexture(background);
    re.setPosition(0, 0);
    fenetre.draw(re);

    int posX = 37;

    int i = 0;
    for(i = 0; i < 4; i++) {
        RectangleShape configButton(Vector2f(140,300));
        configButton.setFillColor(sf::Color(0,0,0,90));
        configButton.setPosition(posX, 60);
        configButton.setOutlineThickness(3);


        Sprite selector;
        Text selectorModeText;
        selectorModeText.setFont(menufont);
        selectorModeText.setCharacterSize(16);
        selectorModeText.setColor(Color(255, 255, 255));

        if(playermode[i] == 0) {
            selector.setTexture(playerselector);
            selectorModeText.setString("Joueur");
            selectorModeText.setPosition(posX + 27, 250);
            configButton.setOutlineColor(Color(192, 57, 43));
        } else if(playermode[i] == 1){
            selector.setTexture(iaselector);
            selectorModeText.setString("IA");
            selectorModeText.setPosition(posX + 60, 250);
            configButton.setOutlineColor(Color(192, 57, 43));
        }else{
            selector.setTexture(noneselector);
            selectorModeText.setString("Aucun");
            selectorModeText.setPosition(posX + 33, 250);
            configButton.setOutlineColor(Color(255, 255, 255));
        }

        selector.scale(4, 4);
        selector.setPosition(posX + 5, 100);


        Text playText;
        playText.setString("Changer");
        playText.setFont(menufont);
        playText.setPosition(posX + 15, 330);
        playText.setCharacterSize(16);
        playText.setColor(Color(241, 196, 15));

        fenetre.draw(configButton);
        fenetre.draw(playText);
        fenetre.draw(selector);
        fenetre.draw(selectorModeText);

        posX += 170;
    }

    Text backText;
    backText.setString("RETOUR");
    backText.setFont(menufont);
    backText.setPosition(20, 20);
    backText.setCharacterSize(14);
    backText.setColor(Color(255, 255, 255));
    fenetre.draw(backText);

    Text playText;
    playText.setString("JOUER");
    playText.setFont(menufont);
    playText.setPosition(310, 430);
    playText.setCharacterSize(22);
    playText.setColor(Color(255, 255, 255));
    fenetre.draw(playText);


    fenetre.display();

}

/*
Change le mode du joueur entre IA <-> Joueur <-> Inactif
*/
void setMode(int player, int mode) {
    playermode[player] = mode;
}

/*
Affiche l'écran d'accueil
*/
void displayHomeScreen(RenderWindow &fenetre, bool colorGame, bool colorSettings)
{
    menu = HOME;

    sf::Texture background;
    !background.loadFromFile("Media/Image/background_Menu.png");
    sf::Texture logoTexture;
    !logoTexture.loadFromFile("Media/Image/logobomberman.png");

    Sprite re;
    re.setTexture(background);
    re.setPosition(0, 0);

    Sprite logo;
    logo.setTexture(logoTexture);
    logo.setPosition(70, 0);

    RectangleShape playButton(Vector2f(250,80));
    playButton.setFillColor(sf::Color(0,0,0,90));
    playButton.setPosition(50, 350);
    playButton.setOutlineThickness(3);
    if(colorGame)
        playButton.setOutlineColor(Color(192, 57, 43));
    else
        playButton.setOutlineColor(Color(46,125,50));

    RectangleShape configButton(Vector2f(250,80));
    configButton.setFillColor(sf::Color(0,0,0,90));
    configButton.setPosition((UI_WIDTH - 300), 350);
    configButton.setOutlineThickness(3);
    if(colorSettings)
        configButton.setOutlineColor(Color(192, 57, 43));
    else
        configButton.setOutlineColor(Color(46,125,50));

    Text playText;
    playText.setString("JOUER");
    playText.setFont(menufont);
    playText.setPosition(120, 380);
    playText.setCharacterSize(22);
    if(colorGame)
        playText.setColor(Color(241, 196, 15));

    Text configText;
    configText.setString("QUITTER");
    configText.setFont(menufont);
    configText.setPosition(475, 380);
    configText.setCharacterSize(22);
    if(colorSettings)
        configText.setColor(Color(241, 196, 15));


    Text creditText;
    creditText.setString("Thibault Dufour");
    creditText.setFont(menufont);
    creditText.setPosition(270, (UI_HEIGHT - 20));
    creditText.setCharacterSize(11);

    fenetre.setSize(Vector2u(UI_WIDTH, UI_HEIGHT));
    fenetre.clear(Color::Black);
    fenetre.draw(re);
    fenetre.draw(logo);
    fenetre.draw(playButton);
    fenetre.draw(configButton);
    fenetre.draw(playText);
    fenetre.draw(configText);
    fenetre.draw(creditText);
    fenetre.display();
}

void displayOpponentType(RenderWindow &fenetre, bool settings, bool ia, bool player) {
    menu = GAMEMODE;

    sf::Texture background;
    !background.loadFromFile("Media/Image/background_Menu.png");

    Sprite re;
    re.setTexture(background);
    re.setPosition(0, 0);

    RectangleShape playButton(Vector2f(120,80));
    playButton.setFillColor(sf::Color(0,0,0,90));
    playButton.setPosition(50, 350);
    playButton.setOutlineThickness(3);
    if(player)
        playButton.setOutlineColor(Color(192, 57, 43));
    else
        playButton.setOutlineColor(Color(46,125,50));

    RectangleShape iaButton(Vector2f(120,80));
    iaButton.setFillColor(sf::Color(0,0,0,90));
    iaButton.setPosition(180, 350);
    iaButton.setOutlineThickness(3);
    if(ia)
        iaButton.setOutlineColor(Color(192, 57, 43));
    else
        iaButton.setOutlineColor(Color(46,125,50));

    RectangleShape configButton(Vector2f(250,80));
    configButton.setFillColor(sf::Color(0,0,0,90));
    configButton.setPosition((UI_WIDTH - 300), 350);
    configButton.setOutlineThickness(3);
    if(settings)
        configButton.setOutlineColor(Color(192, 57, 43));
    else
        configButton.setOutlineColor(Color(46,125,50));

    Text playText;
    playText.setString("1 vs 1");
    playText.setFont(menufont);
    playText.setPosition(70, 380);
    playText.setCharacterSize(22);
    if(player)
        playText.setColor(Color(241, 196, 15));

    Text playIa;
    playIa.setString("1 vs IA");
    playIa.setFont(menufont);
    playIa.setPosition(190, 380);
    playIa.setCharacterSize(22);
    if(ia)
        playIa.setColor(Color(241, 196, 15));

    Text configText;
    configText.setString("REGLAGES");
    configText.setFont(menufont);
    configText.setPosition(465, 380);
    configText.setCharacterSize(22);
    if(settings)
        configText.setColor(Color(241, 196, 15));


    Text creditText;
    creditText.setString("Made with love by Loris Pinna and Thibault Dufour");
    creditText.setFont(menufont);
    creditText.setPosition(270, (UI_HEIGHT - 20));
    creditText.setCharacterSize(11);

    fenetre.setSize(Vector2u(UI_WIDTH, UI_HEIGHT));
    fenetre.clear(Color::Black);
    fenetre.draw(re);
    fenetre.draw(playButton);
    fenetre.draw(configButton);
    fenetre.draw(iaButton);
    fenetre.draw(playText);
    fenetre.draw(playIa);
    fenetre.draw(configText);
    fenetre.draw(creditText);
    fenetre.display();
}
