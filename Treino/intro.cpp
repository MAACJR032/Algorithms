#include <iostream>
#include <vector>

// Typedef
// typedef std::vector<std::pair<std::string, int>> pairlist_t;

// OU

// using
using text_t = std::string;

namespace first{
    int x = 20;
}
int main()
{
    // Print
    int x = 10;
    std::cout << x << '\n';

    // Strings
    std::string name = "Marcio";
    std::cout << name << '\n';

    std::cout << name << ' '<< x << '\n';

    // Namespace
    std::cout << first::x << '\n';

    // using namespace first, não precisaria colocar first::

    // pairlist_t pairlist (declarar variável do tipo pairlist_t)

    // scanf
    std::string nome;
    std::cout << "Qual seu nome? ";

    // std::cin >> nome;
    // Input de string que aceita espaços
    std::getline(std::cin, nome);

    int idade;
    std::cout << "Qual sua idade? ";
    std::cin >> idade;

    std::cout << "Oi, " << nome << '\n';
    std::cout << "Voce tem " << idade << " anos\n";

    // Caso a ordem das perguntas estivesse invertida, poderia dar problema no buffer na hora de ler a string
    // std::getline(std::cin >> std::ws, nome); (ws - white spaces, limpa o buffer)
    return 0;
}
