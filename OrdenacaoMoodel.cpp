#include <iostream>

using namespace std;

struct treenode
{
	int info;
	treenode *esq;
	treenode *dir;
};

typedef treenode* treenodeptr;

void tInsere(treenodeptr &p, int x)
{
	if (p == NULL) // insere na raiz
	{
		p = new treenode;
		p->info = x;
		p->dir = NULL;
		p->esq = NULL;
	}
	else if (x < p->info) // insere na subarvore esquerda
		tInsere(p->dir, x);
	else             // insere na subarvore direita
		tInsere(p->esq, x);
}

void emOrdem (treenodeptr arvore)
{
	if (arvore != NULL)
	{
		emOrdem(arvore->esq);
		cout << arvore->info << endl;
		emOrdem(arvore->dir);
	}
}

int main()
{
	treenodeptr arvore = NULL;
	treenodeptr p = NULL;

	int numero;//numeros a serem inseridos

	cin >> numero;
	while(numero != -1)
	{
		tInsere(arvore, numero);
		cin >> numero;
	}
	
	emOrdem(arvore);

	return 0;
}
