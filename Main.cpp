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
map<string, int> dis;

void addNode(){

  system("CLS");
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


    if(cin.fail()){
      cout << "Tente novamente!" << endl;
      cin.clear();
      cin.ignore(INT_MAX, '\n');
      system("CLS");
      return ;
    }

    adjList[a].pb({dist, b});
    adjList[b].pb({dist, a});
    vis.insert(a), vis.insert(b);
    cout << "Aresta adicionada com sucesso!" << endl;

  } else {
    cout << "Lista de Nodes: " << endl;
    vector<string> aux;
    for(auto i : vis) cout << i << endl, aux.pb(i);

    cout << "Adicione um caminho entre dois nodes!" << endl;

  cout << " --- " << endl;
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

      if(cin.fail()){
      cout << "Tente novamente!" << endl;
      cin.clear();
      cin.ignore(INT_MAX, '\n');
      system("CLS");
      return ;
      // continue;
    }
      
      vis.insert(a), vis.insert(b);
      bool at = false;
      for(int i=0;i<sz(adjList[a]);i++){

        if(adjList[a][i].S == b){
          at = true;
          adjList[a][i].F = dist;

          for(int j=0;j<sz(adjList[b]);j++){
            if(adjList[b][j].S == a){
              adjList[b][j].F = dist;
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

      system("CLS");
      if(!at)
      cout << "Aresta adicionada com sucesso!" << endl;
      else cout << "Aresta atualizada com sucesso!" << endl;
      cout << " ---- " << endl << endl;
  }

}

void listaNodes(){  
  map<string, int> vis2;
  set<pair<string, pair<string, int> > > lista;
  for(auto i : adjList){
    for(auto j : i.S){

      string aa = i.F, bb = j.S;
      if(aa > bb) swap(aa, bb);
      lista.insert({aa, {bb, j.F}});

    }
  }
  for(auto i : lista){
    cout << i.F << " - " << i.S.F << " : " << i.S.S << endl;
  }
}

void dijkstra(){
  priority_queue< pair<int, string>, vector< pair<int, string> >, greater<pair<int,string>>> pq;

  string root;
  cout << "Escolha o node raiz: ";
  bool at = false;
  vector<string> aux;
  for(auto i : vis) aux.pb(i);
  for(int i=0;i<sz(aux);i++){
    cout << i << " - " << aux[i] << endl;
  }
  int op;
  cin >> op;

  if(cin.fail()){
      cout << "Tente novamente!" << endl;
      cin.clear();
      cin.ignore(INT_MAX, '\n');
      system("CLS");
      return ;
  }

  if(op < 0 or op >= sz(aux)){
    cout << "Selecione uma opcao valida!" << endl;
    return ;
  }

  for(auto i : vis) dis[i] = 191919190;
  dis[aux[op]] = 0;
  pq.push({0, aux[op]});

  while(!pq.empty()){
    string atual = pq.top().S;
    pq.pop();
    for(auto i : adjList[atual]){
      if(dis[atual] + i.F < dis[i.S]){
        dis[i.S] = dis[atual] + i.F;
        pq.push({dis[i.S], i.S});
      }
    }
  }

  cout << "Dijkstra terminado, menor caminho de " << root << " para os outros nodes:" << endl;
  for(auto i : vis){
    if(i == root) continue;
    cout << i << " : " << dis[i] << endl;
  }

}

map<string, int> peso;
map<string, string> pai;

string proc(string x){
  if(pai[x] == x) return x;
  return pai[x] = proc(pai[x]);
}

void junta(string a, string b){
  a = proc(a);
  b = proc(b);

  if(peso[a] < peso[b]){
    pai[a] = b;
  } else if(peso[a] > peso[b]){
    pai[b] = a;
  } else{
    pai[a] = b;
    peso[b]++;
  }
}

void kruskal(){
  vector<pair<int, pair<string, string>>> aux, mst;

  for(auto i : vis){
    pai[i] = i;
    for(auto j : adjList[i]){
      aux.pb({j.F,{i, j.S}});
    }
  }

  sort(aux.begin(), aux.end());

  int sum = 0;
  for(int i=0;i<sz(aux);i++){
    string x = aux[i].S.F, y = aux[i].S.S;
    if(proc(x) != proc(y)){
      junta(x, y);
      mst.pb({aux[i].F,{x, y}});
      sum += aux[i].F;
    }
  }

  cout << "Kruskal rodado com sucesso!" << endl;
  cout << "Soma total das arestas: " << sum << endl;
  cout << "Arestas da MST: " << endl;
  for(int i=0;i<sz(mst);i++) cout << mst[i].S.S << " - " << mst[i].S.F << " : " << mst[i].F << endl;
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

    if(cin.fail()){
      cout << "Tente novamente!" << endl;
      cin.clear();
      cin.ignore(INT_MAX, '\n');
      continue;
    }

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
      } else {
        cout << "Escolha uma opcao valida!" << endl;
      }
    } catch(exception& e){
      cout << "Por favor, tente novamente!" << endl;
    }

  } 


  return 0;
}
