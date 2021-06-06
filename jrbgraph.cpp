#include "jrbgraph.hpp"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <queue>
#include <bits/stdc++.h>

using namespace std;

Graph createGraph()
{
	Graph newGraph = make_jrb();
	return newGraph;
}

void addEdge_int(Graph graph, int v1, int v2, int weight)
{
	// do thi vo huong nen can co (v1 v2) va (v2 v1)
	// them canh v1 v2
	// check xem da co dinh tren cay chua
	JRB bn = jrb_find_int(graph, v1);
	if(bn==NULL) // neu chua co thi them vao
	{		
		JRB tree = make_jrb(); 
		jrb_insert_int(tree, v2, new_jval_i(weight));
		jrb_insert_int(graph, v1, new_jval_v((void*)tree));
	}
	else // dinh v1 da co tren cay
	{
		//node = jrb_find_int(g, v1);
		// them canh v1 v2
		JRB tree = (JRB) jval_v(bn->val);
		jrb_insert_int(tree, v2, new_jval_i(weight));			
	}
	
	// them canh v2 v1
	bn = jrb_find_int(graph, v2);
	if(bn==NULL) // neu chua co thi them vao
	{
		JRB tree = make_jrb();
		jrb_insert_int(tree, v1, new_jval_i(weight));
		jrb_insert_int(graph, v2, new_jval_v(tree));
	}
	else  // da co dinh v2 thi chi them canh v2 v1
	{
		JRB tree = (JRB) jval_v(bn->val);
		jrb_insert_int(tree, v1, new_jval_i(weight));
	}
}

void addEdge_str(Graph graph, char* v1, char* v2, int weight)
{
	// do thi vo huong nen can co (v1 v2) va (v2 v1)
	// them canh v1 v2
	// check xem da co dinh tren cay chua
	JRB bn = jrb_find_str(graph, v1);
	if(bn==NULL) // neu chua co thi them vao
	{		
		JRB tree = make_jrb(); 
		jrb_insert_str(tree, strdup(v2), new_jval_i(weight));
		jrb_insert_str(graph, strdup(v1), new_jval_v(tree));
	}
	else // dinh v1 da co tren cay
	{
		//node = jrb_find_int(g, v1);
		// them canh v1 v2
		JRB tree = (JRB) jval_v(bn->val);
		jrb_insert_str(tree, strdup(v2), new_jval_i(weight));			
	}
	// them canh v2 v1
	// check xem da co dinh tren cay chua
	bn = jrb_find_str(graph, v2);
	if(bn==NULL) // neu chua co thi them vao
	{		
		JRB tree = make_jrb(); 
		jrb_insert_str(tree, strdup(v1), new_jval_i(weight));
		jrb_insert_str(graph, strdup(v2), new_jval_v(tree));
	}
	else // dinh v2 da co tren cay
	{
		// them canh v1 v2
		JRB tree = (JRB) jval_v(bn->val);
		jrb_insert_str(tree, strdup(v1), new_jval_i(weight));			
	}
}

int getAdjacentVertices_str (Graph graph, char* v, char output[50][50])
{
	JRB node = jrb_find_str(graph, v);
	JRB tree = (JRB) jval_v(node->val);
	int total = 0;   
	jrb_traverse(node, tree)
	{
		strcpy(output[total],jval_s(node->key));
		total++;
	}    
	return total;
}

int getAdjacentVertices_int (Graph graph, int v, int* output)
{
	JRB node = jrb_find_int(graph, v);
	JRB tree = (JRB) jval_v(node->val);
	int total = 0;   
	jrb_traverse(node, tree)
	{
		output[total++] = jval_i(node->key);
	}    
	return total;
}

list<string> getAllVertexes(Graph graph)
{
	list<string> vertexes;
	for(JRB ptr = jrb_first(graph); ptr != jrb_nil(graph); ptr = jrb_next(ptr))
	{
		vertexes.push_back(jval_s(ptr->key));
	}
	return vertexes;
}

void BFS(Graph graph, char* start)
{
	queue<string> Q;
	Q.push(start);
	char v[50];
	unordered_set <string> visitedList ;
	
	visitedList.insert(start);
	
	while(!Q.empty())
	{		
		strcpy(v, (Q.front()).c_str());
		printf("%5s, ", v);
		Q.pop();
		char output[50][50];
		int n = getAdjacentVertices_str (graph, v, output);
		for (int i=0; i<n; i++) {
			if(visitedList.find(output[i]) == visitedList.end())
			{
				Q.push(output[i]);
				visitedList.insert(output[i]);
			}	
		}
	}
}

