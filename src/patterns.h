//
//  patterns.h
//  conway
//
//  Created by Chris Roby on 6/2/12.
//  Copyright (c) 2012 Chris Roby, 70bpm, LLC. All rights reserved.
//

#pragma once

#include "gameOfLife.h"

class patterns {
public:
  static void gliderGun(cell **grid, int startPosX, int startPosY);
  static void pufferTrain(cell **grid, int startPosX, int startPosY);
};