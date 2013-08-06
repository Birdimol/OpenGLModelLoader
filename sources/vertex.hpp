#ifndef DEF_VERTEX
#define DEF_VERTEX

#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <GL/gl.h>
#include <GL/glu.h>
#include <string>

#include "point3D.hpp"

class Vertex
{
    public :
    Vertex();
    Vertex(Point3D A, Point3D B, Point3D C);
    Vertex(Point3D A, Point3D B, Point3D C, GLuint texture, bool * LIGHT, bool * NORM);
    Vertex(Point3D A, Point3D B, Point3D C, GLuint texture, float coord_texture_x_1, float coord_texture_y_1, float coord_texture_x_2, float coord_texture_y_2, bool * LIGHT, bool * NORM, bool hautGauche);
    void afficher_haut_gauche_lignes();
    void afficher_bas_droite_lignes();
    void afficher_haut_gauche_texture();
    void afficher_bas_droite_texture();
    void afficher_haut_gauche_couleur();
    void afficher_couleur(float r, float g, float b);
    void changeTexture(GLuint nouvelleTexture);
    float getAltitude(float x, float z);
    void calcule_normale();
    void tracer_normale();
    void calcule_normale2();
    float get_normale_moyenne();
    void set_eclairage_normale(float valeur_pour_A, float valeur_pour_B, float valeur_pour_C);
    void Afficher(Materiel materiel, Lumiere *adresse_source_lumiere);

    private :
    Point3D A;
    Point3D B;
    Point3D C;
    GLuint texture;

    bool hautGauche;

    float monteeX;
    float monteeZ;

    float angleX;
    float angleZ;

    float normaleX;
    float normaleY;
    float normaleZ;

    float eclairage_A;
    float eclairage_B;
    float eclairage_C;

    float eclairage_normale_A;
    float eclairage_normale_B;
    float eclairage_normale_C;

    float coord_texture_x_1;
    float coord_texture_x_2;
    float coord_texture_y_1;
    float coord_texture_y_2;

    bool* LIGHT;
    bool* NORM;

};

#endif
