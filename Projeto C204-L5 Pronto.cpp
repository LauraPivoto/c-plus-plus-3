#include <iostream>
#include <list>
#include <climits>
#include <cmath>
using namespace std;

struct custo_inicial{
	int identificacao;
	int custo_ate_super;
};

struct info_moto
{
	int tempo; //tempo do motoboy ate o supermercado
	int motoqueiro; // identificação do motoqueiro
	int itens[100]; // itens que foram pegos
};

// struct para montar o grafo de entregas, nesse caso usaremos dijkstra
struct no
{
	int v; // vertice de destino da aresta
	int peso; // peso da aresta
};

// função que cria a aresta do grafo
void cria_aresta(list<no>adj[], int u, int v, int p)
{
	no aux; // var aux para inserir as arestas em adj

	aux.v = v;
	aux.peso = p;
	adj[u].push_back(aux);
	aux.v = u;
	adj[v].push_back(aux);
}

// função que calcula o menor custo dos caminhos do grafo
void dijkstra(list<no>adj[], int nVertices, int start, int end, info_moto motoboy[], int &custo_total)
{
	bool intree[10];
	int distance[10];
	int parent[10];
	list<int> caminho; // lista para armazenar o caminho feito com menor custo
	int u, v;
	int destino;
	int weight;
	int dist;
	list<no>::iterator p; // iterator para varrer a lista adj
	int custo = 0; // var aux para armazenar o custo do caminho
	list<int>::iterator c;

	for(u = 1; u <= nVertices; u++)
	{
		intree[u] = false;
		distance[u] = INT_MAX;
		parent[u] = -1;
	}
	distance[start] = 0;
	v = start;
	while(intree[v] == false)
	{
		intree[v] = true;
		for(p = adj[v].begin(); p != adj[v].end(); p++)
		{
			destino = p->v;
			weight = p->peso;
			if(distance[destino] > distance[v] + weight)
			{
				distance[destino] = distance[v] + weight;
				parent[destino] = v;
			}
		}
		v = 0;
		dist = INT_MAX;
		for(u = 1; u <= nVertices; u++)
		{
			if(intree[u] == false && dist > distance[u])
			{
				dist = distance[u];
				v = u;
			}
		}
	}

	// salvando o end na var u para poder fazer o controle de parents
	u = end;
	// colocando o elemento final no primeiro lugar da fila
	caminho.push_front(end);
	// salvando o caminho na fila
	while(parent[u] != -1) // se parents for -1, quer dizer que não tem mais caminhos
	{
		caminho.push_front(parent[u]);
		u = parent[u];
	}
	// salvando o custo
	custo = distance[end]; // o custo, por ser acumulativo, é igual a distancia do último vértice

	// mostrando o vetor na ordem certa e o custo do caminho total
	cout << "Menor caminho: ";
	for(c = caminho.begin(); c != caminho.end(); c++) // foram salvos 4 caminhos, mas no vetor as posições vão de 0 - 3
	{
		cout << *c << " ";
	}

	// fazendo a somatória do custo do caminho percorrido por cada motoboy
	cout << endl;
	custo_total += custo;
}

//funcao de quick sort
void quickSort(info_moto motoboy[], int nmotoboys, int i, int j)
{
	//variaveis
	int esq = i, dir = j, pivo;
	info_moto trab;

	pivo = motoboy[(int)round((esq + dir) / 2.0)].tempo;

	//estrutura para reorganizar
	do
	{

		while(motoboy[esq].tempo < pivo)
			esq++;

		while(motoboy[dir].tempo > pivo)
			dir--;

		if(esq <= dir)
		{

			trab.tempo = motoboy[esq].tempo;
			motoboy[esq].tempo = motoboy[dir].tempo;
			motoboy[dir].tempo = trab.tempo;

			trab.motoqueiro = motoboy[esq].motoqueiro;
			motoboy[esq].motoqueiro = motoboy[dir].motoqueiro;
			motoboy[dir].motoqueiro = trab.motoqueiro;

			esq++;
			dir--;

		}

	}
	while(esq <= dir);

	if(dir - i >= 0)
		quickSort(motoboy, nmotoboys, i, dir);

	if(j - esq >= 0)
		quickSort(motoboy, nmotoboys, esq, j);

}

