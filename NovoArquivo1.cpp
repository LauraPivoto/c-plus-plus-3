#include <iostream> // Entrada e sa?da
#include <climits> // INT_MAX

using namespace std;

int main()
{
	
	caminho caminho[100];
	int pd[100][100]; //isso vai olhar (quanto tem e quanto pode usar)
	
	int capacidade_mochila = 18;
	
	//cria��o do struct de entregas
	item v[100];

	
	int numero_entregadores;
	cout << "Qual o numero de entregadores? " << endl;

	cin >> numero_entregadores;

	entregadores teste[numero_entregadores];

	//verificar qual o melhor entregador para a l�gica
	for(int i = 1; i <= numero_entregadores ; i++)
	{
		teste[i].n_entregador = i;
		cout << "Qual o tamanho do percurso para o entregador " << i << " para ir ao supermercado?" << endl;
		cin >> teste[i].valor_ida_supermercado;
	}
	
	int entregador_mais_caro = -9999;
	for(int i = 1; i <= numero_entregadores ; i++)
	{
		if(teste[i].valor_ida_supermercado > entregador_mais_caro && teste[i].usado == false){
			entregador_mais_caro = teste[i].n_entregador;
		}
	}
	cout << "o entregador usado no momento ser� o " << entregador_mais_caro  << endl;
	teste[entregador_mais_caro].usado = true;
	int custo_total = 0;
	custo_total = custo_total + teste[entregador_mais_caro].valor_ida_supermercado;
	
	int entregas[100][100]; // custo[i][j] = custo de ir da entrega 'i' para a entrega 'j'
	int supermarket; // Primeiro e �ltimo ponto do percurso
	int numero_entregas; //n�mero de entregas

	cout << "Entre com o numero de entregas" << endl;
	cin >> numero_entregas;

	for(int i = 1; i <= numero_entregas; i++)
	{
		cout << "Entre com a identifica��o e peso da entrega " << i << endl;
		cin >> v[i].val >> v[i].peso;
	}

	for(int i = 1; i <= numero_entregas; i++){
		for(int j = i + 1; j < numero_entregas; j++)
		{
			cout << "Entre com o custo de ir da entrega " << i << " para a entrega " << j << endl;
			cin >> entregas[i][j];
			entregas[j][i] = entregas[i][j]; // Custo de i->j = custo de j->i
		} 
	}

	bool vis[100]; // marca se ja visitou ou nao uma cidade
	
	int menor_custo; // menor custo da viagem
	
	int custo_at; // menor custo atual
	
	int cidade_atual; // cidade atual
	int proxima_cidade; // proxima cidade

	// inicializando vetor vis (nenhuma cidade foi visitada no inicio)
	for(int i = 0; i < numero_entregas; i++)
		vis[i] = false;

	// guloso
	menor_custo = 0;
	cidade_atual = cidade_inicial;
	for(int i = 0; i < n - 1; i++) // n-1 vezes = qnt de caminhos (exceto a volta para a cidade inicial)
	{
		vis[cidade_atual] = true; // marco que ja visitei a cidade atual
		// encontrar qual a proxima cidade mais proxima
		custo_at = INT_MAX;
		for(int j = 0; j < n; j++)
		{
			if(!vis[j] && custo_at > custo[cidade_atual][j])
			{
				proxima_cidade = j;
				custo_at = custo[cidade_atual][j];
			}
		}
		menor_custo += custo_at;
		cidade_atual = proxima_cidade;
	}
	menor_custo += custo[cidade_atual][cidade_inicial];
	cout << "Menor custo = " << menor_custo << endl; 

	return 0;
}



