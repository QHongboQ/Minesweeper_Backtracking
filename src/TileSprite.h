#ifndef TILESPRITE_H
#define TILESPRITE_H
#include <SFML/Graphics.hpp>
#include <Malena/common.hpp>
#include "Malena/Utilities/TextureSlicer.h"

class TileSprite : public ml::Rectangle {
public:
    TileSprite(const sf::Texture& sharedTexture);   // Constructor

    TileSprite(const TileSprite& other)
        : ml::Rectangle(other), texture(other.texture) {
        setTexture(texture);
        setTextureRect(other.getTextureRect());
        setSize(other.getSize());
        setPosition(other.getPosition());
    }
    
    void setByGrid(int row, int col);   // Set the sprite by grid

    
private:
    const sf::Texture* texture; // Pointer to the texture
};

#endif // TILESPRITE_H
