#include "CTexture.h"
#include "COGLRenderer.h"

CTexture::CTexture():
    m_TexID(0), m_TexHeight(0), m_TexWidth(0), m_TexPixels(NULL)
{}

CTexture::~CTexture()
{
    DestroyTexture();
}

void CTexture::DestroyTexture()
{
    if( m_TexID )
    {
        glDeleteTextures(1, &m_TexID);
        m_TexID = m_TexHeight = m_TexWidth = 0;
    }
}

bool CTexture::operator!() const
{
    return m_TexID;
}

CTexture::operator const void*()
{
    return m_TexID?this:0;
}

SDL_Surface * CTexture::flipSurface(SDL_Surface * surface)
{
    int current_line,pitch;
    // créer une nouvelle image
    SDL_Surface * fliped_surface = SDL_CreateRGBSurface(SDL_SWSURFACE,
                                   surface->w,surface->h,
                                   surface->format->BitsPerPixel,
                                   surface->format->Rmask,
                                   surface->format->Gmask,
                                   surface->format->Bmask,
                                   surface->format->Amask);

    SDL_LockSurface(surface);
    SDL_LockSurface(fliped_surface);

    pitch = surface->pitch;
    for(current_line = 0; current_line < surface->h; ++current_line)
    {
        // copier chaque lignes à l'opposée dans la nouvelle image
        // ex : sur une image de 32lignes, la copie de la ligne 1 sera dans la ligne 32
        memcpy(&((unsigned char* )fliped_surface->pixels)[current_line*pitch],
               &((unsigned char* )surface->pixels)[(surface->h - 1 - current_line)*pitch],
               pitch);
    }

    SDL_UnlockSurface(fliped_surface);
    SDL_UnlockSurface(surface);
    return fliped_surface;
}

void CTexture::LoadTextureFromFile(const char * filename,bool mipmap)
{
    SDL_Surface *picture_surface = NULL;
    SDL_Surface *gl_surface = NULL;
    SDL_Surface *gl_fliped_surface = NULL;
    Uint32 rmask, gmask, bmask, amask;

    picture_surface = IMG_Load(filename);
    if (picture_surface == NULL)
        throw C3DTextureException("Cannot load " + std::string(filename));

    #if SDL_BYTEORDER == SDL_BIG_ENDIAN
        rmask = 0xff000000;
        gmask = 0x00ff0000;
        bmask = 0x0000ff00;
        amask = 0x000000ff;
    #else
        rmask = 0x000000ff;
        gmask = 0x0000ff00;
        bmask = 0x00ff0000;
        amask = 0xff000000;
    #endif

    // Charger le format de texture d'ogl
    SDL_PixelFormat format = *(picture_surface->format);
    format.BitsPerPixel = 32;
    format.BytesPerPixel = 4;
    format.Rmask = rmask;
    format.Gmask = gmask;
    format.Bmask = bmask;
    format.Amask = amask;
    // Recrée la Texture en mode rgba (OGL)
    gl_surface = SDL_ConvertSurface(picture_surface,&format,SDL_SWSURFACE);
    // Retourner la Texture, SDL commence sont repère en Haut à Gauche et OGL comment en Bas à Gauche
    gl_fliped_surface = flipSurface(gl_surface);

    LoadTextureFromPixels32(static_cast<GLuint*>(gl_fliped_surface->pixels), picture_surface->w, picture_surface->h, mipmap);

    // Libérer les images chargées en mémoire
    SDL_FreeSurface(gl_fliped_surface);
    SDL_FreeSurface(gl_surface);
    SDL_FreeSurface(picture_surface);
}

void CTexture::LoadTextureFromPixels32( GLuint *pixels, GLuint width, GLuint height, bool mipmap )
{
    // Détruire la texture si elle existe
    DestroyTexture();

    m_TexHeight = height; m_TexWidth = width;

    // Générer l'ID de la texture
    glGenTextures(1, &m_TexID);
    // Charger la texture
    COGLRenderer::Get().Load2DTexture(*this);
    // Si on défini le mipmap
    if (mipmap)
    {
        // Créer le mipmap sur la texture
        gluBuild2DMipmaps(GL_TEXTURE_2D, 4, m_TexWidth,
                          m_TexHeight, GL_RGBA,GL_UNSIGNED_BYTE,
                          pixels);
    }
    // sinon créer une texture normale
    else
    {
        glTexImage2D(GL_TEXTURE_2D, 0, 4, m_TexWidth,
                     m_TexHeight, 0, GL_RGBA,GL_UNSIGNED_BYTE,
                     pixels);
    }
    // Filtre appliqué lorsque la texture est rendue plus petite que sa taille originale
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, mipmap ? GL_LINEAR_MIPMAP_LINEAR : GL_LINEAR);
    // Filtre appliqué lorsque la texture est rendue plus grande que sa taille originale
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    // Décharger la texture (toujours dans la GPU quand même)
    COGLRenderer::Get().Unload2DTexture();
}

void CTexture::Lock()
{
    // La texture est chargée et pas verrouillée
    if( !m_TexPixels && m_TexID )
    {
        // Allouer la mémoire pour la texture
        m_TexPixels = new GLuint[m_TexWidth*m_TexHeight];

        COGLRenderer::Get().Load2DTexture(*this);

        glGetTexImage(GL_TEXTURE_2D, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_TexPixels);

        COGLRenderer::Get().Unload2DTexture();
    }
}

void CTexture::Unlock()
{
    // La texture est chargée et verrouillée
    if( m_TexPixels && m_TexID )
    {
        COGLRenderer::Get().Load2DTexture(*this);
        // Mettre à jour la texture avec nos données
        glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, m_TexWidth, m_TexHeight, GL_RGBA, GL_UNSIGNED_BYTE, m_TexPixels);

        delete[] m_TexPixels; m_TexPixels = NULL;

        COGLRenderer::Get().Unload2DTexture();
    }
}

void CTexture::SetPixelAt(unsigned int x, unsigned int y, GLuint pixel)
{
    if( isLocked() )
        m_TexPixels[y*m_TexWidth+x] = pixel;
}

bool    CTexture::isLocked        ()const{return m_TexPixels;}
GLuint  CTexture::GetTextureID    ()const{return m_TexID    ;}
GLuint  CTexture::GetTextureHeight()const{return m_TexHeight;}
GLuint  CTexture::GetTextureWidth ()const{return m_TexWidth ;}
GLuint* CTexture::GetPixelArray   ()     {return isLocked()?m_TexPixels:NULL;}
GLuint  CTexture::GetPixelAt      (unsigned int x, unsigned int y){return isLocked()?m_TexPixels[y*m_TexWidth+x]:0;}
