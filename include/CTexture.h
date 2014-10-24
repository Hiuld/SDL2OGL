#ifndef CTEXTURE_H
#define CTEXTURE_H

#include "global_includes.h"

#include <SDL_image.h>

class CTexture
{
    GLuint  m_TexID;
    GLuint  m_TexHeight;
    GLuint  m_TexWidth;
    GLuint *m_TexPixels;

    //////////////////////////////////////////////////////////////////
    /// @name : flipSurface (private)
    /// @param : SDL_Surface* : la texture
    /// @return : SDL_Surface* : la texture retourn�e
    /// inverse l'image horizontalement pour afficher la texture � l'endroit
    //////////////////////////////////////////////////////////////////
    SDL_Surface* flipSurface(SDL_Surface * surface);

    public :
        CTexture();
        virtual ~CTexture();
        //////////////////////////////////////////////////////////////////
        /// @name : DestroyTexture (public)
        /// @param : aucun
        /// @return : aucun
        /// d�truit la texture
        //////////////////////////////////////////////////////////////////
        void DestroyTexture    ();
        //////////////////////////////////////////////////////////////////
        /// @name : operator! const(public)
        /// @param : aucun
        /// @return : bool : true si aucune texture de charg�e
        /// la texture n'est pas charg�e
        //////////////////////////////////////////////////////////////////
        bool operator !() const;
        operator const void*();
        GLuint  GetTextureID    () const;
        GLuint  GetTextureHeight() const;
        GLuint  GetTextureWidth () const;
        GLuint  GetPixelAt      (unsigned int x, unsigned int y);
        GLuint* GetPixelArray   ();
        void    SetPixelAt      (unsigned int x, unsigned int y, GLuint pixel);
        //////////////////////////////////////////////////////////////////
        /// @name : LoadTextureFromPixels32 (public)
        /// @param : GLuint *pixels, GLuint width, GLuint height, bool mipmap = false
        /// @return : aucun
        /// charge la texture depuis un tableau de pixels
        //////////////////////////////////////////////////////////////////
        void LoadTextureFromPixels32( GLuint *pixels, GLuint width, GLuint height, bool mipmap = false );
        //////////////////////////////////////////////////////////////////
        /// @name : LoadTextureFromFile (public)
        /// @param : const char * filename, bool mipmap = false
        /// @return : aucun
        /// charge la texture depuis un fichier
        //////////////////////////////////////////////////////////////////
        void LoadTextureFromFile    ( const char * filename, bool mipmap = false );
        //////////////////////////////////////////////////////////////////
        /// @name : Lock (public)
        /// @param : aucun
        /// @return : aucun
        /// verrouille la texture
        //////////////////////////////////////////////////////////////////
        void Lock();
        //////////////////////////////////////////////////////////////////
        /// @name : Unlock (public)
        /// @param : aucun
        /// @return : aucun
        /// d�verrouille et met � jour la texture
        //////////////////////////////////////////////////////////////////
        void Unlock();
        //////////////////////////////////////////////////////////////////
        /// @name : isLocked (public)
        /// @param : aucun
        /// @return : bool
        /// true si la texture est verrouill�e
        //////////////////////////////////////////////////////////////////
        bool isLocked() const;
};

#endif // CTEXTURE_H
