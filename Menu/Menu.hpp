#ifndef MENU_HPP_INCLUDED
#define MENU_HPP_INCLUDED

#include "button.hpp"
#include "text.hpp"

class menu : public sf::Drawable
{
public:
    void addButton(Texture buttonNotPress,Texture buttonOnPress,
                    sf::Vector2f position,int widht,int height);
    void addText(std::string texte,sf::Vector2f position,int policeSize
                 ,std::string pathToFont,sf::Color textColor);
    bool checkButtonPress(int numberButton);
    void update(sf::RenderWindow &window);
    void render(sf::RenderWindow &window);
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
    for(int i=0;i<10;i++)
    {
        target.draw(m_buttonList[i]);
    }
    for(int j=0;j<10;j++)
    {
        target.draw(m_TextList[j]);
    }
    }

private:
    button m_buttonList[10];
    text m_TextList[10];
    sf::RenderWindow m_window;
};

#endif // MENU_HPP_INCLUDED
