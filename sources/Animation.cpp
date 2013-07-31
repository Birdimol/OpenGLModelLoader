
#include "Animation.hpp"

using namespace std;

Animation::Animation(string modeleName, Lumiere *lumiere, int frameNumber)
{
    modify(modeleName,lumiere,frameNumber);
}

void Animation::SetAngle(sf::Vector3f input_angle)
{
    for(int a =0; a< (int)modeles.size();a++)
    {
        modeles[a].SetAngle(input_angle);
    }
}

void Animation::SetAngle(float x, float y, float z)
{
    for(int a =0; a< (int)modeles.size();a++)
    {
        modeles[a].SetAngle(x,y,z);
    }
}

void Animation::modify(string modeleName, Lumiere *lumiere, int frameNumber)
{
    vector<Model> temp(frameNumber);
    playedFrameNumber = 0;
    loop = false;
    frameDelay =( 1.0/24.0);
    playing = false;

    if(frameNumber == 1)
    {
        temp[0].ChargerModele(modeleName);
        temp[0].LieLumiere(lumiere);
        temp[0].setPosition(0,0,0);
    }
    else
    {
        for(int i=0; i<frameNumber; i++)
        {
            string numero_modele = Tools::IntToString(i+1);
            while(numero_modele.length() < 6)
            {
                numero_modele = "0"+numero_modele;
            }
            temp[i].ChargerModele(modeleName+"_"+numero_modele);
            temp[i].LieLumiere(lumiere);
            temp[i].setPosition(0,0,0);
        }
    }
    modeles.clear();
    modeles = temp;
}

void Animation::Play(bool loop_)
{
    loop = loop_;
    playedFrameNumber = 0;
    clock.Reset();
    playing = true;
}

void Animation::Play()
{
    loop = false;
    playedFrameNumber = 0;
    clock.Reset();
    playing = true;
}

void Animation::Stop()
{
    playedFrameNumber = 0;
    playing = false;
}

bool Animation::Afficher(bool showLines)
{
    bool animationFinished=false;
    if(modeles.size() > 1 && playing)
    {
        if(clock.GetElapsedTime() > frameDelay)
        {
            playedFrameNumber++;
            clock.Reset();
        }

        if(playedFrameNumber >= (int)modeles.size())
        {
            if(loop)
            {
                playedFrameNumber=0;
            }
            else
            {
                Stop();
                animationFinished = true;
            }
        }
    }

    if(showLines)
    {
        modeles[playedFrameNumber].AfficherLignes();
    }
    else
    {
        modeles[playedFrameNumber].Afficher();
    }

    return animationFinished;
}
