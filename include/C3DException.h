#ifndef C3DEXCEPTION_H
#define C3DEXCEPTION_H

#include <string>
#include <exception>

class C3DException : std::exception
{
    std::string what;
    public :
        C3DException(const char* what):what(what){}
        C3DException(const std::string& what):what(what){}
        ~C3DException()throw(){}

        const char* What() const {return what.c_str();}
};

class C3DOGLRendererException : public C3DException
{
    public :
        C3DOGLRendererException(const char* what):C3DException(what){}
        C3DOGLRendererException(const std::string& what):C3DException(what){}
};

class C3DTextureException : public C3DException
{
    public :
        C3DTextureException(const char* what):C3DException(what){}
        C3DTextureException(const std::string& what):C3DException(what){}
};

#endif // C3DEXCEPTION_H
