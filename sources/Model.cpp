#include "Model.hpp"
#include "Surface.hpp"
#include "Point3D.hpp"
#include "Materiel.hpp"
#include "Tools.hpp"
#include "Lumiere.hpp"

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include <iostream>
#include <fstream>

#define PI 3.14159265358979323846

Model::Model()
{
    angle.x = 0;
    angle.y = 0;
    angle.z = 0;
    position.x = 0;
    position.y = 0;
    position.z = 0;
}

Model::Model(vector<Surface> input_listeSurfaces)
{
    listeSurfaces = input_listeSurfaces;
    angle.x = 0;
    angle.y = 0;
    angle.z = 0;
    position.x = 0;
    position.y = 0;
    position.z = 0;
}

void Model::AjouterSurface(Surface nouvelleSurface)
{
    listeSurfaces.push_back(nouvelleSurface);
}

void Model::AfficherLignes()
{
    glPushMatrix();
        glTranslated(position.x,position.y,position.z);
        glRotated(angle.y,0,1,0);
        //glRotated(angle.z,0,0,1);

        float mem_source_lumiere_x = source_lumiere->x;
        float mem_source_lumiere_z = source_lumiere->z;

        sf::Vector2f nouvelle_cooord_lumiere = Tools::RotationPoint2D(source_lumiere->x,source_lumiere->z, angle.y/180*PI);
        source_lumiere->x = nouvelle_cooord_lumiere.x;
        source_lumiere->z = nouvelle_cooord_lumiere.y;

        glColor3ub(255,50,50);
        int nombre_surface = listeSurfaces.size();
        for(int a=0; a<nombre_surface; a++)
        {
            listeSurfaces[a].AfficherLignes();
        }

        source_lumiere->x = mem_source_lumiere_x;
        source_lumiere->z = mem_source_lumiere_z;

    glPopMatrix();
}

sf::Vector3f Model::GetAngle()
{
    return angle;
}

void Model::SetAngle(sf::Vector3f input_angle)
{
    angle = input_angle;
}

void Model::SetAngle(float input_x, float input_y, float input_z)
{
    angle.x = input_x;
    angle.y = input_y;
    angle.z = input_z;
}

void Model::Tourne(sf::Vector3f input_angle)
{
    angle += input_angle;
}

void Model::Afficher()
{
    glPushMatrix();
        glTranslated(position.x,position.y,position.z);
        glRotated(angle.y,0,1,0);
        glRotated(angle.z,0,0,1);
        glRotated(angle.x,1,0,0);

        float mem_source_lumiere_x = source_lumiere->x;
        float mem_source_lumiere_z = source_lumiere->z;

        sf::Vector2f nouvelle_cooord_lumiere = Tools::RotationPoint2D(source_lumiere->x,source_lumiere->z, angle.y/180*PI);
        source_lumiere->x = nouvelle_cooord_lumiere.x;
        source_lumiere->z = nouvelle_cooord_lumiere.y;

        int nombre_surface = listeSurfaces.size();

        for(int a=0; a<nombre_surface; a++)
        {
            listeSurfaces[a].Afficher(source_lumiere);
        }

        source_lumiere->x = mem_source_lumiere_x;
        source_lumiere->z = mem_source_lumiere_z;

    glPopMatrix();
}

