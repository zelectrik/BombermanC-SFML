#include "button.hpp"


button::button(Texture buttonNotPress
               ,Texture buttonOnPress,sf::Vector2f position
               ,int widht,int height)
: m_position(position)
, m_isUnderCursor(false)
, m_isPress(false)
, m_widht(widht)
, m_height(height)
{
    m_buttonOnTexture=buttonOnPress.get();
    m_buttonNotTexture=buttonNotPress.get();
    m_buttonSprite.setTexture(*m_buttonNotTexture,true);
    m_buttonSprite.setPosition(m_position);
}

void button::createButton(Texture buttonNotPress,Texture buttonOnPress,
           sf::Vector2f position,int widht,int height)
{
    m_position=position;
    m_isUnderCursor=false;
    m_isPress=false;
    m_widht=widht;
    m_height=height;
    m_buttonOnTexture=buttonOnPress.get();
    m_buttonNotTexture=buttonNotPress.get();
    m_buttonSprite.setTexture(*m_buttonNotTexture,true);
    m_buttonSprite.setPosition(m_position);
}

void button::cursorIsOn(sf::RenderWindow &window)
{
    if(isCollide(sf::Mouse::getPosition(window),
                 m_buttonSprite,m_widht
                 ,m_height))
    {
        m_isUnderCursor=true;
        m_buttonSprite.setTexture(*m_buttonOnTexture,true);
    }
    else

        {m_isUnderCursor=true;
        m_buttonSprite.setTexture(*m_buttonNotTexture,true);
        }
}

bool button::getIsCursorOn()
{
    return m_isUnderCursor;
}

bool button::buttonIsPress()
{
    if(m_isUnderCursor)
        m_isPress=true;
    else
        m_isPress=false;
    return m_isPress;
}

sf::Sprite button::getSprite()
{
    return m_buttonSprite;
}




