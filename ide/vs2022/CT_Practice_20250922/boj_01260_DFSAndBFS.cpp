/*
* [ 백준 1260 ] DFS와 BFS ( S2 )
* - 훈련 날짜 : 2026-04-16 ( 목 )
* - 목적 : 인접 리스트를 활용한 DFS( 재귀/스택 )와 BFS( 큐 )의 기초 구현
* - 핵심 스킬 :
* 1. 작은 정점 번호부터 방문하기 위한 인접 리스트 정렬 ( sort )
* 2. 탐색 간 visited 배열 초기화 ( std::fill )
*/

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

void DFS(int node);
void BFS(int node);

vector<int> Adj[1001];
bool visited[1001];
int n, m;

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int v;
	cin >> n >> m >> v;

	for (int i = 0; i < m; i++)
	{
		int dep, arr;
		cin >> dep >> arr;

		Adj[dep].push_back(arr);
		Adj[arr].push_back(dep);
	}

	for (int i = 1; i <= n; i++)
	{
		sort(Adj[i].begin(), Adj[i].end());
	}

	DFS(v);
	cout << '\n';

	fill(visited, visited + n + 1, false);

	BFS(v);
	cout << '\n';
}

void DFS(int node)
{
	visited[node] = true;
	cout << node << ' ';

	for (int next : Adj[node])
	{
		if (visited[next]) continue;
		DFS(next);
	}
}

void BFS(int node)
{
	queue<int> q;
	q.push(node);
	visited[node] = true;

	while (!q.empty())
	{
		int cur = q.front(); q.pop();
		cout << cur << ' ';

		for (int next : Adj[cur])
		{
			if (visited[next]) continue;
			visited[next] = true;
			q.push(next);
		}
	}
}