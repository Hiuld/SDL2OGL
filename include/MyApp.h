#ifndef MYAPP_H
#define MYAPP_H

#include "CApplication.h"

class MyApp : public CApplication
{
    // Fonctions d'�v�nements issues de la classe CApplication
    virtual void OnInitialize();
    virtual void OnUpdate();
    virtual void OnRender();
    virtual void OnEvent(SDL_Event& event);
    // Fonctions d'�v�nements perso pour une simplification
    void MouseButtonDown(SDL_MouseButtonEvent &MouseButton);
    void MouseButtonUp  (SDL_MouseButtonEvent &MouseButton);
    void MouseMotion    (SDL_MouseMotionEvent &MouseMotion);
    void MouseWheel     (SDL_MouseWheelEvent  &Wheel);
    // Fonctions de rendu de certaine parties de la sc�ne
    void RenderGround();
    void RenderCube();
    void RenderPyramide();
    // rotation en X, Y et Z de la vue de models
    double rotX, rotY, rotZ;
    // position en X, Y et Z de la vue de models
    double posX, posY, posZ;
    // position en X, Y et Z de la cam�ra
    double camX, camY, camZ;
    // field of view (zoom)
    double fov;
    // variables pour le fun des models
    double a, b, c, d;
    int tt;
    // Texture g�n�r�e par programation,
    // C'est la texture par d�faut si une texture ne se charge pas
    void loadText( CTexture&, const char* );
    CTexture DefaultTex;
    // Textures provenant de fichier
    CTexture groundTex, glassTex, tileTex, planetTex[7];
    // Bool�en pour savoir si on utilise le mipmap, si le bouton gauche de la souris est appuy�, etc...
    bool m_LeftClick, mipmap, fullscreen;

    int x, y, lastx, lasty;

    public :
        ~MyApp(){}
};

#endif // MYAPP_H
