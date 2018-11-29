#ifndef FUNCIONES_H
#define FUNCIONES_H

#include <iostream>
#include <utility>
#include <vector>
#include <list>
#include <cmath>
#include <deque>
#include <fstream>
#include <time.h>
//Inclucion de libreria Allegro
#include "allegro5/allegro_acodec.h"
#include "allegro5/allegro_audio.h"
#include "allegro5/color.h"
#include "allegro5/bitmap.h"
#include "allegro5/allegro_image.h"
#include "allegro5/allegro_font.h"
#include "allegro5/allegro_ttf.h"
#include "allegro5/allegro_primitives.h"
#include "allegro5/allegro.h"

#define X_MAX 600
#define Y_MAX 600



using namespace std;

typedef float rasmus;

typedef pair<rasmus,rasmus> punto;



class Rectangle
{

public:
    //a,y---------.
    //|           |
    //|           |
    //.---------b,x
    punto m_A;//uper left
    punto m_B;//lower right


    Rectangle(punto a, punto b);
    void Drow(ALLEGRO_COLOR color);
};

bool overlapRectangle(Rectangle* a, Rectangle* b);


class Nodo
{
public:
    vector<Rectangle*> m_rectangles;
    vector<Nodo*> m_childs;
    Nodo* m_padre;
    int m_cant;
    int m_level;
    Nodo();
    void Child_to_leaf();
    bool m_leaf = false;
};

class RTree
{
public:
    int m_M;
    int m_m;
    Nodo* m_head;
    RTree(int M);
    Rectangle* representative;
    void m_Datos();
    Nodo* Split(Nodo* N);
    Nodo* Split_no_leaf(Nodo* N);

    void Inssert(Rectangle* R);
    void Print(Nodo *n);
    void Search(Rectangle* R, Nodo *n);

};

//Funciones otras
int eval(vector<rasmus> v,int metodo);
bool isInside(Rectangle* a, punto k);
bool colide(Rectangle* a, Rectangle* b);
rasmus area(Rectangle* R);
Rectangle* Fuse(Rectangle* A, Rectangle* B);
Rectangle* Resize(Nodo* X);
void RefusePadres(Nodo* N);
void ReParent(Nodo* N);
vector<Rectangle*> RandRectangleGenerator(int n);

//n, nodo minimal boundary range
void IndexPublishing(RTree Rt, int a, int b, int aa, int bb);
void GraficarServer(int x, int y);
void GraficarMetaServer(int x, int y, int size);


class SN
{

public:
    //a,y---------.
    //|           |
    //|           |
    //.---------b,x
    punto position;//uper left
    int size_graf;//lower right


    SN(punto a, int size);
    void Drow();
};




#endif // FUNCIONES_H
