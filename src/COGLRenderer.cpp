#include "COGLRenderer.h"

GLUquadricObj* COGLRenderer::s_quadric = 0;

COGLRenderer::COGLRenderer():
    m_Window(NULL), m_Context(NULL)
{}

COGLRenderer::~COGLRenderer()
{
    gluDeleteQuadric(s_quadric);
    SDL_GL_DeleteContext(m_Context);
}

//////////////////////////////////////////////////////////////////
/// @name : Initialize (public)
/// @param : SDL_Window* : fenêtre où sera affichée le rendu
/// @return : aucun
/// Initialisation du Renderer sur la fenêtre spécifiée
//////////////////////////////////////////////////////////////////
bool COGLRenderer::Initialize(SDL_Window *Window)
{
    bool success = true;
    // La fenêtre initialisée par SDL
    m_Window = Window;
    // Création du contexte d'OGL sur la fenêtre
    m_Context = SDL_GL_CreateContext(m_Window);

    // OpenGL 2.1
    SDL_GL_SetAttribute( SDL_GL_CONTEXT_MAJOR_VERSION, 2 );
    SDL_GL_SetAttribute( SDL_GL_CONTEXT_MINOR_VERSION, 1 );

    // Initialiser la matrice de projection
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();

    if( GL_NO_ERROR != glGetError() )
        success = false;

    // Initialiser la matrice de vue des models
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();

    if( GL_NO_ERROR != glGetError() )
        success = false;

    // Initializer la couleur d'effacage
    glClearColor(0.f, 0.f, 0.f, 0.f );

    if( GL_NO_ERROR != glGetError() )
        success = false;
    // Activer le test de profondeur (ZBUFFER)
    glEnable(GL_DEPTH_TEST);

    return success;
}

//////////////////////////////////////////////////////////////////
/// @name : BeginScene const(public)
/// @param : aucun
/// @return : aucun
/// Démarre le rendu de la scène
//////////////////////////////////////////////////////////////////
void COGLRenderer::BeginScene() const
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
}

//////////////////////////////////////////////////////////////////
/// @name : EndScene const(public)
/// @param : aucun
/// @return : aucun
/// Termine le rendu et affiche la scène
//////////////////////////////////////////////////////////////////
void COGLRenderer::EndScene() const
{
    SDL_GL_SwapWindow(m_Window);
}

//////////////////////////////////////////////////////////////////
/// @name : ReinitMatrix (public)
/// @param : CEnums::Matrix : la matrice à réinitialiser
/// @return : aucun
/// remet les valeurs par défaut de la matrice
//////////////////////////////////////////////////////////////////
void COGLRenderer::ReinitMatrix(CEnums::Matrix mode)
{
    glMatrixMode(mode);
    glLoadIdentity();
}

//////////////////////////////////////////////////////////////////
/// @name : PushMatrix (public)
/// @param : CEnums::Matrix : la matrice à sauvegarder
/// @return : aucun
/// sauvegarde la matrice
//////////////////////////////////////////////////////////////////
void COGLRenderer::PushMatrix(CEnums::Matrix mode)
{
    glMatrixMode(mode);
    glPushMatrix();
}

//////////////////////////////////////////////////////////////////
/// @name : PopMatrix (public)
/// @param : CEnums::Matrix : la matrice à charger
/// @return : aucun
/// charge la matrice
//////////////////////////////////////////////////////////////////
void COGLRenderer::PopMatrix(CEnums::Matrix mode)
{
    glMatrixMode(mode);
    glPopMatrix();
}

//////////////////////////////////////////////////////////////////
/// @name : SetPerspective (public)
/// @param : GLdouble fov, GLdouble aspect, GLdouble proche, GLdouble loin
/// @return : aucun
/// remet les valeurs par défaut de la matrice
//////////////////////////////////////////////////////////////////
void COGLRenderer::SetPerspective(GLdouble fov, GLdouble aspect, GLdouble proche, GLdouble loin)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(fov, aspect, proche, loin);
}

