#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <GL/gl.h>
#include <GL/glu.h>
#include <string>

#include "Tools.hpp"
#include "Lumiere.hpp"
#include "FlyingCamera.hpp"
#include "ModelLoaderCamera.hpp"
#include "Map.hpp"
#include "Avatar.hpp"

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
    boutonsRotationLumiere.SetX(174);
    boutonsRotationLumiere.SetY(10);
    boutonsRotationLumiere.SetSubRect(sf::IntRect(160, 0, 322, 32));

    sf::Sprite boutonsFilDeFer;
    boutonsFilDeFer.SetImage(iBoutons);
    boutonsFilDeFer.SetX(340);
    boutonsFilDeFer.SetY(10);
    boutonsFilDeFer.SetSubRect(sf::IntRect(322, 0, 482, 32));

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

    sf::String text("Chargement du modele...", font, 30);
    text.SetColor(sf::Color(255,255,255));
    text.SetX(200);
    text.SetY(300);

    App.SetActive();
    App.Draw(text);
    App.Display();

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

    Lumiere lumiere(40,40,40,120);

    string nom;
    nom = "colonne";
    Objet3D colonne(&lumiere, nom, 1);
    colonne.SetPosition(10,0,3);

    //Objet3D objet3D(&lumiere,modele3DFile);
    //objet3D.SetPosition(5,5,5);

    Avatar avatar(5,0,5,&lumiere,modele3DFile);
    FlyingCamera camera(sf::Vector3f(1,4,5),sf::Vector3f(1,6,6));
    camera.SetPosition(avatar.GetCameraPosition());
    camera.SetCible(avatar.GetPosition());
    camera.Info();

    glDisable(GL_TEXTURE_2D);

    Clock.Reset();
    int frame = 0;
    ClockAnimation.Reset();

    glColor3ub(0,0,0);

    glMatrixMode(GL_MODELVIEW);

    //variable de l'angle de rotation du modèle.
    bool rotY = false;
    bool lignes = false;
    bool lightRotation = false;

    const sf::Input& Input = App.GetInput();

    int echelle = 4;
    Map map("map2",echelle,&lumiere);

    //map.calculNormaleParFace();
    //map.calculeNormaleParPoint();

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
            //rotation autour de Y
            sf::Vector2f temp = Tools::RotationPoint2D(lumiere.x,lumiere.z,PI/180);
            lumiere.x = temp.x;
            lumiere.z = temp.y;

            //rotation autour de Z
            //sf::Vector2f temp = Tools::RotationPoint2D(lumiere.x,lumiere.y,PI/180);
            //lumiere.x = temp.x;
            //lumiere.y = temp.y;
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
                        boutonsRotationLumiere.SetSubRect(sf::IntRect(160, 32, 322, 64));
                    }
                    else
                    {
                        lightRotation = false;
                        boutonsRotationLumiere.SetSubRect(sf::IntRect(160, 0, 322, 32));
                    }
                }

                if(Input.GetMouseX() > boutonsFilDeFer.GetPosition().x && Input.GetMouseX() <  boutonsFilDeFer.GetPosition().x+boutonsFilDeFer.GetSize().x
                   && Input.GetMouseY() > boutonsFilDeFer.GetPosition().y && Input.GetMouseY() <  boutonsFilDeFer.GetPosition().y+boutonsFilDeFer.GetSize().y)
                {
                    if(!lignes)
                    {
                        lignes = true;
                        boutonsFilDeFer.SetSubRect(sf::IntRect(322, 32, 482, 64));
                    }
                    else
                    {
                        lignes = false;
                        boutonsFilDeFer.SetSubRect(sf::IntRect(322, 0, 482, 32));
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
                    cout << "Affichage normal" << endl;
                    lignes = false;
                }
            }

            if ((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Key::T))
            {
                map.CalculeNormaleParPoint();
            }

            if((Event.Type == sf::Event::MouseWheelMoved))
            {
                if(Event.MouseWheel.Delta > 0)
                {
                    avatar.ModifyCameraDistance(-1);
                }
                else
                {
                    avatar.ModifyCameraDistance(1);
                }
            }
        }

        //sf::Vector3f positionMemoire = camera.GetPosition();
        avatar.HandleSfmlRealtimeInput(Input);

        if(avatar.GetPosition().x < 0)
        {
            avatar.SetPosition(sf::Vector3f(0,avatar.GetPosition().y,avatar.GetPosition().z));
        }

        if(avatar.GetPosition().z < 0)
        {
            avatar.SetPosition(sf::Vector3f(avatar.GetPosition().x,avatar.GetPosition().y,0));
        }

        if(avatar.GetPosition().x > map.GetLimitX())
        {
            avatar.SetPosition(sf::Vector3f(map.GetLimitX(),avatar.GetPosition().y,avatar.GetPosition().z));
        }

         if(avatar.GetPosition().z > map.GetLimitZ())
        {
            avatar.SetPosition(sf::Vector3f(avatar.GetPosition().x,avatar.GetPosition().y,map.GetLimitZ()));
        }

        avatar.SetPosition(sf::Vector3f(avatar.GetPosition().x,map.GetAltitude(avatar.GetPosition().x,avatar.GetPosition().z),avatar.GetPosition().z));

        camera.SetPosition(avatar.GetCameraPosition());
        camera.SetCible(avatar.GetPosition());

        App.SetActive();
        App.Clear(sf::Color(0, 0, 0));

        // Clear color and depth buffer
        glMatrixMode(GL_MODELVIEW);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glLoadIdentity();

        camera.LookAt();

        if(lightRotation)
        {

        }

        if(lignes)
        {
            avatar.AfficherLignes();
            map.AfficherLigne();
            colonne.AfficherLignes();
        }
        else
        {
            avatar.Afficher();
            map.Afficher();
            colonne.Afficher();
        }

        Tools::AfficherAxes();
        Tools::AfficherPoint(lumiere.x, lumiere.y, lumiere.z, 255, 255 , 255);

        App.Draw(menu);
        App.Draw(boutonsRotationModele);
        App.Draw(boutonsRotationLumiere);
        App.Draw(boutonsFilDeFer);
        App.Draw(text);

        App.Display();
    }
    return 0;
}
