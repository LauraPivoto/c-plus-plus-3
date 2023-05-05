#include <iostream>

using namespace std;

struct treenode
{
	int info;
	treenode *esq;
	treenode *dir;
};

typedef treenode* treenodeptr; //vai definir um novo tipo de variável
//um é sinônimo do outro

void tInsere(treenodeptr & p, int x)
{
	if (p == NULL) // insere na raiz
	{
		p = new treenode;
		p->info = x;
		p->esq = NULL;
		p->dir = NULL;
	}
	else if (x < p->info)   // insere na subarvore esquerda
		tInsere(p->esq, x);
	else             // insere na subarvore direita
		tInsere(p->dir, x);
}

int preOrdemok(treenodeptr arvore, int &inicio_pre,int &a_procurar, int &achado_pre){
    if (arvore != NULL){
        inicio_pre++;
        if(arvore->info == a_procurar){
            achado_pre = inicio_pre;
        }
        preOrdemok(arvore->esq, inicio_pre, a_procurar, achado_pre);
        preOrdemok(arvore->dir, inicio_pre, a_procurar, achado_pre);
    }
}

int emOrdemok(treenodeptr arvore, int &inicio_em,int &a_procurar, int &achado_em){
    if (arvore != NULL){
        emOrdemok(arvore->esq, inicio_em, a_procurar , achado_em);
        inicio_em++;
        if(arvore->info == a_procurar){
            achado_em = inicio_em;
        }
        emOrdemok(arvore->dir, inicio_em, a_procurar, achado_em);
    }
}

int posOrdemok(treenodeptr arvore, int &inicio_pos,int &a_procurar, int &achado_pos){
    if (arvore != NULL){
        posOrdemok(arvore->esq, inicio_pos, a_procurar,  achado_pos);
        posOrdemok(arvore->dir, inicio_pos, a_procurar,  achado_pos);
        inicio_pos++;
        if(arvore->info == a_procurar){
            achado_pos = inicio_pos;
        }
    }
}

int main()
{
    treenodeptr p = NULL;
	
	treenodeptr arvore = NULL; //ponteiro para a raiz da arvore
	//se n fizer da errado

    int X;
    cin >> X;
    while(X != -1){
        tInsere(arvore, X);
        cin >> X;
    }
    
    int procurado;
    int inicio_pre=0, inicio_em = 0, inicio_pos = 0;
    int vetorpre[100], vetorem[100], vetorpos[100];
    cin >> procurado;
    int achado_pre;
    int achado_em;
    int achado_pos;
	
    preOrdemok(arvore, inicio_pre, procurado, achado_pre);
    emOrdemok(arvore, inicio_em, procurado, achado_em);
    posOrdemok(arvore, inicio_pos, procurado, achado_pos);
    
    cout << achado_pre << achado_em << achado_pos;
    
    if(achado_pre < achado_em && achado_pre < achado_pos){
		cout << "Pre" << endl;
	}else if(achado_em < achado_pre && achado_em < achado_pos){
		cout << "Em" << endl;
	}else if(achado_pos < achado_pre && achado_pos < achado_em){
		cout << "Pos" << endl;
	}
    
	return 0;
}