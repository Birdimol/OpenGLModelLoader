
#include "vertex.hpp"

using namespace std;

Vertex::Vertex()
{

}

Vertex::Vertex(Point3D input_A,Point3D input_B,Point3D input_C)
{
    A = input_A;
    B = input_B;
    C = input_C;

    normaleX = 0;
    normaleY = 0;
    normaleZ = 0;

    int lumiereX = 20;
    int lumiereY = 1;
    int lumiereZ = 20;
    int distance_max = 10;

    //lumiere en 10,10,1
    eclairage_A = 0.1+(distance_max-sqrt(((lumiereX-A.GetPosition().x)*(lumiereX-A.GetPosition().x)) + ((lumiereY-A.GetPosition().y)*(lumiereY-A.GetPosition().y)) + ((lumiereZ-A.GetPosition().z)*(lumiereZ-A.GetPosition().z))))/distance_max*0.9;
    eclairage_B = 0.1+(distance_max-sqrt(((lumiereX-B.GetPosition().x)*(lumiereX-B.GetPosition().x)) + ((lumiereY-B.GetPosition().y)*(lumiereY-B.GetPosition().y)) + ((lumiereZ-B.GetPosition().z)*(lumiereZ-B.GetPosition().z))))/distance_max*0.9;
    eclairage_C = 0.1+(distance_max-sqrt(((lumiereX-C.GetPosition().x)*(lumiereX-C.GetPosition().x)) + ((lumiereY-C.GetPosition().y)*(lumiereY-C.GetPosition().y)) + ((lumiereZ-C.GetPosition().z)*(lumiereZ-C.GetPosition().z))))/distance_max*0.9;
}

Vertex::Vertex(Point3D input_A,Point3D input_B,Point3D input_C, GLuint input_texture, bool * input_LIGHT, bool * input_NORM)
{
    A = input_A;
    B = input_B;
    C = input_C;
    texture = input_texture;

    LIGHT = input_LIGHT;

    int lumiereX = 15;
    int lumiereY = 1;
    int lumiereZ = 18;
    float eclairage_min = 0.4;
    float distance_max = 15;

    //lumiere en 10,10,1

    float dist_a = sqrt(((lumiereX-A.GetPosition().x)*(lumiereX-A.GetPosition().x)) + ((lumiereY-A.GetPosition().y)*(lumiereY-A.GetPosition().y)) + ((lumiereZ-A.GetPosition().z)*(lumiereZ-A.GetPosition().z)));
    float dist_b = sqrt(((lumiereX-B.GetPosition().x)*(lumiereX-B.GetPosition().x)) + ((lumiereY-B.GetPosition().y)*(lumiereY-B.GetPosition().y)) + ((lumiereZ-B.GetPosition().z)*(lumiereZ-B.GetPosition().z)));
    float dist_c = sqrt(((lumiereX-C.GetPosition().x)*(lumiereX-C.GetPosition().x)) + ((lumiereY-C.GetPosition().y)*(lumiereY-C.GetPosition().y)) + ((lumiereZ-C.GetPosition().z)*(lumiereZ-C.GetPosition().z)));

    if(dist_a >= distance_max)
    {
        eclairage_A = eclairage_min;
    }
    else
    {
         eclairage_A = eclairage_min+((distance_max-dist_a)/distance_max)*(1-eclairage_min);
    }

    if(dist_b >= distance_max)
    {
        eclairage_B = eclairage_min;
    }
    else
    {
        eclairage_B = eclairage_min+((distance_max-dist_b)/distance_max)*(1-eclairage_min);
    }

    if(dist_c >= distance_max)
    {
        eclairage_C = eclairage_min;
    }
    else
    {
        eclairage_C = eclairage_min+((distance_max-dist_c)/distance_max)*(1-eclairage_min);
    }

    coord_texture_x_1 = 0;
    coord_texture_x_2 = 1;
    coord_texture_y_1 = 0;
    coord_texture_y_2 = 1;
}

