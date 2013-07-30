#include "Camera.hpp"

using namespace std;

Camera::Camera()
{
    InitGluPerspective();
    //positionnement par défaut
    position = sf::Vector3f(0,2,-3);
    cible = sf::Vector3f(0,1,0);
}

Camera::Camera(int position_x, int position_y, int position_z)
{
    InitGluPerspective();
    //positionnement par défaut
    position = sf::Vector3f(position_x,position_y,position_z);
    cible = sf::Vector3f(0,1,0);
}

Camera::Camera(int position_x, int position_y, int position_z, int cible_x, int cible_y, int cible_z)
{
    InitGluPerspective();
    //positionnement par défaut
    position = sf::Vector3f(position_x,position_y,position_z);
    cible = sf::Vector3f(cible_x,cible_y,cible_z);
}

Camera::Camera(sf::Vector3f position_)
{
    position = position_;
    cible = sf::Vector3f(0,1,0);
    InitGluPerspective();
}

Camera::Camera(sf::Vector3f position_, sf::Vector3f cible_)
{
    position = position_;
    cible = cible_;
    InitGluPerspective();
}

void Camera::SetPosition(sf::Vector3f nouvelle_position)
{
    position = nouvelle_position;
}

void Camera::SetCible(sf::Vector3f nouvelle_cible)
{
    cible = nouvelle_cible;
}

void Camera::Info()
{
    cout << "INFO CAMERA" << endl;
    cout << "Position : " << position.x << ", " << position.y << ", " << position.z << endl;
    cout << "Cible : " << cible.x << ", " << cible.y << ", " << cible.z << endl;
    cout << "-------------------------" << endl;
}

sf::Vector3f Camera::GetPosition()
{
    return position;
}

sf::Vector3f Camera::GetCible()
{
    return cible;
}

void Camera::LookAt()
{
    gluLookAt(position.x,position.y,position.z,cible.x,cible.y,cible.z,0,1,0);
}

void Camera::HandleSfmlEvent(sf::Event Event)
{

}

void Camera::InitGluPerspective()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(70.f, 1.f, 0.01f, 500.f);
}

