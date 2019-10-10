#include <EEPROM.h>
#include <SPI.h>
#include <GD2.h>
#include "myassets.h"

class Player
{
public:
    Player(){x = 0.0; y = 0.0; playerState = animationCounter = 0;}
    float x, y;
    int playerState, playerOpenState, animationCounter;
};

class Ghost
{
public:
    Ghost(){}
    float x, y;
    int ghostState;
    int dir;            // 0 = North, 1 = East, 2 = South, 3 = West, 4 = Stand.
};

class Dot
{
public:
    Dot(int ix, int iy) {x = ix; y = iy;}
    int x, y;
    bool powerUp;
};

class Intersection
{
public:
    Intersection(int iindex, int xpos, int ypos, int inorth, int ieast, int isouth, int iwest)
    {
        index = iindex;
        x = xpos;
        y = ypos;
        north = inorth;
        east = ieast;
        south = isouth;
        west = iwest;
    }
    int index;
    int x, y;
    int north, east, south, west;
};

class Map
{
public:
    Map(){}
    int x,y;
    Intersection intersections[65];
};

Player pacMan;
Map level;
int xValue, yValue;
int animationCounter;
int MaxX, MaxY;
long previusTime = 0, currentTime = 0;

// Order of handels:
// 0  >> PacMan state N.
// 1  >> PacMan state E.
// 2  >> PacMan state S.
// 3  >> PacMan state W.
// 4  >> Level One.
// 5  >> Dot.
// 6 >> PowerUp.
// 6 >> RedGhost.
// 7 >> YellowGhost.
// 8 >> PinkGhost.
// 9 >> BlueGhost.
// 10 >> GhostHunt.

