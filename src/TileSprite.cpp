#include "TileSprite.h"


// Constructor
TileSprite::TileSprite(const sf::Texture& sharedTexture) : texture(&sharedTexture) {
    setSize({100.f, 100.f});    // Set the size of the tile sprite
    setTexture(texture);        // Set the texture of the tile sprite

    ml::ImageRects rects = ml::TextureSlicer::getImageRects(*texture, 11, 12);  // Get the image rectangles from the texture
    setTextureRect(rects.getIntRect(0, 0));                                     // Set the texture rectangle to the first image
}


// Set the sprite by grid
void TileSprite::setByGrid(int row, int col) {
    ml::ImageRects rects = ml::TextureSlicer::getImageRects(*texture, 11, 12);  // Get the image rectangles from the texture
    setTextureRect(rects.getIntRect(row, col));                                   // Set the texture rectangle to the specified image
}
