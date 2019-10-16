// This file was generated with the command-line:
//    /usr/local/bin/gd2asset -f myassets.gd2 -o myassets.h PacManNorthBig.png PacManEastBig.png PacManSouthBig.png PacManWestBig.png levelOne.jpg DotBig.png PowerUpBig.png RedGhostBig.png YellowGhostBig.png BlueGhostBig.png PinkGhostBig.png GhostHuntBig.png

#define PACMANNORTHBIG_HANDLE 0
#define PACMANNORTHBIG_WIDTH 14
#define PACMANNORTHBIG_HEIGHT 42
#define PACMANNORTHBIG_CELLS 1
#define PACMANEASTBIG_HANDLE 1
#define PACMANEASTBIG_WIDTH 14
#define PACMANEASTBIG_HEIGHT 42
#define PACMANEASTBIG_CELLS 1
#define PACMANSOUTHBIG_HANDLE 2
#define PACMANSOUTHBIG_WIDTH 14
#define PACMANSOUTHBIG_HEIGHT 42
#define PACMANSOUTHBIG_CELLS 1
#define PACMANWESTBIG_HANDLE 3
#define PACMANWESTBIG_WIDTH 14
#define PACMANWESTBIG_HEIGHT 42
#define PACMANWESTBIG_CELLS 1
#define LEVELONE_HANDLE 4
#define LEVELONE_WIDTH 224
#define LEVELONE_HEIGHT 248
#define LEVELONE_CELLS 1
#define DOTBIG_HANDLE 5
#define DOTBIG_WIDTH 14
#define DOTBIG_HEIGHT 14
#define DOTBIG_CELLS 1
#define POWERUPBIG_HANDLE 6
#define POWERUPBIG_WIDTH 14
#define POWERUPBIG_HEIGHT 14
#define POWERUPBIG_CELLS 1
#define REDGHOSTBIG_HANDLE 7
#define REDGHOSTBIG_WIDTH 14
#define REDGHOSTBIG_HEIGHT 56
#define REDGHOSTBIG_CELLS 1
#define YELLOWGHOSTBIG_HANDLE 8
#define YELLOWGHOSTBIG_WIDTH 14
#define YELLOWGHOSTBIG_HEIGHT 56
#define YELLOWGHOSTBIG_CELLS 1
#define BLUEGHOSTBIG_HANDLE 9
#define BLUEGHOSTBIG_WIDTH 14
#define BLUEGHOSTBIG_HEIGHT 56
#define BLUEGHOSTBIG_CELLS 1
#define PINKGHOSTBIG_HANDLE 10
#define PINKGHOSTBIG_WIDTH 14
#define PINKGHOSTBIG_HEIGHT 56
#define PINKGHOSTBIG_CELLS 1
#define GHOSTHUNTBIG_HANDLE 11
#define GHOSTHUNTBIG_WIDTH 14
#define GHOSTHUNTBIG_HEIGHT 14
#define GHOSTHUNTBIG_CELLS 1
#define ASSETS_END 123256UL
#define LOAD_ASSETS()  (GD.safeload("myassets.gd2"), GD.loadptr = ASSETS_END)
static const shape_t PACMANNORTHBIG_SHAPE = {0, 14, 42, 0};
static const shape_t PACMANEASTBIG_SHAPE = {1, 14, 42, 0};
static const shape_t PACMANSOUTHBIG_SHAPE = {2, 14, 42, 0};
static const shape_t PACMANWESTBIG_SHAPE = {3, 14, 42, 0};
static const shape_t LEVELONE_SHAPE = {4, 224, 248, 0};
static const shape_t DOTBIG_SHAPE = {5, 14, 14, 0};
static const shape_t POWERUPBIG_SHAPE = {6, 14, 14, 0};
static const shape_t REDGHOSTBIG_SHAPE = {7, 14, 56, 0};
static const shape_t YELLOWGHOSTBIG_SHAPE = {8, 14, 56, 0};
static const shape_t BLUEGHOSTBIG_SHAPE = {9, 14, 56, 0};
static const shape_t PINKGHOSTBIG_SHAPE = {10, 14, 56, 0};
static const shape_t GHOSTHUNTBIG_SHAPE = {11, 14, 14, 0};
struct {
  Bitmap pacmannorthbig;
  Bitmap pacmaneastbig;
  Bitmap pacmansouthbig;
  Bitmap pacmanwestbig;
  Bitmap levelone;
  Bitmap dotbig;
  Bitmap powerupbig;
  Bitmap redghostbig;
  Bitmap yellowghostbig;
  Bitmap blueghostbig;
  Bitmap pinkghostbig;
  Bitmap ghosthuntbig;
} bitmaps = {
 /*   pacmannorthbig */  {{ 14,  42}, {  7,  21},      0x0UL,  6,  0},
 /*    pacmaneastbig */  {{ 14,  42}, {  7,  21},    0x498UL,  6,  1},
 /*   pacmansouthbig */  {{ 14,  42}, {  7,  21},    0x930UL,  6,  2},
 /*    pacmanwestbig */  {{ 14,  42}, {  7,  21},    0xdc8UL,  6,  3},
 /*         levelone */  {{224, 248}, {112, 124},   0x1260UL,  6,  4},
 /*           dotbig */  {{ 14,  14}, {  7,   7},  0x1c460UL,  6,  5},
 /*       powerupbig */  {{ 14,  14}, {  7,   7},  0x1c5e8UL,  6,  6},
 /*      redghostbig */  {{ 14,  56}, {  7,  28},  0x1c770UL,  6,  7},
 /*   yellowghostbig */  {{ 14,  56}, {  7,  28},  0x1cd90UL,  6,  8},
 /*     blueghostbig */  {{ 14,  56}, {  7,  28},  0x1d3b0UL,  6,  9},
 /*     pinkghostbig */  {{ 14,  56}, {  7,  28},  0x1d9d0UL,  6, 10},
 /*     ghosthuntbig */  {{ 14,  14}, {  7,   7},  0x1dff0UL,  6, 11}
};
