#include "Map.hpp"

Map::Map(string heightMapFile, int largeurCase_, Lumiere *adresse_source_lumiere)
{
    lumiere = adresse_source_lumiere;

    sf::Image Image;
    if (!Image.LoadFromFile("images/"+heightMapFile+".png"))
    {
        // Error...
    }

    Materiel materielHerbe(1,1,1,0,"herbe","herbe.png");

    largeurX = Image.GetWidth()-1;
    longueurZ = Image.GetHeight()-1;

    cout << "longueurZ map : " << longueurZ << endl;
    cout << "largeurX map : " << largeurX << endl;

    float altitude_max = 40;

    float tableau_points[largeurX][longueurZ];

    for(int x=0; x<=largeurX;x++)
    {
        for(int z=0; z<=longueurZ;z++)
        {
            tableau_points[x][z] = Image.GetPixel(x,z).r*(1/255.f*altitude_max);
        }
    }
    largeurCase = largeurCase_;

    for(int z=0;z<longueurZ;z++)
    {
        for(int x=0;x<largeurX;x++)
        {
            Point3D A(x*largeurCase    , tableau_points[x][z]    ,  z*largeurCase   , 0,1,0, 0,0, 1,1,1,0);
            Point3D B(x*largeurCase    , tableau_points[x][z+1]  , (z+1)*largeurCase, 0,1,0, 0,1, 1,1,1,0);
            Point3D C((x+1)*largeurCase, tableau_points[x+1][z+1], (z+1)*largeurCase, 0,1,0, 1,1, 1,1,1,0);
            Point3D D((x+1)*largeurCase, tableau_points[x+1][z]  ,  z*largeurCase   , 0,1,0, 1,0, 1,1,1,0);

            SurfaceDeMap VA(materielHerbe);
            VA.AjouterPoint(A);
            VA.AjouterPoint(B);
            VA.AjouterPoint(C);
            VA.CalculeMonteeEtNormale();

            SurfaceDeMap VB(materielHerbe);
            VB.AjouterPoint(A);
            VB.AjouterPoint(C);
            VB.AjouterPoint(D);
            VB.CalculeMonteeEtNormale();

            vector< SurfaceDeMap > case_;

            case_.push_back(VA);
            case_.push_back(VB);

            listeCases.push_back(case_);
        }
    }
}

