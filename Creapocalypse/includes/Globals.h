#pragma once
#include <SFML/Graphics/Texture.hpp>

sf::Texture* const GetNullTexture() {
    static sf::Texture* const s_nullTexture = new sf::Texture();
    return s_nullTexture;
}