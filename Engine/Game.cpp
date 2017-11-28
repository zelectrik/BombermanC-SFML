#include "Game.hpp"
#include <functional>


Game::Game()
    : m_FrameLimitSelect(60)
    , m_FramePerSecondText(toString(m_FramePerSecond),sf::Vector2f(20,20)
                           ,24,FONT_ARMALITE_RIFLE,sf::Color::Red)
    , m_nbPlayerDead(0)
    , m_returnMenu(false)

{
    TimePerFrame=sf::seconds(1.f/60.f);
    t_ShowFPS=sf::seconds(1);
    m_gameFinish=false;
    if (!map.load(sf::Vector2f(0,0),TEXTURE_TILE_PATH, sf::Vector2u(TILE_SIZE, TILE_SIZE), WIDTH_MAP, HEIGHT_MAP))//672*672
        std::cout << "error";
    m_FramePerSecond=0;
    if(!m_BackgroundTexture.loadFromFile("Media/Image/background.png"))
        std::cout << "error to load " << "Media/Image/background.png" << std::endl;
    m_BackgroundSprite.setTexture(m_BackgroundTexture);
    m_BackgroundSprite.setPosition(-180,-60);
    m_player.push_back(new player(false,0,"Thibault","Media/Image/player.png",m_FrameLimitSelect,sf::Vector2f(1,1),&map));
    m_playerIsAlive.push_back(true);

}

void Game::reloadGame(sf::RenderWindow &m_window,int nbIa, int nbPlayer)
{
    m_gameFinish=false;
    m_goMenu=false;
    m_player.clear();
    m_playerIsAlive.clear();
    int nbT=nbIa+nbPlayer;
    int nIA=nbIa;
    m_stopGame=false;
    int nPlayer=nbPlayer;
    m_nbPlayer=nbT;
    for(int i=0; i<nbT; i++)
    {
        m_playerIsAlive.push_back(true);
        if(nPlayer!=0)
        {
            switch(i)
            {
            case 0:
                m_player.push_back(new player(false,0,"Blue","Media/Image/player.png",m_FrameLimitSelect,sf::Vector2f(1,1),&map));
                break;
            case 1:
                m_player.push_back(new player(false,1,"Black","Media/Image/player_black.png",m_FrameLimitSelect,sf::Vector2f(WIDTH_MAP,HEIGHT_MAP),&map));
                break;
            case 2:
                m_player.push_back(new player(false,2,"Green","Media/Image/player_green.png",m_FrameLimitSelect,sf::Vector2f(1,HEIGHT_MAP),&map));
                break;
            case 3:
                m_player.push_back(new player(false,3,"Yellow","Media/Image/player_yellow.png",m_FrameLimitSelect,sf::Vector2f(WIDTH_MAP,1),&map));
                break;
            }

            nPlayer--;

        }
        else if(nIA!=0)
        {
            switch(i)
            {
            case 0:
                m_player.push_back(new player(true,0,"Blue","Media/Image/player.png",m_FrameLimitSelect,sf::Vector2f(1,1),&map));
                break;
            case 1:
                m_player.push_back(new player(true,1,"Black","Media/Image/player_black.png",m_FrameLimitSelect,sf::Vector2f(WIDTH_MAP,HEIGHT_MAP),&map));
                break;
            case 2:
                m_player.push_back(new player(true,2,"Green","Media/Image/player_green.png",m_FrameLimitSelect,sf::Vector2f(1,HEIGHT_MAP),&map));
                break;
            case 3:
                m_player.push_back(new player(true,3,"Yellow","Media/Image/player_yellow.png",m_FrameLimitSelect,sf::Vector2f(WIDTH_MAP,1),&map));
                break;
            }
            nIA--;
        }
        for(int i=0; i<m_player.size(); i++)
        {

            for(int j=0; j<m_player.size(); j++)
            {
                if(i!=j)
                    m_player[i]->addEnnemi(m_player[j]);
            }

        }

    }
    for (int i=0; i<m_player.size(); i++)
    {
        m_player[i]->resetPlayer();
        m_playerIsAlive[i]=true;
    }
    m_nbPlayerDead=0;
    if (!map.load(sf::Vector2f(0,0),TEXTURE_TILE_PATH, sf::Vector2u(TILE_SIZE, TILE_SIZE), WIDTH_MAP, HEIGHT_MAP))//672*672
        std::cout << "error";
}

