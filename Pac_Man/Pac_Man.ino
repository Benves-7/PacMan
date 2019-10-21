#include <EEPROM.h>
#include <SPI.h>
#include <GD2.h>
#include "myassets.h"

class Player
{
public:
    Player(){x = 107.0; y = 181.0; playerState = PACMANWESTBIG_HANDLE ; animationCounter = 0;}
    float x, y;
    int playerState, playerOpenState, animationCounter, prevOpenState;
    int powerup = 0;
    bool idle = true;
    int dir = 3;
    int forward = 44;
    int back = 45;
};

class Ghost
{
public:
    Ghost()
    {}

    void draw();

    virtual void Update();

    void move();

    float x, y;
    int sx, sy;
    bool afraid = false;
    int ghostState;
    int goalIntersect = 64;
    int dir = 0;            // 0 = North, 1 = East, 2 = South, 3 = West, 4 = Stand.
};

class Blinky: public Ghost //red
{
public:
    Blinky()
    {
        ghostState = REDGHOSTBIG_HANDLE;
        x = 106;
        y = 86;
        sx = 106;
        sy = 110;
    };

    void Update();
};
class Pinky: public Ghost //pink
{
public:
    Pinky()
    {
        ghostState = PINKGHOSTBIG_HANDLE;
        x = 106;
        y = 110;
        sx = 106;
        sy = 110;
    };

    void Update();
};
class Inky: public Ghost //blue
{
public:
    Inky()
    {
        ghostState = BLUEGHOSTBIG_HANDLE;
        x = 106 - PINKGHOSTBIG_WIDTH - 3, y = 110;
        sx = 106;
        sy = 110;
    };

    void Update();
};
class Clyde: public Ghost //orange
{
public:
    Clyde()
    {
        ghostState = YELLOWGHOSTBIG_HANDLE;
        x = 106 + PINKGHOSTBIG_WIDTH + 3;
        y = 110;
        sx = 106;
        sy = 110;
    };

    void Update();
};

class Intersection
{
public:
    Intersection()
    {};

    Intersection(int iindex, int xpos, int ypos, int inorth, int ieast, int isouth, int iwest)
    {
        index = iindex;
        x = xpos + 1;
        y = ypos + 1;
        north = inorth;
        east = ieast;
        south = isouth;
        west = iwest;
        neighbours[0] = &north;
        neighbours[1] = &east;
        neighbours[2] = &south;
        neighbours[3] = &west;
    }

    int index;
    int x, y;
    int north, east, south, west;
    int *neighbours[4];
};

class Map
{
public:
    Map()
    {}

    int x, y;
    Intersection intersections[67];
};

Player pacMan;
Map level;
int xValue, yValue;
int animationCounter;
int MaxX, MaxY;
long previusTime = 0, currentTime = 0;
Ghost* ghosts[4];
bool dots[26*29];
int powerDots[4] = {2*26,2*26+25,21*26,21*26+25};
int points = 0;
float speed = 1/8.f;
int size = 14;

