#ifndef CAPPLICATION_H
#define CAPPLICATION_H

#include "COGLRenderer.h"

class CApplication
{
    public :SDL_Window    *m_Window;
    unsigned char  m_FPSLimit;
    bool           m_Quit;
    bool           m_FullScreen;
    // int : �cran
    // std::vector<SDL_SiplayMode> : les modes de l'�cran associ�
    std::map<int, std::vector<SDL_DisplayMode> > m_DisplayModes;

    //////////////////////////////////////////////////////////////////
    /// @name : MakeWindow (private)
    /// @param : aucun
    /// @return : aucun
    /// Cr�� la fen�tre
    //////////////////////////////////////////////////////////////////
    void MakeWindow();
    //////////////////////////////////////////////////////////////////
    /// @name : MainLoop (private)
    /// @param : aucun
    /// @return : aucun
    /// G�re les messages
    //////////////////////////////////////////////////////////////////
    void MainLoop();
    //////////////////////////////////////////////////////////////////
    /// @name : initVideoModes (private)
    /// @param : aucun
    /// @return : aucun
    /// R�cup�re les modes vid�os de(s) �cran(s)
    //////////////////////////////////////////////////////////////////
    void initVideoModes();
    //////////////////////////////////////////////////////////////////
    /// @name : virtual OnInitialize (private)
    /// @param : aucun
    /// @return : aucun
    /// Cr�� la fen�tre
    //////////////////////////////////////////////////////////////////
    virtual void OnInitialize() = 0;
    //////////////////////////////////////////////////////////////////
    /// @name : virtual OnUpdate (private)
    /// @param : aucun
    /// @return : aucun
    /// Fonction qui est appel�e avant le rendu de la sc�ne
    //////////////////////////////////////////////////////////////////
    virtual void OnUpdate() = 0;
    //////////////////////////////////////////////////////////////////
    /// @name : virtual OnRender (private)
    /// @param : aucun
    /// @return : aucun
    /// Fonction qui est appel�e lors d'un rendu de sc�ne
    //////////////////////////////////////////////////////////////////
    virtual void OnRender() = 0;
    //////////////////////////////////////////////////////////////////
    /// @name : virtual OnEvent (private)
    /// @param : SDL_Event& : la structure d'�v�nement � g�rer
    /// @return : aucun
    /// Permet de traiter un �v�nement
    //////////////////////////////////////////////////////////////////
    virtual void OnEvent(SDL_Event& event) = 0;

    protected :
        // Le renderer de notre appli 3D
        COGLRenderer &m_Renderer;
        //////////////////////////////////////////////////////////////////
        /// @name : CApplication (protected)
        /// @param : aucun
        /// @return : aucun
        /// Cr�� la fen�tre
        //////////////////////////////////////////////////////////////////
        CApplication();
        //////////////////////////////////////////////////////////////////
        /// @name : ~CApplication (protected)
        /// @param : aucun
        /// @return : aucun
        /// D�truit l'appli en lib�rant les ressources
        //////////////////////////////////////////////////////////////////
        virtual ~CApplication();

    public :
        static CApplication *s_Instance;

        //////////////////////////////////////////////////////////////////
        /// @name : SetTitle (public)
        /// @param : const char* : le titre
        /// @return : aucun
        /// change le titre
        //////////////////////////////////////////////////////////////////
        void SetTitle(const char *NewTitle);
        //////////////////////////////////////////////////////////////////
        /// @name : SetIcon (public)
        /// @param : SDL_Surface* : l'icone
        /// @return : aucun
        /// change l'icone
        //////////////////////////////////////////////////////////////////
        void SetIcon(SDL_Surface *Icon);
        //////////////////////////////////////////////////////////////////
        /// @name : Run (public)
        /// @param : aucun
        /// @return : aucun
        /// D�marre l'application
        //////////////////////////////////////////////////////////////////
        void Run();
        //////////////////////////////////////////////////////////////////
        /// @name : Quit (public)
        /// @param : aucun
        /// @return : aucun
        /// Termine l'application
        //////////////////////////////////////////////////////////////////
        void Quit();
        //////////////////////////////////////////////////////////////////
        /// @name : SetFPSLimit (public)
        /// @param : unsigned char limit (limit = 0 -> 60fps)
        /// @return : aucun
        /// Change la limite de FPS
        //////////////////////////////////////////////////////////////////
        void SetFPSLimit(unsigned char limit = 60);
        //////////////////////////////////////////////////////////////////
        /// @name : GetVideoMode (public)
        /// @param : int : num de l'�cran (1 par d�faut)
        /// @return : std::vector<SDL_DisplayMode> : r�f�rence sur les modes disponibles de l'�cran
        /// r�cup�re les modes de l'�cran
        //////////////////////////////////////////////////////////////////
        const std::vector<SDL_DisplayMode>  GetVideoMode( int screenID = 1 ) const;
        //////////////////////////////////////////////////////////////////
        /// @name : SetVideoMode (public)
        /// @param : SDL_DisplayMode& : le mode, bool : plein �cran
        /// @return : aucun
        /// Change la r�solution de la fen�tre
        //////////////////////////////////////////////////////////////////
        void SetVideoMode(SDL_DisplayMode const&mode, bool fullscreen = false) const;
};

#endif // CAPPLICATION_H
