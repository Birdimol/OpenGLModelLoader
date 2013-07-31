#ifndef DEF_TOOLS
#define DEF_TOOLS

#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <GL/gl.h>
#include <GL/glu.h>
#include <string>
#include <vector>
#include <iomanip>
#include <string>
#include <sstream>

using namespace std;

/*!
* \class Tools Tools.hpp
* \brief classe contenant divers outils mathématiques et autres permettant de gérer, entre autre, la physique du jeu.
* \author Thomas Favay
*
*   Les méthodes sont toujours sous forme statique.
*/
class Tools
{
    public :
    static string RemplaceDoubleSlash(string s);
    static string RemplaceSlash(string s);
    static vector<int> SplitSpace(string s);
    static vector<string> SplitSlashes(string s);
    static int CompteOccurence(char lettre, string chaine);
    static GLuint chargerTexture(string fichier);
    static float DifferenceVecteurs(sf::Vector3f normale, sf::Vector3f lumiere);
    static sf::Vector2f RotationPoint2D(float x, float y, float angle);
    static string IntToString(int a);
    static int StringToInt(string a);
    static string modelSelectionConsoleMenu();
    static map<string, int> getConfig();
};

#endif
