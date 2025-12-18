/*
BOJ 1697 — 숨바꼭질 (Hide and Seek)
Topic: BFS | Shortest Path | Graph
Folder: graph/bfs

⏱ 시간복잡도: O(MAX)         // MAX는 상태공간 크기(일반적으로 100001)
💾 공간복잡도: O(MAX)

📌 핵심 아이디어
- 위치를 정점(0..MAX)으로 보고, 간선은 {x-1, x+1, 2*x}로 정의한 뒤 BFS로 최단 시간을 구한다.
- 시작점 dist=0으로 큐에 넣고, 범위 내 미방문 정점만 dist=부모+1로 확장한다.
- 목표 k를 꺼내는 순간의 dist가 정답이다.

⚠️ 주의할 점
- 경계 체크 필수: nx < 0 || nx > MAX는 스킵.
- 방분 배열을 -1로 초기화하여 미방문/거리 겸용으로 사용.
- 시작==목표면 0을 즉시 출력하면 된다.

✔️ 지문 힌트
- BFS는 무가중 그래프 최단거리 보장. 이웃 생생만 정확히 하면 된다.

💡 추가 메모 (상태공간 상한)
- MAX는 100000으로 충분하다(목표 k ∈ [0, 100000]). 범위를 넘었다가 돌아오는 경로는 항상 범위 안의 다른 경로로 대체 가능하므로 최단거리에 이득이 없다.

*/

/*
* 2025-12-18 복귀 간단 복습
* 상태 : 현재 위치 x
* 간선 : x - 1, x + 1, 2 * x. 
  여기서 2 * x가 100001을 넘어가면 x - 1로 동생을 찾는 시간보다 x - 1을 하고 2 * x 하는 것이 항상 더 빠르거나 같기 때문에 MAX를 100001로 둘 수 있느냐가 가장 큰 생각해볼 점.
* 방문 : 가장 빠른 시간을 찾아야 함, 모든 간선의 비용이 1임 -> BFS 방문. 방문은 큐에 넣을 때 체크.
* 종료 조건 : x가 동생이 있는 위치이거나 queue가 empty가 되면 종료
* 복잡도 : BFS -> O(N)

*/ 


// 2025-10-15 D+3 REVIEW

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int n, k;
	cin >> n >> k;

	vector<int> location(100001, -1);
	queue<int> q;

	q.push(n);
	location[n] = 0;

	while (q.front() != k)
	{
		int cur = q.front(); q.pop();

		for (int i : {cur - 1, cur + 1, 2 * cur})
		{
			if (0 > i || i > 100000) continue;
			if (location[i] != -1) continue;
			q.push(i);
			location[i] = location[cur] + 1;
		}
	}

	cout << location[k] << '\n';
}

// 2025-10-11 ORIGINAL

// #include <iostream>
// #include <vector>
// #include <queue>
// 
// using namespace std;
// 
// int main()
// {
// 	ios::sync_with_stdio(false);
// 	cin.tie(nullptr);
// 
// 	int n, k;
// 	cin >> n >> k;
// 
// 	queue<int> q;
// 	vector<int> visited(100001, -1);
// 
// 	q.push(n);
// 	visited[n] = 0;
// 
// 	while (!q.empty())
// 	{
// 		int cur = q.front(); 
// 		if (cur == k)
// 		{
// 			cout << visited[k] << '\n';
// 			break;
// 		}
// 		q.pop();
// 
// 		for (int dx : {cur + 1, cur - 1, cur * 2})
// 		{
// 			if (0 > dx || dx > 100000) continue;
// 			if (visited[dx] != -1) continue;
// 			q.push(dx);
// 			visited[dx] = visited[cur] + 1;
// 		}
// 	}
// }