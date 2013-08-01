#include "Map.hpp"
#include "Tools.hpp"

Map::Map()
{
    GLuint herbe = Tools::chargerTexture("./images/herbe.png");

    int largeur=20;
    int longueur=20;

    LIGHT = false;
    NORM = true;

    float tableau_points[largeur+1][longueur+1];

    unsigned int Seed = 10;
    sf::Randomizer::SetSeed(Seed);

    for(int i=0; i<=largeur;i++)
    {
        for(int j=0; j<=longueur;j++)
        {
            tableau_points[i][j] = sf::Randomizer::Random(0, 300)/100.0;
            cout << tableau_points[i][j] << ",";
        }
        cout << endl;
    }

    float largeurCase = 4;

    for(int x=0;x<largeur;x++)
    {
        for(int z=0;z<longueur;z++)
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
    int largeur=20;
    int longueur=20;
    for(int i=0; i<longueur;i++)
    {
        for(int j=0; j<largeur;j++)
        {
            listeCaseMaps[i*largeur+j].calcule_normale2();
        }
    }
}

void Map::calculeNormaleParPoint()
{
    int largeur=20;
    int longueur=20;
    for(int i=1; i<longueur-1;i++)
    {
        for(int j=1; j<largeur-1;j++)
        {
            float A =   (
                        listeCaseMaps[i*largeur + j-1].get_normale_moyenne_BD() +
                        listeCaseMaps[i*largeur + j].get_normale_moyenne_BD() +
                        listeCaseMaps[i*largeur + j].get_normale_moyenne_HG() +
                        listeCaseMaps[(i-1)*largeur + j].get_normale_moyenne_HG() +
                        listeCaseMaps[(i-1)*largeur + j-1].get_normale_moyenne_HG() +
                        listeCaseMaps[(i-1)*largeur + j-1].get_normale_moyenne_BD()
                        )/6.0;

            float B =   (
                        listeCaseMaps[(i+1)*largeur+j-1].get_normale_moyenne_BD() +
                        listeCaseMaps[(i+1)*largeur + j].get_normale_moyenne_BD() +
                        listeCaseMaps[(i+1)*largeur + j].get_normale_moyenne_HG() +
                        listeCaseMaps[i*largeur + j].get_normale_moyenne_HG() +
                        listeCaseMaps[i*largeur + j-1].get_normale_moyenne_HG() +
                        listeCaseMaps[i*largeur + j-1].get_normale_moyenne_BD()
                        )/6.0;

            float C =   (
                        listeCaseMaps[(i+1)*largeur + j].get_normale_moyenne_BD() +
                        listeCaseMaps[(i+1)*largeur + j+1].get_normale_moyenne_BD() +
                        listeCaseMaps[(i+1)*largeur + j+1].get_normale_moyenne_HG() +
                        listeCaseMaps[i*largeur + j+1].get_normale_moyenne_HG() +
                        listeCaseMaps[i*largeur + j].get_normale_moyenne_HG() +
                        listeCaseMaps[i*largeur + j].get_normale_moyenne_BD()
                        )/6.0;

            float D =   (
                        listeCaseMaps[i*largeur + j].get_normale_moyenne_BD() +
                        listeCaseMaps[i*largeur + j+1].get_normale_moyenne_BD() +
                        listeCaseMaps[i*largeur + j+1].get_normale_moyenne_HG() +
                        listeCaseMaps[(i-1)*largeur + j+1].get_normale_moyenne_HG() +
                        listeCaseMaps[(i-1)*largeur + j].get_normale_moyenne_HG() +
                        listeCaseMaps[(i-1)*largeur + j].get_normale_moyenne_BD()
                        )/6.0;

            listeCaseMaps[i*largeur + j].set_eclairage_normale(A,D,C,B);
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
