#include "ModelLoaderCamera.hpp"

using namespace std;

void ModelLoaderCamera::Bouge(sf::Vector3f vecteur)
{
    position = position + vecteur;
}

void ModelLoaderCamera::HandleSfmlEvent(sf::Event Event)
{
    if ((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Key::Numpad8))
    {
       SetPosition(sf::Vector3f(0,5,-1));
    }

     if ((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Key::Numpad5))
    {
       SetPosition(sf::Vector3f(0,2,-5));
    }

    if ((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Key::Numpad2))
    {
       SetPosition(sf::Vector3f(0,-5,-2));
    }

    if ((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Key::Add))
    {
       Bouge(sf::Vector3f(0,0,2));
    }

    if ((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Key::Subtract))
    {
       Bouge(sf::Vector3f(0,0,-2));
    }

    if ((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Key::Space))
    {
       Bouge(sf::Vector3f(0,2,0));
    }

    if ((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Key::V))
    {
       Bouge(sf::Vector3f(0,-2,0));
    }
}

void ModelLoaderCamera::Avance()
{
    position.z -= 1;
}

void ModelLoaderCamera::Monte()
{
    position.y += 0.5;
}

void ModelLoaderCamera::Descend()
{
    position.y -= 0.5;
}

void ModelLoaderCamera::Recule()
{
    position.z += 1;
}

void ModelLoaderCamera::handleSfmlRealtimeInput(const sf::Input& Input)
{
    if (Input.IsKeyDown(sf::Key::Add))
    {
       Avance();
    }

    if (Input.IsKeyDown(sf::Key::Numpad8))
    {
       Monte();
    }

    if (Input.IsKeyDown(sf::Key::Numpad2))
    {
       Descend();
    }

    if (Input.IsKeyDown(sf::Key::Subtract))
    {
       Recule();
    }

    if (Input.IsKeyDown(sf::Key::PageUp))
    {
       cible.y += 0.2;
       position.y += 0.2;
    }

    if (Input.IsKeyDown(sf::Key::PageDown))
    {
       cible.y -= 0.2;
       position.y -= 0.2;
    }
}

