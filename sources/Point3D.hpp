#ifndef DEF_POINT3D
#define DEF_POINT3D

#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <GL/gl.h>
#include <GL/glu.h>
#include <string>

#include "Materiel.hpp"
#include "Lumiere.hpp"

/*!
* \class Point3D Point3D.hpp
* \brief Cette classe représente tout point utilisé pour modéliser des objets.
* \author Favay Thomas
*
* Elle permet de gérer la position, les normales et les textures des points.
* Le fait de définir une normale permet de gérer l'éclairage à condition d'avoir la position de la source de lumière.
*
*/
class Point3D
{
    public :
    /*!
    *   \brief Constructeur spécifiant uniquement la position spaciale du point.
    *   Il sera par défaut sans texture, avec une normale verticale et de couleur verte sans transparance.
    *
    */
    Point3D(float px, float py, float pz);

    /*!
    *   \brief Constructeur.
    *
    */
    Point3D(float px, float py, float pz, float nx, float ny, float nz,float tx, float ty, int r, int g, int b, int a);

    /*!
    *   \brief Affiche le point dans l'optique d'un affichage linéaire (pas de texture).
    *
    */
    void AfficherLignes();

    /*!
    *   \brief Affiche le point.
    *
    */
    void Afficher();

    /*!
    *   \brief Affiche le point avec le materiel et la lumiere passée en paramètre.
    *
    */
    void AfficherVecteurLumiere(Lumiere *lumiere);

    /*!
    *   \brief Affiche le vecteur lumiere relatif au point.
    *
    */
    void Afficher(Materiel materiel,Lumiere *lumiere);

    /*!
    *   \brief Affiche les coordonnées spatiales, la normale et les coordonées de l'éventuelle texture.
    *
    */
    void Debug();

    /*!
    *   \brief Défini la couleur du point
    *
    */
    void SetColor(int r, int g, int b, int a);

    /*!
    *   \brief Défini la normale du point qui est utilisée pour gérer l'éclairage.
    *
    */
    void SetNormale(float nx, float ny, float nz);

    /*!
    *   \brief Défini les coordonnées de la texture du point.
    *
    */
    void SetTexture(float x, float y);

    private :
    //position
    float px;/*!\brief position en x du point. */
    float py;/*!\brief position en y du point. */
    float pz;/*!\brief position en z du point. */

    //normales
    float nx;/*!\brief valeur en x du vecteur de la normale. */
    float ny;/*!\brief valeur en y du vecteur de la normale. */
    float nz;/*!\brief valeur en z du vecteur de la normale. */

    //texture
    float tx;/*!\brief position en x de la texture du point. */
    float ty;/*!\brief position en y de la texture du point. */

    //color
    int r;/*!\brief valeur de la composante rouge de la couleur de la surface. */
    int g;/*!\brief valeur de la composante verte de la couleur de la surface. */
    int b;/*!\brief valeur de la composante bleue de la couleur de la surface. */
    int a;/*!\brief valeur de la composante alpha de la couleur de la surface. */


};

#endif