void buildMap()
{
    level.intersections[0] = Intersection(0, 4, 4, -1, 1, 6, -1);
    level.intersections[1] = Intersection(1, 44, 4, -1, 2, 7, 0);
    level.intersections[2] = Intersection(2, 92, 4, -1, -1, 9, 1);
    level.intersections[3] = Intersection(3, 116, 4, -1, 4, 10, -1);
    level.intersections[4] = Intersection(4, 164, 4, -1, 5, 12, 3);
    level.intersections[5] = Intersection(5, 204, 4, -1, -1, 13, -1);
    level.intersections[6] = Intersection(6, 4, 36, 0, 7, 14, -1);
    level.intersections[7] = Intersection(7, 44, 36, 1, 8, 15, 6);
    level.intersections[8] = Intersection(8, 68, 36, -1, 9, 16, 7);
    level.intersections[9] = Intersection(9, 92, 36, 2, 10, -1, 8);
    level.intersections[10] = Intersection(10, 116, 36, 3, 11, -1, 9);
    level.intersections[11] = Intersection(11, 139, 36, -1, 12, 19, 10);
    level.intersections[12] = Intersection(12, 164, 36, 4, 13, 20, 11);
    level.intersections[13] = Intersection(13, 204, 36, 5, -1, 21, 12);
    level.intersections[14] = Intersection(14, 4, 60, 6, 15, -1, -1);
    level.intersections[15] = Intersection(15, 44, 60, 7, -1, 26, 14);
    level.intersections[16] = Intersection(16, 68, 60, 8, 17, -1, -1);
    level.intersections[17] = Intersection(17, 92, 60, -1, -1, 23, 16);
    level.intersections[18] = Intersection(18, 116, 60, -1, 19, 24, -1);
    level.intersections[19] = Intersection(19, 139, 60, 11, -1, -1, 18);
    level.intersections[20] = Intersection(20, 164, 60, 12, 21, 29, -1);
    level.intersections[21] = Intersection(21, 204, 60, 13, -1, -1, 20);
    level.intersections[22] = Intersection(22, 68, 84, -1, 23, 27, -1);
    level.intersections[23] = Intersection(23, 92, 84, 17, 64, -1, 22);
    level.intersections[24] = Intersection(24, 116, 84, 18, 25, -1, 64);
    level.intersections[25] = Intersection(25, 139, 84, -1, -1, 28, 24);
    level.intersections[26] = Intersection(26, 44, 108, 15, 27, 33, 65);
    level.intersections[27] = Intersection(27, 68, 108, 22, -1, 30, 26);
    level.intersections[28] = Intersection(28, 139, 108, 25, 29, 31, -1);
    level.intersections[29] = Intersection(29, 164, 108, 20, 66, 38, 28);
    level.intersections[30] = Intersection(30, 68, 132, 27, 31, 34, -1);
    level.intersections[31] = Intersection(31, 139, 132, 28, -1, 37, 30);
    level.intersections[32] = Intersection(32, 4, 156, -1, 33, 40, -1);
    level.intersections[33] = Intersection(33, 44, 156, 26, 34, 42, 32);
    level.intersections[34] = Intersection(34, 68, 156, 30, 35, -1, 33);
    level.intersections[35] = Intersection(35, 92, 156, -1, -1, 44, 34);
    level.intersections[36] = Intersection(36, 116, 156, -1, 37, 45, -1);
    level.intersections[37] = Intersection(37, 139, 156, 31, 38, -1, 36);
    level.intersections[38] = Intersection(38, 164, 156, 29, 39, 47, 37);
    level.intersections[39] = Intersection(39, 204, 156, -1, -1, 49, 38);
    level.intersections[40] = Intersection(40, 4, 180, 32, 41, -1, -1);
    level.intersections[41] = Intersection(41, 20, 180, -1, -1, 51, 40);
    level.intersections[42] = Intersection(42, 44, 180, 33, 43, 52, -1);
    level.intersections[43] = Intersection(43, 68, 180, -1, 44, 53, 42);
    level.intersections[44] = Intersection(44, 92, 180, 35, 45, -1, 43);
    level.intersections[45] = Intersection(45, 116, 180, 36, 46, -1, 44);
    level.intersections[46] = Intersection(46, 139, 180, -1, 47, 56, 45);
    level.intersections[47] = Intersection(47, 164, 180, 38, -1, 57, 46);
    level.intersections[48] = Intersection(48, 188, 180, -1, 49, 58, -1);
    level.intersections[49] = Intersection(49, 204, 180, 39, -1, -1, 48);
    level.intersections[50] = Intersection(50, 4, 204, -1, 51, 60, -1);
    level.intersections[51] = Intersection(51, 20, 204, 41, 52, -1, 50);
    level.intersections[52] = Intersection(52, 44, 204, 42, -1, -1, 51);
    level.intersections[53] = Intersection(53, 68, 204, 43, 54, -1, -1);
    level.intersections[54] = Intersection(54, 92, 204, -1, -1, 61, 53);
    level.intersections[55] = Intersection(55, 116, 204, -1, 56, 62, -1);
    level.intersections[56] = Intersection(56, 139, 204, 46, -1, -1, 55);
    level.intersections[57] = Intersection(57, 164, 204, 47, 58, -1, -1);
    level.intersections[58] = Intersection(58, 188, 204, 48, 59, -1, 57);
    level.intersections[59] = Intersection(59, 204, 204, -1, -1, 63, 58);
    level.intersections[60] = Intersection(60, 4, 228, 50, 61, -1, -1);
    level.intersections[61] = Intersection(61, 92, 228, 54, 62, -1, 60);
    level.intersections[62] = Intersection(62, 116, 228, 55, 63, -1, 61);
    level.intersections[63] = Intersection(63, 204, 228, 59, -1, -1, 62);
    level.intersections[64] = Intersection(64, 104, 84, -1, 24, -1, 23);
    level.intersections[65] = Intersection(65, 4, 108, -1, 26, -1, 66);
    level.intersections[66] = Intersection(66, 204, 108, -1, 65, -1, 29);
}

