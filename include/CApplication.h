#ifndef CAPPLICATION_H
#define CAPPLICATION_H

#include "COGLRenderer.h"

class CApplication
{
    public :SDL_Window    *m_Window;
    unsigned char  m_FPSLimit;
    bool           m_Quit;
    bool           m_FullScreen;
    // int : écran
    // std::vector<SDL_SiplayMode> : les modes de l'écran associé
    std::map<int, std::vector<SDL_DisplayMode> > m_DisplayModes;

    //////////////////////////////////////////////////////////////////
    /// @name : MakeWindow (private)
    /// @param : aucun
    /// @return : aucun
    /// Créé la fenêtre
    //////////////////////////////////////////////////////////////////
    void MakeWindow();
    //////////////////////////////////////////////////////////////////
    /// @name : MainLoop (private)
    /// @param : aucun
    /// @return : aucun
    /// Gère les messages
    //////////////////////////////////////////////////////////////////
    void MainLoop();
    //////////////////////////////////////////////////////////////////
    /// @name : initVideoModes (private)
    /// @param : aucun
    /// @return : aucun
    /// Récupère les modes vidéos de(s) écran(s)
    //////////////////////////////////////////////////////////////////
    void initVideoModes();
    //////////////////////////////////////////////////////////////////
    /// @name : virtual OnInitialize (private)
    /// @param : aucun
    /// @return : aucun
    /// Créé la fenêtre
    //////////////////////////////////////////////////////////////////
    virtual void OnInitialize() = 0;
    //////////////////////////////////////////////////////////////////
    /// @name : virtual OnUpdate (private)
    /// @param : aucun
    /// @return : aucun
    /// Fonction qui est appelée avant le rendu de la scène
    //////////////////////////////////////////////////////////////////
    virtual void OnUpdate() = 0;
    //////////////////////////////////////////////////////////////////
    /// @name : virtual OnRender (private)
    /// @param : aucun
    /// @return : aucun
    /// Fonction qui est appelée lors d'un rendu de scène
    //////////////////////////////////////////////////////////////////
    virtual void OnRender() = 0;
    //////////////////////////////////////////////////////////////////
    /// @name : virtual OnEvent (private)
    /// @param : SDL_Event& : la structure d'évènement à gérer
    /// @return : aucun
    /// Permet de traiter un évènement
    //////////////////////////////////////////////////////////////////
    virtual void OnEvent(SDL_Event& event) = 0;

    protected :
        // Le renderer de notre appli 3D
        COGLRenderer &m_Renderer;
        //////////////////////////////////////////////////////////////////
        /// @name : CApplication (protected)
        /// @param : aucun
        /// @return : aucun
        /// Créé la fenêtre
        //////////////////////////////////////////////////////////////////
        CApplication();
        //////////////////////////////////////////////////////////////////
        /// @name : ~CApplication (protected)
        /// @param : aucun
        /// @return : aucun
        /// Détruit l'appli en libérant les ressources
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
        /// Démarre l'application
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
        /// @param : int : num de l'écran (1 par défaut)
        /// @return : std::vector<SDL_DisplayMode> : référence sur les modes disponibles de l'écran
        /// récupère les modes de l'écran
        //////////////////////////////////////////////////////////////////
        const std::vector<SDL_DisplayMode>  GetVideoMode( int screenID = 1 ) const;
        //////////////////////////////////////////////////////////////////
        /// @name : SetVideoMode (public)
        /// @param : SDL_DisplayMode& : le mode, bool : plein écran
        /// @return : aucun
        /// Change la résolution de la fenêtre
        //////////////////////////////////////////////////////////////////
        void SetVideoMode(SDL_DisplayMode const&mode, bool fullscreen = false) const;
};

#endif // CAPPLICATION_H
