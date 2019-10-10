// This file was generated with the command-line:
//    /usr/local/bin/gd2asset -f myassets.gd2 -o myassets.h PMNorth.jpg PMEast.jpg PMSouth.jpg PMWest.jpg levelOne.jpg Dot.jpg PowerUp.jpg RedGhost.jpg YellowGhost.jpg BlueGhost.jpg PinkGhost.jpg GhostHunt.jpg

#define PMNORTH_HANDLE 0
#define PMNORTH_WIDTH 15
#define PMNORTH_HEIGHT 30
#define PMNORTH_CELLS 1
#define PMEAST_HANDLE 1
#define PMEAST_WIDTH 15
#define PMEAST_HEIGHT 30
#define PMEAST_CELLS 1
#define PMSOUTH_HANDLE 2
#define PMSOUTH_WIDTH 15
#define PMSOUTH_HEIGHT 30
#define PMSOUTH_CELLS 1
#define PMWEST_HANDLE 3
#define PMWEST_WIDTH 15
#define PMWEST_HEIGHT 30
#define PMWEST_CELLS 1
#define LEVELONE_HANDLE 4
#define LEVELONE_WIDTH 224
#define LEVELONE_HEIGHT 248
#define LEVELONE_CELLS 1
#define DOT_HANDLE 5
#define DOT_WIDTH 10
#define DOT_HEIGHT 9
#define DOT_CELLS 1
#define POWERUP_HANDLE 6
#define POWERUP_WIDTH 13
#define POWERUP_HEIGHT 15
#define POWERUP_CELLS 1
#define REDGHOST_HANDLE 7
#define REDGHOST_WIDTH 15
#define REDGHOST_HEIGHT 15
#define REDGHOST_CELLS 1
#define YELLOWGHOST_HANDLE 8
#define YELLOWGHOST_WIDTH 15
#define YELLOWGHOST_HEIGHT 15
#define YELLOWGHOST_CELLS 1
#define BLUEGHOST_HANDLE 9
#define BLUEGHOST_WIDTH 15
#define BLUEGHOST_HEIGHT 15
#define BLUEGHOST_CELLS 1
#define PINKGHOST_HANDLE 10
#define PINKGHOST_WIDTH 15
#define PINKGHOST_HEIGHT 15
#define PINKGHOST_CELLS 1
#define GHOSTHUNT_HANDLE 11
#define GHOSTHUNT_WIDTH 15
#define GHOSTHUNT_HEIGHT 15
#define GHOSTHUNT_CELLS 1
#define ASSETS_END 117524UL
#define LOAD_ASSETS()  (GD.safeload("myassets.gd2"), GD.loadptr = ASSETS_END)
static const shape_t PMNORTH_SHAPE = {0, 15, 30, 0};
static const shape_t PMEAST_SHAPE = {1, 15, 30, 0};
static const shape_t PMSOUTH_SHAPE = {2, 15, 30, 0};
static const shape_t PMWEST_SHAPE = {3, 15, 30, 0};
static const shape_t LEVELONE_SHAPE = {4, 224, 248, 0};
static const shape_t DOT_SHAPE = {5, 10, 9, 0};
static const shape_t POWERUP_SHAPE = {6, 13, 15, 0};
static const shape_t REDGHOST_SHAPE = {7, 15, 15, 0};
static const shape_t YELLOWGHOST_SHAPE = {8, 15, 15, 0};
static const shape_t BLUEGHOST_SHAPE = {9, 15, 15, 0};
static const shape_t PINKGHOST_SHAPE = {10, 15, 15, 0};
static const shape_t GHOSTHUNT_SHAPE = {11, 15, 15, 0};
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
 /*          pmnorth */  {{ 15,  30}, {  7,  15},      0x0UL,  6,  0},
 /*           pmeast */  {{ 15,  30}, {  7,  15},    0x384UL,  6,  1},
 /*          pmsouth */  {{ 15,  30}, {  7,  15},    0x708UL,  6,  2},
 /*           pmwest */  {{ 15,  30}, {  7,  15},    0xa8cUL,  6,  3},
 /*         levelone */  {{224, 248}, {112, 124},    0xe10UL,  6,  4},
 /*              dot */  {{ 10,   9}, {  5,   4},  0x1c010UL,  6,  5},
 /*          powerup */  {{ 13,  15}, {  6,   7},  0x1c0c4UL,  6,  6},
 /*         redghost */  {{ 15,  15}, {  7,   7},  0x1c24aUL,  6,  7},
 /*      yellowghost */  {{ 15,  15}, {  7,   7},  0x1c40cUL,  6,  8},
 /*        blueghost */  {{ 15,  15}, {  7,   7},  0x1c5ceUL,  6,  9},
 /*        pinkghost */  {{ 15,  15}, {  7,   7},  0x1c790UL,  6, 10},
 /*        ghosthunt */  {{ 15,  15}, {  7,   7},  0x1c952UL,  6, 11}
};
