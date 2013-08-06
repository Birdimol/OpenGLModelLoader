#include "Objet3d.hpp"

Objet3D::Objet3D()
{
    position.x = 0;
    position.y = 0;
    position.z = 0;
    angle = 0;
    currentAnimation = 0;
}

Objet3D::Objet3D(Lumiere *lumiere, float posx, float posy, float posz, float angle_)
{
    position.x = posx;
    position.y = posy;
    position.z = posz;

    angle = angle_;

    currentAnimation = 0;

    Animation temp("canard",lumiere, 1);

    animations.push_back(temp);

    temp.modify("canard_qui_salue",lumiere, 24);
    animations.push_back(temp);
}

Objet3D::Objet3D(Lumiere *lumiere, float posx, float posy, float posz)
{
    position.x = posx;
    position.y = posy;
    position.z = posz;

    currentAnimation = 0;

    Animation temp("canard",lumiere, 1);
    animations.push_back(temp);

    temp.modify("canard_qui_salue",lumiere, 24);
    animations.push_back(temp);
}

string Objet3D::GetCurrentAnimationName()
{
    return animations[currentAnimation].GetName();
}

void Objet3D::SetPosition(float posx, float posy, float posz)
{
    position.x = posx;
    position.y = posy;
    position.z = posz;
}

Objet3D::Objet3D(Lumiere *lumiere, string modeleName,int frameNumber)
{
    position.x = 0;
    position.y = 0;
    position.z = 0;

    currentAnimation = 0;

    AddAnimation(modeleName, lumiere, frameNumber);
}

Objet3D::Objet3D(Lumiere *lumiere, string fcoFileName)
{
    position.x = 0;
    position.y = 0;
    position.z = 0;

    currentAnimation = 0;

    map<string, string> fcoAsMap = Tools::getFcoAsMap(fcoFileName);

    //animation "de base"
    AddAnimation(fcoAsMap["basicAnimation"], lumiere, Tools::StringToInt(fcoAsMap["basicAnimationFrameNumber"]));
    animations[0].SetName(fcoAsMap["basicAnimationName"]);

    for(int a=1; a<=Tools::StringToInt(fcoAsMap["animationNumber"]); a++)
    {
        AddAnimation(fcoAsMap["Animation"+Tools::IntToString(a)], lumiere, Tools::StringToInt(fcoAsMap["Animation"+Tools::IntToString(a)+"FrameNumber"]));
        animations[a].SetName(fcoAsMap["Animation"+Tools::IntToString(a)+"Name"]);
    }

    //on joue l'animation de base
    PlayAnimation(0,true);
}

void Objet3D::AddAnimation(string modeleName, Lumiere *lumiere, int frameNumber)
{
    Animation temp(modeleName,lumiere, frameNumber);
    animations.push_back(temp);
}

void Objet3D::PlayAnimation(int animationNumber, bool repeat)
{
    if(animationNumber < (int)animations.size())
    {
        animations[animationNumber].Play(repeat);
        currentAnimation = animationNumber;
    }
}

void Objet3D::StopAnimation()
{
    animations[currentAnimation].Stop();
}

void Objet3D::SetAngle(sf::Vector3f input_angle)
{
    angle = input_angle.y;
    /*
    for(int a =0; a< (int)animations.size();a++)
    {
        animations[a].SetAngle(input_angle);
    }*/
}

void Objet3D::SetAngle(float x, float y, float z)
{
    angle = y;
    /*
    for(int a =0; a< (int)animations.size();a++)
    {
        animations[a].SetAngle(x,y,z);
    }*/
}

void Objet3D::Afficher()
{
    glPushMatrix();
    glTranslatef(position.x,position.y,position.z);
    glRotated(angle,0,1,0);

    bool animationFinished = animations[currentAnimation].Afficher(false);
    if(animationFinished)
    {
        currentAnimation = 0;
    }

    glPopMatrix();
}

void Objet3D::AfficherLignes()
{
    //glPushMatrix();
    //glRotated(angle,0,1,0);
    //glTranslated(position.x,position.y,position.z);
    glPushMatrix();
    glTranslatef(position.x,position.y,position.z);
    glRotated(angle,0,1,0);

    bool animationFinished = animations[currentAnimation].Afficher(true);
    if(animationFinished)
    {
        currentAnimation = 0;
    }
    //glPopMatrix();

    glPopMatrix();
}
