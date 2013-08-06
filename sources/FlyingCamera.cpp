#include "FlyingCamera.hpp"

using namespace std;

FlyingCamera::FlyingCamera(sf::Vector3f position, sf::Vector3f cible) : Camera(position,cible)
{
    angle.x = 0;
    angle.y = 0;
    angle.z = 0;

    vecteurDeplacement.x = 0;
    vecteurDeplacement.y = 0;
    vecteurDeplacement.z = 1;

    vitesse_rotation = 3;
    vitesse_deplacement = 0.1;

    CalculeCible();
}

void FlyingCamera::Avance()
{
    position.x += vecteurDeplacement.x/10*vitesse_deplacement;
    position.z += vecteurDeplacement.z/10*vitesse_deplacement;
    CalculeCible();
}

void FlyingCamera::AvanceX()
{
    position.x += vecteurDeplacement.x/10*vitesse_deplacement;
    CalculeCible();
}

void FlyingCamera::AvanceZ()
{
    position.z += vecteurDeplacement.z/10*vitesse_deplacement;
    CalculeCible();
}

void FlyingCamera::Monte()
{
    position.y += 0.5;
    cible.y += 0.4;
}

void FlyingCamera::Monte(float distance)
{
    position.y += distance;
    cible.y += distance;
}

void FlyingCamera::Descend()
{
    position.y -= 0.5;
    cible.y -= 0.4;
}

void FlyingCamera::Recule()
{
    position.x -= vecteurDeplacement.x/10*vitesse_deplacement;
    position.z -= vecteurDeplacement.z/10*vitesse_deplacement;
    CalculeCible();
}

sf::Vector3f FlyingCamera::getAngle()
{
    return angle;
}

void FlyingCamera::StrafeDroite()
{
    Tourne(sf::Vector3f(0,90,0));
    Avance();
    Tourne(sf::Vector3f(0,-90,0));
}

void FlyingCamera::StrafeGauche()
{
    Tourne(sf::Vector3f(0,-90,0));
    Avance();
    Tourne(sf::Vector3f(0,90,0));
}

void FlyingCamera::CalculeCible()
{
    //par défaut on regarde vers z+
    float position_relative_x = 0;
    float position_relative_z = 10;

    float angle_y_rad = 3.1416 * (angle.y) / 180.0;

    float tempX = (((position_relative_x)*cos(angle_y_rad))-((position_relative_z)*sin(angle_y_rad)));
    float tempZ = (((position_relative_x)*sin(angle_y_rad))+((position_relative_z)*cos(angle_y_rad)));

    cible.x = tempX+position.x;
    cible.z = tempZ+position.z;

    vecteurDeplacement.x =  cible.x - position.x;
    vecteurDeplacement.z =  cible.z - position.z;
}

void FlyingCamera::Tourne(sf::Vector3f angle_)
{
    angle.y += angle_.y;
    CalculeCible();
}

void FlyingCamera::SetAngle(sf::Vector3f angle_)
{
    angle = angle_;
}

void FlyingCamera::Info()
{
    cout << "-------------------------" << endl;
    cout << "INFO CAMERA" << endl;
    cout << "Position : " << position.x << ", " << position.y << ", " << position.z << endl;
    cout << "Cible : " << cible.x << ", " << cible.y << ", " << cible.z << endl;
    cout << "Angle : " << angle.x << ", " << angle.y << ", " << angle.z << endl;
    cout << "-------------------------" << endl;
}

void FlyingCamera::HandleSfmlEvent(sf::Event Event)
{
    if ((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Key::D))
    {
       StrafeDroite();
    }

    if ((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Key::Q))
    {
       StrafeGauche();
    }
}

void FlyingCamera::handleSfmlRealtimeInput(const sf::Input& Input)
{

    if (Input.IsKeyDown(sf::Key::D))
    {
       StrafeDroite();
    }

    if (Input.IsKeyDown(sf::Key::Q))
    {
       StrafeGauche();(sf::Vector3f(0,-vitesse_rotation,0));
    }

    if(Input.IsKeyDown(sf::Key::E))
    {
        Tourne(sf::Vector3f(0,vitesse_rotation,0));
    }

    if(Input.IsKeyDown(sf::Key::A))
    {
        Tourne(sf::Vector3f(0,-vitesse_rotation,0));
    }

    if (Input.IsKeyDown(sf::Key::Z))
    {
       Avance();
    }

    if (Input.IsKeyDown(sf::Key::Space))
    {
       Monte();
    }

    if (Input.IsKeyDown(sf::Key::N))
    {
       Descend();
    }

    if (Input.IsKeyDown(sf::Key::S))
    {
       Recule();
    }
}
