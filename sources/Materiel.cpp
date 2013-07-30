#include "Tools.hpp"
#include "Materiel.hpp"

Materiel::Materiel()
{

}

Materiel::Materiel(float input_R, float input_G, float input_B, float input_A, string input_nom)
{
    r = input_R;
    g = input_G;
    b = input_B;
    a = input_A;
    nom = input_nom;

    texture = 0;
    possedeTexture = false;
//    cout << nom << " : materiel sans texture" << endl;
}

Materiel::Materiel(float input_R, float input_G, float input_B, float input_A, string input_nom, string pathTexture)
{
    r = input_R;
    g = input_G;
    b = input_B;
    a = input_A;
    nom = input_nom;

    texture = Tools::chargerTexture("./modeles/textures/" + pathTexture);
    possedeTexture = true;
   // cout << nom << " : materiel avec texture" << endl;
}

float Materiel::GetR()
{
    return r;
}

float Materiel::GetG()
{
    return g;
}

float Materiel::GetB()
{
    return b;
}

float Materiel::GetA()
{
    return a;
}

GLuint Materiel::GetTexture()
{
    return texture;
}

string Materiel::GetNom()
{
    return nom;
}

bool Materiel::PossedeTexture()
{
    return possedeTexture;
}

