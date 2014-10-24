#ifndef CSINGLETON_H
#define CSINGLETON_H

// Classe permettant de rendre une classe unique, impossible � copier ou � instancier
// Suffit de mettre le constructeur de la classe d�riv�e en private et de d�clarer la classe CSingleton en friend
template<typename T>
class CSingleton
{
    // Membres Pivate
    static T* me;

    // Fonctions Private
    CSingleton(CSingleton&);
    void operator =(CSingleton&);

    protected:
        // Membres Protected

        // Fonctions Protected
        CSingleton(){}
        ~CSingleton(){}

    public:
        // Membres public

        // Fonctions public
        static T& Get()
        {
            if( !me )
                me = new T;

            return *me;
        }

        static void Destroy()
        {
            delete me;
            me = 0;
        }
};

template<typename T> T* CSingleton<T>::me = 0;

#endif // CSINGLETON_H
