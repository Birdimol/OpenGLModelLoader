#ifndef DEF_MAP
#define DEF_MAP

#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <GL/gl.h>
#include <GL/glu.h>
#include <string>

#include "Model.hpp"

class Map
{
    protected :
    vector<Model> listeModels;

    public :
    Map();
    void Afficher();
};

#endif
