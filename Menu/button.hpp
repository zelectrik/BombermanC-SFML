#ifndef BUTTON_HPP_INCLUDED
#define BUTTON_HPP_INCLUDED

#include <SFML/Graphics.hpp>
#include "../Engine/fonction.hpp"
#include <iostream>
#include "Texture.hpp"



class button : public sf::Drawable
{
public:
    button(Texture buttonNotPress,Texture buttonOnPress,
           sf::Vector2f position,int widht,int height);
    void createButton(Texture buttonNotPress,Texture buttonOnPress,
           sf::Vector2f position,int widht,int height);
    void cursorIsOn(sf::RenderWindow &window);
    bool buttonIsPress();
    bool getIsCursorOn();
    sf::Sprite getSprite();


    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        target.draw(m_buttonSprite,states);
    }

private:
    sf::Texture *m_buttonNotTexture;
    sf::Texture *m_buttonOnTexture;
    sf::Sprite m_buttonSprite;
    sf::Vector2f m_position;
    bool m_isUnderCursor;
    bool m_isPress;
    int m_widht;
    int m_height;
};

#endif // BUTTON_HPP_INCLUDED
