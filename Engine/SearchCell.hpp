#ifndef SEARCHCELL_HPP_INCLUDED
#define SEARCHCELL_HPP_INCLUDED

#define HEIGHT_MAP 15
#define WIDTH_MAP 19


#include "../TileMap/tileMap.hpp"
#include <math.h>

struct SearchCell
{
public:
    int m_xcoord, m_ycoord;
    int m_id;
    SearchCell *parent;
    float G;
    float H;

    SearchCell() : parent(0) {}
    SearchCell(int x, int y,SearchCell *_parent = 0) : m_xcoord(x), m_ycoord(y),
        parent(_parent), m_id(x*WIDTH_MAP+y), G(0), H(0) {};

    float GetF() {return G + H;}
    float ManHattanDistance(SearchCell *nodeEnd)
    {
        float x = (float) (fabs(this->m_xcoord - nodeEnd->m_xcoord));
        float y = (float) (fabs(this->m_ycoord - nodeEnd->m_ycoord));
        return x+y;
    }
};



#endif // SEARCHCELL_HPP_INCLUDED
