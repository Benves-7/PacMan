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
    Blinky(){ghostState = REDGHOST_HANDLE; x = GD.w/2-REDGHOST_WIDTH/2 ; y = 100 ;};  
    void update();
};
class Pinky: public Ghost //pink
{
  public:
    Pinky(){ghostState = PINKGHOST_HANDLE; x = GD.w/2-PINKGHOST_WIDTH/2; y = 120; };
    void update();
  };
class Inky: public Ghost //blue
{
  public:
    Inky(){ghostState = BLUEGHOST_HANDLE; x = GD.w/2-BLUEGHOST_WIDTH/2 - PINKGHOST_WIDTH -5, y = 120;};
    void update();
  };
class Clyde: public Ghost //orange
{
  public:
    Clyde(){ghostState = YELLOWGHOST_HANDLE; x = GD.w/2-YELLOWGHOST_WIDTH/2 + PINKGHOST_WIDTH+5; y = 120;};
    void update();
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
    Intersection(){}
    Intersection(int ix, int iy) { x = ix; y = iy; }
    int x, y;
};

class Map
{
public:
    Map(){}
    int x,y;
    Intersection intersections[64];
};

Player pacMan;
Map level;
int xValue, yValue;
int animationCounter;
int MaxX, MaxY;
long previusTime = 0, currentTime = 0;
Ghost ghosts[4];

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

void buildMap()
{
   
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

    if( pacMan.powerup > 0)
      pacMan.powerup--;

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
        GD.Vertex2ii(this->x,this->y,GHOSTHUNT_HANDLE);
       else
        GD.Vertex2ii(this->x,this->y,this->ghostState);
    };

void Blinky::update()
{};
