#ifndef DEF_OBJET3D
#define DEF_OBJET3D

#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <GL/gl.h>
#include <GL/glu.h>
#include <string>
#include <vector>

#include "Animation.hpp"

using namespace std;

/*!
* \class Objet3D Objet3D.hpp
* \brief Cette classe représente tout objet 3d utilisé, ce dernier est considéré comme un ensemble d'animation (avec une par défaut).
* \author Favay Thomas
*
* Elle permet de gérer les animations, la position, l'angle et le mode d'affichage.
*/
class Objet3D
{
    public :
    Objet3D();
    Objet3D(Lumiere *lumiere, string modeleName,int frameNumber);
    Objet3D(Lumiere *lumiere, float posx, float posy, float posz);
    Objet3D(Lumiere *lumiere, float posx, float posy, float posz, float angle_);
    Objet3D(Lumiere *lumiere, string fcoFileName);
    void SetAngle(sf::Vector3f input_angle);
    void SetAngle(float x, float y, float z);
    void PlayAnimation(int animationNumber);
    void StopAnimation();
    void AddAnimation(string modeleName, Lumiere *lumiere, int frameNumber);
    void Afficher();
    void AfficherLignes();
    void SetPosition(float posx, float posy, float posz);


    private :
    vector<Animation> animations;
    sf::Vector3f position;
    int currentAnimation;
    float angle;
};

#endif