Vertex::Vertex(Point3D input_A,Point3D input_B,Point3D input_C, GLuint input_texture, float input_coord_texture_x_1, float input_coord_texture_y_1, float input_coord_texture_x_2, float input_coord_texture_y_2, bool * input_LIGHT, bool * input_NORM, bool input_hautgauche)
{
    A = input_A;
    B = input_B;
    C = input_C;
    texture = input_texture;

    float temp1 = (A.GetPosition().y - B.GetPosition().y);
    float temp2 = (A.GetPosition().y - C.GetPosition().y);
    if(temp1 < 0 )
    {temp1*=-1;}
    if(temp2 < 0 )
    {temp2*=-1;}

    if(temp1 > temp2)
    {
        normaleY = (3-temp1)/3;
    }
    else
    {
        normaleY = (3-temp2)/3;
    }

    if(B.GetPosition().x == A.GetPosition().x)
    {
        hautGauche = false;
        monteeX = C.GetPosition().y - B.GetPosition().y;
        monteeZ = B.GetPosition().y - A.GetPosition().y;
    }
    else
    {
        hautGauche = true;
        monteeX = A.GetPosition().y - C.GetPosition().y;
        monteeZ = B.GetPosition().y - C.GetPosition().y;
    }

    LIGHT = input_LIGHT;
    NORM = input_NORM;

    int lumiereX = 15;
    int lumiereY = 1;
    int lumiereZ = 18;
    float eclairage_min = 0.4;
    float distance_max = 15;

    //lumiere en 10,10,1

    float dist_a = sqrt(((lumiereX-A.GetPosition().x)*(lumiereX-A.GetPosition().x)) + ((lumiereY-A.GetPosition().y)*(lumiereY-A.GetPosition().y)) + ((lumiereZ-A.GetPosition().z)*(lumiereZ-A.GetPosition().z)));
    float dist_b = sqrt(((lumiereX-B.GetPosition().x)*(lumiereX-B.GetPosition().x)) + ((lumiereY-B.GetPosition().y)*(lumiereY-B.GetPosition().y)) + ((lumiereZ-B.GetPosition().z)*(lumiereZ-B.GetPosition().z)));
    float dist_c = sqrt(((lumiereX-C.GetPosition().x)*(lumiereX-C.GetPosition().x)) + ((lumiereY-C.GetPosition().y)*(lumiereY-C.GetPosition().y)) + ((lumiereZ-C.GetPosition().z)*(lumiereZ-C.GetPosition().z)));

    if(dist_a >= distance_max)
    {
        eclairage_A = eclairage_min;
    }
    else
    {
         eclairage_A = eclairage_min+((distance_max-dist_a)/distance_max)*(1-eclairage_min);
    }

    if(dist_b >= distance_max)
    {
        eclairage_B = eclairage_min;
    }
    else
    {
        eclairage_B = eclairage_min+((distance_max-dist_b)/distance_max)*(1-eclairage_min);
    }

    if(dist_c >= distance_max)
    {
        eclairage_C = eclairage_min;
    }
    else
    {
        eclairage_C = eclairage_min+((distance_max-dist_c)/distance_max)*(1-eclairage_min);
    }

    coord_texture_x_1 = input_coord_texture_x_1;
    coord_texture_x_2 = input_coord_texture_x_2;
    coord_texture_y_1 = input_coord_texture_y_1;
    coord_texture_y_2 = input_coord_texture_y_2;

    angleX = acos((1 + ((1*1 + monteeX*monteeX)) - monteeX*monteeX)/(2*(sqrt(1*1 + monteeX*monteeX))*1))/3.1416*180;
    if((monteeX > 0 && hautGauche) || (monteeX < 0 && !hautGauche))
    {
        angleX = angleX*-1;
    }

    angleZ = acos((1 + ((1*1 + monteeZ*monteeZ)) - monteeZ*monteeZ)/(2*(sqrt(1*1 + monteeZ*monteeZ))*1))/3.1416*180;
    if((monteeZ > 0 && hautGauche) || (monteeZ < 0 && !hautGauche))
    {
        angleZ = angleZ*-1;
    }

    /*
    cout << "Nouveau vertex : " << endl;
    cout << "A : " << A.GetPosition().x << ", " << A.GetPosition().y << ", " << A.GetPosition().z << endl;
    cout << "B : " << B.GetPosition().x << ", " << B.GetPosition().y << ", " << B.GetPosition().z << endl;
    cout << "C : " << C.GetPosition().x << ", " << C.GetPosition().y << ", " << C.GetPosition().z << endl;
    cout << "MonteeX : " << monteeX << endl;
    cout << "MonteeZ : " << monteeZ << endl;
    cout << "angleX : " << angleX << endl;
    cout << "angleZ : " << angleZ << endl;

    if(A.GetPosition().x == B.GetPosition().x)
    {
        cout << "altitude : " << A.GetPosition().x+0.25 << ", " << A.GetPosition().y<< "+ (" << monteeX << "*" << 0.25 <<  " - " << monteeZ << "*" << 0.75<< ")="<<A.GetPosition().y-(monteeX*0.25 + monteeZ*0.75)<< ", " <<A.GetPosition().z+0.75<< endl<< endl;
    }
    else
    {
        cout << "altitude : " << A.GetPosition().x+0.75 << ", " << A.GetPosition().y<< "+ (" << monteeX << "*" << 0.75 <<  " + " << monteeZ << "*" << 0.25<< ")="<<A.GetPosition().y+(monteeX*0.75 + monteeZ*0.25)<< ", " <<A.GetPosition().z+0.25<< endl<< endl;
    }
    */
}

