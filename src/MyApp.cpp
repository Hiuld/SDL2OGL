#include "MyApp.h"

#include <cmath>

void MyApp::OnInitialize()
{
    GLuint pixels[128*128];
    // Création de la texture
    for( int i = 0; i < 128*128; ++i )
    {
        GLubyte *couleurs = (GLubyte*)&pixels[i];
        if( i/128 & (16^(i%128)) & 16 )
        {
            couleurs[0] = 255;
            couleurs[1] = 255;
            couleurs[2] = 255;
            couleurs[3] = 255;
        }
        else
        {
            couleurs[0] = 255;
            couleurs[1] = 0;
            couleurs[2] = 0;
            couleurs[3] = 255;
        }
    }
    DefaultTex.LoadTextureFromPixels32(pixels, 128, 128, true);

    try
    {
        tileTex.LoadTextureFromFile("tiles_ctf05r.jpg",true);
        groundTex.LoadTextureFromFile("metal091.jpg",true);
        try
        {
            glassTex.LoadTextureFromFile("stainedglass05.jpg", true);
        }
        catch( C3DTextureException &e )
        {
            glassTex = DefaultTex;
        }
    }
    catch( C3DTextureException &e )
    {
        groundTex = DefaultTex;
    }

    SetTitle("Un titre");
    //SetIcon(icone);
    rotX = rotY = rotZ = 0.0;
    posX = posY = posZ = 0.0;
    //rotY = 45;
    fpsLimit = 60;
    m_Renderer.SetPerspective(70, (double)1024/768, 1, 1000);
    //rotateOnX = true; rotateOnY = true;
    mipmap = false;
    fullscreen = false;
    m_LeftClick = false;
    fov = 70;
    c = b = a = 0;
    camX = 3;
    camY = 0;
    camZ = 3;
    monte = true;
}

void MyApp::OnUpdate()
{
    m_Renderer.ReinitMatrix(GL_MODELVIEW);

    gluLookAt(camX,camY,camZ,0,0,0,0,0,1);

    glTranslated(posX, posY, posZ);
    glRotated(rotX, 1, 0, 0);
    glRotated(rotY, 0, 1, 0);
    glRotated(rotZ, 0, 0, 1);
}

void MyApp::RenderGround()
{
    m_Renderer.Load2DTexture(groundTex);
    glBegin(GL_QUADS);
        glColor3ub(255,0,0); glTexCoord2f(0,0);      glVertex3i(-10,-10,-1);
        glColor3ub(0,255,0); glTexCoord2f(10,0);     glVertex3i(10,-10,-1);
        glColor3ub(0,0,255); glTexCoord2f(10,10);    glVertex3i(10,10,-1);
        glColor3ub(255,255,255); glTexCoord2f(0,10);     glVertex3i(-10,10,-1);
    glEnd();
}

void MyApp::RenderCube()
{
    m_Renderer.PushMatrix(GL_MODELVIEW);

    a += 0.05;

    glTranslated(cos(a)*3, 0, 0);

    m_Renderer.Load2DTexture(glassTex);

    for (int i = 0; i < 4; i++)
    {
        glBegin(GL_QUADS);
            glTexCoord2d(0,1);
            glVertex3d(1,1,1);
            glTexCoord2d(0,0);
            glVertex3d(1,1,-1);
            glTexCoord2d(1,0);
            glVertex3d(-1,1,-1);
            glTexCoord2d(1,1);
            glVertex3d(-1,1,1);
        glEnd();
        glRotated(90,0,0,1);
    }
    glBegin(GL_QUADS);
        glTexCoord2d(0,0);
        glVertex3d(1,-1,1);
        glTexCoord2d(1,0);
        glVertex3d(1,1,1);
        glTexCoord2d(1,1);
        glVertex3d(-1,1,1);
        glTexCoord2d(0,1);
        glVertex3d(-1,-1,1);
    glEnd();

    m_Renderer.PopMatrix(GL_MODELVIEW);
}