//ORGANIZAÇÃO MOCHILA E ENTREGAS
void mochila(int nitens, int capacidade_mochila, int numero_entregas, int cidade_inicial, int peso[], info_moto motoboy[], int nmotoboys, list<no>adj[], custo_inicial custo_inicial[])
{
	int capacidade_restante; // capacidade restante da mochila para cada motoboy
	
	int j, i; // contadores
	
	capacidade_restante = capacidade_mochila; // setando a capacidade restante sendo igual a capacidade total da mochila
	bool pega[100]; // var aux para ver se o item ja foi pego ou não
	bool aux = false; // caso ele parta do supermercado ou não
	int k = 0; // contador de itens pegos
	int custo_total = 0; // custo total percorrido pelo caminho de cada motoboy

	//inicializando os itens pegos pelos motoboys como -1
	for(j = 1; j <= nmotoboys; j++)
		for(i = 1; i <= nitens + 1; i++)
			motoboy[j].itens[i] = -1;

	//setando que nenhum item foi pego
	for(i = 0; i <= nitens; i++)
		pega[i] = false;
	
	int custoo = 0;
	int c =0;
	int b =0;

	//analizando quais itens serao pegos pelos motoboys
	for(j = 1; j <= nmotoboys; j++)
	{
		for(i = 1; i <= nitens + 1; i++)
		{
			if(capacidade_restante >= peso[i] && i != cidade_inicial && pega[i] == false)
			{
				k++;
				motoboy[j].itens[k] = i;
				capacidade_restante -= peso[i];
				pega[i] = true;
			}
		}

		// mostrando as compras pegas pelos motoboys
		if(k == 0) // não pegou nenhum item
		{
			cout << "Motoboy " << motoboy[j].motoqueiro << " nao pegou nenhum item" << endl;
			cout << "Nao realizou entregas" << endl;
			cout << "Nao teve tempo de entrega" << endl;
		}

		else if(k != 0) // caso pegou alguma coisa
		{
			cout << "Motoboy " << motoboy[j].motoqueiro << " pegou o(s) item(ns): ";
			for(i = 1; i <= k; i++)
				if(motoboy[j].itens[i] != -1){
					cout << motoboy[j].itens[i] << " ";
					c = motoboy[j].itens[i];
				}
				
				cout << endl;
			
				//custoo = custo_inicial[c].custo_ate_super;
				//cout << "CUSTO DE VOLTA: " << custoo;

			// criando a rota e mostrando o caminho feito por cada entregador
			for(i = 1; i <= k; i++)
			{
				if(aux == false) // caso base, em que ele sai do supermercado
				{
					dijkstra(adj, numero_entregas, cidade_inicial, motoboy[j].itens[i], motoboy, custo_total);
					aux = true;
				}
				else // caso geral, caso ele não parta do supermercado
					dijkstra(adj, numero_entregas, motoboy[j].itens[i - 1], motoboy[j].itens[i], motoboy, custo_total); // sai da casa anterior e vai até a casa atual

			}
		}
		if (k != 0) // mostrando o tempo total gasto por cada motoboy
			cout << "Ele gastou " << custo_total<< " min" << endl;

		custo_total = 0; // resetando o tempo total para o próximo motoboy
		aux = false; // resetando o caso base para o próximo motoboy
		capacidade_restante = capacidade_mochila; // resetando a capacidade restante para o próximo motoboy
		k = 0; // resetando a posição do item que foi pego pelo motoboy
		cout << endl;
	}
}

int main()
{
	
	list<no> adj[100]; 				// LISTA DE ADJACENCIA PARA O Dijkstra
	int entrega1, entrega2; 		// POSICAO ATUAL E PROXIMA DO MOTOBOY
	int distancia_entrega;			//DISTANCIA ENTRE CADA ENTRADA
	int numero_entregas;
	list<no>::iterator p;
	int supermercado; 			//LOCAL DO SUPER
	
	custo_inicial custo_inicial[100];
	
	int i, j; 						//CONTADOR
	
	int nmotoboys; 					//NUMERO MOTOBOYS
	info_moto motoboy[100]; 				//STRUCT PARA OS info_motoS DOS MOTOBOYS
	int capacidade_mochila;
	int nitens; 					//NUMERO ITENS
	int peso[100]; 					//PESO DOS ITENS

	cout << "Qual o número de entregas?" << endl;
	cin >> numero_entregas;

	cout << "Qual a posição do supermercado?" << endl;
	cin >> supermercado;

	//CRIAÇÃO DO GRAFO
	cout << "Coloque os seguintes info_motos: origem, destino e distancia entre cada entrega:" << endl;
	cout << "Digite -1 -1 -1 quando preencher todas as casas e o tempo entre elas" << endl;
	cin >> entrega1 >> entrega2 >> distancia_entrega;
	while(entrega1 != -1 && entrega2 != -1 && distancia_entrega != -1)
	{
		cria_aresta(adj, entrega1, entrega2, distancia_entrega);
		cout << "Coloque os seguintes info_motos: origem, destino e distancia entre cada entrega:" << endl;
		cin >> entrega1 >> entrega2 >> distancia_entrega;
	}
	
	for(int i=1; i<=numero_entregas;i++){
		cout << "Agora coloque SOMENTE o custo de ida do supermercado até a entrega " << i << endl;
		custo_inicial[i].identificacao = i;
		cin >> custo_inicial[i].custo_ate_super;
	}
	
	for(int i=1; i<=numero_entregas;i++){
		cout << custo_inicial[i].identificacao << " " << custo_inicial[i].custo_ate_super << endl;
	}

	cout << "Qual a quantidade de motoboys?" << endl;
	cin >> nmotoboys;

	for(i = 1; i <= nmotoboys; i++)
	{
		cout << "Indique o numero do motoqueiro:";
		cin >> motoboy[i].motoqueiro;

		cout << "Indique o tempo do motoqueiro" << motoboy[i].motoqueiro << endl;
		cin >> motoboy[i].tempo;
	}

	//ORDENANDO OS MOTOBOYS, PARA TERMOS DE PREFERENCIA O DE MENOR TEMPO
	j = nmotoboys;
	quickSort(motoboy, nmotoboys, 1, j);

	// ENTRANDO COM AS VARIAVEIS PARA A MOCHILA
	cout << "Indique o numero de entregas:" << endl;
	cin >> nitens;

	cout << "Indique o peso máximo da mochila:" << endl;
	cin >> capacidade_mochila;

	// ENTRANDO COM O PESO DE CADA ITEM
	for(i = 1; i <= nitens + 1; i++)
		if(i != supermercado)
		{
			cout << "Entre com o peso do item " << i << ":" <<endl;
			cin >> peso[i];
		}
		
	cout << endl;

	// VENDO QUAIS ITENS VAO PARA A MOCHILA
	mochila(nitens, capacidade_mochila, numero_entregas, supermercado, peso, motoboy, nmotoboys, adj, custo_inicial);

	cout << endl;
	
	return 0;
}