#include "Vertix.h"
#include <iostream>
#include <queue>
using namespace std;

class Graph
{
	int noOfVertices;
	Vertix **adj;
	bool *visited = 0;
	int *indegree;
	char* topologicalSort;

public:
	Graph()
	{
		noOfVertices = 0;
		adj = nullptr;
		visited = nullptr;
		indegree = nullptr;
		topologicalSort = nullptr;
	}

	Graph(int n)
	{
		noOfVertices = n;
		adj = new Vertix *[noOfVertices];
		visited = new bool[noOfVertices]{0};
		indegree = new int[noOfVertices]{0};
		topologicalSort = new char[noOfVertices] {'\0'};
		for (int i = 0; i < noOfVertices; i++)
		{
			char e = i + 'A';
			adj[i] = new Vertix(e);
		}
	}

	void addEdge(char u, char v)
	{
		indegree[v - 'A'] += 1; // for Kahn's Algorithm
		Vertix *end = new Vertix(v);
		Vertix *temp = adj[u - 'A'];
		bool flag = 1;
		while (temp->next && flag)
		{
			if (temp->next->name == v)
				flag = 0;
			temp = temp->next;
		}
		if (flag)
			temp->next = end;
	}

	char* kahnsAlgorithm()
	{
		queue<char> que;
		for (int i = 0; i < noOfVertices; i++)
		{
			char e = i + 'A';
			if (!indegree[i])
			{
				que.push(e);
			}
		}
		int i = 0;
		while (!que.empty())
		{
			char e = que.front();
			topologicalSort[i++] = e;
			que.pop();
			Vertix *p = adj[e - 'A']->next;
			while (p)
			{
				indegree[p->name - 'A'] -= 1;
				if (indegree[p->name - 'A'] == 0)
					que.push(p->name);
				p = p->next;
			}
		}
		return topologicalSort;
	}
};


int main()
{
	int V, E;
	cout << "Enter the no of nodes your graph have: ";
	cin >> V;
	Graph graph(V);
	cout << "Enter the no of Edges your graph have: ";
	cin >> E;
	cout << "Enter the edges one by one: ";
	for (int i = 0; i < E; i++)
	{
		char u, v;
		cin >> u >> v;
		graph.addEdge(u, v);
	}
	char* tSort;
	tSort = graph.kahnsAlgorithm();
	for (int i = 0; i < V; i++)
	{
		cout << tSort[i] << " ";
	}
	cout << endl;
}