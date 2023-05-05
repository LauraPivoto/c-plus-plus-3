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

int nAbaixo(int notas[], int nAlunos, float media){
	int abaixo = 0;
	for(int i = 1; i <= nAlunos; i++){
		if(notas[i] < media){
			abaixo++;
		}
	}
	return abaixo;
}

int nAcima(int notas[], int nAlunos, float media){
	int acima = 0;
	for(int i = 1; i <= nAlunos; i++){
		if(notas[i] > media){
			acima++;
		}
	}
	return acima;
}

int main(){
	int nAlunos;
	
	cin >> nAlunos;
	
	int notas[nAlunos];
	
	for(int i = 1; i <= nAlunos; i++){
		cin >> notas[i];
	}
	
	cout << "Media da turma = ";
	float media1 = media(notas, nAlunos);
	cout << fixed << setprecision(2) << media1<< endl;
	
	cout << "Alunos com nota abaixo da media: ";
	cout << fixed << setprecision(2) << nAbaixo(notas, nAlunos, media1)<< endl;
	
		cout << "Alunos com nota acima da media: ";
	cout << fixed << setprecision(2) <<  nAcima(notas, nAlunos, media1)<< endl;
}