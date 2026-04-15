/*
* [ 백준 11279 ] 최대 힙 ( S2 )
* - 훈련 날짜 : 2026-04-15 ( 수 )
* - 알고리즘 : 우선순위 큐 ( Priority Queue )
* - 핵심 개념 : std ::priority_queue의 기본 사용법
* - 최적화 : 연속된 메모리( vector ) 기반으로 CPU 캐시 친화적인 이진 트리 구현
* 1. push : O( log N ), 트리의 맨 밑에 삽입 후 위로 올림( Heapify Up )
* 2. pop : O( log N ), 루트를 제거하고 맨 마지막 노드를 올린 뒤 아래로 내림( Heapify Down )
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

	priority_queue<int> pq;

	while (n--)
	{
		int x;
		cin >> x;

		if (x == 0)
		{
			if (pq.empty())
				cout << 0 << '\n';
			else
			{
				cout << pq.top() << '\n';
				pq.pop();
			}
		}
		else
			pq.push(x);
	}
}