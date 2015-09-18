
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <X11/Xlib.h>

#define EventMask (KeyPressMask | ExposureMask)

#define PI 3.1415926535

float XWMax, XWMin, YWMax, YWMin;  // Valores das coordenadas que definem o universo

struct Window {
  float xmin,
        xmax,
        ymin,
        ymax;
        };
      
typedef struct Window window;

struct ViewPort {
  int xmin,
      xmax,
      ymin,
      ymax;
      };
      
typedef struct Viewport viewport;

struct Point2D {
  float x,
        y;
  int   color;
  };
      
typedef struct Point2D point;

struct Object2D {
  int numbers_of_points;
  point * points;
  };
  
typedef struct Object2D object; 

struct Color {
  float red,
        green,
        blue;
        };
      
typedef struct Color ColorValues;    
  
struct Palette {
  int numbers_of_colors;
  ColorValues * colors;
  };

typedef struct Palette palette;

struct Buffer {
  int MaxX,
      MaxY;
  int * buffer;
  };

typedef struct Buffer bufferdevice;

void SetWorld(float, float, float, float);              //DONE
point * SetPoint(float, float, int);                    //DONE
object * CreateObject(int);                             //DONE
object * CreateCircle(float,int);                       //TODO
int SetObject(point *, object *);                       //TODO
object * ChangeColor(object *, int);                    //TODO
palette * CreatePalette(int);                           //DONE
int SetColor(float, float, float, palette *);           //TODO
ColorValues * GetColor(int, palette *);                 //TODO
bufferdevice * CreateBuffer(int, int);                  //TODO
window * CreateWindow(float, float, float, float);      //TODO
point * Sru2Srn(point *, window *);                     //TODO
point * Srn2Srd(point *, bufferdevice *);               //TODO
int InWin(point *, window *);                           //TODO
point * InterX(point *, point *, float);                //TODO
point * InterY(point *, point *, float);                //TODO
int DrawLine(point *, point *, window *, bufferdevice *, int);  //TODO
int DrawObject(object *, window *, bufferdevice *);     //TODO
int Fill(object *, window *, bufferdevice *, int);      //TODO
object * Rotate(object *, float);                       //TODO
object * Translate(object *, float, float);             //TODO
object * Scale(object *, float, float);                 //TODO
ColorValues * RGB2HSV(ColorValues *);                   //TODO
ColorValues * HSV2RGB(ColorValues *);                   //TODO
int DumpX(bufferdevice *, palette *);                   //TODO

