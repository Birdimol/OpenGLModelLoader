#include "Surface.hpp"
#include "Point3D.hpp"
#include "Materiel.hpp"

Surface::Surface()
{

}

Surface::Surface(vector<Point3D> input_listePoints)
{
    listePoints = input_listePoints;
}

Surface::Surface(Materiel input_materiel)
{
    materiel = input_materiel;
}

void Surface::AjouterPoint(Point3D nouveauPoint)
{
    listePoints.push_back(nouveauPoint);
}

void Surface::AfficherLignes()
{
    int nombrePoints = listePoints.size();

    glBegin(GL_LINE_LOOP);
        for(int a=0; a<nombrePoints; a++)
        {
            listePoints[a].AfficherLignes();
        }
    glEnd();
}

void Surface::Afficher(Lumiere *adresse_source_lumiere)
{
    int nombrePoints = listePoints.size();
    /*for(int a=0; a<nombrePoints; a++)
    {
        listePoints[a].AfficherVecteurLumiere(adresse_source_lumiere);
    }*/

    if(materiel.PossedeTexture())
    {
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D,materiel.GetTexture());
    }
    else
    {
        glDisable(GL_TEXTURE_2D);
    }

    if(nombrePoints == 3)
    {
        glColor3ub(materiel.GetR()*255,materiel.GetG()*255,materiel.GetB()*255);
        glBegin(GL_TRIANGLES);
            for(int a=0; a<nombrePoints; a++)
            {
                listePoints[a].Afficher(materiel,adresse_source_lumiere);
            }
        glEnd();
    }
    else if(nombrePoints == 4)
    {
        glColor3ub(materiel.GetR()*255,materiel.GetG()*255,materiel.GetB()*255);
        glBegin(GL_QUADS);
        for(int a=0; a<nombrePoints; a++)
            {
                listePoints[a].Afficher(materiel,adresse_source_lumiere);
            }
        glEnd();
    }
}

Materiel Surface::getMateriel()
{
    return materiel;
}

void Surface::Debug()
{
    int nombrePoints = listePoints.size();
    cout << "Face : " << endl;

    for(int a=0; a<nombrePoints; a++)
    {
        listePoints[a].Debug();
    }
}
