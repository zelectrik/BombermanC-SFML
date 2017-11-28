#include "tileMap.hpp"

bool TileMap::load(sf::Vector2f position,const std::string& tileset, sf::Vector2u tileSize, unsigned int width, unsigned int height)
{

    if(m_reload==true)
    {
        m_tile.clear();
        m_generateMap.clear();
        m_mapPosition.clear();
    }
    m_widht=width+2;
    m_height=height+2;
    TileMap::Mapgenerator(m_widht,m_height);
    int n=0;
    // on charge la texture du tileset
    if (!m_tileset.loadFromFile(tileset))
        return false;

    // on redimensionne le tableau de vertex pour qu'il puisse contenir tout le niveau
    m_vertices.setPrimitiveType(sf::Quads);
    m_vertices.resize((m_widht) * (m_height) * 4);
    m_position=position;
    m_tileSize=tileSize;

    // on remplit le tableau de vertex, avec un quad par tuile
    for (unsigned int i = 0; i < m_widht; ++i)
        for (unsigned int j = 0; j < m_height; ++j)
        {
            // on récupère le numéro de tuile courant
            int tileNumber = m_generateMap[i + (j * m_widht)];
            //int tileNumber=rand()%4;
            m_tile.push_back(new tile(tileNumber,sf::Vector2f(i * tileSize.x+position.x,
                                  + j * tileSize.y+position.y),n));
            m_mapPosition.push_back(sf::Vector2f(i * tileSize.x + position.x
                                                 , j * tileSize.y + position.y ));
            // on en déduit sa position dans la texture du tileset
            int tu = tileNumber % (m_tileset.getSize().x / tileSize.x);
            int tv = tileNumber / (m_tileset.getSize().x / tileSize.x);

            // on récupère un pointeur vers le quad à définir dans le tableau de vertex
            sf::Vertex* quad = &m_vertices[(i + j * m_widht) * 4];

            // on définit ses quatre coins
            quad[0].position = sf::Vector2f(i * tileSize.x + position.x, j * tileSize.y + position.y);
            quad[1].position = sf::Vector2f((i + 1) * tileSize.x + position.x, j * tileSize.y + position.y);
            quad[2].position = sf::Vector2f((i + 1) * tileSize.x + position.x, (j + 1) * tileSize.y + position.y);
            quad[3].position = sf::Vector2f(i * tileSize.x + position.x, (j + 1) * tileSize.y + position.y);

            // on définit ses quatre coordonnées de texture
            quad[0].texCoords = sf::Vector2f(tu * tileSize.x, tv * tileSize.y);
            quad[1].texCoords = sf::Vector2f((tu + 1) * tileSize.x, tv * tileSize.y);
            quad[2].texCoords = sf::Vector2f((tu + 1) * tileSize.x, (tv + 1) * tileSize.y);
            quad[3].texCoords = sf::Vector2f(tu * tileSize.x, (tv + 1) * tileSize.y);

            n++;
        }
    m_reload=true;
    return true;
}



void TileMap::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    // on applique la transformation
    states.transform *= getTransform();

    // on applique la texture du tileset
    states.texture = &m_tileset;

    // et on dessine enfin le tableau de vertex
    target.draw(m_vertices, states);
}


void TileMap::Mapgenerator(unsigned int width,unsigned int height)
{
    srand(time(NULL));
    /**************Procedural map**************/
    for(int i=0; i<height; i++)
    {
        for(int j=0; j<width; j++)
        {
            if((i==1 && j==1 )||(i==2 && j==1 )||(i==1 && j==2)||(i==3 && j==1 )||(i==1 && j==3)
                    ||(i==height-2 && j==1 )||(i==height-2 && j==2 )||(i==height-3 && j==1)||(i==height-2 && j==3 )||(i==height-4 && j==1)
                    ||(i==1 && j==width-2 )||(i==2 && j==width-2 )||(i==1 && j==width-3)||(i==3 && j==width-2 )||(i==1 && j==width-4)
                    ||(i==height-2 && j==width-2 )||(i==height-3 && j==width-2 )||(i==height-2 && j==width-3)||(i==height-4 && j==width-2 )||(i==height-2 && j==width-4))
            {
                m_generateMap.push_back(TYPE_GROUND);
            }
            else
            {
                /**************Realy Procedural map**************/
                if(j==0 || j==width-1 || i==0 || i==height-1)//to make no wall nearly border
                    m_generateMap.push_back(TYPE_WALL);
                else if(j>0)
                {
                    if(m_generateMap[i*width+j-1]==TYPE_WALL || m_generateMap[(i-1)*width+j]==TYPE_WALL || m_generateMap[(i-1)*width+j-1]==TYPE_WALL  && i>0)
                        m_generateMap.push_back(1+rand()%3);

                    else
                        m_generateMap.push_back(TYPE_WALL);
                }
                else
                    m_generateMap.push_back(rand()%4);

            }
        }
    }
}

