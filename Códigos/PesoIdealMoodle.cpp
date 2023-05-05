#include <iostream>
#include <iomanip>

using namespace std;

float ideal(float h, char sexo){
	float resultado;
	if(sexo == 'M'){
		resultado =  72.7 * h - 58;
	}else{
		resultado = 62.1 * h - 44.7;
	}
	cout << "Peso Ideal = ";
		cout <<fixed << setprecision(2)<<  resultado;
		cout <<  " kg" << endl;
}

int main(){
	char sexo;
	float altura;
	
	cin >> altura >> sexo;
	
	ideal(altura, sexo);
	
	return 0;
}