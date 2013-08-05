#include "Tools.hpp"

#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <GL/gl.h>
#include <GL/glu.h>
#include <string>
#include <vector>
#include <fstream>
#include <map>

using namespace std;

string Tools::RemplaceDoubleSlash(string s)
{
    //Remplace "//" par "/1/".
    string s1="";
    for(unsigned int i=0;i<s.size();i++)
    {
        if(i<s.size()-1&&s[i]=='/'&&s[i+1]=='/')
        {
            s1+="/0/";
            i++;
        }
        else
            s1+=s[i];
    }

    return s1;
}

float Tools::DifferenceVecteurs(sf::Vector3f normale, sf::Vector3f lumiere)
{
    float produitScalaire = normale.x*lumiere.x + normale.y*lumiere.y + normale.z*lumiere.z;

    float normeNormale = sqrt(normale.x*normale.x + normale.y*normale.y + normale.z*normale.z);

    float normeLumiere = sqrt(lumiere.x*lumiere.x + lumiere.y*lumiere.y + lumiere.z*lumiere.z);

    float angle = acos( produitScalaire / (normeNormale*normeLumiere) );

    /*
    cout << "DifferenceVecteurs " << normale.x << ", " << normale.y << ", " << normale.z << " et " <<  lumiere.x << ", " << lumiere.y << ", " << lumiere.z << endl;
    cout << "PS : " << produitScalaire << endl;
    cout << "NN : " << normeNormale << endl;
    cout << "NL : " << normeLumiere << endl;
    cout << "angle : " << angle << endl<< endl;
    */

    return angle;
}

string Tools::RemplaceSlash(string s)
{
    //Remplace les '/' par des espaces.
    string ret="";
    for(unsigned int i=0;i<s.size();i++)
    {
        if(s[i]=='/')
            ret+=' ';
        else
            ret+=s[i];
    }

    return ret;
}

vector<int> Tools::SplitSpace(string s)
{
    //Eclate une chaîne au niveau de ses espaces.
    vector<int> ret;
    string s1="";
    for(unsigned int i=0;i<s.size();i++)
    {
        if(s[i]==' '||i==s.size()-1)
        {
            if(i==s.size()-1)
                s1+=s[i];
            ret.push_back(strtod(s1.c_str(),NULL));
            s1="";
        }
        else
            s1+=s[i];
    }

    return ret;
}

string Tools::modelSelectionConsoleMenu()
{
    string choix;
    cout << endl << "  FacantaEngine 1.a - ModelViewer - 2013 - Favay Thomas" << endl << endl;
    cout << "  -------------------------" << endl;
    cout << "  | PageUp to look up     |" << endl;
    cout << "  | PageDown to look down |" << endl;
    cout << "  | PavNum8 to go up      |" << endl;
    cout << "  | PavNum2 to go down    |" << endl;
    cout << "  | - to take distance    |" << endl;
    cout << "  | + to go closer        |" << endl;
    cout << "  | C to reset rotation   |" << endl;
    cout << "  -------------------------" << endl << endl;
    cout << "  Enter the model you want to see." << endl;
    cout << "  The model must be located in the modeles directory and must be an fco file." << endl;
    cout << "  > ";
    cin >> choix;

    string choix_complet = "modeles/"+choix+".obj";

    ifstream ifile(choix_complet.c_str());
    if(ifile)
    {
        return choix;
    }
    else
    {
        cout << "/!\\ Model not found. /!\\ " << endl;
        return "canard";
    }
}

map<string, string> Tools::getFcoAsMap(string fcoFileName)
{
    map<string, string> fcoFileAsMap;

    string line;
    string completeFileName = "modeles/"+fcoFileName+".fco";
    ifstream myfile (completeFileName.c_str());

    if (myfile.is_open())
    {
        while ( myfile.good() )
        {
            getline(myfile,line);

            //if line isn't empty;
            if(line.size() > 0)
            {
                //erasing space in line
                std::size_t found = line.find_first_of(" ");
                while(found!=std::string::npos)
                {
                    line.erase(line.begin()+found);
                    found=line.find_first_of(" ");
                }

                //Ignoring sections and comments
                if(line.at(0) != ';' && line.at(0) != '[')
                {
                    found=line.find_first_of("=");
                    if(found!=std::string::npos)
                    {
                        string arg = line.substr(0,found);
                        string value = line.substr(found+1);
                        fcoFileAsMap[arg] = value;
                    }
                }
            }
        }
        myfile.close();
    }
    else
    {
        cout << "Fichier fco (modeles/"+fcoFileName+".fco) introuvable." << endl;
    }

    return fcoFileAsMap;
}

