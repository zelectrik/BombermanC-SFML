#ifndef TEXTURE_HPP_INCLUDED
#define TEXTURE_HPP_INCLUDED

#include <SFML/Graphics/Texture.hpp>
#include <memory>
#include <map>

class Texture
{
    public:
        Texture(std::string const &id);
        virtual ~Texture();

        /* retourne la texture référencée par l'objet
         * retourne nullptr si la texture n'a pas ete load correctement
         */
        sf::Texture* get();

    protected:
        std::shared_ptr<sf::Texture> m_texture;

        static std::map<std::string, std::weak_ptr<sf::Texture>> m_textures;
        static std::shared_ptr<sf::Texture> load(std::string const &id);

    private:
};

#endif // TEXTURE_HPP_INCLUDED

