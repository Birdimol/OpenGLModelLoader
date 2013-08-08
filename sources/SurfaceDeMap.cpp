#include "SurfaceDeMap.hpp"

SurfaceDeMap::SurfaceDeMap(Materiel materiel) : Surface(materiel)
{
}

float SurfaceDeMap::GetAltitude(float X, float Z)
{
    float altitude=listePoints[0].GetPosition().y;
    altitude += monteeX*X;
    altitude += monteeZ*Z;
    return altitude;
}

void SurfaceDeMap::CalculeMonteeEtNormale()
{
    //on calculera toujours par rapport au premier point de la surface.
    if(listePoints[0].GetPosition().x == listePoints[1].GetPosition().x)
    {
        //cette surface est le triangle :
        //  ^
        // 1|___2
        //  |  /
        // Z| /
        //  |/
        // 0 ----->
        //      X

        monteeX = listePoints[2].GetPosition().y - listePoints[1].GetPosition().y;
        monteeZ = listePoints[1].GetPosition().y - listePoints[0].GetPosition().y;

        normale = Tools::GetNormaleDeDeuxVecteurs(sf::Vector3f(listePoints[1].GetPosition().x - listePoints[2].GetPosition().x,listePoints[1].GetPosition().y - listePoints[2].GetPosition().y,listePoints[1].GetPosition().z - listePoints[2].GetPosition().z),
                                                  sf::Vector3f(listePoints[1].GetPosition().x - listePoints[0].GetPosition().x,listePoints[1].GetPosition().y - listePoints[0].GetPosition().y,listePoints[1].GetPosition().z - listePoints[0].GetPosition().z));
    }
    else
    {
        //cette surface est le triangle :
        //  ^
        //  |   1
        // Z|  /|
        //  | / |
        // 0|/  |2
        //  ------>
        //      X

        monteeX = listePoints[2].GetPosition().y - listePoints[0].GetPosition().y;
        monteeZ = listePoints[1].GetPosition().y - listePoints[2].GetPosition().y;

        normale = Tools::GetNormaleDeDeuxVecteurs(sf::Vector3f(listePoints[2].GetPosition().x - listePoints[0].GetPosition().x,listePoints[2].GetPosition().y - listePoints[0].GetPosition().y,listePoints[2].GetPosition().z - listePoints[0].GetPosition().z),
                                                  sf::Vector3f(listePoints[2].GetPosition().x - listePoints[1].GetPosition().x,listePoints[2].GetPosition().y - listePoints[1].GetPosition().y,listePoints[2].GetPosition().z - listePoints[1].GetPosition().z));
    }

    //Normale par face : égale pour tout les points
    listePoints[0].SetNormale(normale.x,normale.y,normale.z);
    listePoints[1].SetNormale(normale.x,normale.y,normale.z);
    listePoints[2].SetNormale(normale.x,normale.y,normale.z);
}

sf::Vector3f SurfaceDeMap::GetNormale()
{
    return normale;
}

void SurfaceDeMap::SetNormale(int numeroDuPoint, sf::Vector3f normale_)
{
    listePoints[numeroDuPoint].SetNormale(normale_.x,normale_.y,normale_.z);
}

bool SurfaceDeMap::EstHautGauche()
{
    if(listePoints[0].GetPosition().x == listePoints[1].GetPosition().x)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void SurfaceDeMap::Afficher(Lumiere *adresse_source_lumiere)
{
    if(materiel.PossedeTexture())
    {
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D,materiel.GetTexture());
    }
    else
    {
        glDisable(GL_TEXTURE_2D);
    }

    glColor3ub(materiel.GetR()*255,materiel.GetG()*255,materiel.GetB()*255);

    glBegin(GL_TRIANGLES);
    for(int a=0; a<3; a++)
    {
        listePoints[a].Afficher(materiel,adresse_source_lumiere);
    }
    glEnd();

    //Tools::AfficherVecteur(listePoints[0].GetPosition().x,listePoints[0].GetPosition().y,listePoints[0].GetPosition().z,sf::Vector3f(normale.x,normale.y,normale.z),255,255,255);
}

void SurfaceDeMap::AfficherLignes()
{
    int nombrePoints = listePoints.size();

    glBegin(GL_LINE_LOOP);
        for(int a=0; a<nombrePoints; a++)
        {
            listePoints[a].AfficherLignes();
        }
    glEnd();

    //Tools::AfficherVecteur(listePoints[0].GetPosition().x,listePoints[0].GetPosition().y,listePoints[0].GetPosition().z,sf::Vector3f(normale.x,normale.y,normale.z),255,255,255);
}
