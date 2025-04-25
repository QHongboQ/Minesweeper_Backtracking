#include "TileSprite.h"

TileSprite::TileSprite(const sf::Texture& sharedTexture) : texture(&sharedTexture) {
    setSize({100.f, 100.f});
    setTexture(texture);

    ml::ImageRects rects = ml::TextureSlicer::getImageRects(*texture, 11, 12);
    setTextureRect(rects.getIntRect(0, 0));
}

void TileSprite::setByGrid(int row, int col) {
    ml::ImageRects rects = ml::TextureSlicer::getImageRects(*texture, 11, 12);
    setTextureRect(rects.getIntRect(row, col));
}
