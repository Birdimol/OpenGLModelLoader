/*!
 * \file SurfaceDeMap.hpp
 * \brief Header de la classe SurfaceDeMap.
 * \author Birdimol
 * \version 0.1a
 * \date 08 aout 2013
 *
 */

#ifndef DEF_SURFACEDEMAP
#define DEF_SURFACEDEMAP

#include "Surface.hpp"
#include "Tools.hpp"

class SurfaceDeMap : public Surface
{
    public :
        SurfaceDeMap(Materiel materiel);
        float GetAltitude(float X, float Z);
        void CalculeMonteeEtNormale();
        void Afficher(Lumiere *adresse_source_lumiere);
        void AfficherLignes();
        sf::Vector3f GetNormale();
        void SetNormale(int numeroDuPoint, sf::Vector3f normale);
        bool EstHautGauche();
    private :
        float monteeX;
        float monteeZ;
        sf::Vector3f normale;
};

#endif
