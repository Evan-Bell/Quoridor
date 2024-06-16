// constants.hpp

#ifndef CONSTANTS_H
#define CONSTANTS_H

#define SIZE 9
#define WALLS ((SIZE == 9) ? 10 : static_cast<int>((SIZE * SIZE) / 4 - SIZE * 1.5 + 3.25))
#define CELL_SIZE (180 / SIZE) // Size of each cell in pixels

#endif // CONSTANTS_H