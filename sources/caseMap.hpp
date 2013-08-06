#ifndef DEF_CASEMAP
#define DEF_CASEMAP

#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <GL/gl.h>
#include <GL/glu.h>
#include <string>

#include "vertex.hpp"


/*
    D____________________________C_
    |c                         b/|
    |                        /  c|
    |                     /      |
    |       VB         /         |
  ^ |               /            |
  X |            /               |
    |         /         VA       |
    |      /                     |
    |a  /                       |
    |/a_________________________b|
    A                            B
                Z >

*/

class CaseMap
{
    public :
    CaseMap(int x, int y);
    CaseMap(int x, int y, Vertex A, Vertex B);
    CaseMap(int x, int y, Vertex A, Vertex B, GLuint texture);
    void afficher();
    void afficher(Materiel materiel, Lumiere *adresse_source_lumiere);
    void afficherBleu();
    void afficherCouleur();
    void changeTexture(GLuint nouvelleTexture);
    float getAltitudeA(float x, float z);
    float getAltitudeB(float x, float z);
    void calcule_normale();
    void SetTexture(GLuint input_texture);
    void calcule_normale2();
    float get_normale_moyenne_HG();
    float get_normale_moyenne_BD();
    void set_eclairage_normale(float valeur_pour_A, float valeur_pour_B, float valeur_pour_C, float valeur_pour_D);

    private :
    int x;
    int y;
    Vertex A;
    Vertex B;
    GLuint texture;
};

#endif