void Map::CalculeNormaleParPoint()
{
    for(int x=0; x<largeurX;x++)
    {
        for(int z=0; z<longueurZ;z++)
        {
            //On commence par le point A de cette case
            sf::Vector3f normaleCalculee(0,0,0);
            if(z == 0 || x == 0)
            {
                //si ce point est au bord de la map, on ne calcule pas, la normale est verticale par défaut.
                normaleCalculee.y=1;
            }
            else
            {
                normaleCalculee += listeCases[(z-1)*largeurX + x-1][1].GetNormale();
                normaleCalculee += listeCases[(z-1)*largeurX + x-1][0].GetNormale();
                normaleCalculee += listeCases[z*largeurX + x][1].GetNormale();
                normaleCalculee += listeCases[z*largeurX + x][0].GetNormale();
                normaleCalculee += listeCases[(z-1)*largeurX + x][1].GetNormale();
                normaleCalculee += listeCases[z*largeurX + x-1][0].GetNormale();

                normaleCalculee.x /= 6;
                normaleCalculee.y /= 6;
                normaleCalculee.z /= 6;
            }

            listeCases[z*largeurX+x][0].SetNormale(0,normaleCalculee);
            listeCases[z*largeurX+x][1].SetNormale(0,normaleCalculee);

            normaleCalculee.x = 0;
            normaleCalculee.y = 0;
            normaleCalculee.z = 0;

            if(x == 0 || z == longueurZ-1)
            {
                 normaleCalculee.y=1;
            }
            else
            {
                normaleCalculee += listeCases[z*largeurX + x-1][1].GetNormale();
                normaleCalculee += listeCases[z*largeurX + x-1][0].GetNormale();
                normaleCalculee += listeCases[(z+1)*largeurX + x][0].GetNormale();
                normaleCalculee += listeCases[(z+1)*largeurX + x][1].GetNormale();
                normaleCalculee += listeCases[(z)*largeurX + x][1].GetNormale();
                normaleCalculee += listeCases[(z+1)*largeurX + x-1][0].GetNormale();

                normaleCalculee.x /= 6;
                normaleCalculee.y /= 6;
                normaleCalculee.z /= 6;
            }

            listeCases[z*largeurX+x][0].SetNormale(1,normaleCalculee);

            normaleCalculee.x = 0;
            normaleCalculee.y = 0;
            normaleCalculee.z = 0;

            if(x == largeurX-1 ||  z == longueurZ-1)
            {
                normaleCalculee.y=1;
            }
            else
            {
                normaleCalculee += listeCases[z*largeurX + x][1].GetNormale();
                normaleCalculee += listeCases[z*largeurX + x][0].GetNormale();
                normaleCalculee += listeCases[(z+1)*largeurX + x+1][1].GetNormale();
                normaleCalculee += listeCases[(z+1)*largeurX + x+1][0].GetNormale();
                normaleCalculee += listeCases[(z+1)*largeurX + x][0].GetNormale();
                normaleCalculee += listeCases[z*largeurX + x+1][1].GetNormale();

                normaleCalculee.x /= 6;
                normaleCalculee.y /= 6;
                normaleCalculee.z /= 6;
            }

            listeCases[z*largeurX+x][0].SetNormale(2,normaleCalculee);
            listeCases[z*largeurX+x][1].SetNormale(1,normaleCalculee);

            normaleCalculee.x = 0;
            normaleCalculee.y = 0;
            normaleCalculee.z = 0;

            if(x == largeurX-1 ||  z == 0)
            {
                normaleCalculee.y=1;
            }
            else
            {
                normaleCalculee += listeCases[(z)*largeurX +x+1][1].GetNormale();
                normaleCalculee += listeCases[(z)*largeurX +x+1][0].GetNormale();
                normaleCalculee += listeCases[(z-1)*largeurX + x][0].GetNormale();
                normaleCalculee += listeCases[(z-1)*largeurX + x][1].GetNormale();
                normaleCalculee += listeCases[(z-1)*largeurX + x+1][1].GetNormale();
                normaleCalculee += listeCases[z*largeurX + x][0].GetNormale();
            }

            listeCases[z*largeurX+x][1].SetNormale(2,normaleCalculee);

            normaleCalculee.x = 0;
            normaleCalculee.y = 0;
            normaleCalculee.z = 0;
        }
    }
}

float Map::GetLimitX()
{
    return largeurCase*largeurX;
}

float Map::GetLimitZ()
{
    return largeurCase*longueurZ;
}

void Map::Afficher()
{
    for(int a=0; a<(int)listeCases.size(); a++)
    {
        glEnable(GL_TEXTURE_2D);
        listeCases[a][0].Afficher(lumiere);
        listeCases[a][1].Afficher(lumiere);
    }
}

float Map::GetAltitude(float x, float z)
{
    int coordonneeX = floor(x/largeurCase);
    int coordonneeZ = floor(z/largeurCase);

    float coordonneeXRelative = (x - coordonneeX*largeurCase)/largeurCase;
    float coordonneeZRelative = (z - coordonneeZ*largeurCase)/largeurCase;

    if(coordonneeXRelative > coordonneeZRelative)
    {
        return listeCases[coordonneeZ*largeurX + coordonneeX][1].GetAltitude(coordonneeXRelative,coordonneeZRelative);
    }
    else
    {
        return listeCases[coordonneeZ*largeurX + coordonneeX][0].GetAltitude(coordonneeXRelative,coordonneeZRelative);
    }
}

void Map::AfficherLigne()
{
    for(int a=0; a<(int)listeCases.size(); a++)
    {
        glDisable(GL_TEXTURE_2D);
        listeCases[a][0].AfficherLignes();
        listeCases[a][1].AfficherLignes();
        glEnable(GL_TEXTURE_2D);
    }
}
