//
//  game.cpp
//  EnTT Example
//
//  Created by Indi Kernick on 17/9/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#include "game.hpp"

#include "sprites.hpp"
#include "graphics.hpp"
#include "factories.hpp"
#include "move player system.hpp"
#include "blit sprites system.hpp"
#include "get player pos system.hpp"

void runGame(WINDOW *win) {
  configureWindow(win);
  initColorPairs();

  FrameBuf screen{getWindowSize(win)};
  Registry reg;
  makePlayer(reg, {0, 0});
  makeObject(reg, {5, 5}, makeRockSprite());
  makeObject(reg, {24, 2}, makeTreeSprite());
  makeObject(reg, {-(12), -(1)}, makeMonsterSprite());
  makeObject(reg, {-(25), 3}, makeFlowerSprite());

  bool quit = false;
  while (!quit) {
    int ch;
  	while ((ch = wgetch(win)) != ERR) {
      if (ch == 'q') {
  	    quit = true;
  	    break;
  	  } else if (ch == KEY_RESIZE) {
  	    screen.resize(getWindowSize(win));
  	  } else if (ch == KEY_UP) {
  	    movePlayer(reg, Grid::Dir::UP);
  	  } else if (ch == KEY_RIGHT) {
  	    movePlayer(reg, Grid::Dir::RIGHT);
  	  } else if (ch == KEY_DOWN) {
  	    movePlayer(reg, Grid::Dir::DOWN);
  	  } else if (ch == KEY_LEFT) {
  	    movePlayer(reg, Grid::Dir::LEFT);
   	  }
  	}
  	blitSprites(reg, screen, screen.size() / 2 - getPlayerPos(reg));
  	renderScreen(win, screen);
  	screen.fill(Cell{});
  }
  // delwin(win);
}