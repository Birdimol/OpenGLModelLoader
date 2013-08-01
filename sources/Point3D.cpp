#include "point3D.hpp"
#include "Tools.hpp"

#define PI 3.14159265358979323846

using namespace std;

Point3D::Point3D()
{
}

Point3D::Point3D(float input_px, float input_py, float input_pz)
{
    px = input_px;
    py = input_py;
    pz = input_pz;

    nx = 0;
    ny = 1;
    nz = 0;

    tx = -1;
    ty = -1;

    r = 0;
    g = 1;
    b = 0;
    a = 0;
}

Point3D::Point3D(float input_px, float input_py, float input_pz, float input_nx, float input_ny, float input_nz,float input_tx, float input_ty, int input_r, int input_g, int input_b, int input_a)
{
    px = input_px;
    py = input_py;
    pz = input_pz;

    nx = input_nx;
    ny = input_ny;
    nz = input_nz;

    tx = input_tx;
    ty = input_ty;

    r = input_r;
    g = input_g;
    b = input_b;
    a = input_a;
}

sf::Vector3f Point3D::GetPosition()
{
    sf::Vector3f temp(px,py,pz);
    return temp;
}

void Point3D::SetColor(int input_r, int input_g, int input_b, int input_a)
{
    r = input_r;
    g = input_g;
    b = input_b;
    a = input_a;
}

void Point3D::SetTexture(float x, float y)
{
    tx = x;
    ty = y;
}

void Point3D::SetNormale(float input_nx, float input_ny, float input_nz)
{
    nx = input_nx;
    ny = input_ny;
    nz = input_nz;

    //cout << "Nouvelles normales du point : " << nx << ", " << ny << "," << nz << endl;
}

void Point3D::AfficherLignes()
{
    glVertex3d(px,py,pz);
}

void Point3D::Afficher()
{
    if(tx != -1 && ty != -1)
    {
        glTexCoord2f(tx,ty);
    }
    glVertex3d(px,py,pz);
}

void Point3D::AfficherVecteurLumiere(Lumiere *lumiere)
{
    glDisable(GL_TEXTURE_2D);
    glBegin(GL_LINES);
        glColor3ub(255,0,0);
        glVertex3f(px,py,pz);
        glVertex3f(lumiere->x,lumiere->y,lumiere->z);
    glEnd();

    glBegin(GL_LINES);
        glColor3ub(255,255,255);
        glVertex3f(px,py,pz);
        glVertex3f(px+nx,py+ny,pz+nz);
    glEnd();
}

void Point3D::Afficher(Materiel materiel, Lumiere *lumiere)
{
    sf::Vector3f normale(nx,ny,nz);
    sf::Vector3f vect_lumiere(lumiere->x-px,lumiere->y-py,lumiere->z-pz);

    float angle = Tools::DifferenceVecteurs(normale,vect_lumiere);

    //Si c'est 0 = Pile en face
    //Si c'est Pi/2 = c'est a 90°
    //Si c'est Pi, c'est opposé

    //Donc, si c'est > que Pi/2 no light !

    float intensite = lumiere->lumiereMinimum; //lumiere minimum
    if(angle < PI/2)
    {
        intensite += (255-lumiere->lumiereMinimum) * ((PI/2 - angle) / (PI/2)); //lumiere minimum
    }

    //intensite = 255;
    //glColor3ub(materiel.GetR()*255*intensite,materiel.GetG()*255*intensite,materiel.GetB()*255*intensite);
    glColor3ub(materiel.GetR()*intensite, materiel.GetG()*intensite, materiel.GetB()*intensite);

    if(tx != -1 && ty != -1)
    {
        glTexCoord2f(tx,ty);
    }
    glVertex3d(px,py,pz);
}

void Point3D::Debug()
{
    cout << "Point : " << px << " x, " << py << " y," << pz << " z  Norm : " << nx << " x, " << ny << " y," << nz << " z  Coord Texture : " << tx << ", " << ty <<  endl;
}