#define ggr(x,y) for(int EnVariabelSomInteKommerFinnas = 0;EnVariabelSomInteKommerFinnas<x;EnVariabelSomInteKommerFinnas++){y;} 
#define set dots[ x++ + y * 26 ] = true;
void makeDots()
{
    for (int x = 0; x < 26; x++)
    {
        for (int y = 0; y < 29; y++)
        {
            dots[x + 26 * y] = false;
        }
    }

    int x = 0;
    int y = 0;

    ggr(12, set)
    x++;
    x++;
    ggr(12, set)

    ggr(3,
        y++;
                dots[0 + y * 26] = true;
                dots[5 + y * 26] = true;
                dots[11 + y * 26] = true;
    )
    x = 0;
    y++;
    ggr(26, set)

    ggr(2,
        y++;

                dots[0 + y * 26] = true;
                dots[5 + y * 26] = true;
                dots[8 + y * 26] = true;
    )

    y++;
    x = 0;
    ggr(6, set);
    ggr(2, x++);
    ggr(4, set)

    ggr(2,
        y++;
                dots[5 + y * 26] = true;
                dots[11 + y * 26] = true;
    )

    y++;
    x = 5;
    set;
    ggr(2, x++)
    ggr(5, set)

    ggr(2,
        y++;
                dots[5 + y * 26] = true;
                dots[8 + y * 26] = true;
    )

    y++;
    x = 5;
    ggr(4, set)

    ggr(2,
        y++;
                dots[5 + y * 26] = true;
                dots[8 + y * 26] = true;
    )

    y++;
    x = 5;
    set;
    ggr(2, x++)
    ggr(5, set)


    ggr(2,
        y++;
                dots[5 + y * 26] = true;
                dots[8 + y * 26] = true;
    )

    y++;
    x = 0;
    ggr(12, set)

    ggr(2,
        y++;
                x = 0;
                dots[0 + y * 26] = true;
                dots[5 + y * 26] = true;
                dots[11 + y * 26] = true;
    )

    y++;
    x = 0;
    ggr(3, set)
    ggr(2, x++)
    ggr(7, set)

    ggr(2,
        y++;
                dots[2 + y * 26] = true;
                dots[5 + y * 26] = true;
                dots[8 + y * 26] = true;
    )

    y++;
    x = 0;
    ggr(6, set)
    ggr(2, x++)
    ggr(4, set)

    ggr(2,
        y++;
                dots[0 + y * 26] = true;
                dots[11 + y * 26] = true;
    )

    y++;
    x = 0;
    ggr(24, set)

    for (int x = 0; x < 13; x++)
    {
        for (int y = 0; y < 29; y++)
        {
            dots[25 - x + 26 * y] = dots[x + 26 * y];
        }
    }
}

void drawDots()
{
    for (int x = 0; x < 26; x++)
    {
        for (int y = 0; y < 29; y++)
        {
            const int dotIndex = x+y*26;
            if (dots[dotIndex])
            {
                GD.Vertex2ii(level.x + 5 + x * 8, level.y + 5 + y * 8, DOTBIG_HANDLE);
            
              if (dotIndex == powerDots[0] ||
                  dotIndex == powerDots[1] ||
                  dotIndex == powerDots[2] ||
                  dotIndex == powerDots[3]
                      )
              {
                  GD.Vertex2ii(level.x + 5 + x * 8, level.y + 5 + y * 8, POWERUPBIG_HANDLE);
              }
            }
        }
    }
}

