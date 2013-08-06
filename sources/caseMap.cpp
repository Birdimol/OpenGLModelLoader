#include "caseMap.hpp"
using namespace std;

CaseMap::CaseMap(int input_x, int input_y)
{
    x = input_x;
    y = input_y;
}

CaseMap::CaseMap(int input_x, int input_y, Vertex input_A, Vertex input_B)
{
    x = input_x;
    y = input_y;
    A = input_A;
    B = input_B;
}

CaseMap::CaseMap(int input_x, int input_y, Vertex input_A, Vertex input_B, GLuint input_texture)
{
    x = input_x;
    y = input_y;
    A = input_A;
    B = input_B;
    texture = input_texture;
}

void CaseMap::changeTexture(GLuint nouvelleTexture)
{
    A.changeTexture(nouvelleTexture);
    B.changeTexture(nouvelleTexture);
}

void CaseMap::afficherCouleur()
{
    A.afficher_couleur(0/255,102.0/255.0,0/255);
    B.afficher_couleur(0/255,102.0/255.0,0/255);
}

void CaseMap::afficher(Materiel materiel, Lumiere *adresse_source_lumiere)
{
    A.Afficher(materiel,adresse_source_lumiere);
    B.Afficher(materiel,adresse_source_lumiere);
}

void CaseMap::afficher()
{
    if(glIsEnabled(GL_TEXTURE_2D))
    {
        glColor3d(1,1,1);
        A.afficher_haut_gauche_texture();
        B.afficher_bas_droite_texture();
    }
    else
    {
        glColor3d(1,0,0);
        A.afficher_haut_gauche_lignes();
        B.afficher_bas_droite_lignes();
    }
    /*
    glColor3d(0,1,0);
    A.tracer_normale();
    B.tracer_normale();
    */
}

float CaseMap::get_normale_moyenne_HG()
{
    return A.get_normale_moyenne();
}

float CaseMap::get_normale_moyenne_BD()
{
    return B.get_normale_moyenne();
}

void CaseMap::set_eclairage_normale(float valeur_pour_A, float valeur_pour_B, float valeur_pour_C, float valeur_pour_D)
{
    A.set_eclairage_normale(valeur_pour_A,valeur_pour_B,valeur_pour_C);
    B.set_eclairage_normale(valeur_pour_A,valeur_pour_C,valeur_pour_D);
}

void CaseMap::afficherBleu()
{
    if(glIsEnabled(GL_TEXTURE_2D))
    {
        glColor3d(0.5,0.5,1);
        A.afficher_haut_gauche_texture();
        B.afficher_bas_droite_texture();
    }
    else
    {
        glColor3d(0,0,1);
        A.afficher_haut_gauche_lignes();
        B.afficher_bas_droite_lignes();
    }
}

/*

    Voila comment que c'est

   X ^
     |
    d|___c
     |B /|
     | / |
     |/ A|
     ------------------>
    a    b             Z

*/

float CaseMap::getAltitudeA(float input_x, float input_z)
{
    return A.getAltitude(input_x,input_z);
}

float CaseMap::getAltitudeB(float input_x, float input_z)
{
    return B.getAltitude(input_x,input_z);
}

void CaseMap::calcule_normale()
{
    A.calcule_normale();
    B.calcule_normale();
}

void CaseMap::calcule_normale2()
{
    A.calcule_normale2();
    B.calcule_normale2();
}
