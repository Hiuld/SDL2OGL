#ifndef CQUADRIQUE_H
#define CQUADRIQUE_H

#include "global_includes.h"
#include "CTexture.h"

class CQuadrique
{
    CEnums::QuadStyle m_Style;
    CTexture const   *m_Texture;

    protected :
        CEnums::QuadType  m_Type;

        CQuadrique(CEnums::QuadStyle style);
        ~CQuadrique();

    public :
        //////////////////////////////////////////////////////////////////
        /// @name : Setteurs (public)
        /// @param : X
        /// @return : aucun
        /// Modifie les attributs de la classe
        //////////////////////////////////////////////////////////////////
        void SetTexture(CTexture const& texture);
        void UnsetTexture();
        void SetStyle(CEnums::QuadStyle newStyle);
        //////////////////////////////////////////////////////////////////
        /// @name : Getteurs (public)
        /// @param : aucun
        /// @return : X
        /// Récupère les attributs de la classe
        //////////////////////////////////////////////////////////////////
        CTexture   const* GetTexture()const;
        CEnums::QuadStyle GetStyle  ()const;
        CEnums::QuadType  GetType   ()const;
};

class CSphere : public CQuadrique
{
    GLdouble m_Rayon;
    // Découpes (précision de la sphère)
    GLint    m_Vertical;
    GLint    m_Horizontal;

    public :
        CSphere( GLdouble rayon = 1, GLint vertical = 40, GLint horizontal = 40, CEnums::QuadStyle style = CEnums::QS_FILL );
        //////////////////////////////////////////////////////////////////
        /// @name : Setteurs (public)
        /// @param : X
        /// @return : aucun
        /// Modifie les attributs de la classe
        //////////////////////////////////////////////////////////////////
        void SetRadius( GLdouble const radius );
        void SetSlice ( GLint const slice );
        void SetStack ( GLint const stack );
        //////////////////////////////////////////////////////////////////
        /// @name : Getteurs (public)
        /// @param : aucun
        /// @return : X
        /// Récupère les attributs de la classe
        //////////////////////////////////////////////////////////////////
        GLdouble GetRadius()const;
        GLint    GetSlice()const;
        GLint    GetStack()const;
};

class CCylinder : public CQuadrique
{
    GLdouble m_RayonBase, m_RayonHaut, m_Hauteur;
    // Découpes (précision du cylindre)
    GLint    m_Vertical;

    public :
        CCylinder( GLdouble baseRadius = 1, GLdouble topRadius = 1, GLdouble height = 2, GLint slice = 20, CEnums::QuadStyle style = CEnums::QS_FILL );
        //////////////////////////////////////////////////////////////////
        /// @name : Setteurs (public)
        /// @param : X
        /// @return : aucun
        /// Modifie les attributs de la classe
        //////////////////////////////////////////////////////////////////
        void SetBaseRadius( GLdouble const radius );
        void SetTopRadius ( GLdouble const radius );
        void SetHeight    ( GLdouble const height );
        void SetSlice     ( GLint const slice );
        //////////////////////////////////////////////////////////////////
        /// @name : Getteurs (public)
        /// @param : aucun
        /// @return : X
        /// Récupère les attributs de la classe
        //////////////////////////////////////////////////////////////////
        GLdouble GetBaseRadius()const;
        GLdouble GetTopRadius ()const;
        GLdouble GetHeight    ()const;
        GLint    GetSlice     ()const;
};

class CDisk : public CQuadrique
{
    GLdouble m_RayonInterieur, m_RayonExterieur;
    // Découpes (précision du disque)
    GLint    m_Vertical;

    public :
        CDisk( GLdouble innerRadius = 1, GLdouble outterRadius = 5, GLint slice = 20, CEnums::QuadStyle style = CEnums::QS_FILL );
        //////////////////////////////////////////////////////////////////
        /// @name : Setteurs (public)
        /// @param : X
        /// @return : aucun
        /// Modifie les attributs de la classe
        //////////////////////////////////////////////////////////////////
        void SetInnerRadius ( GLdouble const radius );
        void SetOutterRadius( GLdouble const radius );
        void SetSlice       ( GLint const slice );
        //////////////////////////////////////////////////////////////////
        /// @name : Getteurs (public)
        /// @param : aucun
        /// @return : X
        /// Récupère les attributs de la classe
        //////////////////////////////////////////////////////////////////
        GLdouble GetInnerRadius()const;
        GLdouble GetOutterRadius ()const;
        GLint    GetSlice     ()const;
};

class CPartialDisk : public CQuadrique
{
    GLdouble m_RayonInterieur, m_RayonExterieur, m_AngleDebut, m_AngleFin;
    GLint    m_Vertical;

    public :
        CPartialDisk( GLdouble innerRadius = 1.2, GLdouble outterRadius = 1.8, GLdouble start = 0, GLdouble sweep = 180, GLint slice = -1, CEnums::QuadStyle style = CEnums::QS_FILL );

        //////////////////////////////////////////////////////////////////
        /// @name : Setteurs (public)
        /// @param : X
        /// @return : aucun
        /// Modifie les attributs de la classe
        //////////////////////////////////////////////////////////////////
        void SetInnerRadius ( GLdouble const radius );
        void SetOutterRadius( GLdouble const radius );
        void SetStartAngle  ( GLdouble const degree );
        void SetSweepAngle  ( GLdouble const degree );
        void SetSlice       ( GLint const slice );
        //////////////////////////////////////////////////////////////////
        /// @name : Getteurs (public)
        /// @param : aucun
        /// @return : X
        /// Récupère les attributs de la classe
        //////////////////////////////////////////////////////////////////
        GLdouble GetInnerRadius ()const;
        GLdouble GetOutterRadius()const;
        GLdouble GetStartAngle  ()const;
        GLdouble GetSweepAngle  ()const;
        GLint    GetSlice       ()const;
};

#endif // CQUADRIQUE_H
