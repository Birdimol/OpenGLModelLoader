#ifndef DEF_MODEL
#define DEF_MODEL

#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <GL/gl.h>
#include <GL/glu.h>
#include <string>
#include <vector>

#include "Model.hpp"
#include "Point3D.hpp"
#include "Surface.hpp"
#include "Materiel.hpp"
#include "Lumiere.hpp"

using namespace std;

class Model
{
    public :
    Model();
    Model(vector<Surface> listeSurfaces);
    void AjouterSurface(Surface nouvelleSurface);
    void AfficherLignes();
    void Afficher();
    int ChargerModele(string nomFichier);
    void Debug();
    void LieLumiere(Lumiere *lumiere);
    sf::Vector3f GetAngle();
    void SetAngle(sf::Vector3f input_angle);
    void SetAngle(float x, float y, float z);
    void setPosition(float x, float y, float z);
    void Tourne(sf::Vector3f input_angle);

    private :
    Materiel GetMateriel(string nom);
    vector<Surface> listeSurfaces;
    vector<Materiel> listeMateriel;
    Lumiere *source_lumiere;

    sf::Vector3f angle;
    sf::Vector3f position;
};

#endif