map<string, int> Tools::getConfig()
{
    map<string, int> config;

    //default_value
    config["window_width"] = 600;
    config["window_height"] = 480;
    config["fullscreen"] = 0;
    config["antialiasing"] = 0;

    string line;
    ifstream myfile ("config/config.ini");

    if (myfile.is_open())
    {
        while ( myfile.good() )
        {
            getline(myfile,line);

            //if line isn't empty;
            if(line.size() > 0)
            {
                //erasing space in line
                std::size_t found = line.find_first_of(" ");
                while(found!=std::string::npos)
                {
                    line.erase(line.begin()+found);
                    found=line.find_first_of(" ");
                }

                //Ignoring sections and comments
                if(line.at(0) != ';' && line.at(0) != '[')
                {
                    found=line.find_first_of("=");
                    if(found!=std::string::npos)
                    {
                        string arg = line.substr(0,found);
                        string value = line.substr(found+1);
                        config[arg] = Tools::StringToInt(value);
                    }
                }
            }
        }
        myfile.close();
    }
    else
    {
        cout << "Fichier de config (config/config.ini) introuvable." << endl;
    }

    return config;
}

void Tools::AfficherAxes()
{
    glDisable(GL_TEXTURE_2D);
    glLineWidth((GLfloat)2);
    glBegin(GL_LINES);
        glColor3ub(0,0,255);
        glVertex3d(0,0,0);
        glVertex3d(50,0,0);

        glColor3ub(255,0,0);
        glVertex3d(0,0,0);
        glVertex3d(0,0,50);

        glColor3ub(0,255,0);
        glVertex3d(0,0,0);
        glVertex3d(0,50,0);
    glEnd();
    glLineWidth((GLfloat)1);

    glPointSize((GLfloat)10);
    glBegin(GL_POINTS);
        glColor3ub(0,0,255);
        glVertex3d(50,0,0);

        glColor3ub(0,255,0);
        glVertex3d(0,50,0);

        glColor3ub(255,0,0);
        glVertex3d(0,0,50);
    glEnd();
    glPointSize((GLfloat)1);
}

vector<string> Tools::SplitSlashes(string s)
{
    //Eclate une chaîne au niveau de ses espaces.
    vector<string> ret;
    string s1="";
    for(unsigned int i=0;i<s.size();i++)
    {
        if(s[i]=='\\'||i==s.size()-1)
        {
            if(i==s.size()-1)
                s1+=s[i];
            ret.push_back(s1);
            s1="";
        }
        else
            s1+=s[i];
    }

    return ret;
}

int Tools::CompteOccurence(char lettre, string chaine)
{
    int nombreCaractere = chaine.size();
    int compte = 0;
    for(int a = 0; a < nombreCaractere; a++)
    {
        if(chaine[a] == lettre)
        {
            compte++;
        }
    }
    return compte;
}

string Tools::IntToString(int a)
{
    ostringstream Convert;
    Convert << a;
    string Nstr = Convert.str();
    return Nstr;
}

int Tools::StringToInt(string a)
{
    return atoi(a.c_str());
}


GLuint Tools::chargerTexture(string fichier)
{
    //identifiant de la texture initialisé à 0
    GLuint identifiant_texture = 1;

    //chargement de l'image dont le nom de fichier est reçu en paramètre
    sf::Image Image;
    if (!Image.LoadFromFile(fichier))
        return EXIT_FAILURE;

    //parametrage de la texture
    glGenTextures(1, &identifiant_texture);
    glBindTexture(GL_TEXTURE_2D, identifiant_texture);
    gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, Image.GetWidth(), Image.GetHeight(), GL_RGBA, GL_UNSIGNED_BYTE, Image.GetPixelsPtr());

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    //renvoi de l'identifiant
    return identifiant_texture;
}

sf::Vector2f Tools::RotationPoint2D(float x, float y, float input_angle)
{
    sf::Vector2f reponse;

    reponse.x = x*cos(input_angle) - y*sin(input_angle);
    reponse.y = y*cos(input_angle) + x*sin(input_angle);

    return reponse;
}

