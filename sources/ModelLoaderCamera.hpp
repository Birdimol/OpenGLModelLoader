
#ifndef DEF_MODELLOADERCAMERA
#define DEF_MODELLOADERCAMERA

#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <GL/gl.h>
#include <GL/glu.h>
#include <string>

#include "Camera.hpp"

/*!
* \class ModelLoaderCamera ModelLoaderCamera.hpp
* \brief Cette camera est une camera qui fixe un objectif, elle ne permet pas de se déplacer librement mais est pratique pour visionner des modeles.
* \author Favay Thomas
*
* Elle permet de se rapprocher, s'éloigner regarder de haut, d'en bas et de monter et descendre.
*/
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
