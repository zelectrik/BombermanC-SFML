#include "Menu.hpp"


void menu::addButton(Texture buttonNotPress,Texture buttonOnPress,
                    sf::Vector2f position,int widht,int height)
{
        m_buttonList[0].createButton(buttonNotPress,buttonOnPress
                                      ,position,widht,height);
}

void menu::addText(std::string texte,sf::Vector2f position,int policeSize
                 ,std::string pathToFont,sf::Color textColor)
{
    //m_TextList[0]=(texte,position,policeSize,pathToFont,textColor);
}

bool menu::checkButtonPress(int numberButton)
{
    return m_buttonList[numberButton].buttonIsPress();
}

void menu::update(sf::RenderWindow &window)
{
    for(int i=0;i<10;i++)
    {
        m_buttonList[i].cursorIsOn(window);
    }
}

void menu::render(sf::RenderWindow& window)
{


    for(int i=0;i<10;i++)
    {
        window.draw(m_buttonList[i]);
    }
    for(int j=0;j<10;j++)
    {
        window.draw(m_TextList[j]);
    }
}
