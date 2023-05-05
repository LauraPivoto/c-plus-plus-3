#include <iostream>
#include <cstring>

using namespace std;

struct homem //criação da struct homem com nome e nota
{
	char nome[50];
	int nota1, nota2, nota3, nota4;
};

int main()
{
	int numero_homens, i = 1, notas = 0, maior_nota = -9999, soma = 0;
	int vencedor; //o vencedor deverá ser indicado pela posição

	cin >> numero_homens;
	cin.ignore(); //pra arrumar a entreada de dados

	homem forte[10]; //criando uma struct


	for(i = 1; i <= numero_homens; i++)
	{
		cin.getline(forte[i].nome, 50);
		cin >> forte[i].nota1 >> forte[i].nota2 >> forte[i].nota3 >> forte[i].nota4;

		soma = soma +  forte[i].nota1 + forte[i].nota2 + forte[i].nota3 + forte[i].nota4;
		if(soma > maior_nota)
		{
			maior_nota = soma;
			vencedor = i;
		}
		cin.ignore();
		soma = 0;
	}


	cout << "Vencedor: " << forte[vencedor].nome;
}