void setup()
{
    GD.begin();
    LOAD_ASSETS(); // Load all assets.

    // split all pacMan sprites into animation cells.
    GD.BitmapHandle(PACMANNORTHBIG_HANDLE);
    GD.BitmapLayout(ARGB4, 2 * size, size);
    GD.BitmapHandle(PACMANEASTBIG_HANDLE);
    GD.BitmapLayout(ARGB4, 2 * size, size);
    GD.BitmapHandle(PACMANSOUTHBIG_HANDLE);
    GD.BitmapLayout(ARGB4, 2 * size, size);
    GD.BitmapHandle(PACMANWESTBIG_HANDLE);
    GD.BitmapLayout(ARGB4, 2 * size, size);
    GD.BitmapHandle(REDGHOSTBIG_HANDLE);
    GD.BitmapLayout(ARGB4, 2 * size, size);
    GD.BitmapHandle(YELLOWGHOSTBIG_HANDLE);
    GD.BitmapLayout(ARGB4, 2 * size, size);
    GD.BitmapHandle(BLUEGHOSTBIG_HANDLE);
    GD.BitmapLayout(ARGB4, 2 * size, size);
    GD.BitmapHandle(PINKGHOSTBIG_HANDLE);
    GD.BitmapLayout(ARGB4, 2 * size, size);


    Serial.begin(9600);

    pacMan = Player();
    MaxX = GD.w;
    MaxY = GD.h;
    level.x = MaxX / 2 - 112;
    level.y = MaxY / 2 - 124;
    buildMap();
    makeDots();

    ghosts[0] = new Blinky();
    ghosts[1] = new Pinky();
    ghosts[2] = new Inky();
    ghosts[3] = new Clyde();
}
#define swapDirection {int temp = pacMan.forward; pacMan.forward=pacMan.back;pacMan.back=temp;}