void buildMap() {
    level.intersections[0] =  Intersection( 0, level.x + 4  , level.y + 4  , -1,  1,  6, -1);
    level.intersections[1] =  Intersection( 1, level.x + 44 , level.y + 4  , -1,  2,  7,  0);
    level.intersections[2] =  Intersection( 2, level.x + 92 , level.y + 4  , -1, -1,  9,  1);
    level.intersections[3] =  Intersection( 3, level.x + 116, level.y + 4  , -1,  4, 10, -1);
    level.intersections[4] =  Intersection( 4, level.x + 164, level.y + 4  , -1,  5, 12,  3);
    level.intersections[5] =  Intersection( 5, level.x + 204, level.y + 4  , -1, -1, 13, -1);
    level.intersections[6] =  Intersection( 6, level.x + 4  , level.y + 36 ,  0,  7, 14, -1);
    level.intersections[7] =  Intersection( 7, level.x + 44 , level.y + 36 ,  1,  8, 15,  6);
    level.intersections[8] =  Intersection( 8, level.x + 68 , level.y + 36 , -1,  9, 16,  7);
    level.intersections[9] =  Intersection( 9, level.x + 92 , level.y + 36 ,  2, 10, -1,  8);
    level.intersections[10] = Intersection(10, level.x + 116, level.y + 36 ,  3, 11, -1,  9);
    level.intersections[11] = Intersection(11, level.x + 139, level.y + 36 , -1, 12, 19, 10);
    level.intersections[12] = Intersection(12, level.x + 164, level.y + 36 ,  4, 13, 20, 11);
    level.intersections[13] = Intersection(13, level.x + 204, level.y + 36 ,  5, -1, 21, 12);
    level.intersections[14] = Intersection(14, level.x + 4  , level.y + 60 ,  6, 15, -1, -1);
    level.intersections[15] = Intersection(15, level.x + 44 , level.y + 60 ,  7, -1, 26, 14);
    level.intersections[16] = Intersection(16, level.x + 68 , level.y + 60 ,  8, 17, -1, -1);
    level.intersections[17] = Intersection(17, level.x + 92 , level.y + 60 , -1, -1, 23, 16);
    level.intersections[18] = Intersection(18, level.x + 116, level.y + 60 , -1, 19, 24, -1);
    level.intersections[19] = Intersection(19, level.x + 139, level.y + 60 , 11, -1, -1, 18);
    level.intersections[20] = Intersection(20, level.x + 164, level.y + 60 , 12, 21, 29, -1);
    level.intersections[21] = Intersection(21, level.x + 204, level.y + 60 , 13, -1, -1, 20);
    level.intersections[22] = Intersection(22, level.x + 68 , level.y + 84 , -1, 23, 27, -1);
    level.intersections[23] = Intersection(23, level.x + 92 , level.y + 84 , 17, 64, -1, 22);
    level.intersections[24] = Intersection(24, level.x + 116, level.y + 84 , 18, 25, -1, 64);
    level.intersections[25] = Intersection(25, level.x + 139, level.y + 84 , -1, -1, 28, 24);
    level.intersections[26] = Intersection(26, level.x + 44 , level.y + 108, 15, 27, 33, 29);
    level.intersections[27] = Intersection(27, level.x + 68 , level.y + 108, 22, -1, 30, 26);
    level.intersections[28] = Intersection(28, level.x + 139, level.y + 108, 25, 29, 31, -1);
    level.intersections[29] = Intersection(29, level.x + 164, level.y + 108, 20, 26, 38, 28);
    level.intersections[30] = Intersection(30, level.x + 68 , level.y + 132, 27, 31, 34, -1);
    level.intersections[31] = Intersection(31, level.x + 139, level.y + 132, 28, -1, 37, 30);
    level.intersections[32] = Intersection(32, level.x + 4  , level.y + 156, -1, 33, 40, -1);
    level.intersections[33] = Intersection(33, level.x + 44 , level.y + 156, 26, 34, 42, 32);
    level.intersections[34] = Intersection(34, level.x + 68 , level.y + 156, 30, 35, -1, 33);
    level.intersections[35] = Intersection(35, level.x + 92 , level.y + 156, -1, -1, 44, 34);
    level.intersections[36] = Intersection(36, level.x + 116, level.y + 156, -1, 37, 45, -1);
    level.intersections[37] = Intersection(37, level.x + 139, level.y + 156, 31, 38, -1, 36);
    level.intersections[38] = Intersection(38, level.x + 164, level.y + 156, 29, 39, 47, 37);
    level.intersections[39] = Intersection(39, level.x + 204, level.y + 156, -1, -1, 49, 38);
    level.intersections[40] = Intersection(40, level.x + 4  , level.y + 180, 32, 41, -1, -1);
    level.intersections[41] = Intersection(41, level.x + 20 , level.y + 180, -1, -1, 51, 40);
    level.intersections[42] = Intersection(42, level.x + 44 , level.y + 180, 33, 42, 52, -1);
    level.intersections[43] = Intersection(43, level.x + 68 , level.y + 180, -1, 44, 53, 42);
    level.intersections[44] = Intersection(44, level.x + 92 , level.y + 180, 35, 45, -1, 43);
    level.intersections[45] = Intersection(45, level.x + 116, level.y + 180, 36, 46, -1, 44);
    level.intersections[46] = Intersection(46, level.x + 139, level.y + 180, -1, 47, 56, 45);
    level.intersections[47] = Intersection(47, level.x + 164, level.y + 180, 38, -1, 57, 46);
    level.intersections[48] = Intersection(48, level.x + 188, level.y + 180, -1, 49, 58, -1);
    level.intersections[49] = Intersection(49, level.x + 204, level.y + 180, 39, -1, -1, 48);
    level.intersections[50] = Intersection(50, level.x + 4  , level.y + 204, -1, 51, 60, -1);
    level.intersections[51] = Intersection(51, level.x + 20 , level.y + 204, 41, 52, -1, 50);
    level.intersections[52] = Intersection(52, level.x + 44 , level.y + 204, 42, -1, -1, 51);
    level.intersections[53] = Intersection(53, level.x + 68 , level.y + 204, 43, 54, -1, -1);
    level.intersections[54] = Intersection(54, level.x + 92 , level.y + 204, -1, -1, 61, 53);
    level.intersections[55] = Intersection(55, level.x + 116, level.y + 204, -1, 56, 62, -1);
    level.intersections[56] = Intersection(56, level.x + 139, level.y + 204, 46, -1, -1, 55);
    level.intersections[57] = Intersection(57, level.x + 164, level.y + 204, 47, 58, -1, -1);
    level.intersections[58] = Intersection(58, level.x + 188, level.y + 204, 48, 59, -1, 57);
    level.intersections[59] = Intersection(59, level.x + 204, level.y + 204, -1, -1, 63, 58);
    level.intersections[60] = Intersection(60, level.x + 4  , level.y + 228, 50, 61, -1, -1);
    level.intersections[61] = Intersection(61, level.x + 92 , level.y + 228, 54, 62, -1, 60);
    level.intersections[62] = Intersection(62, level.x + 116, level.y + 228, 55, 63, -1, 61);
    level.intersections[63] = Intersection(63, level.x + 204, level.y + 228, 59, -1, -1, 62);
    level.intersections[64] = Intersection(64, level.x + 104, level.y + 84 , -1, 24, -1, 23);
}

