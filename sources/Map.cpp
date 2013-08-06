#include "Map.hpp"
#include "Tools.hpp"

Map::Map(string heightMapFile, int largeurCase_)
{
    sf::Image Image;
    if (!Image.LoadFromFile("images/"+heightMapFile+".png"))
    {
        // Error...
    }

    GLuint herbe = Tools::chargerTexture("./images/herbe.png");

    LIGHT = false;
    NORM = true;

    largeurX = Image.GetWidth()-1;
    longueurZ = Image.GetHeight()-1;

    cout << "longueurZ map : " << longueurZ << endl;
    cout << "largeurX map : " << largeurX << endl;

    float altitude_max = 10;

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
            Point3D A(x*largeurCase    , tableau_points[x][z]    ,  z*largeurCase   );
            Point3D B(x*largeurCase    , tableau_points[x][z+1]  , (z+1)*largeurCase);
            Point3D C((x+1)*largeurCase, tableau_points[x+1][z+1], (z+1)*largeurCase);
            Point3D D((x+1)*largeurCase, tableau_points[x+1][z]  ,  z*largeurCase   );

            Vertex VA(A,B,C,herbe,0,0,1,1, &LIGHT, &NORM, false);
            Vertex VB(A,C,D,herbe,0,0,1,1, &LIGHT, &NORM, true);

            CaseMap caseMap(0, 0, VA, VB, herbe);

            listeCaseMaps.push_back(caseMap);
        }
    }
}

Map::Map(int largeur, int longueur,int largeurCase_)
{
    largeurX = largeur;
    longueurZ = longueur;

    GLuint herbe = Tools::chargerTexture("./images/herbe.png");

    LIGHT = false;
    NORM = true;

    float tableau_points[largeur+1][longueur+1];

    unsigned int Seed = 10;
    sf::Randomizer::SetSeed(Seed);

    //1 point de largeur et longueur en plus qu'il n'y a de cases, d'ou le <=
    for(int x=0; x<=largeurX;x++)
    {
        for(int z=0; z<=longueurZ;z++)
        {
            //on reste plat sur les bords
            if(x == 0 || z == 0 || x == largeurX || z == longueurZ)
            {
                tableau_points[x][z] = 0;
            }
            else if(x >= 4 && x <= 7 && z <= 6)
            {
                tableau_points[x][z] = 3;
            }
            else
            {
                tableau_points[x][z] = 0;
            }
            cout << tableau_points[x][z] << ",";
        }
        cout << endl;
    }
    largeurCase = largeurCase_;

    for(int z=0;z<longueurZ;z++)
    {
        for(int x=0;x<largeurX;x++)
        {
            Point3D A(x*largeurCase    , tableau_points[x][z]    ,  z*largeurCase   );
            Point3D B(x*largeurCase    , tableau_points[x][z+1]  , (z+1)*largeurCase);
            Point3D C((x+1)*largeurCase, tableau_points[x+1][z+1], (z+1)*largeurCase);
            Point3D D((x+1)*largeurCase, tableau_points[x+1][z]  ,  z*largeurCase   );

            Vertex VA(A,B,C,herbe,0,0,1,1, &LIGHT, &NORM, false);
            Vertex VB(A,C,D,herbe,0,0,1,1, &LIGHT, &NORM, true);

            CaseMap caseMap(0, 0, VA, VB, herbe);

            listeCaseMaps.push_back(caseMap);
        }
    }
}

void Map::calculNormaleParFace()
{
    for(int x=0; x<largeurX;x++)
    {
        for(int z=0; z<longueurZ;z++)
        {
            listeCaseMaps[z*largeurX+x].calcule_normale2();
        }
    }
}

