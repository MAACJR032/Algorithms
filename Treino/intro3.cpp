#include <iostream>

int main()
{
    std::string name;

    std::cout << "Qual o seu nome: ";
    std::getline(std::cin, name);

    if (name.length() > 12)
        std::cout << "Seu nome deve ter menos de 12 caracteres\n";
    else
        std::cout << "Bem-vindo " << name << '\n';
    
    name.empty(); // Verifica se a string é vazia
    name.clear(); //Esvazia a string

    name.append("@gmail.com"); // Concatena a string

    std::cout << name.at(0); // Printa o caractere na posição 0

    name.insert(0, "@"); // Insere @ na posição 0
    name.find(' '); // Encontra a posição do primeiro espaço na string
    name.erase(0, 3); // Remove os caracteres entre das posições 0 a 2 (x, y) x inclusive e y não inclusive
    
     
    return 0;
}