void DFS(Graph graph, char* start)
{
	stack<string> S;
	S.push(start);
	char v[50];
	// gan nhan cac dinh la chua duoc tham
	unordered_set <string> notvisitedList ;
	for(JRB ptr = jrb_first(graph); ptr != jrb_nil(graph); ptr = jrb_next(ptr))
	{
		notvisitedList.insert(jval_s(ptr->key));
	}
	
	int timecount = 1;
	// dinh bat dau chuyen thanh dang tham
	notvisitedList.erase(start);
	printf("Bat dau tham %5s tai %d\n",start, timecount);
	
	while(!S.empty())
	{
		timecount++;
		// xet dinh v o dau stack		
		strcpy(v, (S.top()).c_str());
		//printf("%5s, ", v);
		char output[50][50];
		
		// kiem tra co dinh nao ke voi v ma chua tham
		int n = getAdjacentVertices_str (graph, v, output);
		int check = 0;
		for (int i=0; i<n; i++) {
			if(notvisitedList.find(output[i]) != notvisitedList.end())
			{
				S.push(output[i]);
				notvisitedList.erase(output[i]);
				printf("Bat dau tham %5s tai %d\n", output[i], timecount);
				check = 1;
				break;
			}	
		}
		if(check==0) // khong ton tai dinh nao ma chua tham
		{
			S.pop();
			printf("Ket thuc tham %5s tai %d\n", v, timecount);
		}
	}
}
void dropGraph(Graph graph)
{
	JRB node;
	jrb_traverse(node, graph)
	{
		jrb_free_tree((jrb_node*) jval_v(node->val) );
	}
    
}
int getEdgeWeight_str(Graph graph, char* v1, char* v2)
{
	JRB node = jrb_find_str(graph, v1);
	JRB tree = (JRB) jval_v(node->val);
	int total = 0;   
	jrb_traverse(node, tree)
	{
		if(strcmp(jval_s(node->key),v2)==0)
			return jval_i(node->val);
	}   
	return -1; 
}
void dijkstra(Graph graph, char* start, char* end)
{
	typedef pair<int, string> pi;
	
	priority_queue<pi, vector<pi>, greater<pi> > Q;
	Q.push(make_pair(0,start));
	char v[50];
	unordered_set <string> visitedList ;
	
	//map<string, string> preVertexList;
	//string preVertex = "NaN";
	
	while(!Q.empty())
	{		
		pair<int, string> top = Q.top();
		strcpy(v, top.second.c_str());
		
		Q.pop();
		if(visitedList.find(v) != visitedList.end()) continue;
		//preVertexList[v] = preVertex;
		//preVertex = v;
		visitedList.insert(v);
		int currentWeight = top.first;
		printf("%5s , total weight %d\n", v, currentWeight);
		if(strcmp(v,end)==0)
		{
			printf("Reach %s\n",end);
			printf("Total cost: %d\n", currentWeight);
			/*preVertex = preVertexList[end];
			while(preVertex.compare("NaN")!=0)
			{
				cout<<preVertex<<",";
				preVertex = preVertexList[preVertex];
			}*/
			return;
		}
		char output[50][50];
		int n = getAdjacentVertices_str (graph, v, output);
		for (int i=0; i<n; i++) {
			if(visitedList.find(output[i]) == visitedList.end())
			{
				int edgeweight = getEdgeWeight_str(graph,v,output[i]);
				Q.push(make_pair(currentWeight+edgeweight, output[i]));	
			}	
		}
	}
}

void PRIM(Graph graph, char* start)
{
	unordered_set <string> Connected, Unconnected;
	int totalweight = 0;
	// them cac dinh tren do thi vao tap chua co tren cay
	for(JRB ptr = jrb_first(graph); ptr != jrb_nil(graph); ptr = jrb_next(ptr))
	{
		Unconnected.insert(jval_s(ptr->key));
	}
	Connected.insert(start);
	Unconnected.erase(start);
	char u[50], c[50], minc[50], minu[50];
	int min;
	while(!Unconnected.empty())
	{
		min = 99999;
		// can tim canh co trogn so nho nhat ma 1 dinh thuoc C v� dinh thuoc U
		for (auto itr = Connected.begin(); itr != Connected.end(); ++itr) {
			strcpy(c,(*itr).c_str());
			char output[50][50];
			int n = getAdjacentVertices_str (graph, c, output);
			for (int i=0; i<n; i++) {
				if(Unconnected.find(output[i]) != Unconnected.end())
				{
					int edgeweight = getEdgeWeight_str(graph,c,output[i]);
					if(min>edgeweight)
					{
						min = edgeweight;
						strcpy(minc,c);
						strcpy(minu,output[i]);
					}
				}	
			}
		}	
		printf("them canh (%s,%s), weight %d\n",minu,minc,min);
		// bo sung them canh (minc, minu)
		totalweight = totalweight + min;
		Connected.insert(minu);
		Unconnected.erase(minu);	
	}
	printf("Total weight : %d\n",totalweight);	
}
