#include <iostream>
#include <vector>
using namespace std;

// Função p/ encoontrar a entrada
// Checar caminhos possíveis a partir da entrada
// Quando chegar no tesouro, se o Nº de armadilhas vezes 2 for maior q o Nº q ele consegue escapar é imposssible

int main()
{
    // x - tesouro, @ - entrada, # - paredes, . - piso seguro, s - espinhos
    int rows, width, avoid;
    cin >> rows >> width >> avoid;
    
    for (int i = 0; i < rows; i++)
    {
        string mapa[width];
        cin >> mapa[i];
    }
    
    return 0;
}