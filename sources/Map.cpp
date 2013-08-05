#include "Map.hpp"
#include "Tools.hpp"

Map::Map(int largeur, int longueur)
{
    largeurX = largeur;
    longueurZ = longueur;

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
            else if((x == 5 && (z == 5 || z ==6)) || (x == 6 && (z == 5 || z ==6)))
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

    largeurCase = 4;


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
            float A =   (
                        listeCaseMaps[(z-1)*largeurX + x].get_normale_moyenne_BD() +
                        listeCaseMaps[(z-1)*largeurX + x].get_normale_moyenne_BD() +
                        listeCaseMaps[(z-1)*largeurX + x-1].get_normale_moyenne_BD() +
                        listeCaseMaps[z*largeurX + x].get_normale_moyenne_HG() +
                        listeCaseMaps[z*largeurX + x-1].get_normale_moyenne_HG() +
                        listeCaseMaps[z*largeurX + x-1].get_normale_moyenne_BD()
                        )/6.0;

            float B =   (
                        listeCaseMaps[(z)*largeurX +x].get_normale_moyenne_BD() +
                        listeCaseMaps[(z)*largeurX + x].get_normale_moyenne_HG() +
                        listeCaseMaps[(z+1)*largeurX + x-1].get_normale_moyenne_HG() +
                        listeCaseMaps[(z+1)*largeurX + x-1].get_normale_moyenne_BD() +
                        listeCaseMaps[(z+1)*largeurX + x].get_normale_moyenne_HG() +
                        listeCaseMaps[z*largeurX + x-1].get_normale_moyenne_BD()
                        )/6.0;

            float C =   (
                        listeCaseMaps[(z+1)*largeurX + x].get_normale_moyenne_BD() +
                        listeCaseMaps[(z+1)*largeurX + x].get_normale_moyenne_HG() +
                        listeCaseMaps[z*largeurX + x+1].get_normale_moyenne_HG() +
                        listeCaseMaps[z*largeurX + x+1].get_normale_moyenne_BD() +
                        listeCaseMaps[(z+1)*largeurX + x+1].get_normale_moyenne_HG() +
                        listeCaseMaps[z*largeurX + x].get_normale_moyenne_BD()
                        )/6.0;

            float D =   (
                        listeCaseMaps[z*largeurX + x].get_normale_moyenne_BD() +
                        listeCaseMaps[z*largeurX + x].get_normale_moyenne_HG() +
                        listeCaseMaps[(z-1)*largeurX + x+1].get_normale_moyenne_HG() +
                        listeCaseMaps[(z-1)*largeurX + x+1].get_normale_moyenne_BD() +
                        listeCaseMaps[(z)*largeurX + x+1].get_normale_moyenne_HG() +
                        listeCaseMaps[(z-1)*largeurX + x].get_normale_moyenne_BD()
                        )/6.0;

            listeCaseMaps[z*largeurX + x].set_eclairage_normale(A,D,C,B);
        }
    }
}

void Map::Afficher()
{
    for(int a=0; a<(int)listeCaseMaps.size(); a++)
    {
        listeCaseMaps[a].afficher();
    }
}
