#ifndef COGLRENDERER_H
#define COGLRENDERER_H

#include "CSingleton.h"
#include "CTexture.h"
#include "CQuadrique.h"

class COGLRenderer : public CSingleton<COGLRenderer>
{
    friend CSingleton<COGLRenderer>;

    SDL_Window     *m_Window;
    SDL_GLContext   m_Context;
    static GLUquadricObj *s_quadric;

    COGLRenderer();
    ~COGLRenderer();

    public :
        //////////////////////////////////////////////////////////////////
        /// @name : BeginScene const(public)
        /// @param : aucun
        /// @return : aucun
        /// D�marre le rendu de la sc�ne
        //////////////////////////////////////////////////////////////////
        void BeginScene() const;
        //////////////////////////////////////////////////////////////////
        /// @name : EndScene const(public)
        /// @param : aucun
        /// @return : aucun
        /// Termine le rendu et affiche la sc�ne
        //////////////////////////////////////////////////////////////////
        void EndScene  () const;
        //////////////////////////////////////////////////////////////////
        /// @name : Initialize (public)
        /// @param : SDL_Window* : fen�tre o� sera affich�e le rendu
        /// @return : aucun
        /// Initialisation du Renderer sur la fen�tre sp�cifi�e
        //////////////////////////////////////////////////////////////////
        bool Initialize(SDL_Window *Window);
        //////////////////////////////////////////////////////////////////
        /// @name : ReinitMatrix (public)
        /// @param : CEnums::Matrix : la matrice � r�initialiser
        /// @return : aucun
        /// remet les valeurs par d�faut de la matrice
        //////////////////////////////////////////////////////////////////
        void ReinitMatrix(CEnums::Matrix mode);
        //////////////////////////////////////////////////////////////////
        /// @name : PushMatrix (public)
        /// @param : CEnums::Matrix : la matrice � sauvegarder
        /// @return : aucun
        /// sauvegarde la matrice
        //////////////////////////////////////////////////////////////////
        void PushMatrix  (CEnums::Matrix mode);
        //////////////////////////////////////////////////////////////////
        /// @name : PopMatrix (public)
        /// @param : CEnums::Matrix : la matrice � charger
        /// @return : aucun
        /// charge la matrice
        //////////////////////////////////////////////////////////////////
        void PopMatrix   (CEnums::Matrix mode);
        //////////////////////////////////////////////////////////////////
        /// @name : SetPerspective (public)
        /// @param : GLdouble fov, GLdouble aspect, GLdouble proche, GLdouble loin
        /// @return : aucun
        /// remet les valeurs par d�faut de la matrice
        //////////////////////////////////////////////////////////////////
        void SetPerspective(GLdouble fov, GLdouble aspect, GLdouble proche, GLdouble loin);
        //////////////////////////////////////////////////////////////////
        /// @name : SetVSync (public)
        /// @param : int : activer (oui par d�faut)
        /// @return : aucun
        /// active ou d�sactive le VSync
        //////////////////////////////////////////////////////////////////
        void SetVSync(int activate = 1);
        //////////////////////////////////////////////////////////////////
        /// @name : ChangeViewPort (public)
        /// @param : GLint x, GLint y, GLint width, GLint height
        /// @return : aucun
        /// change la partie de l'�cran o� afficher le rendu
        //////////////////////////////////////////////////////////////////
        void ChangeViewPort( GLint x, GLint y, GLint width, GLint height );
        //////////////////////////////////////////////////////////////////
        /// @name : Load2DTexture (public)
        /// @param : CTexture const& : la texture � charger
        /// @return : aucun
        /// charge la texture pour un rendu
        //////////////////////////////////////////////////////////////////
        void Load2DTexture( CTexture const& texID );
        //////////////////////////////////////////////////////////////////
        /// @name : Unload2DTexture (public)
        /// @param : aucun
        /// @return : aucun
        /// d�charge la texture pour un rendu
        //////////////////////////////////////////////////////////////////
        void Unload2DTexture();
        //////////////////////////////////////////////////////////////////
        /// @name : RenderQuadric (public)
        /// @param : CQuadrique&
        /// @return : aucun
        /// Affiche le Quadrique sur la sc�ne
        //////////////////////////////////////////////////////////////////
        void RenderQuadric( CQuadrique& quadric );
};

#endif // COGLRENDERER_H
