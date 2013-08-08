#include "Avatar.hpp"

Avatar::Avatar(float position_x, float position_y, float position_z, Objet3D objet)
{
    position.x = position_x;
    position.y = position_y;
    position.z = position_z;

    objet3D = objet;

    objet3D.SetPosition(position_x,position_y,position_z);

    vitesseRotation = 1;
    vitesseDeplacement = 0.1;
    angle = 0;
    distanceCamera = 5;

    CalculVecteurDeplacement();
    CalculCameraPosition();
    objet3D.SetAngle(sf::Vector3f(0,-angle+90,0));

    enMouvement = false;
}

Avatar::Avatar(float position_x, float position_y, float position_z, Lumiere *lumiere, string fcoFileName)
{
    Objet3D temp(lumiere,  fcoFileName);
    objet3D = temp;

    position.x = position_x;
    position.y = position_y;
    position.z = position_z;

    objet3D.SetPosition(position_x,position_y,position_z);

    vitesseRotation = 1;
    vitesseDeplacement = 0.1;
    angle = 0;
    distanceCamera = 5;

    CalculVecteurDeplacement();
    CalculCameraPosition();
    objet3D.SetAngle(sf::Vector3f(0,-angle+90,0));

    enMouvement = false;
}

void Avatar::SetAngle(int angle_)
{
    if(angle_ > 360)
    {
        angle_ = angle_ % 360;
    }
    angle = angle_;
    objet3D.SetAngle(sf::Vector3f(0,angle_,0));
}

void Avatar::SetPosition(sf::Vector3f position_)
{
    position.x = position_.x;
    position.y = position_.y;
    position.z = position_.z;
    CalculVecteurDeplacement();
    CalculCameraPosition();
}

sf::Vector3f Avatar::GetPosition()
{
    return position;
}

sf::Vector3f Avatar::GetCameraPosition()
{
    return cameraPosition;
}

void Avatar::HandleSfmlRealtimeInput(const sf::Input& Input)
{
    bool mouvementDetecte = false;

    if (Input.IsKeyDown(sf::Key::D))
    {
       StrafeDroite();
       mouvementDetecte = true;
    }

    if (Input.IsKeyDown(sf::Key::Q))
    {
       StrafeGauche();
       mouvementDetecte = true;
    }

    if(Input.IsKeyDown(sf::Key::E))
    {
        Tourne(vitesseRotation);
        mouvementDetecte = true;
    }

    if(Input.IsKeyDown(sf::Key::A))
    {
        Tourne(-vitesseRotation);
        mouvementDetecte = true;
    }

    if (Input.IsKeyDown(sf::Key::Z))
    {
       Avance();
       mouvementDetecte = true;
    }

    if (Input.IsKeyDown(sf::Key::Space))
    {
       Saute();
    }

    if (Input.IsKeyDown(sf::Key::S))
    {
       Recule();
       mouvementDetecte = true;
    }

    if(mouvementDetecte)
    {
        if(enMouvement == false)
        {
            objet3D.PlayAnimation(1,true);
            enMouvement = true;
        }
    }
    else
    {
        enMouvement = false;
        objet3D.PlayAnimation(0, true);
    }
}

void Avatar::ModifyCameraDistance(float distance)
{
    distanceCamera += distance;

    if(distanceCamera < 3)
    {
        distanceCamera = 3;
    }
    CalculCameraPosition();
}

void Avatar::Avance()
{
    position.x += vecteurDeplacement.x*vitesseDeplacement;
    position.z += vecteurDeplacement.z*vitesseDeplacement;
    objet3D.SetPosition(position.x,position.y,position.z);
    CalculCameraPosition();
}

void Avatar::Recule()
{
    position.x -= vecteurDeplacement.x*vitesseDeplacement;
    position.z -= vecteurDeplacement.z*vitesseDeplacement;
    objet3D.SetPosition(position.x,position.y,position.z);
    CalculCameraPosition();
}

void Avatar::StrafeGauche()
{

}

void Avatar::StrafeDroite()
{

}

void Avatar::Saute()
{

}

void Avatar::AGenoux()
{

}

void Avatar::CalculVecteurDeplacement()
{
    float angle_y_rad = 3.1416 * (angle) / 180.0;

    vecteurDeplacement.x = (((0)*cos(angle_y_rad))-((1)*sin(angle_y_rad)));
    vecteurDeplacement.z = (((0)*sin(angle_y_rad))+((1)*cos(angle_y_rad)));
}

void Avatar::CalculCameraPosition()
{
    cameraPosition.x = position.x - (vecteurDeplacement.x*distanceCamera);
    cameraPosition.z = position.z - (vecteurDeplacement.z*distanceCamera);
    cameraPosition.y = position.y + 2 + distanceCamera;
}

void Avatar::Tourne(float angle_)
{
    angle += angle_;

    objet3D.SetAngle(sf::Vector3f(0,-angle+90,0));

    CalculVecteurDeplacement();
    CalculCameraPosition();
}

void Avatar::Afficher()
{
    objet3D.Afficher();
}

void Avatar::AfficherLignes()
{
    objet3D.AfficherLignes();
}

void Avatar::Info()
{

}
