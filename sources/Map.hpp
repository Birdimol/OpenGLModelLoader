#ifndef DEF_MAPDESURFACE
#define DEF_MAPDESURFACE

#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <GL/gl.h>
#include <GL/glu.h>
#include <string>

#include "Materiel.hpp"
#include "Tools.hpp"
#include "SurfaceDeMap.hpp"

/*

    2 5 8
  ^ 1 4 7
  X 0 3 6
    Z >

*/

class Map
{
    protected :
    vector< vector< SurfaceDeMap > > listeCases;
    int largeurX;
    int longueurZ;
    int largeurCase;
    Lumiere* lumiere;

    public :
    Map(string heightMapFile, int largeurCase_, Lumiere *adresse_source_lumiere);

    void Afficher();
    void Afficher(Materiel materiel, Lumiere *adresse_source_lumiere);
    void AfficherLigne();

    void CalculeNormaleParPoint();
    float GetAltitude(float x, float z);

    float GetLimitX();
    float GetLimitZ();
};

#endif
