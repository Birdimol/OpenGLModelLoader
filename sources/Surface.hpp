/*!
 * \file Surface.hpp
 * \brief Header de la classe Surface.
 * \author Birdimol
 * \version 0.1a
 * \date 27 décembre 2011
 *
 */

#ifndef DEF_SURFACE
#define DEF_SURFACE

#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <GL/gl.h>
#include <GL/glu.h>
#include <string>
#include <vector>

#include "Point3D.hpp"
#include "Materiel.hpp"

using namespace std;

/*!
* \class Surface Surface.hpp
* \brief classe representant une surface 3D.
* \author Favay Thomas
*  La classe gère la création et l'affichage de surface 3D dans le jeu.
*
*/
class Surface
{
    public :
    /*!
     *  \brief Constructeur
     *
     *  Constructeur par défaut de la classe Surface
     *
     */
    Surface();

    /*!
     *  \brief Constructeur
     *
     *  Constructeur de la classe Surface ou l'on spécifie le Materiel à utiliser.
     *
     *  \param materiel : Materiel à utiliser.
     */
    Surface(Materiel materiel);

    /*!
     *  \brief Constructeur
     *
     *  Constructeur de la classe Surface ou l'on spécifie la liste de points qui composent la surface.
     *
     *  \param listePoints : vector des Point3D 's composant la surface.
     */
    Surface(vector< Point3D > listePoints);

    void AjouterPoint(Point3D nouveauPoint);

    /*!
     *  \brief Permet d'afficher la surface sous forme linéaire.
     *
     */
    void AfficherLignes();

    /*!
     *  \brief Permet d'afficher la surface.
     *  \param lumiere : un pointeur vers un objet de type Lumiere qui défini quelle source de lumière utiliser pour l'éclairage de la surface.
     */
    void Afficher(Lumiere *lumiere);

    /*!
     *  \brief Permet d'afficher la surface.
     */
    void Debug();

    /*!
     *  \brief Renvoie le matériel de la surface.
     *
     */
    Materiel getMateriel();

    protected :
    /*! \brief Liste des points de la surface. */
    vector< Point3D > listePoints;

    /*! \brief Le materiel à appliquer à la surface. */
    Materiel materiel;

};

#endif
