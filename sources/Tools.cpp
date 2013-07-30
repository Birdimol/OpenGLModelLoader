#include "Tools.hpp"

#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <GL/gl.h>
#include <GL/glu.h>
#include <string>
#include <vector>

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
    //Eclate une cha�ne au niveau de ses espaces.
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

vector<string> Tools::SplitSlashes(string s)
{
    //Eclate une cha�ne au niveau de ses espaces.
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


GLuint Tools::chargerTexture(string fichier)
{
    //identifiant de la texture initialis� � 0
    GLuint identifiant_texture = 1;

    //chargement de l'image dont le nom de fichier est re�u en param�tre
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

