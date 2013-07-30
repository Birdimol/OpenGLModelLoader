#ifndef DEF_CAMERA
#define DEF_CAMERA

#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <GL/gl.h>
#include <GL/glu.h>
#include <string>

class Camera
{
    protected :
    sf::Vector3f position;
    sf::Vector3f cible;

    public :
    Camera();
    Camera(int position_x, int position_y, int position_z);
    Camera(int position_x, int position_y, int position_z, int cible_x, int cible_y, int cible_z);
    Camera(sf::Vector3f position );
    Camera(sf::Vector3f position, sf::Vector3f cible);

    void SetPosition(sf::Vector3f position);
    sf::Vector3f GetPosition();

    void SetCible(sf::Vector3f cible);
    sf::Vector3f GetCible();

    void HandleSfmlEvent(sf::Event Event);

    void LookAt();

    void InitGluPerspective();

    void Info();
};

#endif


