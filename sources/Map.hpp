#ifndef DEF_MAP
#define DEF_MAP

#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <GL/gl.h>
#include <GL/glu.h>
#include <string>

#include "CaseMap.hpp"

class Map
{
    protected :
    vector<CaseMap> listeCaseMaps;
    bool LIGHT ;
    bool NORM;
    int largeurX;
    int longueurZ;
    int largeurCase;


    public :
    Map(int largeur, int longueur);
    void Afficher();
    void calculNormaleParFace();
    void calculeNormaleParPoint();
};

#endif
