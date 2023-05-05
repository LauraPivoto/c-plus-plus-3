#include <iostream>
#include <iomanip>
#include <math.h>

using namespace std;

float media(int notas[], int nAlunos){
	float soma;
	for(int i = 1; i <= nAlunos; i++){
		soma = soma + notas[i];
	}
	
	float resultado = soma/nAlunos;
	return resultado;
}

int main(){
	int nAlunos;
	
	cin >> nAlunos;
	
	int notas[nAlunos];
	
	for(int i = 1; i <= nAlunos; i++){
		cin >> notas[i];
	}
	
	cout << "Media da turma = ";
	cout << fixed << setprecision(2) << media(notas, nAlunos)<< endl;
}