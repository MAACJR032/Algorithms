#include <iostream>
using namespace std;

// Constructor: Método especial que é chamado automaticamente quando um objeto é instanciado
// é útil para atribuir valores para atrinutos como argumentos

class Student
{        
    public:
        string name;
        int age;
        double media;
    
    Student(string name, int age, double media)
    {
        this->name = name;
        this->age = age;
        this->media = media;

        // Se os parametros do constructor tiverem nome diferente dos atributos, não precisa do this

        /*
        Ex: Student(string x, int y, double z)
        {
            name = x;
            age = y;
            media = z;
        }
        */
    }
};

int main()
{
    Student student1("Mark", 22, 7.5);

    cout << student1.name << '\n';
    cout << student1.age << '\n';
    cout << student1.media << '\n';

    return 0;
}