#include<iostream>
#include<vector>
#include<string>
#include<cstdlib>
#include<algorithm>
using std::vector, std::cin, std::cout, std::string, std::unique, std::sort;
struct Graph{
	vector<vector<int>> head;
	inline void setSize(int n){
		head.resize(n);
	}
	inline void addEdge(int u, int v){
		head.at(u).push_back(v);
	}
	inline void unique(int size){
		for(auto &e: head){
			vector<bool> fy(size, false);
			for(int i=0; i<e.size(); ++i){
				if(fy.at(e.at(i))){
					e.at(i)=e.at(e.size()-1);
					e.pop_back();
					--i;
					continue;
				}
				fy.at(e.at(i))=true;
			}
		}
	}
} forward_graph, reverse_graph, peer_graph, forward_edge, reverse_edge, peer_edge;
vector<string> map, answer, source;
inline int checkOrdinal(string target){
	int left=0, right=map.size()-1, middle;
	while(left<=right){
		middle=(left+right)>>1;
		if(target<map.at(middle)) right=middle-1;
		else if(map.at(middle)<target) left=middle+1;
		else return middle;
	}
	return -1;
}
inline void loadData(){
	freopen("./data.txt", "r", stdin);
	string orgin;
	while(cin>>orgin){
		source.push_back(orgin);
		for(int i=0, t; i<orgin.size(); ++i){
			t=orgin.find_first_of("-+", i);
			if(t==string::npos) t=orgin.size();
			map.push_back(string(orgin.begin()+i, orgin.begin()+t));
			i=t;
		}
	}
	sort(map.begin(), map.end());
	map.erase(unique(map.begin(), map.end()), map.end());
	forward_edge.setSize(map.size());
	reverse_edge.setSize(map.size());
	peer_edge.setSize(map.size());
	for(auto &e: source){
		vector<int> reactant, product;
		for(int i=0, t; i<e.find('-', 0); ++i){
			t=e.find_first_of("+-", i);
			reactant.push_back(checkOrdinal(e.substr(i, t-i)));
			i=t;
		}
		for(int i=e.find('-', 0)+1, t; i<e.size(); ++i){
			t=e.find('+', i);
			if(t==string::npos) t=e.size();
			product.push_back(checkOrdinal(e.substr(i, t-i)));
			i=t;
		}
		for(auto &i: reactant){
			for(auto &j: product){
				forward_edge.addEdge(i, j);
				reverse_edge.addEdge(j, i);
			}
			for(auto &j: reactant){
				if(i==j) continue;
				peer_edge.addEdge(i, j);
				peer_edge.addEdge(j, i);
			}
		}
		forward_edge.unique(map.size());
		reverse_edge.unique(map.size());
		peer_edge.unique(map.size());
	}
	fclose(stdin);
}
inline void inputGraph(){
	int n, u, v;
	string t;
	cout<<"the number of nodes:";
	cin>>n;
	forward_graph.setSize(n);
	reverse_graph.setSize(n);
	peer_graph.setSize(n);
	answer.resize(n, "");
	cout<<"the number of directed edges:";
	cin>>n;
	for(int i=1; i<=n; ++i){
		cout<<"new directed edge:";
		cin>>u>>v;
		forward_graph.addEdge(u-1, v-1);
		reverse_graph.addEdge(v-1, u-1);
	}
	cout<<"the number of undirected edges:";
	cin>>n;
	for(int i=1; i<=n; ++i){
		cout<<"new undirected edge:";
		cin>>u>>v;
		peer_graph.addEdge(u-1, v-1);
		peer_graph.addEdge(v-1, u-1);
	}
	cout<<"the number of conditions";
	cin>>n;
	for(int i=0; i<n; ++i){
		cout<<"new condition:";
		cin>>u>>t;
		answer.at(u)=t;
	}
}
inline void outputAnswer(){
	// system("chcp 65001 > nul");

}
void dfs(int post=0){

}
int main(){
	loadData();
	inputGraph();
	dfs();
	return 0;
}
