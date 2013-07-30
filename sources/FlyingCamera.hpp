
#ifndef DEF_FLYINGCAMERA
#define DEF_FLYINGCAMERA

#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <GL/gl.h>
#include <GL/glu.h>
#include <string>

#include "Camera.hpp"

class FlyingCamera : public Camera
{
    protected :
    sf::Vector3f angle;
    int vitesse_rotation;
    int vitesse_deplacement;

    public :
    FlyingCamera() : Camera(){};
    FlyingCamera(int position_x, int position_y, int position_z) : Camera(position_x, position_y, position_z){};
    FlyingCamera(int position_x, int position_y, int position_z, int cible_x, int cible_y, int cible_z) : Camera(position_x, position_y, position_z, cible_x, cible_y, cible_z){};
    FlyingCamera(sf::Vector3f position) : Camera(position){};
    FlyingCamera(sf::Vector3f position, sf::Vector3f cible);
    FlyingCamera(sf::Vector3f position, sf::Vector3f cible, sf::Vector3f angle);

    void Tourne(sf::Vector3f vecteur);
    void StrafeDroite();
    void StrafeGauche();
    void Avance();
    void Recule();
    void Monte();
    void Descend();

    void SetAngle(sf::Vector3f angle);

    void HandleSfmlEvent(sf::Event Event);
    void handleSfmlRealtimeInput(const sf::Input& Input);

    void Info();
};

#endif