int Model::ChargerModele(string nomFichier)
{
    string temp = "./modeles/"+nomFichier+".obj";

    string fichierMTL = "";


    ifstream fichier(temp.c_str());  //Ouverture d'un fichier en lecture


    if(fichier)
    {
        string ligne;
        string ligne2;

        char dataString1[255];
        char dataString2[255];
        char dataString3[255];
        char dataString4[255];

        float dataFloat1;
        float dataFloat2;
        float dataFloat3;
        float dataFloat4;

        vector<Point3D> listePoints;
        vector<sf::Vector2f> listeTexture;
        vector<sf::Vector3f> listeNormale;

        Materiel materielActif;

        //Tout est prêt pour la lecture.
        while(getline(fichier, ligne))    //Tant qu'on n'est pas a la fin, on lit
        {
            //cout << ligne << endl;

            //si ça commence par 'v'
            if(ligne[0]=='u')
            {
                //on utilise un nouveau materiel pour les prochaines faces
                char nom_temp[255];
                sscanf(ligne.c_str(),"usemtl %s",nom_temp);
                materielActif = GetMateriel(nom_temp);

            }
            else if(ligne[0]=='v')
            {
                if(ligne[1]==' ') //Vertex
                {
                    sscanf(ligne.c_str(),"v %s %s %s",dataString1,dataString2,dataString3);
                    dataFloat1 = strtod(dataString1,NULL);
                    dataFloat2 = strtod(dataString2,NULL);
                    dataFloat3 = strtod(dataString3,NULL);

                    Point3D nouveauPoint(dataFloat1, dataFloat2, dataFloat3, 0, 1, 0, -1, -1, 255, 255, 255, 0);
                    listePoints.push_back(nouveauPoint);
                }
                else if(ligne[1]=='t') //Texture
                {
                    sscanf(ligne.c_str(),"vt %s %s",dataString1,dataString2);
                    dataFloat1 = strtod(dataString1,NULL);
                    dataFloat2 = strtod(dataString2,NULL);

                    sf::Vector2f temp(dataFloat1,dataFloat2);

                    listeTexture.push_back(temp);

                    //cout << listeTexture.size() << " : Nouveau point de texture ajoute : "<< dataFloat1 << ", " << dataFloat2<< endl;
                }
                else if(ligne[1]=='n') //Normale
                {
                    sscanf(ligne.c_str(),"vn %s %s %s",dataString1,dataString2,dataString3);

                    dataFloat1 = strtod(dataString1,NULL);
                    dataFloat2 = strtod(dataString2,NULL);
                    dataFloat3 = strtod(dataString3,NULL);

                    sf::Vector3f temp(dataFloat1,dataFloat2,dataFloat3);

                    listeNormale.push_back(temp);
                }
            }
            else if(ligne[0]=='f') //Indice faces
            {
                //On compte le nombre d'espace pour savoir le nombre de point
                if(Tools::CompteOccurence(' ',ligne)== 4)
                {
                    //des faces carrées
                    //cout << endl << "On traite une face carree."<< endl;
                    if(Tools::CompteOccurence('/',ligne)== 8)
                    {
                        //cout << "face avec texture."<< endl;
                        //Lignes avec deux slashes -> point/textures/normales
                        ligne=Tools::RemplaceDoubleSlash(ligne); //On remplace "//" par "/1/" dans toute la ligne
                        ligne=Tools::RemplaceSlash(ligne); //On remplace les '/' par des espaces, ex : pour "f 1/2/3 4/5/6 7/8/9" on obtiendra "f 1 2 3 4 5 6 7 8 9"
                        vector<int> termes=Tools::SplitSpace(ligne.substr(2)); //On éclate la chaîne en ses espaces (le substr permet d'enlever "f ")

                        int nombre_points = (int)termes.size()/3;
                        //cout << "la face a " << nombre_points << " points."<< endl;

                        Surface nouvelleSurface(materielActif);

                        for(int a = 0; a < nombre_points; a++)
                        {
                            //cout << "Le point de texture que l'on veut ajoute est le point : " << a*3+1 << endl;
                            //On ajoute la texture au point si elle existe
                            if(((int)listeTexture.size()) > termes[a*3+1]-1 && termes[a*3+1]-1 >= 0)
                            {
                                //cout << "Ajout de la texture " << listeTexture[termes[a*3+1]-1].x << ", " << listeTexture[termes[a*3+1]-1].y << " ."<< endl;
                                listePoints[termes[a*3]-1].SetTexture(listeTexture[termes[a*3+1]-1].x, 1-listeTexture[termes[a*3+1]-1].y);
                            }
                            else
                            {
                                //cout << "Erreur : pas de texture trouvee" << endl;
                            }

                            if(((int)listeNormale.size()) > termes[a*3+2]-1)
                            {
                                listePoints[termes[a*3]-1].SetNormale(listeNormale[termes[a*3+2]-1].x, listeNormale[termes[a*3+2]-1].y, listeNormale[termes[a*3+2]-1].z);
                            }

                            //on ajoute le point
                            nouvelleSurface.AjouterPoint(listePoints[termes[a*3]-1]);
                        }

                        listeSurfaces.push_back(nouvelleSurface);
                    }
                    else if(Tools::CompteOccurence('/',ligne)== 4)
                    {
                        //cout << "ligne avec texture et sans normale."<< endl;
                        //Lignes avec un slashes -> point/textures
                        ligne=Tools::RemplaceSlash(ligne); //On remplace les '/' par des espaces, ex : pour "f 1/2/3 4/5/6 7/8/9" on obtiendra "f 1 2 3 4 5 6 7 8 9"
                        vector<int> termes=Tools::SplitSpace(ligne.substr(2)); //On éclate la chaîne en ses espaces (le substr permet d'enlever "f ")

                        int nombre_points = (int)termes.size()/2;
                        //cout << "ligne qui a "<< nombre_points << " points." << endl;
                        Surface nouvelleSurface(materielActif);

                        for(int a = 0; a < nombre_points; a++)
                        {
                            //On ajoute la texture au point
                            //cout << " if(((int)listeTexture.size()) > termes["<<a*2+1<<"]-1 && termes["<<a*2+1<<"]-1 >= 0)"<<endl;
                            if(((int)listeTexture.size()) > termes[a*2+1]-1 && termes[a*2+1]-1 >= 0)
                            {
                                //cout << "listePoints["<<termes[a*2]-1<<"].SetTexture("<<listeTexture[termes[a*2+1]-1].x<<","<<listeTexture[termes[a*2+1]-1].y<<");"<< endl;
                                listePoints[termes[a*2]-1].SetTexture(listeTexture[termes[a*2+1]-1].x, 1-listeTexture[termes[a*2+1]-1].y);
                            }
                            nouvelleSurface.AjouterPoint(listePoints[termes[a*2]-1]);
                        }

                        listeSurfaces.push_back(nouvelleSurface);
                    }
                    else if(Tools::CompteOccurence('/',ligne)== 0)
                    {
                        //cout << "ligne sans texture et sans normales."<< endl;
                        sscanf(ligne.c_str(),"f %s %s %s %s",dataString1,dataString2,dataString3,dataString4);
                        dataFloat1 = strtod(dataString1,NULL);
                        dataFloat2 = strtod(dataString2,NULL);
                        dataFloat3 = strtod(dataString3,NULL);
                        dataFloat4 = strtod(dataString4,NULL);

                        Surface nouvelleSurface(materielActif);
                        nouvelleSurface.AjouterPoint(listePoints[dataFloat1-1]);
                        nouvelleSurface.AjouterPoint(listePoints[dataFloat2-1]);
                        nouvelleSurface.AjouterPoint(listePoints[dataFloat3-1]);
                        nouvelleSurface.AjouterPoint(listePoints[dataFloat4-1]);

                        listeSurfaces.push_back(nouvelleSurface);
                    }
                }
                else if(Tools::CompteOccurence(' ',ligne)== 3)
                {
                    //des faces triangulaires
                    if(Tools::CompteOccurence('/',ligne)== 6)
                    {
                        //Lignes avec deux slashes -> point/textures/normales
                        ligne=Tools::RemplaceDoubleSlash(ligne); //On remplace "//" par "/1/" dans toute la ligne
                        ligne=Tools::RemplaceSlash(ligne); //On remplace les '/' par des espaces, ex : pour "f 1/2/3 4/5/6 7/8/9" on obtiendra "f 1 2 3 4 5 6 7 8 9"
                        vector<int> termes=Tools::SplitSpace(ligne.substr(2)); //On éclate la chaîne en ses espaces (le substr permet d'enlever "f ")

                        int nombre_points = (int)termes.size()/3;

                        Surface nouvelleSurface(materielActif);

                        for(int a = 0; a < nombre_points; a++)
                        {
                            //On ajoute la texture au point si elle existe
                            if(((int)listeTexture.size()) > termes[a*3+1]-1 && termes[a*3+1]-1 >= 0)
                            {
                                listePoints[termes[a*3]-1].SetTexture(listeTexture[termes[a*3+1]-1].x, 1-listeTexture[termes[a*3+1]-1].y);
                            }

                            if(((int)listeNormale.size()) > termes[a*3+2]-1)
                            {
                                listePoints[termes[a*3]-1].SetNormale(listeNormale[termes[a*3+2]-1].x, listeNormale[termes[a*3+2]-1].y, listeNormale[termes[a*3+2]-1].z);
                            }

                            //on ajoute le point
                            nouvelleSurface.AjouterPoint(listePoints[termes[a*3]-1]);
                        }

                        listeSurfaces.push_back(nouvelleSurface);
                    }
                    else if(Tools::CompteOccurence('/',ligne)== 3)
                    {
                        //Lignes avec un slashes -> point/textures
                        ligne=Tools::RemplaceSlash(ligne); //On remplace les '/' par des espaces, ex : pour "f 1/2/3 4/5/6 7/8/9" on obtiendra "f 1 2 3 4 5 6 7 8 9"
                        vector<int> termes=Tools::SplitSpace(ligne.substr(2)); //On éclate la chaîne en ses espaces (le substr permet d'enlever "f ")

                        int nombre_points = (int)termes.size()/2;

                        Surface nouvelleSurface(materielActif);

                        for(int a = 0; a < nombre_points; a++)
                        {
                            //On ajoute la texture au point
                            if(((int)listeTexture.size()) > termes[a*2+1]-1 && termes[a*2+1]-1 >= 0)
                            {
                                listePoints[termes[a*2]-1].SetTexture(listeTexture[termes[a*2+1]-1].x, 1-listeTexture[termes[a*2+1]-1].y);
                            }
                            nouvelleSurface.AjouterPoint(listePoints[termes[a*2]-1]);
                        }

                        listeSurfaces.push_back(nouvelleSurface);
                    }
                    else if(Tools::CompteOccurence('/',ligne)== 0)
                    {
                        sscanf(ligne.c_str(),"f %s %s %s",dataString1,dataString2,dataString3);
                        dataFloat1 = strtod(dataString1,NULL);
                        dataFloat2 = strtod(dataString2,NULL);
                        dataFloat3 = strtod(dataString3,NULL);

                        Surface nouvelleSurface(materielActif);
                        nouvelleSurface.AjouterPoint(listePoints[dataFloat1-1]);
                        nouvelleSurface.AjouterPoint(listePoints[dataFloat2-1]);
                        nouvelleSurface.AjouterPoint(listePoints[dataFloat3-1]);

                        listeSurfaces.push_back(nouvelleSurface);
                    }
                }
            }
            else if(ligne[0]=='m')//fichier MTL et si c'est la première frame (comme ça on ne charge pas plusieurs fois le même MTL et la même texture)
            {
                fichierMTL = ligne.substr(7);

                string temp = "./modeles/" + fichierMTL;

                char nomMateriel[255];
                char pathTexture[255];
                string stringPathTexture = "";

                ifstream fichier2(temp.c_str());  //Ouverture d'un fichier en lecture
                if(fichier2)
                {
                    while(getline(fichier2, ligne2))    //Tant qu'on n'est pas a la fin, on lit
                    {
                        if(ligne2[0]=='K' && ligne2[1]=='d')
                        {
                            sscanf(ligne2.c_str(),"Kd %s %s %s",dataString1,dataString2,dataString3);
                            dataFloat1 = strtod(dataString1,NULL);
                            dataFloat2 = strtod(dataString2,NULL);
                            dataFloat3 = strtod(dataString3,NULL);
                        }
                        else if(ligne2[0]=='d')
                        {
                            sscanf(ligne2.c_str(),"d %s",dataString4);
                            dataFloat4 = strtod(dataString4,NULL);
                        }
                        else if(ligne2[0]=='i')
                        {
                            //derniere ligne
                            //mais peut-etre texture juste après
                            getline(fichier2, ligne2);
                            if(ligne2[0]=='m' && ligne2[1]=='a')
                            {
                                sscanf(ligne2.c_str(),"map_Kd %s",pathTexture);

                                vector<string> temp2;

                                temp2 = Tools::SplitSlashes(pathTexture);

                                stringPathTexture = temp2[temp2.size()-1];
                            }

                            if(stringPathTexture.size() == 0)
                            {
                                //pas de texture
                                Materiel nouveau_materiel(dataFloat1,dataFloat2,dataFloat3,dataFloat4,nomMateriel);
                                listeMateriel.push_back(nouveau_materiel);
                            }
                            else
                            {
                                //texture
                                Materiel nouveau_materiel(dataFloat1,dataFloat2,dataFloat3,dataFloat4,nomMateriel,stringPathTexture);
                                listeMateriel.push_back(nouveau_materiel);
                            }

                            stringPathTexture="";
                        }
                        else if(ligne2[0]=='n' && ligne2[1]=='e')
                        {
                            sscanf(ligne2.c_str(),"newmtl %s",nomMateriel);
                        }
                    }
                }
            }
        }
        return 1;
    }
    else
    {
        cout << "ERREUR: Impossible d'ouvrir le fichier en lecture." << endl;
        return 0;
    }
}

Materiel Model::GetMateriel(string nom)
{
    int nombre_materiel = listeMateriel.size();
    for(int z=0;z<nombre_materiel;z++)
    {
        if(nom.compare(listeMateriel[z].GetNom())==0)
        {
            return listeMateriel[z];
        }
    }
    return listeMateriel[0];
}

void Model::LieLumiere(Lumiere *adresse_source_lumiere)
{
    source_lumiere = adresse_source_lumiere;
}

void Model::setPosition(float x, float y, float z)
{
    position.x = x;
    position.y = y;
    position.z = z;
}

void Model::Debug()
{
    int nombre_surface = listeSurfaces.size();
    for(int a=0; a<nombre_surface; a++)
    {
        listeSurfaces[a].Debug();
    }
}
