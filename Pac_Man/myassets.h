// This file was generated with the command-line:
//    /usr/local/bin/gd2asset -f myassets.gd2 -o myassets.h PMNorth.jpg PMEast.jpg PMSouth.jpg PMWest.jpg levelOne.jpg Dot.jpg PowerUp.jpg RedGhost.jpg YellowGhost.jpg BlueGhost.jpg PinkGhost.jpg GhostHunt.jpg

#define PMNORTH_HANDLE 0
#define PMNORTH_WIDTH 12
#define PMNORTH_HEIGHT 24
#define PMNORTH_CELLS 1
#define PMEAST_HANDLE 1
#define PMEAST_WIDTH 12
#define PMEAST_HEIGHT 24
#define PMEAST_CELLS 1
#define PMSOUTH_HANDLE 2
#define PMSOUTH_WIDTH 12
#define PMSOUTH_HEIGHT 24
#define PMSOUTH_CELLS 1
#define PMWEST_HANDLE 3
#define PMWEST_WIDTH 12
#define PMWEST_HEIGHT 24
#define PMWEST_CELLS 1
#define LEVELONE_HANDLE 4
#define LEVELONE_WIDTH 224
#define LEVELONE_HEIGHT 248
#define LEVELONE_CELLS 1
#define DOT_HANDLE 5
#define DOT_WIDTH 8
#define DOT_HEIGHT 7
#define DOT_CELLS 1
#define POWERUP_HANDLE 6
#define POWERUP_WIDTH 8
#define POWERUP_HEIGHT 9
#define POWERUP_CELLS 1
#define REDGHOST_HANDLE 7
#define REDGHOST_WIDTH 12
#define REDGHOST_HEIGHT 12
#define REDGHOST_CELLS 1
#define YELLOWGHOST_HANDLE 8
#define YELLOWGHOST_WIDTH 12
#define YELLOWGHOST_HEIGHT 12
#define YELLOWGHOST_CELLS 1
#define BLUEGHOST_HANDLE 9
#define BLUEGHOST_WIDTH 12
#define BLUEGHOST_HEIGHT 12
#define BLUEGHOST_CELLS 1
#define PINKGHOST_HANDLE 10
#define PINKGHOST_WIDTH 12
#define PINKGHOST_HEIGHT 12
#define PINKGHOST_CELLS 1
#define GHOSTHUNT_HANDLE 11
#define GHOSTHUNT_WIDTH 12
#define GHOSTHUNT_HEIGHT 12
#define GHOSTHUNT_CELLS 1
#define ASSETS_END 115104UL
#define LOAD_ASSETS()  (GD.safeload("myassets.gd2"), GD.loadptr = ASSETS_END)
static const shape_t PMNORTH_SHAPE = {0, 12, 24, 0};
static const shape_t PMEAST_SHAPE = {1, 12, 24, 0};
static const shape_t PMSOUTH_SHAPE = {2, 12, 24, 0};
static const shape_t PMWEST_SHAPE = {3, 12, 24, 0};
static const shape_t LEVELONE_SHAPE = {4, 224, 248, 0};
static const shape_t DOT_SHAPE = {5, 8, 7, 0};
static const shape_t POWERUP_SHAPE = {6, 8, 9, 0};
static const shape_t REDGHOST_SHAPE = {7, 12, 12, 0};
static const shape_t YELLOWGHOST_SHAPE = {8, 12, 12, 0};
static const shape_t BLUEGHOST_SHAPE = {9, 12, 12, 0};
static const shape_t PINKGHOST_SHAPE = {10, 12, 12, 0};
static const shape_t GHOSTHUNT_SHAPE = {11, 12, 12, 0};
struct {
  Bitmap pmnorth;
  Bitmap pmeast;
  Bitmap pmsouth;
  Bitmap pmwest;
  Bitmap levelone;
  Bitmap dot;
  Bitmap powerup;
  Bitmap redghost;
  Bitmap yellowghost;
  Bitmap blueghost;
  Bitmap pinkghost;
  Bitmap ghosthunt;
} bitmaps = {
 /*          pmnorth */  {{ 12,  24}, {  6,  12},      0x0UL,  6,  0},
 /*           pmeast */  {{ 12,  24}, {  6,  12},    0x240UL,  6,  1},
 /*          pmsouth */  {{ 12,  24}, {  6,  12},    0x480UL,  6,  2},
 /*           pmwest */  {{ 12,  24}, {  6,  12},    0x6c0UL,  6,  3},
 /*         levelone */  {{224, 248}, {112, 124},    0x900UL,  6,  4},
 /*              dot */  {{  8,   7}, {  4,   3},  0x1bb00UL,  6,  5},
 /*          powerup */  {{  8,   9}, {  4,   4},  0x1bb70UL,  6,  6},
 /*         redghost */  {{ 12,  12}, {  6,   6},  0x1bc00UL,  6,  7},
 /*      yellowghost */  {{ 12,  12}, {  6,   6},  0x1bd20UL,  6,  8},
 /*        blueghost */  {{ 12,  12}, {  6,   6},  0x1be40UL,  6,  9},
 /*        pinkghost */  {{ 12,  12}, {  6,   6},  0x1bf60UL,  6, 10},
 /*        ghosthunt */  {{ 12,  12}, {  6,   6},  0x1c080UL,  6, 11}
};