void updatePlayer()
{
    // read the input on analog pin 0:
    xValue = analogRead(A13);
    yValue = analogRead(A14);

    if (yValue < 350)
    {
        pacMan.dir = 0;
    }
    if (xValue > 650)
    {
        pacMan.dir = 1;
    }
    if (yValue > 650)
    {
        pacMan.dir = 2;
    }
    if (xValue < 350)
    {
        pacMan.dir = 3;
    }

    Intersection forward = level.intersections[pacMan.forward];
    // pacman has reached intersection.
    if (pacMan.x == forward.x && pacMan.y == forward.y)
    {
        // player has made legal turn.
        if (pacMan.dir == 0 && forward.north != -1)
        {
            pacMan.playerState = PACMANNORTHBIG_HANDLE;
            pacMan.back = pacMan.forward;
            pacMan.forward = forward.north;
            pacMan.idle = false;
        }
        else if (pacMan.dir == 1 && forward.east != -1)
        {
            pacMan.playerState = PACMANEASTBIG_HANDLE;
            pacMan.back = pacMan.forward;
            pacMan.forward = forward.east;
            pacMan.idle = false;
        }
        else if (pacMan.dir == 2 && forward.south != -1)
        {
            pacMan.playerState = PACMANSOUTHBIG_HANDLE;
            pacMan.back = pacMan.forward;
            pacMan.forward = forward.south;
            pacMan.idle = false;
        }
        else if (pacMan.dir == 3 && forward.west != -1)
        {
            pacMan.playerState = PACMANWESTBIG_HANDLE;
            pacMan.back = pacMan.forward;
            pacMan.forward = forward.west;
            pacMan.idle = false;
        }
            // player has not made legal turn and can not continue forward.
        else
        {
            if (pacMan.playerState == 0 && forward.north == -1)
            {
                pacMan.idle = true;
                pacMan.back = pacMan.forward;
            }
            else if (pacMan.playerState == 1 && forward.east == -1)
            {
                pacMan.idle = true;
                pacMan.back = pacMan.forward;
            }
            else if (pacMan.playerState == 2 && forward.south == -1)
            {
                pacMan.idle = true;
                pacMan.back = pacMan.forward;
            }
            else if (pacMan.playerState == 3 && forward.west == -1)
            {
                pacMan.idle = true;
                pacMan.back = pacMan.forward;
            }
                // player has not made legal turn but can continue forward.
            else
            {
                if (pacMan.playerState == 0)
                {
                    pacMan.back = pacMan.forward;
                    pacMan.forward = forward.north;
                }
                else if (pacMan.playerState == 1)
                {
                    pacMan.back = pacMan.forward;
                    pacMan.forward = forward.east;
                }
                else if (pacMan.playerState == 2)
                {
                    pacMan.back = pacMan.forward;
                    pacMan.forward = forward.south;
                }
                else if (pacMan.playerState == 3)
                {
                    pacMan.back = pacMan.forward;
                    pacMan.forward = forward.west;
                }
            }
        }
    }
    else
    {
        if (forward.y == level.intersections[pacMan.back].y) // y är rätt
        {
            if (xValue > 650)
            {
                if (!(pacMan.playerState == PACMANEASTBIG_HANDLE))
                {
                    swapDirection;
                    pacMan.playerState = PACMANEASTBIG_HANDLE;
                }
                pacMan.idle = false;
            }
            else if (xValue < 350)
            {
                if (!(pacMan.playerState == PACMANWESTBIG_HANDLE))
                {
                    swapDirection;

                    pacMan.playerState = PACMANWESTBIG_HANDLE;
                }
                pacMan.idle = false;
            }
        }
        else
        {
            if (yValue > 650)
            {
                if (!(pacMan.playerState == PACMANSOUTHBIG_HANDLE))
                {
                    swapDirection;
                    pacMan.playerState = PACMANSOUTHBIG_HANDLE;
                }
                pacMan.idle = false;
            }
            else if (yValue < 350)
            {
                if (!(pacMan.playerState == PACMANNORTHBIG_HANDLE))
                {
                    swapDirection;
                    pacMan.playerState = PACMANNORTHBIG_HANDLE;
                }
                pacMan.idle = false;
            }
        }
    }

    if (!pacMan.idle)
    {
        if (pacMan.playerState == PACMANNORTHBIG_HANDLE) // North
        {
            pacMan.y -= speed;
        }
        else if (pacMan.playerState == PACMANEASTBIG_HANDLE) // East
        {
            pacMan.x += speed;
        }
        else if (pacMan.playerState == PACMANSOUTHBIG_HANDLE) // South
        {
            pacMan.y += speed;
        }
        else if (pacMan.playerState == PACMANWESTBIG_HANDLE) // West
        {
            pacMan.x -= speed;
        }
        const int dotIndex = floor((pacMan.x - 4) / 8) + floor((pacMan.y - 4) / 8) * 26;
        if (dots[dotIndex])
        {
            dots[dotIndex] = false;
            points += 50;
            if (dotIndex == powerDots[0] ||
                dotIndex == powerDots[1] ||
                dotIndex == powerDots[2] ||
                dotIndex == powerDots[3]
                    )
            {
                points += 150;
                pacMan.powerup = 1000;
            }
        }
    }

    if (pacMan.y == level.intersections[65].y)
    {
        if (pacMan.x == level.intersections[65].x - 14)
        {
            pacMan.x = level.intersections[66].x;
            pacMan.y = level.intersections[66].y;
        }
        if (pacMan.x == level.intersections[66].x + 14)
        {
            pacMan.x = level.intersections[65].x;
            pacMan.y = level.intersections[65].y;
        }
    }

    if (pacMan.powerup > 0)
        pacMan.powerup--;

    if (!pacMan.idle && pacMan.animationCounter > 5)
    {
        pacMan.animationCounter = 0;
        if (pacMan.playerOpenState == 0)
        {
            pacMan.prevOpenState = pacMan.playerOpenState;
            pacMan.playerOpenState = 1;
        }
        else if (pacMan.playerOpenState == 1)
        {
            if (pacMan.prevOpenState == 0)
            {
                pacMan.playerOpenState = 2;
            }
            else
            {
                pacMan.playerOpenState = 0;
            }
        }
        else
        {
            pacMan.prevOpenState = pacMan.playerOpenState;
            pacMan.playerOpenState = 1;
        }
    }
    else
    {
        pacMan.animationCounter++;
    }

    for (int i = 0; i < 4; ++i)
    {
        if((pacMan.x + 14 > ghosts[i]->x && pacMan.x < ghosts[i]->x + 14) && (pacMan.y + 14 > ghosts[i]->y && pacMan.y < ghosts[i]->y + 14))
        {
            if (pacMan.powerup > 0)
            {
                ghosts[i]->x = ghosts[i]->sx;
                ghosts[i]->y = ghosts[i]->sy;
                ghosts[i]->goalIntersect = 64;
                points += 100;
            }
            else
            {
                pacMan.playerState = BLACK_HANDLE;
                speed = 0.0;
            }
        }
    }

}
void drawMirrorPacMan()
{
    if(pacMan.y == level.intersections[65].y)
    {
        if (pacMan.x >= level.intersections[66].x)
        {
            int offset = pacMan.x - level.intersections[66].x;
            offset = 14 - offset;
            GD.Vertex2ii(level.x + level.intersections[65].x - offset, level.y + pacMan.y, pacMan.playerState, pacMan.playerOpenState);
        }
        else if (pacMan.x <= level.intersections[65].x)
        {
            int offset = level.intersections[65].x - pacMan.x;
            offset = 14 - offset;
            GD.Vertex2ii(level.x + level.intersections[66].x + offset, level.y + pacMan.y, pacMan.playerState, pacMan.playerOpenState);
        }
    }
}
void updateGhosts()
{
  for(int i=0;i<4;i++)
  {
    ghosts[i]->Update();
  }
}
void drawGhosts()
{
  for(int i=0;i<4;i++)
  {
    ghosts[i]->draw();
  }
}

