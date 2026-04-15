/*
* [ 백준 1655 ] 가운데를 말해요 ( G2 )
* - 훈련 날짜 : 2026-04-15 ( 수 )
* - 알고리즘 : 우선순위 큐 ( Priority Queue ), 투 힙 ( Two-Heap )
* - 핵심 로직 : 최대 힙( 작은 절반 )과 최소 힙( 큰 절반 )을 사용하여 중앙값을 O( log N )으로 추적.
* 1. 크기 유지 : 최대 힙의 크기는 항상 최소 힙의 크기와 같거나 1 크도록 번갈아 삽입.
* 2. 밸런스 유지 : 최대 힙의 top > 최소 힙의 top 이면 두 값을 교환( Swap ).
* 3. 결과 : 항상 최대 힙의 top이 전체 데이터의 중앙값이 됨.
*/

#include <iostream>
#include <queue>

using namespace std;

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int n;
	cin >> n;

	priority_queue<int> max_pq;
	priority_queue<int, vector<int>, greater<int>> min_pq;

	for(int i = 0; i < n; i++)
	{
		int x;
		cin >> x;

		if (i % 2 == 0)
			max_pq.push(x);
		else
			min_pq.push(x);

		if ((!max_pq.empty() && !min_pq.empty()) && max_pq.top() > min_pq.top())
		{
			int temp = max_pq.top();
			max_pq.pop();
			max_pq.push(min_pq.top());
			min_pq.pop();
			min_pq.push(temp);
		}

		cout << max_pq.top() << '\n';
	}
}