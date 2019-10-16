#include <EEPROM.h>
#include <SPI.h>
#include <GD2.h>
#include "myassets.h"

class Player
{
public:
    Player(){x = 0.0; y = 0.0; playerState = animationCounter = 0;}
    float x, y;
    int playerState, playerOpenState, animationCounter, prevOpenState, dir;
    int 
    int powerup = 0;
};

class Ghost
{
public:
    Ghost(){}
    void draw();
    void update(){};
    float x, y;
    int ghostState;
    int dir;            // 0 = North, 1 = East, 2 = South, 3 = West, 4 = Stand.
};

class Blinky: public Ghost //red
{
  public:
    Blinky();
    void update();
};
class Pinky: public Ghost //pink
{
  public:
    Pinky(){ghostState = PINKGHOSTBIG_HANDLE; x = GD.w/2-PINKGHOSTBIG_WIDTH/2; y = 120; };
    void update();
  };
class Inky: public Ghost //blue
{
  public:
    Inky(){ghostState = BLUEGHOSTBIG_HANDLE; x = GD.w/2-BLUEGHOSTBIG_WIDTH/2 - PINKGHOSTBIG_WIDTH -3, y = 120;};
    void update();
  };
class Clyde: public Ghost //orange
{
  public:
    Clyde(){ghostState = YELLOWGHOSTBIG_HANDLE; x = GD.w/2-YELLOWGHOSTBIG_WIDTH/2 + PINKGHOSTBIG_WIDTH+3; y = 120;};
    void update();
};

class Dot
{
public:
    Dot(int ix, int iy, bool powerUp=false) {x = ix; y = iy; this->powerUp=powerUp;};
    int x, y;
    bool powerUp;
};

class Intersection
{
public:
    Intersection(){};
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
    int* neighbours[4] = {&north,&east,&south,&west};
};

class Map
{
public:
    Map(){}
    int x,y;
    Intersection intersections[65];
};

