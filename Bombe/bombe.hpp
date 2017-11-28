#ifndef BOMBE_HPP_INCLUDED
#define BOMBE_HPP_INCLUDED

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <iostream>
#include "../TileMap/tileMap.hpp"
#include "../Menu/Texture.hpp"

#define SIZE_BOMB 32
#define PATH_TO_BOMB_TEXTURE "Media/Image/Bomb/classicBomb.png"
#define PATH_TO_EXPLOSION_TEXTURE "Media/Image/Bomb/classicExplosion.png"
#define PATH_TO_EXPLOSION_SOUND "Media/Sound/explosion.wav"
#define DELAY_EXPLOSION 3
#define DELAY_DISPLAY 1


class bomb : public sf::Drawable
{
public:
    bomb(); ///Constructeur de bomb
    void update(TileMap &mapGen);
    /*****Permet de mettre a jour la bomb toute les frames
          les bombes en verifiant si le temps écoulé de la
          bombe est supérieur au temps de l'explosion si oui
          on creer les cases ou les bombes exploses
          et si le temps est superieur au temps de destruction de
          la bombe on la detruit.
    ****/
    void createBomb(sf::Vector2f BombPosition,sf::Vector2f casePosition,int bombPower,TileMap &map);
    /*****Rend la bomb active avec une certaine position
          et une certaine puissance.
    ****/
    bool getBombIsUse();
    /*****Return si la bomb est active
    ****/
    int getNumberOfCaseExplode();
    /*****Return le nombre de case ou il y a eu une explosion
    ****/
    bool damagePlayer(sf::Vector2f playerPosition);
    /*****Return si le joueur est en vie apres avoir été ou touché
          dans une case ou il y a eu une explosion
    ****/
    bool damageBomb(bomb *bombs);
    /*****Return si la bomb passer en parametre a été touché par une explosion
          Si Oui celle ci explosera en meme temps
    ****/
    sf::Vector2f positionBombTouch(sf::Vector2f position);
    /*****Return position passer en parametre ???(je sais pas pourquoi)
    ****/
    void damageTile(TileMap &mapGen);
    /***** Si Une brique ou du bois est toucher le transforme en terre ou en bonus
           Si un bonnus est toucher le tranforme en terre
    ****/
    sf::Vector2f getCaseExplose(int number);
    /***** Si Une brique ou du bois est toucher le transforme en terre ou en bonus
           Si un bonnus est toucher le tranforme en terre
    ****/
    void launchBomb();
    /***** met la valeur de m_launch a true
    ****/
    bool getLaunch();
    /***** return la valeur m_launch
    ****/
    sf::Vector2f getBombPosition();
    /***** return la position de la bomb
    ****/



    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
    {

        if(m_isUse==true)
        {
            target.draw(m_bombSprite,states);
            if(m_isExplode==true)
            {
                for(int i=0; i<m_explosionSprite.size(); i++)
                {
                    target.draw(m_explosionSprite[i],states);
                }
            }
        }
    }
    /***** Permet de dessiner la bomb est de dessiner les explosion lorsque elle existe.
    ****/

private:
    Texture m_bombTexture;
    sf::Sprite m_bombSprite;

    Texture m_explosionTexture;
    std::vector<sf::Sprite> m_explosionSprite;

    sf::Time m_delayToExplosion;
    sf::Clock m_timer;
    sf::Time m_displayExplosion;

    sf::Vector2f m_positionBomb;
    sf::Vector2f m_caseBomb;

    sf::SoundBuffer m_sbExplosion;
    sf::Sound m_sExplosion;

    std::vector<sf::Vector2f> m_caseExplosion;

    int m_bombPower;

    bool m_isExplode;
    bool m_makeDamage;
    bool m_Destruct;
    bool m_isUse;
    bool m_isSolid;
    bool m_launch;

};


#endif // BOMBE_HPP_INCLUDED
