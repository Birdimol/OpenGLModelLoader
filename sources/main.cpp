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
    string modele3DFile = Tools::modelSelectionConsoleMenu();

    //parametres liés à config.ini
    map<string, int> config = Tools::getConfig();

    sf::WindowSettings settings(24,8,config["antialiasing"]);

    int windowStyle;

    if(config["fullscreen"] == 1)
    {
        windowStyle = sf::Style::Fullscreen;
    }
    else
    {
        windowStyle = sf::Style::Close;
    }

    sf::RenderWindow App(sf::VideoMode(config["window_width"], config["window_height"], 32), "SFML OpenGL", windowStyle, settings);
    //------------------


    //MENU-------------------------------------------------------


    sf::Image iBoutons;
    if (!iBoutons.LoadFromFile("images/boutons.png"))
    {
        cout << "images/boutons.png introuvable." << endl;
    }
    sf::Sprite boutonsRotationModele;
    boutonsRotationModele.SetImage(iBoutons);
    boutonsRotationModele.SetX(10);
    boutonsRotationModele.SetY(10);
    boutonsRotationModele.SetSubRect(sf::IntRect(0, 0, 158, 32));

    sf::Sprite boutonsRotationLumiere;
    boutonsRotationLumiere.SetImage(iBoutons);
    boutonsRotationLumiere.SetX(170);
    boutonsRotationLumiere.SetY(10);
    boutonsRotationLumiere.SetSubRect(sf::IntRect(160, 0, 330, 32));

    sf::Sprite menu;
    menu.SetImage(iBoutons);
    menu.SetSubRect(sf::IntRect(0, 100, 1024, 150));
    menu.SetX(0);
    menu.SetY(0);
    //------------------------------------------------------------

    App.UseVerticalSync(true);
    App.SetFramerateLimit(60);
    App.EnableKeyRepeat(true);
    App.PreserveOpenGLStates(true);

    sf::Font font;
    if (!font.LoadFromFile("police/arial.ttf"))
    {
        cout << "impossible de charger la police d'ecriture 'police/arial.ttf'." << endl;
        return 1;
    }

    sf::String text("FPS : ??", font, 30);
    text.SetColor(sf::Color(0,0,0));
    text.SetX(650);
    text.SetY(10);

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

    Objet3D objet3D(&lumiere,modele3DFile,1);

    //objet3D.AddAnimation("duck_step2",&lumiere,48);

    glDisable(GL_TEXTURE_2D);

    Clock.Reset();
    int frame = 0;
    ClockAnimation.Reset();

    glColor3ub(0,0,0);

    glMatrixMode(GL_MODELVIEW);

    ModelLoaderCamera camera(sf::Vector3f(0,4,4),sf::Vector3f(0,4,2));

    bool rotX = false;
    bool rotY = false;
    bool rotZ = false;

    bool lignes = true;
    bool lightRotation = false;

    float angleX = 0;
    float angleY = 0;
    float angleZ = 0;

    const sf::Input& Input = App.GetInput();

    // Start game loop
    while (App.IsOpened())
    {
        frame++;
        if(Clock.GetElapsedTime() > 1)
        {
            text.SetText("FPS : " + Tools::IntToString(frame));
            frame = 0;
            Clock.Reset();
        }

        //la lumiere tourne
        if(lightRotation)
        {
            lumiere.x = Tools::RotationPoint2D(lumiere.x,lumiere.z,PI/180).x;
            lumiere.z = Tools::RotationPoint2D(lumiere.x,lumiere.z,PI/180).y;
        }

        sf::Event Event;

        while (App.GetEvent(Event))
        {
            // Close window : exit
            if (Event.Type == sf::Event::Closed || ((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Key::Escape)))
                App.Close();

            if (Event.Type == sf::Event::MouseButtonPressed)
            {
                if(Input.GetMouseX() > boutonsRotationModele.GetPosition().x && Input.GetMouseX() <  boutonsRotationModele.GetPosition().x+boutonsRotationModele.GetSize().x
                   && Input.GetMouseY() > boutonsRotationModele.GetPosition().y && Input.GetMouseY() <  boutonsRotationModele.GetPosition().y+boutonsRotationModele.GetSize().y)
                {
                    if(!rotY)
                    {
                        rotY = true;
                        boutonsRotationModele.SetSubRect(sf::IntRect(0, 32, 158, 64));
                    }
                    else
                    {
                        rotY = false;
                        boutonsRotationModele.SetSubRect(sf::IntRect(0, 0, 158, 32));
                    }
                }

                if(Input.GetMouseX() > boutonsRotationLumiere.GetPosition().x && Input.GetMouseX() <  boutonsRotationLumiere.GetPosition().x+boutonsRotationLumiere.GetSize().x
                   && Input.GetMouseY() > boutonsRotationLumiere.GetPosition().y && Input.GetMouseY() <  boutonsRotationLumiere.GetPosition().y+boutonsRotationLumiere.GetSize().y)
                {
                    if(!lightRotation)
                    {
                        lightRotation = true;
                        boutonsRotationLumiere.SetSubRect(sf::IntRect(160, 32, 330, 64));
                    }
                    else
                    {
                        lightRotation = false;
                        boutonsRotationLumiere.SetSubRect(sf::IntRect(160, 0, 330, 32));
                    }
                }
            }

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

            if((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Key::C))
            {
                angleX = 0;
                angleY = 0;
                angleZ = 0;
            }

            if((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Key::J))
            {
                objet3D.PlayAnimation(1);
            }
        }

        camera.handleSfmlRealtimeInput(Input);

        App.SetActive();

        // Clear color and depth buffer
        glMatrixMode(GL_MODELVIEW);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glLoadIdentity();

        camera.LookAt();

        if(rotY)
        {
            angleY += 0.5;
            objet3D.SetAngle(angleX,angleY,angleZ);
        }

        objet3D.Afficher();

        App.Draw(menu);
        App.Draw(boutonsRotationModele);
        App.Draw(boutonsRotationLumiere);
        App.Draw(text);

        App.Display();
    }
    return 0;
}
