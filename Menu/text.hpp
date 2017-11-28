#ifndef TEXT_HPP_INCLUDED
#define TEXT_HPP_INCLUDED

#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>

#define FONT_ARIAL "Media/Font/arial.ttf"
#define FONT_AIRSTREAM "Media/Font/Airstream.ttf"
#define FONT_ARCHERY_BLACK "Media/Font/Archery_Black.ttf"
#define FONT_ARMALITE_RIFLE "Media/Font/armalite_rifle.ttf"


class text : public sf::Drawable
{
public:
    text(std::string text,sf::Vector2f position,int policeSize,std::string pathToFont,sf::Color textColor);
    ~text();
    void setTextPosition(sf::Vector2f position);
    void setText(std::string texte);
    void drawText(sf::RenderWindow &window);
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        target.draw(m_drawText,states);
    }
    sf::Text getText();

private:
    sf::Font m_font;
    sf::Text m_drawText;
    sf::Color m_textColor;
    sf::Vector2f m_position;
    std::string m_text;
    int m_textPolice;

};

#endif // TEXT_HPP_INCLUDED
