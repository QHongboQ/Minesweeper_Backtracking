#ifndef MINESWEEPERAPP_H
#define MINESWEEPERAPP_H

#include <Malena/common.hpp>
#include "BackTracking.h"
#include "TileSprite.h"
#include "Board.h"

class MinesweeperApp : public ml::Application {
public:
    MinesweeperApp(const sf::Texture& sharedTexture);

    void initialization() override;
    void registerEvents() override;
    void update();

private:
    sf::Texture sharedTexture;
    Board board;
    BackTracking backtracking;
};
    

#endif // MINESWEEPERAPP_H