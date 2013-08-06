#ifndef DEF_MAP
#define DEF_MAP

#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <GL/gl.h>
#include <GL/glu.h>
#include <string>

#include "CaseMap.hpp"

/*

    2 5 8
  ^ 1 4 7
  X 0 3 6
    Z >

*/

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
    Map(int largeur, int longueur,int largeurCase_);
    Map(string heightMapFile, int largeurCase_);
    void Afficher();
    void Afficher(Materiel materiel, Lumiere *adresse_source_lumiere);
    float GetAltitude(float x, float z);
    void AfficherLigne();
    void AfficherCouleur();
    void calculNormaleParFace();
    void calculeNormaleParPoint();
    float GetLimitX();
    float GetLimitZ();
};

#endif
