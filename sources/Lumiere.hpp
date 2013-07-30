#ifndef DEF_LUMIERE
#define DEF_LUMIERE

#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <GL/gl.h>
#include <GL/glu.h>
#include <string>

#include "Materiel.hpp"

class Lumiere
{
    public :
    Lumiere(float x, float y, float z, float lumiereMinimum);

    float x;
    float y;
    float z;

    float lumiereMinimum;

};

#endif