void MyApp::RenderPyramide()
{
    m_Renderer.PushMatrix(GL_MODELVIEW);

    b += M_PI/80;
    c += M_PI/150;

    if( b >= M_PI )
        b = 0;

    if( c >= M_PI )
        c = 0;

    glTranslated(0, sin(c)+5, 1-sin(b));

    m_Renderer.Load2DTexture(tileTex);
    for (int i = 0; i < 4; i++)
    {
        glBegin(GL_TRIANGLES);
            glTexCoord2d(i%2,0);
            glVertex3d(1,1,-1);
            glTexCoord2d((i+1)%2,0);
            glVertex3d(-1,1,-1);
            glTexCoord2d(0.5,1);
            glVertex3d(0,0,1);
        glEnd();
        glRotated(90,0,0,1);
    }

    m_Renderer.PopMatrix(GL_MODELVIEW);
}

void MyApp::OnRender()
{
    RenderGround();
    RenderCube();
    RenderPyramide();
}

void MyApp::OnEvent(SDL_Event& event)
{
    switch( event.type )
    {
        case SDL_QUIT: Quit(); break;
        case SDL_KEYDOWN:
            switch( event.key.keysym.sym )
            {
                case SDLK_ESCAPE: Quit(); break;
                case SDLK_z       : ++posX; break;
                case SDLK_s       : --posX; break;
                case SDLK_q       : ++posY; break;
                case SDLK_d       : --posY; break;
                case SDLK_PAGEDOWN: m_Renderer.SetPerspective(fov+=2,(double)1024/768, 1, 1000 ); break;
                case SDLK_PAGEUP  : m_Renderer.SetPerspective(fov-=2,(double)1024/768, 1, 1000 ); break;
                case SDLK_END     : m_Renderer.SetPerspective(fov=70, (double)1024/768, 1, 1000); break;
                case SDLK_KP_PLUS : SetFPSLimit(fpsLimit < 60 ? ++fpsLimit : 0); break;
                case SDLK_KP_MINUS: SetFPSLimit(fpsLimit > 30  ? --fpsLimit : 0); break;
                case SDLK_c       :
                    mipmap = !mipmap;
                    try
                    {
                        groundTex.LoadTextureFromFile("metal091.jpg", mipmap);
                    }
                    catch( C3DTextureException &e )
                    {
                        groundTex = DefaultTex;
                    }
                    break;
                case SDLK_f       :
                    /*fullscreen = !fullscreen;
                    if( fullscreen )
                    {
                        SDL_SetWindowFullscreen(m_Window, SDL_WINDOW_FULLSCREEN);
                        SDL_SetWindowSize(m_Window, 1280, 1024);
                    }
                    else
                    {
                        SDL_SetWindowFullscreen(m_Window, SDL_WINDOW_SHOWN);
                        SDL_SetWindowSize(m_Window, 1024, 768);
                    }*/

                    break;
            }
        case SDL_MOUSEBUTTONDOWN: MouseButtonDown(event.button); break;
        case SDL_MOUSEBUTTONUP  :   MouseButtonUp(event.button); break;
        case SDL_MOUSEMOTION    :     MouseMotion(event.motion); break;
        case SDL_MOUSEWHEEL     :      MouseWheel(event.wheel ); break;
    }
}



void MyApp::MouseButtonDown(SDL_MouseButtonEvent& MouseButton)
{
    switch( MouseButton.button )
    {
        case SDL_BUTTON_LEFT:
            m_LeftClick = true;
            x = MouseButton.x;
            y = MouseButton.y;
            break;
    }
}

void MyApp::MouseButtonUp(SDL_MouseButtonEvent& MouseButton)
{
    switch( MouseButton.button )
    {
        case SDL_BUTTON_LEFT:
            m_LeftClick = false;
            break;
    }
}

void MyApp::MouseMotion(SDL_MouseMotionEvent& MouseMotion)
{
    // Si le bouton gauche de la souris est appuyé
    if( m_LeftClick )
    {
        // Sauvegarde de l'ancienne coordonnée de x et y
        lastx = x; lasty = y;
        // Récupération des nouvelles coordonnées
        SDL_GetMouseState(&x, &y);
        // Calculer le déplacement
        rotZ += (double)(x - lastx)/2;
        // %360 pour que la rotation soit comprise entre -359.99 et +359.99
        rotZ = std::fmod(rotZ, 360.0);
        rotY += (double)(y - lasty)/2;
        rotY = std::fmod(rotY, 360.0);
    }
}

void MyApp::MouseWheel(SDL_MouseWheelEvent& Wheel)
{
    if( Wheel.y < 0 )
    {
        camZ += 0.5;
    }
    else
    {
        camZ -= 0.5;
    }
}

