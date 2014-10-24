#include "COGLRenderer.h"

#include <SDL_opengl.h>

COGLRenderer::COGLRenderer():
    m_Window(NULL), m_Context(NULL)
{}

COGLRenderer::~COGLRenderer()
{
    SDL_GL_DeleteContext(m_Context);
}

bool COGLRenderer::Initialize(SDL_Window *Window)
{
    bool success = true;

    m_Window = Window;
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

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);

    return success;
}

void COGLRenderer::BeginScene() const
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
}

void COGLRenderer::EndScene() const
{
    SDL_GL_SwapWindow(m_Window);
}

void COGLRenderer::ReinitMatrix(GLenum mode)
{
    glMatrixMode(mode);
    glLoadIdentity();
}

void COGLRenderer::PushMatrix(GLenum mode)
{
    glMatrixMode(mode);
    glPushMatrix();
}

void COGLRenderer::PopMatrix(GLenum mode)
{
    glMatrixMode(mode);
    glPopMatrix();
}

void COGLRenderer::SetPerspective(GLdouble fov, GLdouble aspect, GLdouble proche, GLdouble loin)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(fov, aspect, proche, loin);
}

void COGLRenderer::SetVSync(int activate)
{
    SDL_GL_SetSwapInterval( activate );
}

void COGLRenderer::ChangeViewPort( GLint x, GLint y, GLint width, GLint height )
{
    glViewport(x, y, width, height);
}

void COGLRenderer::Load2DTexture( CTexture const& texID )
{
    glBindTexture(GL_TEXTURE_2D, texID.GetTextureID());
}

void COGLRenderer::Unload2DTexture()
{
    Load2DTexture(CTexture());
}
