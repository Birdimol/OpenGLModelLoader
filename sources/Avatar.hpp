#ifndef DEF_AVATAR
#define DEF_AVATAR

#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <GL/gl.h>
#include <GL/glu.h>
#include <string>
#include "Objet3D.hpp"

class Avatar
{
    private :
    sf::Vector3f position;
    sf::Vector3f cameraPosition;
    Objet3D objet3D;
    int angle;
    float vitesseRotation;
    float vitesseDeplacement;
    sf::Vector3f vecteurDeplacement;
    void Avance();
    void Recule();
    void StrafeGauche();
    void StrafeDroite();
    void Saute();
    void AGenoux();
    void Tourne(float angle);
    void CalculCameraPosition();
    void CalculVecteurDeplacement();
    float distanceCamera;
    bool enMouvement;

    public :
    Avatar(float position_x, float position_y, float position_z, Objet3D objet);
    Avatar(float position_x, float position_y, float position_z, Lumiere *lumiere, string fcoFileName);


    void SetPosition(sf::Vector3f position);
    void SetAngle(int angle);
    sf::Vector3f GetPosition();
    sf::Vector3f GetCameraPosition();
    void ModifyCameraDistance(float distance);

    void Afficher();
    void AfficherLignes();

    void HandleSfmlRealtimeInput(const sf::Input& Input);
    void Info();
};

#endif
