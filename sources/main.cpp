#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <GL/gl.h>
#include <GL/glu.h>
#include <string>

#include "Point3D.hpp"
#include "Surface.hpp"
#include "Model.hpp"
#include "Tools.hpp"
#include "Lumiere.hpp"
#include "FlyingCamera.hpp"
#include "ModelLoaderCamera.hpp"
#include "Animation.hpp"
#include "Objet3D.hpp"

#define PI 3.14159265358979323846

using namespace std;

int main()
{
    sf::WindowSettings settings(24,8,2 );
    sf::Window App(sf::VideoMode(800, 600, 32), "SFML OpenGL", sf::Style::Close, settings);
    App.UseVerticalSync(true);
    App.SetFramerateLimit(60);
    App.EnableKeyRepeat(true);

    // Create a clock for measuring time elapsed
    sf::Clock Clock;
    sf::Clock ClockAnimation;

   // Set color and depth clear value
    glClearDepth(1.f);
    glClearColor(0.4, 0.4, 0.8, 0.f);

    // Enable Z-buffer read and write
    glEnable(GL_DEPTH_TEST);
    glDepthMask(GL_TRUE);
    glEnable(GL_TEXTURE_2D);

    // Setup a perspective projection
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    Lumiere lumiere(0,100,100,120);
    int angleLumiere = 0;

    Objet3D canard(&lumiere,"duck_step2",1);

    canard.AddAnimation("duck_step2",&lumiere,48);

    glDisable(GL_TEXTURE_2D);

    Clock.Reset();
    ClockAnimation.Reset();
    //int frame = 0;

    bool lignes = true;
    glColor3ub(255,50,50);

    glMatrixMode(GL_MODELVIEW);

    FlyingCamera camera(sf::Vector3f(0,2,3),sf::Vector3f(0,2,2));

    bool rotX = false;
    bool rotY = false;
    bool rotZ = false;

    float angleX = 0;
    float angleY = 0;
    float angleZ = 0;

    const sf::Input& Input = App.GetInput();

    // Start game loop
    while (App.IsOpened())
    {
        /*frame++;
        if(Clock.GetElapsedTime() > 1)
        {*/
            //cout << frame << endl;
            //frame = 0;

        //}
        // Process events

        //la lumiere tourne
        lumiere.x = Tools::RotationPoint2D(lumiere.x,lumiere.z,PI/180).x;
        lumiere.z = Tools::RotationPoint2D(lumiere.x,lumiere.z,PI/180).y;

        sf::Event Event;

        while (App.GetEvent(Event))
        {
            // Close window : exit
            if (Event.Type == sf::Event::Closed || ((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Key::Escape)))
                App.Close();

            if ((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Key::F1))
            {
                if(!lignes)
                {
                    cout << "Affichage de lignes" << endl;
                    lignes = true;
                }
                else
                {
                    cout << "Affichage de couleur" << endl;
                    lignes = false;
                }
            }

            if ((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Key::F2))
            {
                if(!rotX)
                {
                    rotX = true;
                }
                else
                {
                    rotX = false;
                }
            }

            if ((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Key::F3))
            {
                if(!rotY)
                {
                    rotY = true;
                }
                else
                {
                    rotY = false;
                }
            }

            if ((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Key::F4))
            {
                if(!rotZ)
                {
                    rotZ = true;
                }
                else
                {
                    rotZ = false;
                }
            }

            if ((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Key::Up))
            {
                lumiere.z+=0.2;
            }

            if ((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Key::Down))
            {
                lumiere.z-=0.2;
            }

            if ((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Key::Left))
            {
                lumiere.x+=0.2;
            }

            if ((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Key::Right))
            {
                lumiere.x-=0.2;
            }

            if ((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Key::PageUp))
            {
                lumiere.y+=0.2;
            }

            if ((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Key::PageDown))
            {
                lumiere.y-=0.2;
            }

            if((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Key::C))
            {
                angleX = 0;
                angleY = 0;
                angleZ = 0;
            }

            if((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Key::J))
            {
                canard.PlayAnimation(1);
            }
        }

        camera.handleSfmlRealtimeInput(Input);

        App.SetActive();

        // Clear color and depth buffer
        glMatrixMode(GL_MODELVIEW);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glLoadIdentity();

        camera.LookAt();

        if(rotX)
        {
            angleX += 0.5;
        }

        if(rotY)
        {
            angleY += 0.5;
        }

        if(rotZ)
        {
            angleZ += 0.5;
        }

        //modele1.SetAngle(angleX,angleY,angleZ);

            //le cube de lumieregl
            glDisable(GL_TEXTURE_2D);
            glPointSize( 20 );
            glBegin(GL_POINTS);
                glColor3ub(255,255,255);
                glVertex3f(lumiere.x,lumiere.y,lumiere.z);
            glEnd();
            glPointSize( 1 );


            /*if(lignes)
            {
                cubeAnime[animation].AfficherLignes();
            }
            else
            {
                cubeAnime[animation].Afficher();
            }*/

        canard.Afficher();

        //glPopMatrix();

        // Finally, display rendered frame on screen
        App.Display();
    }
    return 0;
}
