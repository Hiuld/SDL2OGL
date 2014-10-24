#include "CApplication.h"

CApplication *CApplication::s_Instance = NULL;

CApplication::CApplication():
    m_Window(NULL),
    m_FPSLimit(1000/60),
    // On lance l'appli
    m_Quit(false),
    // Initialiser la référence vers l'API de rendu
    m_Renderer(COGLRenderer::Get())
{
    s_Instance = this;
}

CApplication::~CApplication()
{
    // Détruit l'API de rendu
    m_Renderer.Destroy();
    SDL_DestroyWindow(m_Window);
    SDL_Quit();
}

void CApplication::SetTitle( const char* NewTitle )
{
    SDL_SetWindowTitle(m_Window, NewTitle);
}

void CApplication::SetIcon(SDL_Surface* Icon)
{
    SDL_SetWindowIcon(m_Window, Icon);
}

void CApplication::MakeWindow()
{
    SDL_Init(SDL_INIT_VIDEO);
    m_Window = SDL_CreateWindow("Insert title here", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1024, 768, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN );
}

void CApplication::SetFPSLimit(unsigned char limit)
{
    if( limit )
        m_FPSLimit = 1000/limit;
    else
        m_FPSLimit = 0;
}

void CApplication::Quit()
{
    m_Quit = true;
}

void CApplication::Run()
{
    MakeWindow();
    initVideoModes();
    m_Renderer.Initialize(m_Window);
    OnInitialize();
    MainLoop();
}

void CApplication::MainLoop()
{
    SDL_Event event;
    Uint32 startTime, elapsedTime;

    while( !m_Quit )
    {
        // Le temps avant l'éxécution
        startTime = SDL_GetTicks();
        // Tant qu'il y a des messages, les traiter
        while( SDL_PollEvent(&event) )
        {
            OnEvent(event);
        }
        // Mise à jour de la scène
        OnUpdate();
        // Démarrer le rendu
        m_Renderer.BeginScene();
        OnRender();
        m_Renderer.EndScene();

        // Si on a mis moins de temps que le nombre de FPS demandé, on attend
        if( (elapsedTime = SDL_GetTicks()-startTime) < m_FPSLimit )
        {
            SDL_Delay(m_FPSLimit - elapsedTime);
        }
    }
}

void CApplication::initVideoModes()
{
    SDL_DisplayMode mode;

    int numDisplay = SDL_GetNumVideoDisplays();

    for( int i = 0; i < numDisplay; ++i )
    {
        int displayModes = SDL_GetNumDisplayModes(0);
        for( int j = 0; j < displayModes; ++j )
        {
            SDL_GetDisplayMode(i, j, &mode);
            m_DisplayModes[i+1].push_back(mode);
        }
    }
}

const std::vector<SDL_DisplayMode>  CApplication::GetVideoMode( int screenID ) const
{
    if( m_DisplayModes.find(screenID) != m_DisplayModes.end() )
        return m_DisplayModes.at(screenID);
    else
        return std::vector<SDL_DisplayMode>();
}

void CApplication::SetVideoMode(SDL_DisplayMode const&mode, bool fullscreen) const
{
    SDL_SetWindowFullscreen(m_Window, fullscreen?SDL_WINDOW_FULLSCREEN:0);
    SDL_SetWindowDisplayMode(m_Window, &mode);
}
