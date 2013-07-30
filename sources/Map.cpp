#include "Map.hpp"

Map::Map()
{

}

void Map::Afficher()
{
    int nombre_modeles = listeModels.size();

    for(int a=0; a<nombre_modeles; a++)
    {
        listeModels[a].Afficher();
    }
}
