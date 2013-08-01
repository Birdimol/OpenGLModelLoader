#include "FlyingCamera.hpp"

using namespace std;

FlyingCamera::FlyingCamera(sf::Vector3f position, sf::Vector3f cible) : Camera(position,cible)
{
    angle.x = cible.x - position.x;
    angle.y = cible.y - position.y;
    angle.z = cible.z - position.z;

    vitesse_rotation = 3;
    vitesse_deplacement = 3;
}

void FlyingCamera::Avance()
{
    position.x += angle.x/10*vitesse_deplacement;
    position.z += angle.z/10*vitesse_deplacement;
    cible.x += angle.x/10*vitesse_deplacement;
    cible.z += angle.z/10*vitesse_deplacement;
}

void FlyingCamera::Monte()
{
    position.y += 0.5;
    cible.y += 0.4;
}

void FlyingCamera::Descend()
{
    position.y -= 0.5;
    cible.y -= 0.4;
}

void FlyingCamera::Recule()
{
    position.x -= angle.x/10*vitesse_deplacement;
    position.z -= angle.z/10*vitesse_deplacement;
    cible.x -= angle.x/10*vitesse_deplacement;
    cible.z -= angle.z/10*vitesse_deplacement;
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

void FlyingCamera::Tourne(sf::Vector3f vecteur)
{
    float angle_y_rad = 3.1416 * (vecteur.y) / 180.0;

    float position_relative_x = (cible.x-position.x);
    float position_relative_z = (cible.z-position.z);

    float tempX = (((position_relative_x)*cos(angle_y_rad))-((position_relative_z)*sin(angle_y_rad)));
    float tempZ = (((position_relative_x)*sin(angle_y_rad))+((position_relative_z)*cos(angle_y_rad)));

    cible.x = tempX+position.x;
    cible.z = tempZ+position.z;

    angle.x = cible.x - position.x;
    angle.y = cible.y - position.y;
    angle.z = cible.z - position.z;

//    Info();
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