void setup()
{
    GD.begin();
    LOAD_ASSETS(); // Load all assets.

    // split all pacMan sprites into animation cells.
    GD.BitmapHandle(PMNORTH_HANDLE);
    GD.BitmapLayout(ARGB4, 2 * 15, 15);
    GD.BitmapHandle(PMEAST_HANDLE);
    GD.BitmapLayout(ARGB4, 2 * 15, 15);
    GD.BitmapHandle(PMSOUTH_HANDLE);
    GD.BitmapLayout(ARGB4, 2 * 15, 15);
    GD.BitmapHandle(PMWEST_HANDLE);
    GD.BitmapLayout(ARGB4, 2 * 15, 15);

    Serial.begin(9600);

    MaxX = GD.w;
    MaxY = GD.h;
    level.x = MaxX/2 - 112;
    level.y = MaxY/2 - 124;
    buildMap();
    Serial.println(MaxX);
    Serial.println(MaxY);
}

void updatePlayer()
{
    // read the input on analog pin 0:
    xValue = analogRead(A13);
    yValue = analogRead(A14);

    if (xValue > 650) {
        pacMan.playerState = PMEAST_HANDLE;
    }
    if (xValue < 350) {
        pacMan.playerState = PMWEST_HANDLE;
    }
    if (yValue > 650) {
        pacMan.playerState = PMSOUTH_HANDLE;
    }
    if (yValue < 350) {
        pacMan.playerState = PMNORTH_HANDLE;
    }

    if (pacMan.playerState == PMNORTH_HANDLE) // North
    {
        if (pacMan.y > 0) {
            pacMan.y -= 0.1;
        }
    } else if (pacMan.playerState == PMEAST_HANDLE) // East
    {
        if (pacMan.x < MaxX - 15) {
            pacMan.x += 0.1;
        }
    } else if (pacMan.playerState == PMSOUTH_HANDLE) // South
    {
        if (pacMan.y < MaxY - 15) {
            pacMan.y += 0.1;
        }
    } else if (pacMan.playerState == PMWEST_HANDLE) // West
    {
        if (pacMan.x > 0) {
            pacMan.x -= 0.1;
        }
    }

    if (pacMan.animationCounter > 90)
    {
        pacMan.animationCounter = 0;
        if (pacMan.playerOpenState == 0)
        {
            pacMan.playerOpenState = 1;
        } else{
            pacMan.playerOpenState = 0;
        }
    } else {
        pacMan.animationCounter++;
    }
}
void updateGhost()
{

}

void draw()
{
    GD.Clear();
    GD.Begin(BITMAPS);
    GD.Vertex2ii(level.x, level.y, 4);    //draw map in center of screen.
    GD.Vertex2ii(pacMan.x, pacMan.y, pacMan.playerState, pacMan.playerOpenState); // draw pacMan
}
void checkSwapBuffer()
{
    currentTime = millis();
    if ((currentTime - previusTime) > (1000/60))
    {
        previusTime = currentTime;
        GD.swap();
    }
}

void loop()
{
  updatePlayer();   // update player position.
  updateGhost();    // update all ghost position.

  draw();               // draw frame.
  checkSwapBuffer();    // check and then swap frame if needed.

  delay(1);
}
