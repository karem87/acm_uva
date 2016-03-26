/* Problem: 10067 	Playing with Wheels 	Accepted 	C++11
 * UVa Online Judge
 * Marcelo Adriano Amancio - marcelousp@gmail.com
 * compile: g++ -o t uva10067.cpp --std=c++11
 * run: ./t <input.txt
 */
#include <cstdio>
#include <iostream>
#include <set>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

struct quad{
  int v[4];
  
  void move(int op, int i){v[i]=(10+v[i] + op)%10;}
  int toi()const{ return 1000*v[0]+100*v[1]+10*v[2]+v[3];}
  bool operator<(const quad& q) const{ return toi()<q.toi();};
  void read_from_input(){cin>>v[0]>>v[1]>>v[2]>>v[3];}
  quad copy(){ quad q; for(int i=0;i<4;i++) q.v[i] = v[i]; return q;}
  vector<quad> make_nb(){ vector<quad> n(8); 
    for(int i=0;i<8;i++){ n[i]=copy(); n[i].move(2*(i%2)-1,i/2);} return n;}
};

quad s,r;
set <int>se;
vector<bool> discovered;
vector<int> parent; 
vector<int> nallow;

void init(int n){
  discovered = vector<bool>(n, false);
  parent = vector<int>(n,-1); 
  nallow.clear();
}

bool valid_vertice(int v){
  return find(nallow.begin(), nallow.end(), v) == nallow.end();
}

void bfs(quad start){
  queue <quad>q; q.push(start);
  discovered[start.toi()];
  while(!q.empty()){
    quad v = q.front(); q.pop();
    for(auto e:v.make_nb()){
      int ie = e.toi();
      if(valid_vertice(ie)){
        if(!discovered[ie]){
          q.push(e);
          discovered[ie] = true;
          parent[ie] = v.toi();
        }
      }
    }
  }
}

int process_bfs(int s, int r){
  if(parent[r]==-1) return -1;
  if(r==s) return 0;
  int cc = 0;
  while(r!=s){
    r=parent[r];
    cc++;
  }
  return cc;
}

int main(){
  int n;
  cin>>n;

  while(n--){
    init(10005);

    s.read_from_input();
    r.read_from_input();
    int e;
    cin>>e;
    while(e--){
      quad t;
      t.read_from_input();
      nallow.push_back(t.toi());
    }
    bfs(s);
    cout<< process_bfs(s.toi(), r.toi());
    cout<<endl;
  }

  return 0;
}

