/*
BOJ 1021 — 회전하는 큐 (Rotating Queue)
Topic: Deque | Simulation | Rotation
Folder: deque/rotation

⏱ 시간복잡도: O(N·M)   // 각 타깃마다 선형 탐색 + 회전
💾 공간복잡도: O(N)

📌 핵심 아이디어
- 현재 덱에서 타깃의 인덱스 idx를 찾고, 왼쪽 거리 idx vs 오른쪽 거리 size-idx를 비교해 더 가까운 방향으로만 회전.
- 덱의 front가 타깃이 되면 pop_front, 회전 횟수를 누적해 정답으로 출력.

⚠️ 주의할 점
- idx를 찾을 때 매칭하면 즉시 break로 탐색 종료(불필요 반복 방지).
- 왼/오 거리가 같을 때의 정책을 고정(예: 왼쪽 우선: idx <= size-idx).
- 회전은 "한 방향"으로만 반복하고, front가 타깃이 되면 즉시 제거.

✔️ 지문 힌트
- 원형 구조를 선형으로 펼쳤다고 생각하면, 타깃까지의 왼쪽/오른쪽 이동 칸 수 비교로 환원된다.
- 덱 연산: 왼쪽 회전 = pop_front->push_back, 오른쪽 회전 = pop_back->push_front.

*/

// 2025-11-06 D+14 REVIEW

#include <iostream>
#include <deque>
#include <algorithm>

using namespace std;

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int n, m, cnt = 0;
	cin >> n >> m;

	deque<int> dq;
	for (int i = 1; i <= n; i++)
		dq.push_back(i);

	while (m--)
	{
		int target, idx = -1, dq_size = (int)dq.size();
		cin >> target;

		if (target == dq.front())
		{
			dq.pop_front();
			continue;
		}

		int left = find(dq.begin(), dq.end(), target) - dq.begin();
		int right = dq_size - left;

		while (dq.front() != target)
		{
			if (left <= right)
			{
				dq.push_back(dq.front());
				dq.pop_front();
			}
			else
			{
				dq.push_front(dq.back());
				dq.pop_back();
			}
			cnt++;
		}
		dq.pop_front();
	}

	cout << cnt << '\n';
}

// 2025-10-13 D+3 REVIEW

// #include <iostream>
// #include <deque>
// #include <algorithm>
// 
// using namespace std;
// 
// int main()
// {
// 	ios::sync_with_stdio(false);
// 	cin.tie(nullptr);
// 
// 	int n, m, cnt = 0;
// 	cin >> n >> m;
// 
// 	deque<int> dq;
// 	for (int i = 1; i <= n; i++)
// 		dq.push_back(i);
// 
// 	while (m--)
// 	{
// 		int target;
// 		cin >> target;
// 
// 		if (target == dq.front())
// 		{
// 			dq.pop_front();
// 			continue;
// 		}
// 
// 		int left = find(dq.begin(), dq.end(), target) - dq.begin();
// 		int right = static_cast<int>(dq.size()) - left;
// 
// 		while (dq.front() != target)
// 		{
// 			if (left <= right)
// 			{
// 				dq.push_back(dq.front());
// 				dq.pop_front();
// 			}
// 			else
// 			{
// 				dq.push_front(dq.back());
// 				dq.pop_back();
// 			}
// 			cnt++;
// 		}
// 		dq.pop_front();
// 	}
// 
// 	cout << cnt << '\n';
// }

// 2025-10-06 ORIGINAL

// #include <iostream>
// #include <deque>
// 
// using namespace std;
// 
// int main()
// {
// 	ios::sync_with_stdio(false);
// 	cin.tie(nullptr);
// 
// 	int n, m, cnt = 0;
// 	cin >> n >> m;
// 
// 	deque<int> dq;
// 	for (int i = 1; i <= n; i++)
// 		dq.push_back(i);
// 
// 	while (m--)
// 	{
// 		int target, idx = 0;
// 		cin >> target;
// 
// 		for (int i = 0; i < (int)dq.size(); i++)
// 		{
// 			if (dq[i] == target)
// 				idx = i;
// 		}
// 
// 		while (dq.front() != target)
// 		{
// 			if (idx < ((int)dq.size() - idx))
// 			{
// 				dq.push_back(dq.front());
// 				dq.pop_front();
// 			}
// 			else
// 			{
// 				dq.push_front(dq.back());
// 				dq.pop_back();
// 			}
// 			cnt++;
// 		}
// 
// 		if (dq.front() == target)
// 			dq.pop_front();
// 	}
// 
// 	cout << cnt << '\n';
// }