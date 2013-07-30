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

void Objet3D::AddAnimation(string modeleName, Lumiere *lumiere, int frameNumber)
{
    Animation temp(modeleName,lumiere, frameNumber);
    animations.push_back(temp);
}

void Objet3D::PlayAnimation(int animationNumber)
{
    if(animationNumber > 0 && animationNumber < (int)animations.size())
    {
        animations[animationNumber].Play();
        currentAnimation = animationNumber;
    }
}

void Objet3D::StopAnimation()
{
    animations[currentAnimation].Stop();
}

void Objet3D::Afficher()
{
    //glPushMatrix();
    //glRotated(angle,0,1,0);
    //glTranslated(position.x,position.y,position.z);
    bool animationFinished = animations[currentAnimation].Afficher();
    if(animationFinished)
    {
        currentAnimation = 0;
    }
    //glPopMatrix();
}