Player pacMan;
int size = 14;
float speed = 0.1;
Map level;
int xValue, yValue;
int animationCounter;
int MaxX, MaxY;
long previusTime = 0, currentTime = 0;
Ghost ghosts[4];
bool dots[26*29];

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
    level.intersections[0] =  Intersection( 0, level.x + 5  , level.y + 5  , -1,  1,  6, -1);
    level.intersections[1] =  Intersection( 1, level.x + 45 , level.y + 5  , -1,  2,  7,  0);
    level.intersections[2] =  Intersection( 2, level.x + 93 , level.y + 5  , -1, -1,  9,  1);
    level.intersections[3] =  Intersection( 3, level.x + 117, level.y + 5  , -1,  4, 10, -1);
    level.intersections[4] =  Intersection( 4, level.x + 165, level.y + 5  , -1,  5, 12,  3);
    level.intersections[5] =  Intersection( 5, level.x + 205, level.y + 5  , -1, -1, 13, -1);
    level.intersections[6] =  Intersection( 6, level.x + 5  , level.y + 37 ,  0,  7, 14, -1);
    level.intersections[7] =  Intersection( 7, level.x + 45 , level.y + 37 ,  1,  8, 15,  6);
    level.intersections[8] =  Intersection( 8, level.x + 69 , level.y + 37 , -1,  9, 16,  7);
    level.intersections[9] =  Intersection( 9, level.x + 93 , level.y + 37 ,  2, 10, -1,  8);
    level.intersections[10] = Intersection(10, level.x + 117, level.y + 37 ,  3, 11, -1,  9);
    level.intersections[11] = Intersection(11, level.x + 140, level.y + 37 , -1, 12, 19, 10);
    level.intersections[12] = Intersection(12, level.x + 165, level.y + 37 ,  4, 13, 20, 11);
    level.intersections[13] = Intersection(13, level.x + 205, level.y + 37 ,  5, -1, 21, 12);
    level.intersections[14] = Intersection(14, level.x + 5  , level.y + 61 ,  6, 15, -1, -1);
    level.intersections[15] = Intersection(15, level.x + 45 , level.y + 61 ,  7, -1, 26, 14);
    level.intersections[16] = Intersection(16, level.x + 69 , level.y + 61 ,  8, 17, -1, -1);
    level.intersections[17] = Intersection(17, level.x + 93 , level.y + 61 , -1, -1, 23, 16);
    level.intersections[18] = Intersection(18, level.x + 117, level.y + 61 , -1, 19, 24, -1);
    level.intersections[19] = Intersection(19, level.x + 140, level.y + 61 , 11, -1, -1, 18);
    level.intersections[20] = Intersection(20, level.x + 165, level.y + 61 , 12, 21, 29, -1);
    level.intersections[21] = Intersection(21, level.x + 205, level.y + 61 , 13, -1, -1, 20);
    level.intersections[22] = Intersection(22, level.x + 69 , level.y + 85 , -1, 23, 27, -1);
    level.intersections[23] = Intersection(23, level.x + 93 , level.y + 85 , 17, 64, -1, 22);
    level.intersections[24] = Intersection(24, level.x + 117, level.y + 85 , 18, 25, -1, 64);
    level.intersections[25] = Intersection(25, level.x + 140, level.y + 85 , -1, -1, 28, 24);
    level.intersections[26] = Intersection(26, level.x + 45 , level.y + 109, 15, 27, 33, 29);
    level.intersections[27] = Intersection(27, level.x + 69 , level.y + 109, 22, -1, 30, 26);
    level.intersections[28] = Intersection(28, level.x + 140, level.y + 109, 25, 29, 31, -1);
    level.intersections[29] = Intersection(29, level.x + 165, level.y + 109, 20, 26, 38, 28);
    level.intersections[30] = Intersection(30, level.x + 69 , level.y + 133, 27, 31, 34, -1);
    level.intersections[31] = Intersection(31, level.x + 140, level.y + 133, 28, -1, 37, 30);
    level.intersections[32] = Intersection(32, level.x + 5  , level.y + 157, -1, 33, 40, -1);
    level.intersections[33] = Intersection(33, level.x + 45 , level.y + 157, 26, 34, 42, 32);
    level.intersections[34] = Intersection(34, level.x + 69 , level.y + 157, 30, 35, -1, 33);
    level.intersections[35] = Intersection(35, level.x + 93 , level.y + 157, -1, -1, 44, 34);
    level.intersections[36] = Intersection(36, level.x + 117, level.y + 157, -1, 37, 45, -1);
    level.intersections[37] = Intersection(37, level.x + 140, level.y + 157, 31, 38, -1, 36);
    level.intersections[38] = Intersection(38, level.x + 165, level.y + 157, 29, 39, 47, 37);
    level.intersections[39] = Intersection(39, level.x + 205, level.y + 157, -1, -1, 49, 38);
    level.intersections[40] = Intersection(40, level.x + 5  , level.y + 181, 32, 41, -1, -1);
    level.intersections[41] = Intersection(41, level.x + 21 , level.y + 181, -1, -1, 51, 40);
    level.intersections[42] = Intersection(42, level.x + 45 , level.y + 181, 33, 42, 52, -1);
    level.intersections[43] = Intersection(43, level.x + 69 , level.y + 181, -1, 44, 53, 42);
    level.intersections[44] = Intersection(44, level.x + 93 , level.y + 181, 35, 45, -1, 43);
    level.intersections[45] = Intersection(45, level.x + 117, level.y + 181, 36, 46, -1, 44);
    level.intersections[46] = Intersection(46, level.x + 140, level.y + 181, -1, 47, 56, 45);
    level.intersections[47] = Intersection(47, level.x + 165, level.y + 181, 38, -1, 57, 46);
    level.intersections[48] = Intersection(48, level.x + 189, level.y + 181, -1, 49, 58, -1);
    level.intersections[49] = Intersection(49, level.x + 205, level.y + 181, 39, -1, -1, 48);
    level.intersections[50] = Intersection(50, level.x + 5  , level.y + 205, -1, 51, 60, -1);
    level.intersections[51] = Intersection(51, level.x + 21 , level.y + 205, 41, 52, -1, 50);
    level.intersections[52] = Intersection(52, level.x + 45 , level.y + 205, 42, -1, -1, 51);
    level.intersections[53] = Intersection(53, level.x + 69 , level.y + 205, 43, 54, -1, -1);
    level.intersections[54] = Intersection(54, level.x + 93 , level.y + 205, -1, -1, 61, 53);
    level.intersections[55] = Intersection(55, level.x + 117, level.y + 205, -1, 56, 62, -1);
    level.intersections[56] = Intersection(56, level.x + 140, level.y + 205, 46, -1, -1, 55);
    level.intersections[57] = Intersection(57, level.x + 165, level.y + 205, 47, 58, -1, -1);
    level.intersections[58] = Intersection(58, level.x + 189, level.y + 205, 48, 59, -1, 57);
    level.intersections[59] = Intersection(59, level.x + 205, level.y + 205, -1, -1, 63, 58);
    level.intersections[60] = Intersection(60, level.x + 5  , level.y + 229, 50, 61, -1, -1);
    level.intersections[61] = Intersection(61, level.x + 93 , level.y + 229, 54, 62, -1, 60);
    level.intersections[62] = Intersection(62, level.x + 117, level.y + 229, 55, 63, -1, 61);
    level.intersections[63] = Intersection(63, level.x + 205, level.y + 229, 59, -1, -1, 62);
    level.intersections[64] = Intersection(64, level.x + 105, level.y + 85 , -1, 24, -1, 23);
}
#define ggr(x,y) for(int EnVariabelSomInteKommerFinnas = 0;EnVariabelSomInteKommerFinnas<x;EnVariabelSomInteKommerFinnas++){y;} 
#define set dots[ x++ + y * 26 ] = true;
void makeDots()
{
for(int x=0; x<26; x++)
  {
    for(int y=0; y<29; y++)
    {
      dots[x+26*y]=false;
    }
  }
  int x=0;
  int y= 0;

    ggr(12,set) 
    x++;
    x++;
    ggr(12,set) 

    ggr(3,
      y++;
      dots[0 + y * 26 ] = true;
      dots[5 + y * 26 ] = true;
      dots[11 + y * 26 ] = true;
    )
    x=0;
    y++;
    ggr(26,set) 

    ggr(2,
          y++;
  
      dots[0 + y * 26 ] = true;
      dots[5 + y * 26 ] = true;
      dots[8 + y * 26 ] = true;
      )

    y++;
    x=0;
    ggr(6,set);
    ggr(2,x++);
    ggr(4,set)

    ggr(2,
        y++;
        dots[5 + y * 26 ] = true;
        dots[11 + y * 26 ] = true;
    )
    


    y++;
    x=5;
    set;
    ggr(2,x++)
    ggr(5,set)
    
    ggr(2,
      y++;
      dots[5 + y * 26 ] = true;
      dots[8 + y * 26 ] = true;
      )

    y++;
    x=5;
    ggr(4,set)

    ggr(2,
      y++;
      dots[5 + y * 26 ] = true;
      dots[8 + y * 26 ] = true;
    )

    y++; x=5;
    set;
    ggr(2,x++)
    ggr(5,set)


   ggr(2,
    y++;
      dots[5 + y * 26 ] = true;
      dots[8 + y * 26 ] = true;
    )
 
   y++;x=0;
   ggr(12,set)
  
   ggr(2,
    y++;x=0;
    dots[0 + y * 26 ] = true;
    dots[5 + y * 26 ] = true;
    dots[11 + y * 26 ] = true;
    )

    y++;x=0;
    ggr(3,set)
    ggr(2,x++)
    ggr(10,set)

    ggr(2,
      y++;
      dots[2 + y * 26 ] = true;
      dots[5 + y * 26 ] = true;
      dots[8 + y * 26 ] = true;
    )

    y++;x=0;
    ggr(6,set)
    ggr(2,x++)
    ggr(4,set)

    ggr(2,
    y++;
      dots[0 + y * 26 ] = true;
      dots[11 + y * 26 ] = true;
    )

    y++;x=0;
    ggr(24,set)
    
for(int x=0; x<13; x++)
  {
    for(int y=0; y<29; y++)
    {
      dots[25-x+26*y]=dots[x+26*y];
    }
  }
/*
  
  int current = 0;
  
  while(current < 64)
  {
    Intersection* currentIntr = &level.intersections[current];
    
      int x8= (currentIntr->x-level.x-4)/8;
      int y8 = (currentIntr->y-level.y-4)/8;

    
    for(int i=0;i<4;i++)
    {
     int index = *(currentIntr->neighbours[i]);
     Serial.println("__________________");
      delay(20);
      Serial.println(index);
    delay(20);
     if(index == -1)
      continue;
     Intersection* neighbour = &level.intersections[index];
     
      if(neighbour->index < current)
        continue;
      
      int xdif = abs(x8 - (neighbour->x-level.x-4)/8); 
      int ydif = abs(y8 - (neighbour->y-level.y-4)/8);  
      

delay(20);
Serial.println(y8);
delay(20);
Serial.println((neighbour->y-level.y-4)/8);
delay(20)    ;  
      int x=0;
      do
      {
        int y=0;
        do
        {
          //Serial.println(x8+x+(26*(y8+y)));
          dots[x8+x+(26*(y8+y))] = true;
     
          y+=1;
        }
        while(y<ydif);
        x+=1;
      }
      while(x<xdif);
      //Serial.println("__________________");
  
    }

    current++;
  }
  */
}

