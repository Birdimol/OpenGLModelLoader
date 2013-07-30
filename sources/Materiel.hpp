#ifndef DEF_MATERIEL
#define DEF_MATERIEL

#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <GL/gl.h>
#include <GL/glu.h>
#include <string>
#include <vector>

using namespace std;

class Materiel
{
    public :
    Materiel();
    Materiel(float R, float G, float B, float A, string nom);
    Materiel(float R, float G, float B, float A, string nom, string pathTexture);
    float GetR();
    float GetG();
    float GetB();
    float GetA();
    string GetNom();
    GLuint GetTexture();
    bool PossedeTexture();

    private :
    float r;
    float g;
    float b;
    float a;
    string nom;
    GLuint texture;
    bool possedeTexture;
};

#endif
