// 2026-04-10 (금)

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

struct Edge {
	int dist, arr;

	Edge(int ndist, int narr)
		:dist(ndist), arr(narr) {
	};

	bool operator>(const Edge& other) const {
		return dist > other.dist;
	}
};

void Dijkstra(int start);

const int mx_dist = 1e9;
const int mx_v = 801;
const long long INF = 1e9;
int n, e;
vector<Edge> adj[mx_v];
long long d[mx_v], p1[mx_v], p2[mx_v], p3[mx_v];

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	cin >> n >> e;

	for (int i = 0; i < e; i++)
	{
		int dep, arr, dist;
		cin >> dep >> arr >> dist;

		adj[dep].emplace_back(dist, arr);
		adj[arr].emplace_back(dist, dep);
	}

	int v1, v2;
	cin >> v1 >> v2;

	Dijkstra(1);
	copy(d, d + n + 1, p1);	// 배열 복사 함수
	Dijkstra(v1);
	copy(d, d + n + 1, p2);
	Dijkstra(n);
	copy(d, d + n + 1, p3);

	long long ans = min(p1[v1] + p2[v2] + p3[v2], p1[v2] + p2[v2] + p3[v1]);

	if (ans >= mx_dist) cout << -1 << '\n';
	else cout << ans << '\n';
}

void Dijkstra(int start)
{
	fill(d, d + n + 1, INF);
	priority_queue<Edge, vector<Edge>, greater<Edge>> pq;

	d[start] = 0;
	pq.emplace(0, start);

	while (!pq.empty())
	{
		auto cur = pq.top(); pq.pop();
		long long cd = cur.dist;
		int cnode = cur.arr;

		if (cd > d[cnode]) continue;

		for (const auto& next : adj[cnode])
		{
			long long nd = cd + next.dist;
			int nnode = next.arr;

			if (nd >= d[nnode]) continue;

			pq.emplace(nd, nnode);
			d[nnode] = nd;
		}
	}
}

// 2026-03-11 (수)

// #include <iostream>
// #include <vector>
// #include <queue>
// #include <algorithm>
// 
// using namespace std;
// 
// vector<long long> Dijkstra
// (int start, int n, const vector<vector<pair<int, int>>>& con_list);
// 
// const int mx_dist = 1e9;
// 
// int main()
// {
// 	ios::sync_with_stdio(false);
// 	cin.tie(nullptr);
// 
// 	int n, e;
// 	cin >> n >> e;
// 
// 	vector<vector<pair<int, int>>> con_list(n + 1);
// 
// 	for (int i = 0; i < e; i++)
// 	{
// 		int dep, arr, dist;
// 		cin >> dep >> arr >> dist;
// 
// 		con_list[dep].emplace_back(dist, arr);
// 		con_list[arr].emplace_back(dist, dep);
// 	}
// 
// 	int v1, v2;
// 	cin >> v1 >> v2;
// 
// 	vector<long long> p1, p2, p3;
// 
// 	p1 = Dijkstra(1, n, con_list);
// 	p2 = Dijkstra(v1, n, con_list);
// 	p3 = Dijkstra(n, n, con_list);
// 
// 	long long ans = min(p1[v1] + p2[v2] + p3[v2], p1[v2] + p2[v2] + p3[v1]);
// 	
// 	if (ans >= mx_dist) cout << -1 << '\n';
// 	else cout << ans << '\n';
// }
// 
// vector<long long> Dijkstra(int start, int n, const vector<vector<pair<int, int>>>& con_list)
// {
// 	vector<long long> d(n + 1, mx_dist);
// 	priority_queue
// 		<pair<long long, int>, vector<pair<long long, int>>,
// 		greater<pair<long long, int>>> pq;
// 
// 	d[start] = 0;
// 	pq.emplace(0, start);
// 
// 	while (!pq.empty())
// 	{
// 		auto cur = pq.top(); pq.pop();
// 		long long cd = cur.first;
// 		int cnode = cur.second;
// 
// 		if (cd > d[cnode]) continue;
// 
// 		for (auto next : con_list[cnode])
// 		{
// 			long long nd = cd + next.first;
// 			int nnode = next.second;
// 
// 			if (nd >= d[nnode]) continue;
// 
// 			pq.emplace(nd, nnode);
// 			d[nnode] = nd;
// 		}
// 	}
// 
// 	return d;
// }