void Vertex::set_eclairage_normale(float valeur_pour_A, float valeur_pour_B, float valeur_pour_C)
{
    eclairage_normale_A = valeur_pour_A;
    eclairage_normale_B = valeur_pour_B;
    eclairage_normale_C = valeur_pour_C;
}

void Vertex::calcule_normale()
{
    float temp1 = (A.GetPosition().y - B.GetPosition().y);
    float temp2 = (A.GetPosition().y - C.GetPosition().y);
    if(temp1 < 0 )
    {temp1*=-1;}
    if(temp2 < 0 )
    {temp2*=-1;}

    if(temp1 > temp2)
    {
        normaleY = (3-temp1)/3;
    }
    else
    {
        normaleY = (3-temp2)/3;
    }
}

float Vertex::get_normale_moyenne()
{
    return normaleY;
}

void Vertex::calcule_normale2()
{
    if(!hautGauche)
    {
        monteeX = C.GetPosition().y - B.GetPosition().y;
        monteeZ = B.GetPosition().y - A.GetPosition().y;
    }
    else
    {
        monteeX = A.GetPosition().y - C.GetPosition().y;
        monteeZ = B.GetPosition().y - C.GetPosition().y;
    }

    //La montée est correcte !

    //essayons de trouver les angles

    angleX = acos((1 + ((1*1 + monteeX*monteeX)) - monteeX*monteeX)/(2*(sqrt(1*1 + monteeX*monteeX))*1))/3.1416*180;
    if((monteeX > 0 && hautGauche) || (monteeX < 0 && !hautGauche))
    {
        angleX = angleX*-1;
    }

    angleZ = acos((1 + ((1*1 + monteeZ*monteeZ)) - monteeZ*monteeZ)/(2*(sqrt(1*1 + monteeZ*monteeZ))*1))/3.1416*180;
    if((monteeZ > 0 && hautGauche) || (monteeZ < 0 && !hautGauche))
    {
        angleZ = angleZ*-1;
    }

    //valeur_minimum
    normaleY = 0.3;

    if((angleX*angleX) > (angleZ*angleZ))
    {
        float temp = angleX;
        if(temp < 0){temp = temp*-1;}
        normaleY += 0.7-(0.7*(temp)/90);
    }
    else
    {
        float temp = angleZ;
        if(temp < 0){temp = temp*-1;}
        normaleY += 0.7-(0.7*(temp)/90);
    }



    eclairage_normale_A = normaleY;
    eclairage_normale_B = normaleY;
    eclairage_normale_C = normaleY;

    /*
    cout << "normX : " << (-90+(normaleX))*90/3.1416 << endl;
    cout << "normY : " << normaleY << endl;
    cout << "normZ : " << (-90+(normaleZ))*90/3.1416 << endl;
    cout << "norm : " << normaleX << ", " << normaleZ << endl;
    cout << "lumi : " << x_lumiere << ", " << z_lumiere << endl;
    cout << "diff : " << x_lumiere-normaleX << ", " << z_lumiere-normaleZ << endl << endl;
    */
    /*
    cout << A.GetPosition().x << "," << A.GetPosition().z << " : " << B.GetPosition().x << "," << B.GetPosition().z << " : " << C.GetPosition().x << "," << C.GetPosition().z << endl;
    cout << "diff : " << difference_x << ", " << difference_z << endl;
    cout << "norm : " << normaleX << ", " << normaleZ << endl;
    if(A.GetPosition().x == B.GetPosition().x)
    {
        cout << "vect : " << A.GetPosition().x+0.25 << "," << A.GetPosition().y+getAltitude(0.25,0.75)<< "," << A.GetPosition().z+0.75 << " -> " << A.GetPosition().x+0.25-cos(normaleX/180*3.1416) << "," << A.GetPosition().y+getAltitude(0.25,0.75)+ 1<< "," << A.GetPosition().z+0.75-cos(normaleZ/180*3.1416) << endl << endl;
    }
    else
    {
        cout << "vect : " << A.GetPosition().x+0.75 << "," << A.GetPosition().y+getAltitude(0.75,0.25)<< "," << A.GetPosition().z+0.25 << " -> " << A.GetPosition().x+0.75-cos(normaleX/180*3.1416) << "," << A.GetPosition().y+getAltitude(0.75,0.25)+ 1 << "," << A.GetPosition().z+0.25-cos(normaleZ/180*3.1416) << endl << endl;
    }
    */
}