void Game::run(sf::RenderWindow& m_window)
{
    sf::Clock clock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;
    m_window.setView(sf::View(sf::Vector2f((map.getLineColumn().x*32)/2,(map.getLineColumn().y*32)/2),sf::Vector2f(map.getLineColumn().x*32,map.getLineColumn().y*32)));
    while(m_window.isOpen() && m_gameFinish==false)
    {
        if(m_isPause==false)
        {
            processEvents(m_window);

            timeSinceLastUpdate +=clock.restart();

            while(timeSinceLastUpdate > TimePerFrame)
            {
                timeSinceLastUpdate-=TimePerFrame;
                processEvents(m_window);
                update(TimePerFrame);
            }
        }
        else if(m_gameFinish==false)
        {
            sf::Event event;
            while(m_window.pollEvent(event))
            {
                switch(event.type)
                {
                case sf::Event::Closed:
                    m_window.close();
                    break;
                case sf::Event::KeyPressed:
                    m_window.setKeyRepeatEnabled(false);
                    if(event.key.code==sf::Keyboard::Space)
                    {
                        m_isPause=false;
                    }
                    if(event.key.code==sf::Keyboard::Escape)
                    {
                        m_gameFinish=true;
                        m_stopGame=true;
                    }
                    break;
                }
            }
            timeSinceLastUpdate = clock.restart();
        }
        render(m_window);
    }
    sf::Text winner;
    sf::Font win_font;
    win_font.loadFromFile("Media/Font/font.ttf");
    if(m_gameFinish==true && m_goMenu==false&&m_stopGame==false)
    {
        winner.setFont(win_font);
        winner.setPosition(130,100);
        for(int i=0;i<m_player.size();i++)
        {
            if(m_player[i]->getLife()>0)
                winner.setString("        "+m_player[i]->getName()+" win!\n\n\n           ECHAP \nPour revenir au \n           menu");
        }


    }
    while(m_window.isOpen() && m_gameFinish==true && m_goMenu==false&&m_stopGame==false)
    {

        m_window.clear();
        sf::Event event;
        m_window.draw(winner);
            while(m_window.pollEvent(event))
            {
                switch(event.type)
                {
                case sf::Event::Closed:
                    m_window.close();
                    break;
                case sf::Event::KeyPressed:
                    m_window.setKeyRepeatEnabled(false);
                    if(event.key.code==sf::Keyboard::Escape)
                    {
                        m_goMenu=true;
                    }
                    break;
                }
            }
            timeSinceLastUpdate = clock.restart();
            m_window.display();
        }

    m_window.setView(sf::View(sf::Vector2f(UI_WIDTH/2,UI_HEIGHT/2),sf::Vector2f(UI_WIDTH,UI_HEIGHT)));
}

void Game::processEvents(sf::RenderWindow &m_window)
{
    sf::Event event;
    while(m_window.pollEvent(event))
    {
        switch(event.type)
        {
        case sf::Event::Closed:
            m_window.close();
            break;
        case sf::Event::KeyPressed:
            m_window.setKeyRepeatEnabled(false);
            for(int i=0; i<m_player.size(); i++)
            {
                if(m_playerIsAlive[i]==true)
                    m_player[i]->eventPlayerInput(event.key.code,map);
            }
            if(event.key.code==sf::Keyboard::Escape)
            {
                m_isPause=true;
            }
            break;
            if(event.key.code==sf::Keyboard::Escape)
            {
                if(m_gameFinish==true)
                {
                    m_returnMenu=true;

                }
            }
        }
    }
    for(int i =0; i<m_player.size(); i++)
    {
        if(m_playerIsAlive[i]==true)
            m_player[i]->handlePlayerInput(map);
    }
}

void Game::update(sf::Time deltaTime)
{
    for(int i=0; i<m_player.size(); i++)
    {
        bool playerAlive=m_playerIsAlive[i];
        for(int j=0; j<m_player.size(); j++)
        {
            if(j!=i)
            {
                playerAlive=m_player[i]->updatePlayer(deltaTime,map,*m_player[j],j);
                if(playerAlive==false && m_playerIsAlive[i]==true)
                {
                    m_playerIsAlive[i]=false;
                    m_nbPlayerDead++;
                    m_player[i]->killPlayer();
                }
            }
        }
    }

    if(m_nbPlayer-m_nbPlayerDead==1)
        m_gameFinish=true;
}

void Game::render(sf::RenderWindow& m_window)
{
    m_window.clear();
    if(m_isPause==false)
    {
        m_window.draw(map);
        for(int i=0; i<m_player.size(); i++)
        {
            m_player[i]->drawPlayer(m_window);
        }
    }
    else
    {
        sf::Texture t_pause;
        if(!t_pause.loadFromFile("Media/Image/aide.png"))
            std::cout << "error to open aide"<<std::endl;
        sf::Sprite s_pause;
        s_pause.setTexture(t_pause);
        m_window.draw(s_pause);
    }
    m_window.display();
}
