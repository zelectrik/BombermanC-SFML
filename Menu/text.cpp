#include "text.hpp"

text::text(std::string yourText,sf::Vector2f position,
           int policeSize,std::string pathToFont,sf::Color textColor)
: m_text(yourText)
, m_textColor(textColor)
, m_position(position)
, m_textPolice(policeSize)
{
    if(!m_font.loadFromFile(pathToFont))
        std::cout<<"error to load "<<pathToFont<<std::endl;
    m_drawText.setFont(m_font);
    m_drawText.setString(m_text);
    m_drawText.setCharacterSize(m_textPolice);
    m_drawText.setColor(m_textColor);
    m_drawText.setPosition(m_position);
    int weightText = m_drawText.getGlobalBounds().width;
    int heightText = m_drawText.getGlobalBounds().height;
    m_drawText.setOrigin(sf::Vector2f(weightText/2,heightText/2));
}

text::~text()
{

}


void text::drawText(sf::RenderWindow &window)
{
    window.draw(m_drawText);
}

void text::setTextPosition(sf::Vector2f position)
{
    m_position=position;
    m_drawText.setPosition(m_position);
}

void text::setText(std::string texte)
{
    m_text=texte;
    m_drawText.setString(m_text);
    int weightText = m_drawText.getGlobalBounds().width;
    int heightText = m_drawText.getGlobalBounds().height;
    m_drawText.setOrigin(sf::Vector2f(weightText/2,heightText/2));

}

sf::Text text::getText()
{
    return m_drawText;
}