void Vertex::tracer_normale()
{
    if(A.GetPosition().x == B.GetPosition().x)
    {
        glPushMatrix();
        //on se déplace à l'endroit ou tracer le vertex
        glTranslated(A.GetPosition().x+0.25,getAltitude(0.25,0.75),A.GetPosition().z+0.75);
        glRotated(angleX,0,0,1);
        glRotated(angleZ,1,0,0);
        glBegin(GL_LINES);
            glVertex3f(0,0,0);
            glVertex3f(0,1,0);
        glEnd();
        glPopMatrix(); //hop je remets tout comme je l'ai trouvé
    }
    else
    {
        glPushMatrix();
        //on se déplace à l'endroit ou tracer le vertex
        glTranslated(A.GetPosition().x+0.75,getAltitude(0.75,0.25),A.GetPosition().z+0.25);
        glRotated(angleX,0,0,1);
        glRotated(angleZ,1,0,0);
        glBegin(GL_LINES);
            glVertex3f(0,0,0);
            glVertex3f(0,1,0);
            //glVertex3f(A.GetPosition().x+0.75,getAltitude(0.75,0.25),A.GetPosition().z+0.25);
            //glVertex3f(A.GetPosition().x+0.75-cos(angleX+90),1+getAltitude(0.75,0.25),A.GetPosition().z+0.25-cos(angleZ+90));
        glEnd();
        glPopMatrix(); //hop je remets tout comme je l'ai trouvé
    }
}


void Vertex::changeTexture(GLuint nouvelleTexture)
{
    texture = nouvelleTexture;
}

float Vertex::getAltitude(float x, float z)
{
    if(hautGauche)
    {
        return A.GetPosition().y-(monteeX*x + monteeZ*z);
    }
    else
    {
        return A.GetPosition().y+(monteeX*x + monteeZ*z);
    }
}

