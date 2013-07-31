
#ifndef DEF_MODELLOADERCAMERA
#define DEF_MODELLOADERCAMERA

#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <GL/gl.h>
#include <GL/glu.h>
#include <string>

#include "Camera.hpp"

class ModelLoaderCamera : public Camera
{
    public :
    ModelLoaderCamera() : Camera(){};
    ModelLoaderCamera(int position_x, int position_y, int position_z) : Camera(position_x, position_y, position_z){};
    ModelLoaderCamera(int position_x, int position_y, int position_z, int cible_x, int cible_y, int cible_z) : Camera(position_x, position_y, position_z, cible_x, cible_y, cible_z){};
    ModelLoaderCamera(sf::Vector3f position) : Camera(position){};
    ModelLoaderCamera(sf::Vector3f position, sf::Vector3f cible) : Camera(position, cible){};

    void Bouge(sf::Vector3f vecteur);
    void HandleSfmlEvent(sf::Event Event);
    void handleSfmlRealtimeInput(const sf::Input& Input);
    void Avance();
    void Recule();
    void Monte();
    void Descend();
};

#endif