void Map::calculeNormaleParPoint()
{
    for(int x=0; x<largeurX;x++)
    {
        for(int z=0; z<longueurZ;z++)
        {
            float A;
            if(z == 0 || x == 0)
            {
                A = 1;

            }
            else
            {
                A =   (
                        listeCaseMaps[(z-1)*largeurX + x-1].get_normale_moyenne_BD() +
                        listeCaseMaps[(z-1)*largeurX + x-1].get_normale_moyenne_HG() +
                        listeCaseMaps[z*largeurX + x].get_normale_moyenne_BD() +
                        listeCaseMaps[z*largeurX + x].get_normale_moyenne_HG() +
                        listeCaseMaps[(z-1)*largeurX + x].get_normale_moyenne_BD() +
                        listeCaseMaps[z*largeurX + x-1].get_normale_moyenne_HG()
                        )/6.0;
            }
            float B;

            if(x == 0 || z == longueurZ-1)
            {
                B = 1;
                //cout << z << endl;
            }
            else
            {
                B = (
                        listeCaseMaps[z*largeurX + x-1].get_normale_moyenne_BD() +
                        listeCaseMaps[z*largeurX + x-1].get_normale_moyenne_HG() +
                        listeCaseMaps[(z+1)*largeurX + x].get_normale_moyenne_HG() +
                        listeCaseMaps[(z+1)*largeurX + x].get_normale_moyenne_BD() +
                        listeCaseMaps[(z)*largeurX + x].get_normale_moyenne_BD() +
                        listeCaseMaps[(z+1)*largeurX + x-1].get_normale_moyenne_HG()
                        )/6.0;
            }

            float C;
            if(x == largeurX-1 ||  z == longueurZ-1)
            {
                C = 1;
            }
            else
            {
                C =     (
                        listeCaseMaps[z*largeurX + x].get_normale_moyenne_BD() +
                        listeCaseMaps[z*largeurX + x].get_normale_moyenne_HG() +
                        listeCaseMaps[(z+1)*largeurX + x+1].get_normale_moyenne_BD() +
                        listeCaseMaps[(z+1)*largeurX + x+1].get_normale_moyenne_HG() +
                        listeCaseMaps[(z+1)*largeurX + x].get_normale_moyenne_HG() +
                        listeCaseMaps[z*largeurX + x+1].get_normale_moyenne_BD()
                        )/6.0;
            }


            float D;

            if(x == largeurX-1 ||  z == 0)
            {
                D = 1;
            }
            else
            {
                D =     (
                        listeCaseMaps[(z)*largeurX +x+1].get_normale_moyenne_BD() +
                        listeCaseMaps[(z)*largeurX +x+1].get_normale_moyenne_HG() +
                        listeCaseMaps[(z-1)*largeurX + x].get_normale_moyenne_HG() +
                        listeCaseMaps[(z-1)*largeurX + x].get_normale_moyenne_BD() +
                        listeCaseMaps[(z-1)*largeurX + x+1].get_normale_moyenne_BD() +
                        listeCaseMaps[z*largeurX + x].get_normale_moyenne_HG()
                        )/6.0;
            }

            listeCaseMaps[z*largeurX + x].set_eclairage_normale(A,B,C,D);
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
    for(int a=0; a<(int)listeCaseMaps.size(); a++)
    {
        glEnable(GL_TEXTURE_2D);
        listeCaseMaps[a].afficher();
    }
}

void Map::Afficher(Materiel materiel, Lumiere *adresse_source_lumiere)
{
    for(int a=0; a<(int)listeCaseMaps.size(); a++)
    {
        listeCaseMaps[a].afficher(materiel, adresse_source_lumiere);
    }
}

float Map::GetAltitude(float x, float z)
{
    int coordonneeX = floor(x/largeurCase);
    int coordonneeZ = floor(z/largeurCase);

    float coordonneeXRelative = (x - coordonneeX*largeurCase)/largeurCase;
    float coordonneeZRelative = (z - coordonneeZ*largeurCase)/largeurCase;

    if(coordonneeZRelative > coordonneeXRelative)
    {
        return listeCaseMaps[coordonneeZ*largeurX + coordonneeX].getAltitudeA(coordonneeXRelative,coordonneeZRelative);
    }
    else
    {
        return listeCaseMaps[coordonneeZ*largeurX + coordonneeX].getAltitudeB(coordonneeXRelative,coordonneeZRelative);
    }
}

void Map::AfficherCouleur()
{
    for(int a=0; a<(int)listeCaseMaps.size(); a++)
    {
        glDisable(GL_TEXTURE_2D);
        listeCaseMaps[a].afficherCouleur();
    }
}

void Map::AfficherLigne()
{
    for(int a=0; a<(int)listeCaseMaps.size(); a++)
    {
        glDisable(GL_TEXTURE_2D);
        listeCaseMaps[a].afficher();
        glEnable(GL_TEXTURE_2D);
    }
}
