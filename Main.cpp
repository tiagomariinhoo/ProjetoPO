#include <bits/stdc++.h>
using namespace std;
 
#define DEBUG if(1)
#define MAX INT_MAX
#define MAXLL INT_MAX
#define MAXU ULLONG_MAX
#define MIN -2000000
#define endl "\n"
#define INF INT_MAX
#define MOD 1000000007
#define s(n) scanf("%d", &n)
#define ss(a,b) scanf("%d %d",&a,&b)
#define pb push_back
#define mp make_pair
#define M_PI 3.14159265358979323846
#define sz(a) int(a.size())
#define lli long long int
#define rep(i,a,n) for (int i=a;i<n;i++)
#define ler(a,n,vec) for(int i=0;i<n;i++)s(a), vec.pb(a)
typedef vector<lli> vi;
typedef vector<vi> vvi;
typedef pair<int,int> ii;
#define DEBUG if(1)
#define F first
#define S second
int dx[] = {0, 1, 0, -1};
int dy[] = {1, 0, -1, 0};
int ddx[] = {1, 0};
int ddy[] = {1, 1};
#define MAXN 100001
#define MAXL 20

map<string, vector< pair<double, string> > > adjList;
set<string> vis;

void addNode(){
	if(vis.size() == 0){
		string a, b;
		double dist;
		cout << "Ainda nao tem nodes disponiveis!" << endl;
		cout << "Por favor, insira o nome dos nodes. " << endl;
		cout << "Nome 1: " << endl;
		cin >> a;
		cout << "Nome 2: " << endl;
		cin >> b;
		cout << "Distancia: " << endl;
		cin >> dist;

		adjList[a].pb({dist, b});
		adjList[b].pb({dist, a});
		vis.insert(a), vis.insert(b);
		cout << "Aresta adicionada com sucesso!" << endl;

	} else {
		cout << "Lista de Nodes: " << endl;
		vector<string> aux;
		for(auto i : vis) cout << i << endl, aux.pb(i);

		cout << "1 - Para adicionar a um node existente" << endl;
		cout << "2 - Para adicionar dois nodes novos" << endl;
		int op;
		cin >> op;
		if(op == 1){	
			cout << "Escolha o node: " << endl;
			for(int i=0;i<sz(aux);i++) cout << i << " - " << aux[i] << endl;

			int op2;
			cin >> op2;
			if(op2 < 0 or op2 >= sz(aux)){
				cout << "Tente novamente!" << endl;
				return ;
			}

			cout << "Digite o nome e a distancia para juntar ao Node " << aux[op] << endl;
			string a;
			cout << "Nome: ";
			cin >> a;
			cout << endl;
			cout << "Distancia: ";
			cout << endl;
			double dist;
			cin >> dist;

			bool at = false;
			for(auto i : adjList[aux[op]]){
				if(i.S == a){
					i.F = dist;
					at = true;

					for(auto j : adjList[a]){
						if(j.S == aux[op]){
							j.F = dist;
							break;
						}
					}

					break;
				}
			}

			if(!at){
			adjList[aux[op]].pb({dist, a});
			adjList[a].pb({dist, aux[op]});
			}

			vis.insert(a);
			cout << "Aresta adicionada com sucesso!" << endl;
		} else if(op == 2){
			string a, b;
			double dist;
			cout << "Digite o nome dos nodes!" << endl;
			cout << "Nome 1: ";
			cout << endl;
			cin >> a;
			cout << "Nome 2: ";
			cout << endl;
			cin >> b;
			cout << "Dist: ";
			cout << endl;
			cin >> dist;
			
			vis.insert(a), vis.insert(b);
			bool at = false;
			for(auto i : adjList[a]){
				if(i.S == b){
					at = true;
					i.F = dist;

					for(auto j : adjList[b]){
						if(j.S == a){
							j.F = dist;
							break;
						}
					}
					break;
				}
			}

			if(!at){
				adjList[a].pb({dist, b});
				adjList[b].pb({dist, a});
			}

			cout << "Aresta adicionada com sucesso!" << endl;
		} else{
			cout << "Selecione uma opcao valida!" << endl;
			return ;
		}

	}

}

void listaNodes(){	
	map<string, int> vis2;
	for(auto i : adjList){
		for(auto j : i.S){
			// if(vis2[i.F] or vis2[j.S]) continue;
			cout << i.F << " " << j.S << endl;
			cout << "Distancia: " << j.F << endl;
			vis2[i.F] = 1, vis2[j.S] = 1;
		}
	}
}

void dijkstra(){

}

void kruskal(){

}

int main(){	

	while(1){
		int op;
		cout << "Escolha uma opcao!" << endl;
		cout << "1 - Adicionar Node" << endl;
		cout << "2 - Listar Nodes" << endl;
		cout << "3 - Rodar Dijkstra" << endl;
		cout << "4 - Rodar Kruskal" << endl;
		cout << "0 - Sair" << endl;

		cin >> op;
		try{
			if(op == 1){
				addNode();
			} else if(op == 2){
				listaNodes();
			} else if(op == 3){
				dijkstra();
			} else if(op == 4){
				kruskal();
			} else if(op == 0){
				break;
			}	else {
				cout << "Escolha uma opcao valida!" << endl;
			}
		} catch(exception& e){
			cout << "Por favor, tente novamente!" << endl;
		}

	}	


	return 0;
}

