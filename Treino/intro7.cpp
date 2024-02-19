#include <iostream>
using namespace std;

class human
{
    public:
    // Atributos: características de um objeto
        string name;
        string job;
        int age = 30;

        // Podemos colocar valores default, que podem ser alterados, nos atributos
        // Ex: int age = 20;

    // Métodos: funções que um objeto pode fazer
        void eat()
        {
            cout << "This person is eating\n";
        }
        int Age(int age)
        {
            cout << "This person is " << age << " years old\n";
            return age;
        }
};

class Car
{
    public:
        string color;
        string model;
        int year;

        void accelerate()
        {
            cout << "Pedal to the metal!\n";
        }
        void brake()
        {
            cout << "You step on the brake\n";
        }
};

int main()
{
    human human1;

    human1.name = "Rick";
    human1.job = "Developer";
    human1.age = 30;

    cout << human1.name << '\n';
    cout << human1.job << '\n';
    cout << human1.age << '\n';

    human1.eat();
    human1.Age(human1.age);


    Car car1;

    car1.model = "Mustang";
    car1.year = 2023;
    car1.color = "Blue";

    cout << car1.model << '\n';
    cout << car1.year << '\n';
    cout << car1.color << '\n';
    
    car1.accelerate();
    car1.brake();

    return 0;
}