void drawDots()
{
  for(int x=0; x<26; x++)
  {
    for(int y=0; y<29; y++)
    {
      if(dots[x+26*y])
      {
        
        GD.Vertex2ii(level.x+4+5+x*8, level.y+4+5+y*8, DOTBIG_HANDLE);
        //GD.Vertex2ii(100,100, DOT_HANDLE);
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

    MaxX = GD.w;
    MaxY = GD.h;
    level.x = MaxX/2 - 112;
    level.y = MaxY/2 - 124;
    buildMap();
    makeDots();
    Serial.println(MaxX);
    Serial.println(MaxY);
    pacMan.x = level.intersections[26].x; pacMan.y = level.intersections[26].y;
    ghosts[0] = Blinky();
    ghosts[1] = Pinky();
    ghosts[2] = Inky();
    ghosts[3] = Clyde();
}

void updatePlayer()
{
    // read the input on analog pin 0:
    xValue = analogRead(A13);
    yValue = analogRead(A14);

    if (xValue > 650) {
        dir = 0;
        pacMan.playerState = PACMANEASTBIG_HANDLE;
    }
    if (xValue < 350) {
        dir = 1;
        pacMan.playerState = PACMANWESTBIG_HANDLE;
    }
    if (yValue > 650) {
        dir = 2;
        pacMan.playerState = PACMANSOUTHBIG_HANDLE;
    }
    if (yValue < 350) {
        dir = 3;
        pacMan.playerState = PACMANNORTHBIG_HANDLE;
    }






    if (pacMan.playerState == PACMANNORTHBIG_HANDLE) // North
    {
        if (pacMan.y > 0) {
            pacMan.y -= speed;
        }
    } else if (pacMan.playerState == PACMANEASTBIG_HANDLE) // East
    {
        if (pacMan.x < MaxX - size) {
            pacMan.x += speed;
        }
    } else if (pacMan.playerState == PACMANSOUTHBIG_HANDLE) // South
    {
        if (pacMan.y < MaxY - size) {
            pacMan.y += speed;
        }
    } else if (pacMan.playerState == PACMANWESTBIG_HANDLE) // West
    {
        if (pacMan.x > 0) {
            pacMan.x -= speed;
        }
    }

    if( pacMan.powerup > 0)
      pacMan.powerup--;

    if (pacMan.animationCounter > 5)
    {
        pacMan.animationCounter = 0;
        if (pacMan.playerOpenState == 0)
        {
            pacMan.prevOpenState = pacMan.playerOpenState;
            pacMan.playerOpenState = 1;
        } else if(pacMan.playerOpenState == 1) {
            if (pacMan.prevOpenState == 0) {
                pacMan.playerOpenState = 2;
            } else {
                pacMan.playerOpenState = 0;
            }
        } else {
            pacMan.prevOpenState = pacMan.playerOpenState;
            pacMan.playerOpenState = 1;
        }
    } else {
        pacMan.animationCounter++;
    } 
}
void updateGhosts()
{
  for(int i=0;i<4;i++)
  {
    ghosts[i].update();
  }
}
void drawGhosts()
{
  for(int i=0;i<4;i++)
  {
    ghosts[i].draw();
  }
}

void draw()
{
    GD.Clear();
    GD.Begin(BITMAPS);
    GD.Vertex2ii(level.x, level.y, 4);    //draw map in center of screen.
    GD.Vertex2ii(pacMan.x, pacMan.y, pacMan.playerState, pacMan.playerOpenState); // draw pacMan
    drawDots();
    drawGhosts();
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
  updateGhosts();    // update all ghost position.

  draw();               // draw frame.
  checkSwapBuffer();    // check and then swap frame if needed.

  delay(1);
}

void Ghost::draw()
    {
       if (pacMan.powerup > 0)
        GD.Vertex2ii(this->x,this->y,GHOSTHUNTBIG_HANDLE);
       else
        GD.Vertex2ii(this->x,this->y,this->ghostState);
    };

Blinky::Blinky() {ghostState = REDGHOSTBIG_HANDLE; x =level.intersections[64].x ; y = level.intersections[64].y ;};

void Blinky::update()
{

};
