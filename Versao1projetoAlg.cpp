#include <iostream>
#include <list>
#include <climits>
#include <cmath>
using namespace std;

//STRUCT UTILIZADA PARA SOMAR O CUSTO DO ENTREGADOR IR AO SUPER NA SOMA FINAL
struct custo_inicial{
	int identificacao;
	int custo_ate_super;
};
//CUSTO 0

struct info_moto
{
	int tempo; //TEMPO MOTOBOY ATÉ O SUPER
	int motoqueiro; // IDENTIFICACAO
	int itens[100]; //ITENS SELECIONADOS
};
//CUSTO 0

//STRUCT PARA MONTAR O GRAFO
struct no
{
	int v; //DESTINO
	int peso; 
};
//CUSTO 0

//FUNCAO DE ARESTAS NO GRAFO
void cria_aresta(list<no>adj[], int u, int v, int p)
{
	no aux;

	aux.v = v;
	aux.peso = p;
	adj[u].push_back(aux);
	aux.v = u;
	adj[v].push_back(aux);
}
//CUSTO 0 POIS NÃO POSSUI FUNÇÃO RECURSIVA OU REPETIÇÃO

//FUNCAO DIJKSTRA PARA ORDENAR NOSSO GRADO
void dijkstra(list<no>adj[], int nVertices, int start, int end, info_moto motoboy[], int &custo_total)
{
	bool intree[10];
	int distance[10];
	int parent[10];
	list<int> caminho; //PARA GUARDAR O MENOR CAMINHO
	int u, v;
	int destino;
	int weight;
	int dist;
	list<no>::iterator p;
	int custo = 0; //ARMAZENA O CUSTO DO CAMINHO
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
	u = end;
	caminho.push_front(end);
	while(parent[u] != -1)
	{
		caminho.push_front(parent[u]);
		u = parent[u];
	}
	custo = distance[end]; //

	// MOSTRANDO O MENOR CAMINHO OBTIDO
	cout << "Menor caminho: ";
	for(c = caminho.begin(); c != caminho.end(); c++)
	{
		cout << *c << " ";
	}

	//CUSTO DO MOTOBOY PERCORRIDO ******ENTRE AS ENTREGAS
	cout << endl;
	custo_total += custo;
}
//Dijkstra TEM CUSTO numero_entregas^2 

