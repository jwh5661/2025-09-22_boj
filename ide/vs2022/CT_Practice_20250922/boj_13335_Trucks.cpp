/*
BOJ 13335 — 트럭 (Trucks)
Topic: Queue | Simulation | Sliding Window
Folder: queue/simulation

⏱ 시간복잡도: O(N + T)   // N: 트럭 수, T: 총 시간(매 초 1회 갱신)
💾 공간복잡도: O(w)       // 다리 길이만큼의 큐

📌 핵심 아이디어
- 다리를 길이 w의 **고정 길이 큐**로 시뮬레이션: 매 초마다 한 칸 전진.
- 큐가 꽉 찼으면(front가 다리에 올라온 지 w초 경과) 맨 앞을 내리고, 다리 현재 하중을 갱신.
- 대기열 선두 트럭을 올릴 수 있으면 push, 아니면 **0을 push**해 시간만 흐르게 한다.
- 모든 트럭이 다리에 올라간 시점에서 ㅊ총 시간 t에 **w를 추가**하면 마지막 트럭이 빠져나가는 시간을 얻는다.

⚠️ 주의할 점
- 새 트럭을 올리기 전, 반드시 **큐 길이 w 체크 -> 하중 갱신**을 먼저 처리.
- 올릴 수 없을 때 0을 push하지 않으면 시간이 정지하여 오답.
- 다 올린 뒤 남은 주행 시간 보정: `t += w`.

✔️ 지문 힌트
- "길이 w인 슬라이딩 윈도우"로 보면 매 초 1칸 전진하며 하중을 유지·갱신하는 문제.
- waiting 큐와 bridge 큐 두 개로 모델링하면 구현이 가장 단순하다.

*/

// 2025-10-13 D+3 REVIEW

#include <iostream>
#include <queue>

using namespace std;

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int n, w, L;
	cin >> n >> w >> L;

	int cur_weight = 0, time = 0;
	queue<int> waiting;
	queue<int> bridge;

	for (int i = 0; i < n; i++)
	{
		int weight;
		cin >> weight;
		waiting.push(weight);
	}

	while (!waiting.empty())
	{
		if (bridge.size() == w)
		{
			cur_weight -= bridge.front();
			bridge.pop();
		}

		int cur_truck = waiting.front();

		if (bridge.size() < w && cur_weight + cur_truck <= L)
		{
			waiting.pop();
			cur_weight += cur_truck;
			bridge.push(cur_truck);
		}
		else
			bridge.push(0);
		time++;
	}

	cout << time + w << '\n';
}

// 2025-10-06 ORIGINAL

// #include <iostream>
// #include <queue>
// 
// using namespace std;
// 
// int main()
// {
// 	ios::sync_with_stdio(false);
// 	cin.tie(nullptr);
// 
// 	int n, w, l, cur_weight = 0, t = 0;
// 	cin >> n >> w >> l;
// 
// 	queue<int> q, bridge_q;
// 	for (int i = 0; i < n; i++)
// 	{
// 		int tmp;
// 		cin >> tmp;
// 		q.push(tmp);
// 	}
// 		
// 
// 	while (!q.empty())
// 	{
// 		int cur_truck = q.front();
// 		if (bridge_q.size() >= w)
// 		{
// 			cur_weight -= bridge_q.front();
// 			bridge_q.pop();
// 		}
// 
// 		if (l >= cur_weight + cur_truck)
// 		{
// 			bridge_q.push(cur_truck);
// 			cur_weight += cur_truck;
// 			q.pop();
// 		}
// 		else
// 			bridge_q.push(0);
// 
// 		t++;
// 	}
// 	t += w;
// 
// 	cout << t << '\n';
// }