void draw()
{
    GD.Clear();
    GD.Begin(BITMAPS);
    GD.Vertex2ii(level.x, level.y, 4);    //draw map in center of screen.
    if(pacMan.playerState == BLACK_HANDLE)
    {
        GD.Vertex2ii(level.x+pacMan.x, level.y+pacMan.y, pacMan.playerState);
    }
    else
    {
        GD.Vertex2ii(level.x+pacMan.x, level.y+pacMan.y, pacMan.playerState, pacMan.playerOpenState); // draw pacMan
    }
    drawMirrorPacMan();
    drawDots();
    drawGhosts();
    GD.cmd_text(0,0,31,0,String(points).c_str());
    GD.cmd_text(0,35,31,0,String(pacMan.forward).c_str());
    GD.Vertex2ii(level.x + level.intersections[65].x - 14, level.y + level.intersections[65].y, BLACK_HANDLE);
    GD.Vertex2ii(level.x + level.intersections[66].x + 14, level.y + level.intersections[66].y, BLACK_HANDLE);

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
  updatePlayer();    // update player position.
  updateGhosts();    // update all ghost position.

  draw();               // draw frame.
  checkSwapBuffer();    // check and then swap frame if needed.

  delay(1);
}

void Ghost::draw()
{
    if (afraid)
        GD.Vertex2ii(level.x + this->x, level.y + this->y, GHOSTHUNTBIG_HANDLE);
    else
        GD.Vertex2ii(level.x + this->x, level.y + this->y, this->ghostState, this->dir);
}
void Ghost::move()
{
    Intersection forward = level.intersections[goalIntersect];
    if (forward.y < y)
    {
        y -= speed/2;
    }
    else if(forward.y > y)
    {
        y += speed/2;
    }
    if(forward.x < x)
    {
        x -= speed/2;
    }
    else if(forward.x > x)
    {
        x += speed/2;
    }
}
int further(int* test)
{
    int retIndex = -1;
    float distans = 0.0;
    for (int i = 0; i < 4; ++i)
    {
        if (test[i] == -1)
        {
            continue;
        }
        float x = pacMan.x - level.intersections[test[i]].x;
        float y = pacMan.y - level.intersections[test[i]].y;
        float cal = sqrt(x * x + y * y);
        if (cal > distans)
        {
            distans = cal;
            retIndex = test[i];
        }
    }
    return retIndex;
}
int runAway(int current)
{
    Intersection currentIntersection = level.intersections[current];
    int dir[] = {-1, -1, -1, -1};
    if (currentIntersection.north != -1)
    {
        dir[0] = currentIntersection.north;
    }
    if (currentIntersection.east != -1)
    {
        dir[1] = currentIntersection.east;
    }
    if (currentIntersection.south != -1)
    {
        dir[2] = currentIntersection.south;
    }
    if (currentIntersection.west != -1)
    {
        dir[3] = currentIntersection.west;
    }
    return further(dir);
}
int closer(int* test, int target)
{
    int retIndex = -1;
    float distans = 10000.0;
    for (int i = 0; i < 4; ++i)
    {
        if (test[i] == -1)
        {
            continue;
        }
        float x = level.intersections[test[i]].x - level.intersections[target].x;
        float y = level.intersections[test[i]].y - level.intersections[target].y;
        float cal = sqrt(x * x + y * y);
        if (cal < distans)
        {
            distans = cal;
            retIndex = test[i];
        }
    }
    if (retIndex != -1)
    {
        return retIndex;
    }
    else
    {
        return -1;
    }
}
int PathFinder(int current, int target)
{
    Intersection currentIntersection = level.intersections[current];
    int dir[] = {-1, -1, -1, -1};
    if (currentIntersection.north != -1)
    {
        dir[0] = currentIntersection.north;
    }
    if (currentIntersection.east != -1)
    {
        dir[1] = currentIntersection.east;
    }
    if (currentIntersection.south != -1)
    {
        dir[2] = currentIntersection.south;
    }
    if (currentIntersection.west != -1)
    {
        dir[3] = currentIntersection.west;
    }
    return closer(dir, target);
}