void Vertex::afficher_haut_gauche_lignes()
{

    glBegin(GL_LINE_LOOP);
    glVertex3d(A.GetPosition().x,A.GetPosition().y,A.GetPosition().z);
    glVertex3d(B.GetPosition().x,B.GetPosition().y,B.GetPosition().z);
    glVertex3d(C.GetPosition().x,C.GetPosition().y,C.GetPosition().z);
    glEnd();

}

void Vertex::afficher_bas_droite_lignes()
{
    glBegin(GL_LINE_LOOP);
    glVertex3d(A.GetPosition().x,A.GetPosition().y,A.GetPosition().z);
    glVertex3d(B.GetPosition().x,B.GetPosition().y,B.GetPosition().z);
    glVertex3d(C.GetPosition().x,C.GetPosition().y,C.GetPosition().z);
    glEnd();
}


void Vertex::afficher_haut_gauche_texture()
{
    glBindTexture(GL_TEXTURE_2D, texture);
    glBegin(GL_TRIANGLES);

    if( *LIGHT == true)
    {
        glColor3f(eclairage_A,eclairage_A,eclairage_A);
    }
    else if(*NORM==true)
    {
        glColor3f(eclairage_normale_A,eclairage_normale_A,eclairage_normale_A);
    }
    glTexCoord2d(coord_texture_x_1,coord_texture_y_1);
    glVertex3d(A.GetPosition().x,A.GetPosition().y,A.GetPosition().z);

    if( *LIGHT == true)
    {
        glColor3f(eclairage_B,eclairage_B,eclairage_B);
    }
    else if(*NORM==true)
    {
        glColor3f(eclairage_normale_B,eclairage_normale_B,eclairage_normale_B);
    }
    glTexCoord2d(coord_texture_x_2,coord_texture_y_1);


    glVertex3d(B.GetPosition().x,B.GetPosition().y,B.GetPosition().z);
    glTexCoord2d(coord_texture_x_2,coord_texture_y_2);

    if( *LIGHT == true)
    {
        glColor3f(eclairage_C,eclairage_C,eclairage_C);
    }
    else if(*NORM==true)
    {
        glColor3f(eclairage_normale_C,eclairage_normale_C,eclairage_normale_C);
    }

    glVertex3d(C.GetPosition().x,C.GetPosition().y,C.GetPosition().z);
    glEnd();
}

void Vertex::afficher_bas_droite_texture()
{
    glBindTexture(GL_TEXTURE_2D, texture);

    glBegin(GL_TRIANGLES);
    if( *LIGHT == true)
    {
        glColor3f(eclairage_A,eclairage_A,eclairage_A);
    }
    else if(*NORM==true)
    {
        glColor3f(eclairage_normale_A,eclairage_normale_A,eclairage_normale_A);
    }
    glTexCoord2d(coord_texture_x_1,coord_texture_y_1);
    glVertex3d(A.GetPosition().x,A.GetPosition().y,A.GetPosition().z);

    if( *LIGHT == true)
    {
        glColor3f(eclairage_B,eclairage_B,eclairage_B);
    }

    else if(*NORM==true)
    {
        glColor3f(eclairage_normale_B,eclairage_normale_B,eclairage_normale_B);
    }
    glTexCoord2d(coord_texture_x_2,coord_texture_y_2);
    glVertex3d(B.GetPosition().x,B.GetPosition().y,B.GetPosition().z);

    if( *LIGHT == true)
    {
        glColor3f(eclairage_C,eclairage_C,eclairage_C);
    }
    else if(*NORM==true)
    {
        glColor3f(eclairage_normale_C,eclairage_normale_C,eclairage_normale_C);
    }
    glTexCoord2d(coord_texture_x_1,coord_texture_y_2);
    glVertex3d(C.GetPosition().x,C.GetPosition().y,C.GetPosition().z);
    glEnd();
}
