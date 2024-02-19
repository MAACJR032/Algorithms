#include <iostream>
using namespace std;

// Herança: Uma classe pode receber atributos e métodos de outra classe
// Ajuda a reutilizar código similar entre multiplas classes

class Animal
{
    public:
        bool alive = true;
    void eat()
    {
        cout << "This animal is eating\n";
    }
};

class Dog : public Animal
{
    public:

    void bark()
    {
        cout << "Woof woof\n";
    }
};

class Cat : public Animal
{
    public:

    void meow()
    {
        cout << "Meow\n";
    }
};

class Shape
{
    public:
        double area, volume;
};

class Cube : public Shape
{
    public:
        double side;

    Cube(double side)
    {
        this->side = side;
        this->area = side*side * 6;
        this->volume = side*side*side;
    }
};

class Sphere : public Shape
{
    public:
        double radius;

    Sphere(double radius)
    {
        this->radius = radius;
        this->area = 4 * 3.14159 * radius * radius;
        this->volume = (4/3.0) * 3.14159 * radius * radius * radius;
    }
};


int main()
{
    Dog dog;
    cout << dog.alive << '\n';
    dog.eat();
    dog.bark();

    Cat cat;
    cout << cat.alive << '\n';
    cat.eat();
    cat.meow();

    Cube cube(5);
    cout << "Area: " << cube.area << " cm^2\n";
    cout << "Volume: " << cube.volume << " cm^3\n";

    Sphere sphere(7);
    cout << "Area: " << sphere.area << " cm^2\n";
    cout << "Volume: " << sphere.volume << " cm^3\n";

    return 0;
}