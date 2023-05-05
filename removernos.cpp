#include <iostream>

using namespace std;

struct treenode
{
	int info;
	treenode *esq;
	treenode *dir;
};

typedef treenode* treenodeptr;

treenodeptr tMenor(treenodeptr &raiz)
{
	treenodeptr t;
	t = raiz;
	if (t->esq == NULL) // encontrou o menor valor
	{
		raiz = raiz->dir;
		return t;
	}
	else // continua a busca na sub´arvore esquerda
		return tMenor(raiz->esq);
}

int tRemove(treenodeptr &raiz, int x)
{
	treenodeptr p;
	if (raiz == NULL) // ´arvore vazia
		return 1;
	if (x == raiz->info)
	{
		p = raiz;
		if (raiz->esq == NULL) // a raiz n~ao tem filho esquerdo
			raiz = raiz->dir;
		else if (raiz->dir == NULL) // a raiz n~ao tem filho direito
			raiz = raiz->esq;
		else // a raiz tem ambos os filhos
		{
			p = tMenor(raiz->dir);
			raiz->info = p->info;
		}
		delete p;
		return 0;
	}
	else if (x < raiz->info)
		return tRemove(raiz->esq, x);
	else
		return tRemove(raiz->dir, x);
}

void tDestruir (treenodeptr &arvore)
{
	if (arvore != NULL)
	{
		tDestruir(arvore->esq);
		tDestruir(arvore->dir);
		delete arvore;
	}
	arvore = NULL;
}

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
	while(numero != 0)
	{
		tInsere(arvore, numero);
		cin >> numero;
	}

	int x;
	
	cin >> x;
	
	tRemove(arvore, x);

	
	emOrdem(arvore);

	return 0;
}