void Clyde::Update()
{
    Intersection forward = level.intersections[goalIntersect];
    afraid = pacMan.powerup > 0 ? true : false;
    if (x == forward.x && y == forward.y)
    {
        if (afraid)
        {
            goalIntersect = runAway(goalIntersect);
        }
        else
        {
            do
            {
                dir = rand() % 4;
                if (dir == 0 && forward.north != -1)
                {
                    goalIntersect = forward.north;
                    break;
                }
                else if (dir == 1 && forward.east != -1)
                {
                    goalIntersect = forward.east;
                    break;
                }
                else if (dir == 2 && forward.south != -1)
                {
                    goalIntersect = forward.south;
                    break;
                }
                else if (dir == 3 && forward.west != -1)
                {
                    goalIntersect = forward.west;
                    break;
                }
            } while (true);
        }
    }
    else
    {
        move();
    }
}
void Blinky::Update()
{
    Intersection forward = level.intersections[goalIntersect];
    afraid = pacMan.powerup > 0 ? true : false;
    if (x == forward.x && y == forward.y)
    {
        if (afraid)
        {
            goalIntersect = runAway(goalIntersect);
        }
        else
        {
            if (goalIntersect != pacMan.back)
            {
                goalIntersect = PathFinder(goalIntersect, pacMan.back);
            }
            else
            {
                goalIntersect = pacMan.forward;
            }
        }
    }
    else
    {
        move();
    }
}
void Pinky::Update()
{
    Intersection forward = level.intersections[goalIntersect];
    afraid = pacMan.powerup > 0 ? true : false;
    if (x == forward.x && y == forward.y)
    {
        if (afraid)
        {
            goalIntersect = runAway(goalIntersect);
        }
        else
        {
            if (goalIntersect != pacMan.forward)
            {
                goalIntersect = PathFinder(goalIntersect, pacMan.forward);
            }
            else
            {
                goalIntersect = pacMan.back;
            }
        }
    }
    else
    {
        move();
    }
}
void Inky::Update()
{
    Intersection forward = level.intersections[goalIntersect];
    afraid = pacMan.powerup > 0 ? true : false;
    if (x == forward.x && y == forward.y)
    {
        if (afraid)
        {
            goalIntersect = runAway(goalIntersect);
        }
        else
        {
            int choice = rand() % 3;
            if (choice == 0)
            {
                if (goalIntersect != pacMan.back)
                {
                    goalIntersect = PathFinder(goalIntersect, pacMan.back);
                }
                else
                {
                    goalIntersect = pacMan.forward;
                }
            }
            else if (choice == 1)
            {
                if (goalIntersect != pacMan.forward)
                {
                    goalIntersect = PathFinder(goalIntersect, pacMan.forward);
                }
                else
                {
                    goalIntersect = pacMan.back;
                }
            }
            else if (choice == 2)
            {
                do
                {
                    dir = rand() % 4;
                    if (dir == 0 && forward.north != -1)
                    {
                        goalIntersect = forward.north;
                        break;
                    }
                    else if (dir == 1 && forward.east != -1)
                    {
                        goalIntersect = forward.east;
                        break;
                    }
                    else if (dir == 2 && forward.south != -1)
                    {
                        goalIntersect = forward.south;
                        break;
                    }
                    else if (dir == 3 && forward.west != -1)
                    {
                        goalIntersect = forward.west;
                        break;
                    }
                } while (true);
                Serial.println(goalIntersect);
            }
        }
    }
    else
    {
        move();
    }
}
