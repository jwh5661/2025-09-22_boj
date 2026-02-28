/*
BOJ 1966 — 프린터 큐 (Printer Queue)
Topic: Queue | Counting | Simulation
Folder: queue/simulation

⏱ 시간복잡도: O(N)         // curMax(=mx_priority)로 상수 시간 판정
💾 공간복잡도: O(N)         // 대기 큐 + 우선순위 카운트

📌 핵심 아이디어
- 큐에는 (원래 인덱스, 중요도)를 저장해 목표 문서를 식별.
- 입력 단계에서 mx_priority(현재 남은 최대 중요도)를 기록.
- 매 스텝 시작 시 num[mx_priority]==0이면 mx_priority를 내려가며 갱신.
- front의 중요도가 mx_priority면 인쇄 확정:
  - 목표 문서면 현재 cnt 출력 후 종료,
  - 아니면 num[prio] 감소, cnt++.
- 중요도가 낮으면 뒤로 보냄(회전). 회전 시 cnt 변화 없음.

⚠️ 주의할 점
- cnt는 **인쇄될 때만** 증가(회전 때 증가 X).
- 카운트 감소는 **인쇄 확정 시점**에만.
- mx_priority 갱신은 “현재 최대 중요도의 잔여 수가 0일 때만” 감소.
- 주석으로 `cnt`의 의미(“현재까지 인쇄된 문서 수”)를 명시하면 가독성↑
- `printer.emplace(i, p);`/중괄호 초기화 `{i, p}`로 간결화 가능
- `vector<int> priority(10);`는 `priority.assign(10, 0);`처럼 “매 케이스 초기화 의도”를 드러내도 좋음(선호 차)
- `auto cur = printer.front(); printer.pop();` → 한 줄 주석으로 “현재 문서 꺼냄” 등 의미 표기(로직 동일, 가독성 개선)

✔️ 코너 케이스
- 모두 같은 중요도 → FIFO로 진행.
- 목표 문서가 처음부터 최고 중요도 → cnt=1 즉시 출력.
- 최대 중요도 소진 시 mx_priority가 순차적으로 내려가 자연스럽게 처리.
*/

// 2026-02-28 D+3 REVIEW 간단 복습 완료

// 2026-02-24 Reboot 간단 복습
// 문서를 입력받을 때 해당 중요도의 문서가 몇 개 있는지를 저장
// 큐에 넣을 때 해당 문서가 원래 몇 번째였는지 저장하기 위해 pair로 저장
// 큐의 맨 앞보다 중요도가 높은 문서가 남아있으면 큐의 맨 앞을 맨 뒤에 push하고 맨 앞을 pop
// 문서를 출력할 때 마다 해당 중요도 문서 갯수 감소
// 다음 출력이 시작되기 전에 현재 남아있는 가장 큰 중요도 산출
// 내가 원했던 문서가 나오면 큐를 즉시 종료하고 cnt 출력 (cnt는 1부터 시작)

// 2025-10-15 D+14 REIVEW

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int t;
	cin >> t;

	while (t--)
	{
		int n, m, mx_prio = -1, cnt = 0;
		cin >> n >> m;

		vector<int> num_prio(10, 0);
		queue<pair<int, int>> q;
		for (int i = 0; i < n; i++)
		{
			int prio;
			cin >> prio;
			q.emplace(i, prio);
			num_prio[prio]++;
			if (mx_prio < prio) mx_prio = prio;
		}

		while (!q.empty())
		{
			while (num_prio[mx_prio] == 0) mx_prio--;

			auto cur = q.front(); q.pop();

			if (cur.second == mx_prio)
			{
				cnt++;
				if (cur.first == m)
				{
					cout << cnt << '\n';
					break;
				}
				else
					num_prio[cur.second]--;
			}
			else
				q.push(cur);
		}
	}
}

// 2025-09-29 D+3 REIVEW

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
// 	int t;
// 	cin >> t;
// 
// 	while (t--)
// 	{
// 		int n, m, mx_prio = -1, cnt = 0;
// 		cin >> n >> m;
// 
// 		vector<int> prio(10, 0);
// 		queue<pair<int, int>> q;
// 		for (int i = 0; i < n; i++)
// 		{
// 			int p;
// 			cin >> p;
// 			prio[p]++;
// 			q.push(make_pair(i, p));
// 			if (mx_prio < p) mx_prio = p;
// 		}
// 
// 		while (!q.empty())
// 		{
// 			auto cur = q.front(); q.pop();
// 			while (prio[mx_prio] == 0) mx_prio--;
// 			if (cur.second == mx_prio)
// 			{
// 				cnt++;
// 				if (cur.first == m)
// 				{
// 					cout << cnt << "\n";
// 					break;
// 				}
// 				else
// 					prio[mx_prio]--;
// 			}
// 			else
// 				q.push(cur);
// 		}
// 	}
// }

// 2025-09-26 D+0 REIVEW

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
// 	int t;
// 	cin >> t;
// 
// 	while (t--)
// 	{
// 		int n, m, cnt = 0, mx_priority = 0;
// 		cin >> n >> m;
// 
// 		queue<pair<int, int>> printer;
// 		vector<int> priority(10);
// 		for (int i = 0; i < n; i++)
// 		{
// 			int p;
// 			cin >> p;
// 
// 			printer.push(make_pair(i, p));
// 			priority[p]++;
// 			if (mx_priority < p) mx_priority = p;
// 		}
// 
// 		while (!printer.empty())
// 		{
// 			auto cur = printer.front();
// 			printer.pop();
// 			while (priority[mx_priority] == 0) mx_priority--;
// 			if (mx_priority == cur.second)
// 			{
// 				cnt++;
// 				if (cur.first == m)
// 				{
// 					cout << cnt << "\n";
// 					break;
// 				}
// 				else
// 					priority[cur.second]--;
// 			}
// 			else
// 				printer.push(cur);
// 		}
// 	}
// }

// 2025-09-26 ORIGINAL

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
// 	int t;
// 	cin >> t;
// 
// 	while (t--)
// 	{
// 		int n, m, cnt = 1, mx_priority = -1;
// 		cin >> n >> m;
// 
// 		vector<int> num(10, 0);
// 		queue<pair<int, int>> q;
// 
// 		for (int i = 0; i < n; i++)
// 		{
// 			int temp;
// 			cin >> temp;
// 
// 			num[temp]++;
// 			q.push(make_pair(i, temp));
// 			if (mx_priority < temp) mx_priority = temp;
// 		}
// 
// 		while (!q.empty())
// 		{
// 			auto cur = q.front(); q.pop();
// 			while (num[mx_priority] == 0) mx_priority--;
// 
// 			if (cur.second == mx_priority)
// 			{
// 				if (cur.first == m)
// 				{
// 					cout << cnt << "\n";
// 					break;
// 				}
// 				else
// 				{
// 					num[cur.second]--;
// 					cnt++;
// 				}
// 			}
// 			else
// 				q.push(cur);
// 		}
// 	}
// }