#ifndef TILESPRITE_H
#define TILESPRITE_H
#include <SFML/Graphics.hpp>
#include <Malena/common.hpp>
#include "Malena/Utilities/TextureSlicer.h"

class TileSprite : public ml::Rectangle {
public:
    TileSprite(const sf::Texture& sharedTexture);
    void setByGrid(int row, int col);
private:
    const sf::Texture* texture;
};

#endif // TILESPRITE_H
