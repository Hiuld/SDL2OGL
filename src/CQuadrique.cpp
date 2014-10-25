#include "CQuadrique.h"

CQuadrique::CQuadrique(CEnums::QuadStyle style):
    m_Style(style), m_Texture(NULL)
{}

CQuadrique::~CQuadrique()
{
}
//////////////////////////////////////////////////////////////////
/// @name : Setteurs (public)
/// @param : X
/// @return : aucun
/// Modifie les attributs de la classe
//////////////////////////////////////////////////////////////////
void CQuadrique::SetTexture(CTexture const& texture){m_Texture = &texture;}
void CQuadrique::UnsetTexture(){m_Texture = 0;}
void CQuadrique::SetStyle(CEnums::QuadStyle newStyle){m_Style = newStyle;}

//////////////////////////////////////////////////////////////////
/// @name : Getteurs (public)
/// @param : aucun
/// @return : X
/// Récupère les attributs de la classe
//////////////////////////////////////////////////////////////////
CTexture      const* CQuadrique::GetTexture()const{return m_Texture;}
CEnums::QuadStyle    CQuadrique::GetStyle  ()const{return m_Style;}
CEnums::QuadType     CQuadrique::GetType   ()const{return m_Type;}

//////////////////////////////////////////////////////////////////////
//
// CSphere
//
//////////////////////////////////////////////////////////////////////

CSphere::CSphere(GLdouble rayon, GLint vertical, GLint horizontal, CEnums::QuadStyle style):
    CQuadrique(style), m_Rayon(rayon), m_Vertical(vertical), m_Horizontal(horizontal)
{
    m_Type = CEnums::QT_SPHERE;
}

//////////////////////////////////////////////////////////////////
/// @name : Setteurs (public)
/// @param : X
/// @return : aucun
/// Modifie les attributs de la classe
//////////////////////////////////////////////////////////////////
void CSphere::SetRadius( GLdouble const radius ){m_Rayon = radius;}
void CSphere::SetSlice ( GLint const slice ){m_Vertical = slice;}
void CSphere::SetStack ( GLint const stack ){m_Horizontal = stack;}

//////////////////////////////////////////////////////////////////
/// @name : Getteurs (public)
/// @param : aucun
/// @return : X
/// Récupère les attributs de la classe
//////////////////////////////////////////////////////////////////
GLdouble CSphere::GetRadius()const{return m_Rayon;}
GLint    CSphere::GetSlice()const{return m_Vertical;}
GLint    CSphere::GetStack()const{return m_Horizontal;}

//////////////////////////////////////////////////////////////////////
//
// CCylinder
//
//////////////////////////////////////////////////////////////////////

CCylinder::CCylinder( GLdouble baseRadius, GLdouble topRadius, GLdouble height, GLint slice, CEnums::QuadStyle style):
    CQuadrique(style), m_RayonBase(baseRadius), m_RayonHaut(topRadius), m_Hauteur(height), m_Vertical(slice)
{
    m_Type = CEnums::QT_CYLINDER;
}

//////////////////////////////////////////////////////////////////
/// @name : Setteurs (public)
/// @param : X
/// @return : aucun
/// Modifie les attributs de la classe
//////////////////////////////////////////////////////////////////
void CCylinder::SetBaseRadius( GLdouble const radius ){m_RayonBase = radius;}
void CCylinder::SetTopRadius( GLdouble const radius ){m_RayonHaut = radius;}
void CCylinder::SetHeight( GLdouble const height ){m_Hauteur = height;}
void CCylinder::SetSlice ( GLint const slice ){m_Vertical = slice;}

//////////////////////////////////////////////////////////////////
/// @name : Getteurs (public)
/// @param : aucun
/// @return : X
/// Récupère les attributs de la classe
//////////////////////////////////////////////////////////////////
GLdouble CCylinder::GetBaseRadius()const{return m_RayonBase;}
GLdouble CCylinder::GetTopRadius()const{return m_RayonHaut;}
GLdouble CCylinder::GetHeight()const{return m_Hauteur;}
GLint    CCylinder::GetSlice()const{return m_Vertical;}

//////////////////////////////////////////////////////////////////////
//
// CDisk
//
//////////////////////////////////////////////////////////////////////

CDisk::CDisk( GLdouble innerRadius, GLdouble outterRadius, GLint slice, CEnums::QuadStyle style ):
    CQuadrique(style), m_RayonInterieur(innerRadius), m_RayonExterieur(outterRadius), m_Vertical(slice)
{
    m_Type = CEnums::QT_DISK;
}
//////////////////////////////////////////////////////////////////
/// @name : Setteurs (public)
/// @param : X
/// @return : aucun
/// Modifie les attributs de la classe
//////////////////////////////////////////////////////////////////
void CDisk::SetInnerRadius ( GLdouble const radius ){m_RayonInterieur = radius;}
void CDisk::SetOutterRadius( GLdouble const radius ){m_RayonExterieur = radius;}
void CDisk::SetSlice       ( GLint const slice     ){m_Vertical = slice;}
//////////////////////////////////////////////////////////////////
/// @name : Getteurs (public)
/// @param : aucun
/// @return : X
/// Récupère les attributs de la classe
//////////////////////////////////////////////////////////////////
GLdouble CDisk::GetInnerRadius ()const{return m_RayonInterieur;}
GLdouble CDisk::GetOutterRadius()const{return m_RayonExterieur;}
GLint    CDisk::GetSlice       ()const{return m_Vertical;}

//////////////////////////////////////////////////////////////////////
//
// CPartialDisk
//
//////////////////////////////////////////////////////////////////////

CPartialDisk::CPartialDisk( GLdouble innerRadius, GLdouble outterRadius, GLdouble start, GLdouble sweep, GLint slice, CEnums::QuadStyle style ):
    CQuadrique(style), m_RayonInterieur(innerRadius), m_RayonExterieur(outterRadius), m_AngleDebut(start)
{
    m_Type = CEnums::QT_PARTIALDISK;
    if( slice == -1 )
        slice = sweep * 20 / 360;
}

//////////////////////////////////////////////////////////////////
/// @name : Setteurs (public)
/// @param : X
/// @return : aucun
/// Modifie les attributs de la classe
//////////////////////////////////////////////////////////////////
void CPartialDisk::SetInnerRadius ( GLdouble const radius ){m_RayonInterieur = radius;}
void CPartialDisk::SetOutterRadius( GLdouble const radius ){m_RayonExterieur = radius;}
void CPartialDisk::SetStartAngle  ( GLdouble const degree ){m_AngleDebut = degree;}
void CPartialDisk::SetSweepAngle  ( GLdouble const degree ){m_AngleFin = degree;}
void CPartialDisk::SetSlice       ( GLint const slice     ){m_Vertical = slice;}
//////////////////////////////////////////////////////////////////
/// @name : Getteurs (public)
/// @param : aucun
/// @return : X
/// Récupère les attributs de la classe
//////////////////////////////////////////////////////////////////
GLdouble CPartialDisk::GetInnerRadius ()const{return m_RayonInterieur;}
GLdouble CPartialDisk::GetOutterRadius()const{return m_RayonExterieur;}
GLdouble CPartialDisk::GetStartAngle  ()const{return m_AngleDebut;}
GLdouble CPartialDisk::GetSweepAngle  ()const{return m_AngleFin;}
GLint    CPartialDisk::GetSlice       ()const{return m_Vertical;}