//////////////////////////////////////////////////////////////////
/// @name : SetVSync (public)
/// @param : int : activer (oui par défaut)
/// @return : aucun
/// active ou désactive le VSync
//////////////////////////////////////////////////////////////////
void COGLRenderer::SetVSync(int activate)
{
    SDL_GL_SetSwapInterval( activate );
}

//////////////////////////////////////////////////////////////////
/// @name : ChangeViewPort (public)
/// @param : GLint x, GLint y, GLint width, GLint height
/// @return : aucun
/// change la partie de l'écran où afficher le rendu
//////////////////////////////////////////////////////////////////
void COGLRenderer::ChangeViewPort( GLint x, GLint y, GLint width, GLint height )
{
    glViewport(x, y, width, height);
}

//////////////////////////////////////////////////////////////////
/// @name : Load2DTexture (public)
/// @param : CTexture const& : la texture à charger
/// @return : aucun
/// charge la texture pour un rendu
//////////////////////////////////////////////////////////////////
void COGLRenderer::Load2DTexture( CTexture const& texID )
{
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texID.GetTextureID());
}

//////////////////////////////////////////////////////////////////
/// @name : Unload2DTexture (public)
/// @param : aucun
/// @return : aucun
/// décharge la texture pour un rendu
//////////////////////////////////////////////////////////////////
void COGLRenderer::Unload2DTexture()
{
    glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_TEXTURE_2D);
}

//////////////////////////////////////////////////////////////////
/// @name : RenderQuadric (public)
/// @param : CQuadrique&
/// @return : aucun
/// Affiche le Quadrique sur la scène
//////////////////////////////////////////////////////////////////
void COGLRenderer::RenderQuadric(CQuadrique& quadric)
{
    //GLUquadricObj* obj = quadric.GetQuad();

    if( !s_quadric )
        s_quadric = gluNewQuadric();

    gluQuadricDrawStyle(s_quadric, quadric.GetStyle());

    if( quadric.GetTexture() )
    {
        gluQuadricTexture(s_quadric, GL_TRUE);
        Load2DTexture(*quadric.GetTexture());
    }
    else
    {
        gluQuadricTexture(s_quadric, GL_FALSE);
        Unload2DTexture();
    }

    switch( quadric.GetType() )
    {
        case CEnums::QT_SPHERE     :
            gluSphere(s_quadric,
                      reinterpret_cast<CSphere*>(&quadric)->GetRadius(),
                      reinterpret_cast<CSphere*>(&quadric)->GetSlice(),
                      reinterpret_cast<CSphere*>(&quadric)->GetStack()
                      );
            break;

        case CEnums::QT_CYLINDER   :
            gluCylinder(s_quadric,
                        reinterpret_cast<CCylinder*>(&quadric)->GetBaseRadius(),
                        reinterpret_cast<CCylinder*>(&quadric)->GetTopRadius(),
                        reinterpret_cast<CCylinder*>(&quadric)->GetHeight(),
                        reinterpret_cast<CCylinder*>(&quadric)->GetSlice(),
                        1
                        );
            break;

        case CEnums::QT_DISK       :
            gluDisk(s_quadric,
                    reinterpret_cast<CDisk*>(&quadric)->GetInnerRadius(),
                    reinterpret_cast<CDisk*>(&quadric)->GetOutterRadius(),
                    reinterpret_cast<CDisk*>(&quadric)->GetSlice(),
                    1
                    );
            break;

        case CEnums::QT_PARTIALDISK:
            gluPartialDisk(s_quadric,
                           reinterpret_cast<CPartialDisk*>(&quadric)->GetInnerRadius(),
                           reinterpret_cast<CPartialDisk*>(&quadric)->GetOutterRadius(),
                           reinterpret_cast<CPartialDisk*>(&quadric)->GetSlice(),
                           1,
                           reinterpret_cast<CPartialDisk*>(&quadric)->GetStartAngle(),
                           reinterpret_cast<CPartialDisk*>(&quadric)->GetSweepAngle()
                           );
            break;

    }
}