sf::Vector2f TileMap::getPointPosition(int line,int column)
{
    return m_mapPosition[line*m_height+column];
}

int TileMap::getTileNumber(int line,int column)
{
    return m_generateMap[line*m_widht+column];
}

sf::Vector2f TileMap::getLineColumn()
{
    return sf::Vector2f(m_widht,m_height);
}

tile* TileMap::getTile(int line,int column)
{
    return m_tile[line*m_widht+column];
}

void TileMap::setTileNumber(int line,int column,int type)
{
    m_generateMap[line*m_widht+column]=type;
    m_tile[line*m_widht+column]->setType(type);
}

void TileMap::updateMap(int line,int column,int tileNumber)
{


    TileMap::setTileNumber(line,column,tileNumber);
    int tu = tileNumber % (m_tileset.getSize().x / m_tileSize.x);
    int tv = tileNumber / (m_tileset.getSize().x / m_tileSize.x);

    sf::Vertex* quad = &m_vertices[(column + line * m_widht) * 4];
    // on définit ses quatre coins
    quad[0].position = sf::Vector2f(column * m_tileSize.x + m_position.x, line * m_tileSize.y + m_position.y);
    quad[1].position = sf::Vector2f((column + 1) * m_tileSize.x + m_position.x, line * m_tileSize.y + m_position.y);
    quad[2].position = sf::Vector2f((column + 1) * m_tileSize.x + m_position.x, (line + 1) * m_tileSize.y + m_position.y);
    quad[3].position = sf::Vector2f(column * m_tileSize.x + m_position.x, (line + 1) * m_tileSize.y + m_position.y);

    // on définit ses quatre coordonnées de texture
    // on définit ses quatre coordonnées de texture
    quad[0].texCoords = sf::Vector2f(tu * m_tileSize.x, tv * m_tileSize.y);
    quad[1].texCoords = sf::Vector2f((tu + 1) * m_tileSize.x, tv * m_tileSize.y);
    quad[2].texCoords = sf::Vector2f((tu + 1) * m_tileSize.x, (tv + 1) * m_tileSize.y);
    quad[3].texCoords = sf::Vector2f(tu * m_tileSize.x, (tv + 1) * m_tileSize.y);
}

void TileMap::setIsFree(int line,int column,bool setIs)
{
    getTile(line,column)->setIsFree(setIs);
}


bool TileMap::getIsFree(int line,int column)
{
    return getTile(line,column)->getIsFree();
}

void TileMap::change(int line,int column,int type,bool randomize)
{
    m_tile[column*m_height+line]->damageTile();
    if(m_generateMap[line*m_widht+column]!=TYPE_WALL
       &&m_generateMap[line*m_widht+column]!=TYPE_GROUND
       && m_tile[column*m_height+line]->getIsDestruct())
    {

        //if(m_tile[line*m_widht+column].DestructTile()==true)
        //{
        if(randomize)
        {
            int random = rand()%10;
        if(random<4||random>6)
            random = TYPE_GROUND;
        type=random;//random;
        }
        m_generateMap[line*m_widht+column]=type;
        int tu = type % (m_tileset.getSize().x / TILE_SIZE);
        int tv = type / (m_tileset.getSize().x / TILE_SIZE);
        sf::Vertex* quad = &m_vertices[(line*m_widht+column) * 4];
        quad[0].position = sf::Vector2f(column * TILE_SIZE, line * TILE_SIZE);
        quad[1].position = sf::Vector2f((column + 1) * TILE_SIZE, line * TILE_SIZE);
        quad[2].position = sf::Vector2f((column + 1) * TILE_SIZE, (line + 1) * TILE_SIZE);
        quad[3].position = sf::Vector2f(column * TILE_SIZE, (line + 1) * TILE_SIZE);
        quad[0].texCoords = sf::Vector2f(tu * TILE_SIZE, tv * TILE_SIZE);
        quad[1].texCoords = sf::Vector2f((tu + 1) * TILE_SIZE, tv * TILE_SIZE);
        quad[2].texCoords = sf::Vector2f((tu + 1) * TILE_SIZE, (tv + 1) * TILE_SIZE);
        quad[3].texCoords = sf::Vector2f(tu * TILE_SIZE, (tv + 1) * TILE_SIZE);
        //}
    }

}
