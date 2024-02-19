#include <iostream>
using namespace std;

class Stove
{        
    // Não se pode alterar o valor de temperature fora da classe
    private:
        int temperature = 0;
    
    public:
        Stove(int temperature)
        {
            setTemp(temperature);
        }

        // É possível ler o valor de um atributo privado
        int getTemp()
        {
            return temperature;
        }

        // É possível alterar o valor de um atributo privado
        void setTemp(int temperature)
        {
            if (temperature < 0)
                this->temperature = 0;
            else if (this->temperature >= 10)
                this->temperature = 10;
            else
                this->temperature = temperature;
        }
};

int main()
{
    Stove stove(0);
    cout << stove.getTemp() << '\n';

    stove.setTemp(100);
    cout << stove.getTemp() << '\n';

    stove.setTemp(5);
    cout << stove.getTemp() << '\n';

    stove.setTemp(-2);
    cout << stove.getTemp() << '\n';

    return 0;
}