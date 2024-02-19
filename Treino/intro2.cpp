#include <iostream>
#include <cmath>
#include <iomanip>

int main()
{
    int x = 4, y =3, z;

    z = std::max(x, y); // z será o maior número, comparando x com y
    std::cout << z << '\n';

    z = std::min(x, y); // z será o menor número, comparando x com y
    std::cout << z << '\n';

    // potência e raiz quadrada
    z = pow(2, 4); // 2 elevado a 4
    z = sqrt(9); // raiz de 9

    // Módulo
    z = abs(-3); // z é o módulo de -3, z = 3

    // Arredondamento
    float h = 2.121;

    z = round(h); // arredonda para cima ou para baixo
    z = ceil(h); // arredonda pra cima
    z = floor(h); // arredonda pra baixo

    // Calculadora hipotenusa
    double a, b, c;

    std::cout << "Digite o valor dos catetos: ";
    std::cin >> a >> b;

    c = sqrt(pow(a, 2) + pow(b, 2));
    std::cout << "A hipotenusa eh " << std::setprecision(2) << std::fixed << c << '\n'; // Coloca apenas 2 casas decimais

    // foreach loop (não precisa iterar, mas não é flexível)
    int notas[] = {2, 7, 6, 8, 10};

    for (int nota : notas)
        std::cout << nota << '\n';
    
    return 0;
}