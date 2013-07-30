#ifndef DEF_ANIMATION
#define DEF_ANIMATION

#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <GL/gl.h>
#include <GL/glu.h>
#include <string>
#include <vector>

#include "Model.hpp"
#include "Lumiere.hpp"
#include "Tools.hpp"

using namespace std;

class Animation
{
    public :
    Animation(string modeleName, Lumiere *lumiere, int frameNumber);
    Animation();
    void modify(string modeleName, Lumiere *lumiere, int frameNumber);
    bool Afficher();
    void Play();
    void Play(bool loop_);
    void Stop();

    private :
    sf::Clock clock;
    vector<Model> modeles;
    float frameDelay;
    bool loop;
    bool playing;
    int playedFrameNumber;
};

#endif

