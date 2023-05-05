#include <iostream>
  
using namespace std;

struct motoboy{
	int n_motoboy;
	int distancia_ate_super;
	int mochila;
};

void bubbleSort(int vetor[], int tamanho)
{
	int i, j; // contadores
	int trab;
	bool troca;
	int limite;
	troca = true;
	limite = tamanho - 1;
	while (troca)
	{
		troca = false;
		for (i = 0; i < limite; i++)
			if (vetor[i] > vetor[i + 1])
			{
				trab = vetor[i];
				vetor[i] = vetor[i + 1];
				vetor[i + 1] = trab;
				j = i;
				troca = true;
			}
		limite = j;
	}
	
	for(int i =0; i<= tamanho-1 ; i++){
		cout << vetor[i] << " " ;
	}
}

int main(){
	
	motoboy motoboys[100];
	
	int n_motoboys;
	cin >> n_motoboys;
	
	for(int i=0;i <n_motoboys;i++){
		motoboys[i].mochila = 0;
	}
	
	int vetor_motoboys[100];
	
	for(int i = 0; i < n_motoboys ; i++)
	{
		motoboys[i].n_motoboy = i;
		cout << "Qual o tamanho do percurso para o entregador " << i << " para ir ao supermercado?" << endl;
		cin >> motoboys[i].distancia_ate_super;
	}
	
	int tamanho = 0;
	for(int i = 0; i < n_motoboys ; i++)
	{
		vetor_motoboys[i] = motoboys[i].distancia_ate_super;
		tamanho++;
	}
		 
 	bubbleSort(vetor_motoboys, tamanho);
 	
 	int vetor_inverso[n_motoboys];
 	for(int i = 0; i < n_motoboys ; i++)
	{
		int j = n_motoboys - 1;
		vetor_inverso[i] = vetor_motoboys[j];
		j--;
		cout << vetor_inverso[i] << endl;
	}
	
	return 0;
}