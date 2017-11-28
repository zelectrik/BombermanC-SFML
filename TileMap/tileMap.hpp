#ifndef TILEMAP_HPP_INCLUDED
#define TILEMAP_HPP_INCLUDED

#include "tile.hpp"
#include <vector>
#include <time.h>
#include <iostream>


#define HEIGHT_MAP 15
#define WIDTH_MAP 19



class TileMap : public sf::Drawable, public sf::Transformable
{
public:

    bool load(sf::Vector2f position,const std::string& tileset, sf::Vector2u tileSize, unsigned int width, unsigned int height);
    /**** Creer une map avec une position, un nom de tileSet et une taille de
    map et une taille de tile
    ****/
    void Mapgenerator(unsigned int width,unsigned int height);
    /*** Genère une map avec une longueur et une hauteur defini.
    ***/
    sf::Vector2f getPointPosition(int line,int column);
    /*** return la position en pixel d'un tile
    ***/
    int getTileNumber(int line,int column);
    /*** return l'identifiant d''un tile
    ***/
    void setTileNumber(int line,int column,int type);
    /*** configure le type d'un tile
    ***/
    tile* getTile(int line,int column);
    /*** return le pointeur d'un tile
    ***/
    void setIsFree(int line,int column,bool setIs);
    /*** set un tile libre
    ***/
    bool getIsFree(int line,int column);
    /*** return si un tile est libre
    ***/
    void updateMap(int line,int column,int tileNumber);
    /*** gere la boucle principale de la tilemap
    ***/
    sf::Vector2f getLineColumn();
    /*** return la largeur et la hauteur de la map
    ***/
    void change(int line,int column,int type,bool randomize);
    /*** modifie la tilemap si le tile est detruit en terre et a une certaine chance de lacher un bonus
    ***/
private:

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    sf::VertexArray m_vertices;
    sf::Texture m_tileset;
    sf::Vector2u m_tileSize;
    std::vector<tile*> m_tile; // to stock all tile;
    std::vector<int> m_generateMap;
    std::vector<sf::Vector2f> m_mapPosition;
    sf::Vector2f m_position;
    bool m_reload=(false);
    int m_widht;
    int m_height;
};


#endif // TILEMAP_HPP_INCLUDED
