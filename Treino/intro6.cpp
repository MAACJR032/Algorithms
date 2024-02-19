#include <iostream>
using namespace std;

// Aceita parametros de dois tipos iguais ou diferentes (ex: int e float)
template <typename E, typename W>

// auto: faz com que o compilador decida qual o tipo de retorno
auto maior(E x, W y)
{
    return (x > y) ? x : y;
}

int main()
{
    cout << maior(1, 2.1) << '\n';  
    
    return 0;
}