//VER QUAL O MOTOBOY É MAIS RAPIDO ATRAVES DA ORGANIZAÇÃO DA MATRIZ
void quickSort(info_moto motoboy[], int nmotoboys, int i, int j)
{
	int esq = i, dir = j, pivo;
	info_moto trab;

	pivo = motoboy[(int)round((esq + dir) / 2.0)].tempo;

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
//CUSTO numero_motoboys

//ORGANIZAÇÃO MOCHILA E ENTREGAS
void mochila(int nitens, int capacidade_mochila, int numero_entregas, int cidade_inicial, int peso[], info_moto motoboy[], int nmotoboys, list<no>adj[], custo_inicial custo_inicial[])
{
	int capacidade_restante; //ESPACO RESTANTE DA MOCHILA
	int j, i; //CONTADORES
	capacidade_restante = capacidade_mochila; //PARA O INICIO DO ALGORITMO, A CAPACIDADE DA MOCHILA AINDA É 100%
	bool pega[100]; //CHECAR QUAL O ESTADO DO ITEM(PEGO OU N)
	bool aux = false; //AUX PARA VERIFICAR SE O MOTOBOY PARTIU DO SUPER
	int k = 0; //SOMATORIO DE ITENS PEGOS
	
	int custo_total = 0; //=CUSTO DO MOTOBOY PERCORRIDO ******ENTRE AS ENTREGAS

	//OS ITENS PEGOS PELOS MOTOBOYS TERÃO ESTADO -1(INDISPONIVEL)
	for(j = 1; j <= nmotoboys; j++)
		for(i = 1; i <= nitens + 1; i++)
			motoboy[j].itens[i] = -1;

	//NENHUM ITEM FOI PEGO NO INICIO
	for(i = 0; i <= nitens; i++)
		pega[i] = false;
	
	int custovolta = 0; //VARIAVEL USADA PARA SOMAR O CUSTO DO MOTOBOY PARA VOLTAR AO SUPER DEPOIS DA CORRIDA
	
	int custoida = 0; //CUSTO INICIAL DO MOTOBOY(PARA ELE CHEGAR AO SUPER)
	
	//AMBAS SERÃO SOMADAS NO FINAL DO CAMINHO
	
	//APENAS AUXILIARES PARA OS CUSTOS ACIMA
	int c =0;
	int b =0;

	//OLHANDO QUAL(IS) SÃO OS MELHOR(ES) ITEM(S):
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

		//RESULTADOS
		if(k == 0) //MOTOBOY NÃO USADO
		{
			cout << "Motoboy " << motoboy[j].motoqueiro << " nao utilizado" << endl;
		}

		else if(k != 0) //MOTOBOY UTILIZADO
		{
			cout << "Motoboy " << motoboy[j].motoqueiro << " pegou: ";
			for(i = 1; i <= k; i++)
				if(motoboy[j].itens[i] != -1){
					cout << motoboy[j].itens[i] << " ";
					c = motoboy[j].itens[i]; //OS AUXILIARES PARA A SOMA FINAL
					b = motoboy[j].tempo;
				}
				
				cout << endl;
			
				//DEFININDO OS ITENS QUE OS AUXS VÃO VALER
				custovolta = custo_inicial[c].custo_ate_super;
				custoida = b;

			//MOSTRANDO A MELHOR ROTA
			for(i = 1; i <= k; i++)
			{
				if(aux == false) //CASO ELE ESTEJA NO COMEÇO DO PERCURSO
				{
					dijkstra(adj, numero_entregas, cidade_inicial, motoboy[j].itens[i], motoboy, custo_total);
					aux = true;
				}
				else // CASO ESTEJA NO FINAL
					dijkstra(adj, numero_entregas, motoboy[j].itens[i - 1], motoboy[j].itens[i], motoboy, custo_total); // sai da casa anterior e vai até a casa atual

			}
		}
		if (k != 0) //TEMPO FINAL
			cout << "Foram gastos: " << custo_total + custoida + custovolta<< " minutos" << endl;

		custo_total = 0; //MUDANDO PARA 0 PARA OS OUTROS MOTOBOYS USAREM
		
		aux = false; //MUDANDO O CASO BASE PARA O PROX MOTOBOY
		
		//RESETANDO O RESTO
		capacidade_restante = capacidade_mochila;
		k = 0;
		cout << endl;
	}
}
//CUSTO numero_itens

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

	cout << "Qual o numero de entregas?" << endl;
	cin >> numero_entregas;

	cout << "Qual a posiçao do supermercado?" << endl;
	cin >> supermercado;

	//CRIAÇÃO DO GRAFO
	cout << "Coloque os seguintes info_motos: origem, destino e distancia entre cada local(incluir supermercado):" << endl;
	cout << "Digite -1 -1 -1 quando acabar os lugares" << endl;
	cin >> entrega1 >> entrega2 >> distancia_entrega;
	while(entrega1 != -1 && entrega2 != -1 && distancia_entrega != -1)
	{
		cria_aresta(adj, entrega1, entrega2, distancia_entrega);
		cin >> entrega1 >> entrega2 >> distancia_entrega;
	}
	
	//ESSA PARTE VAI NOS AJUDAR NA STRUCT DE CUSTO DE IDA DOS MOTOBOYS
	for(int i=1; i<=numero_entregas;i++){
		cout << "Agora coloque SOMENTE o custo de ida do supermercado até a entrega " << i << endl;
		custo_inicial[i].identificacao = i;
		cin >> custo_inicial[i].custo_ate_super;
	}

	cout << "Qual a quantidade de motoboys?" << endl;
	cin >> nmotoboys;

	for(i = 1; i <= nmotoboys; i++)
	{
		motoboy[i].motoqueiro = i;
		
		cout << "Indique o tempo do motoqueiro " << motoboy[i].motoqueiro << endl;
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