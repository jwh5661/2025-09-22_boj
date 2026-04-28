## 📅 2026-04-21
**PRG 42576 - 완주하지 못한 선수**
**PRG 01845 - 폰켓몬**
**PRG 42578 - 의상**

### PRG 42576 - 완주하지 못한 선수
- **Topic:** Hash Map ( std::unordered_map )
- **Folder:** `Week_03/01_Hash/`
- **Time Complexity:** O(N)
- **Space Complexity:** O(N)

- **Key Idea:**
두 배열의 차집합을 구하기 위해, 해시 맵에 이름을 키( Key )로, 등장 횟수를 값( Value )으로 저장하여 카운팅

- **Caution:**
std::string을 루프에서 값 복사( Pass by Value )로 넘기면 심각한 메모리 오버헤드 발생.

- **Improvement:**
map.find( ) 대신 map[key]++의 기본 생성( Default Initialization ) 특성을 활용하여 중복 탐색 비용 제거.

- **Problem Hint:**
"단 한 명의 선수를 제외하고는 모든 선수가 마라톤을 완주" -> 1:1 매칭 후 남는 단일 데이터 색출.

- **Portfolio Selling Point:**
C++에서 무거운 객체( String )을 다룰 때 const string&를 사용하여 불필요한 깊은 복사( Deep Copy )를 원천 차단하는 메모리 방어적 코딩 습관 증명.

---

### PRG 01845 - 폰켓몬
- **Topic:** Hash Set ( std::unordered_set )
- **Folder:** `Week_03/01_Hash/`
- **Time Complexity:** O(N)
- **Space Complexity:** O(N)

- **Key Idea:**
선택 가능한 최대 마리 수( N/2 )와 해시 셋을 통해 중복을 제거한 '고유한 종류 수'를 구한 뒤, 둘 중 더 작은 값을 도출.

- **Caution:**
STL 컨테이너의 size( )는 size_t ( unsigned )를 반환하므로, std::min 함수 사용 시 int와의 타입 충돌로 인한 컴파일 경고/에러 주의.

- **Improvement:**
별도의 if-else 분기 없이 min 함수 한 줄로 논리 구조 압축

- **Problem Hint:**
"가장 많은 종류의 폰켓몬을 선택" -> 값 자체보다 고유한 '종류'의 개수( 중복 제거 )가 핵심.

- **Portfolio Selling Point:**
데이터의 존재 유무와 고유성만 필요할 때 map 대신 set을 채택하여 메모리 풋프린트를 최소화하고, ( int ) 명시적 캐스팅을 통해 실무 환경에서의 엄격한 타입 불일치 에러를 방어하는 디테일.

---

### PRG 42578 - 의상
- **Topic:** Hash Map | Combinations
- **Folder:** `Week_03/01_Hash/`
- **Time Complexity:** O(N)
- **Space Complexity:** O(K) ( K = 옷의 카테고리 종류 수 )

- **Key Idea:**
각 카테고리별 아이템 개수에 '착용하지 않음( +1 )' 상태를 더해 모두 곱한 뒤, 전체를 미착용한 경우( -1 )를 제외하는 조합 연산.

- **Caution:**
누적 곱셈 시 경우의 수가 기하급수적으로 커져 int 범위를 초과할 수 있는 오버플로우 위험.

- **Improvement:**
long long 타입으로 선언하여 큰 수 연산 대비.

- **Problem Hint:**
"서로 다른 옷의 조합의 수", "하루에 최소 한 개의 의상은 입습니다" -> 카테고리별 독립 시행 및 공집함 제외.

- **Portfolio Selling Point:**
C++17 구조적 바인딩( [ key, val ] )을 적극 도입하여 가독성을 높이고, 게임 내 캐릭터 코스튬/장비 슬롯 시스템 등에서 발생할 수 있는 복잡한 경우으 ㅣ수를 최적화된 수학적 모델로 구현할 수 있는 아키텍처적 사고 증명.

---

## 📅 2026-04-22
**PRG 42586 - 기능개발**
**PRG 42587 - 프로세스**

### PRG 42586 - 기능개발
- **Topic:** Queue ( FiFO 스케줄링 )
- **Folder:** `Week_03/02_Stack_Queue/`
- **Time Complexity:** O(N)
- **Space Complexity:** O(N)

- **Key Idea:**
뒤에 있는 기능이 먼저 개발되어도 앞의 기능이 배포될 때 함께 배포되어야 하므로, FIFO 자료구조인 Queue를 사용하여 기준일( day )보다 작거나 같은 후속 작업들을 일괄적으로 pop 하며 카운팅.

- **Caution:**
남은 일수 계산 시 몫과 나머지를 정확히 처리하지 않으면 배포일이 하루씩 밀리거나 당겨지는 논리적 오류 발생.

- **Improvement:**
<cmath>의 ceil( ) 함수나 double 형병환을 피하고 순수 정수 연산으로 올림을 구현하여 퍼포먼스 향상.

- **Problem Hint:**
"앞에 있는 기능이 먼저 배포되어야 합니다." -> Fisrt-In-First-Out ( FIFO ) 구조 도출.

- **Portfolio Selling Point:**
부동소수점 연산 오버헤드와 정밀도 오류를 피하기 위해, 모듈로( % ) 연산자를 활용한 순수 정수 수학( Integer Math ) 기반의 최적화된 올림 로직을 구현하여 엔진 프로그래머로서의 성능 튜닝 감각을 증명.

---

### PRG 42587 - 프로세스
- **Topic:** Queue | Priority Queue ( Max Heap )
- **Folder:** `Week_03/02_Stack_Queue/`
- **Time Complexity:** O(N log N) ( Priority Queue 삽입/삭제 기준 )
- **Space Complexity:** O(N) ( 두 개의 큐 메모리 할당 )

- **Key Idea:**
`queue<pair<우선순위, 인덱스>>`로 프로세스의 본래 위치( location )를 추적하고, priority_queue로 현재 큐에 남은 최댓값을 즉시 파악하여 프로세스 순환( Circular ) 구조를 제어.

- **Caution:**
큐에 우선순위 값만 넣으면, 나중에 꺼냈을 때 해당 프로세스가 내가 찾던 타겟( location )인지 식별할 수 없으므로 반드시 고유 인덱스를 구조체나 pair로 묶어서 관리해야 함.

- **Improvement:**
큐 요소 삽입 시 `push({a, b})` 방식 대신 가변 인자 템플릿인 `emplace(a, b)`를 사용하여 불필요한 복사 생성자 호출 방지.

- **Problem Hint:** 지문 키워드 → 접근법
"더 높은 우선순위가 있다며 다시 큐의 뒤에 넣습니다" -> 데이터를 뽑아서 뒤로 다시 넣는 순환 큐( Circular Queue ) 및 최댓값 지속 추적( Max Heap ) 도출.

- **Portfolio Selling Point:**
게임 엔진의 이벤트 디스패처( Event Dispatcher )가 긴급한 작업( Network, Render )과 일반 작업( UI, Sound )을 스케줄링하는 로직과 동일한 아키텍처. 두 개의 독립적인 STL 컨테이너( queue, priority_queue )를 결합하여 선형 탐색의 비효율성을 극복하는 시스템 설계 능력을 입증함.

---

## 📅 2026-04-23
**PRG 01844 - 게임 맵  최단거리**
**PRG 43162 - 네트워크**

### PRG 01844 - 게임 맵 최단거리
- **Topic:** Graph | BFS 
- **Folder:** `Week_03/03_Graph/`
- **Time Complexity:** O(N * M) *( 맵의 모든 칸을 최대 1번씩 방문 )*
- **Space Complexity:** O(N * M) *(visited 배열 및 Queue 메모리 )*

- **Key Idea:**
시작점에서부터의 최단 거리를 보장하기 위해 너비 우선 탐색( BFS )를 사용.
큐에 좌표를 넣으며 거리를 1씩 누적.

- **Caution:**
목적지에 도달하지 못하는 막힌 지형의 경우 예외 처리( -1 반환 )가 필요함.

- **Improvement:**
방문 여부 배열(`visited`)과 거리 배열(`dist`)을 분리하지 않고, `memset`을 통해 `-1`로 초기화하여 두 가지 목적을 하나의 배열로 통합 처리.

- **Problem Hint:** 
"상대 팀 진영에 최대한 빨리 도착하는 것이 유리", "최단거리" -> 깊게 파고드는 DFS가 아닌, 동심원처럼 퍼져나가며 무조건 최단 거리를 보장하는 BFS 알고리즘 도출.

- **Portfolio Selling Point:**
C++ 정적 분석기(MSVC Code Analysis )가 탐지할 수 있는 빈 배열 메모리 참조 에러(C6385, OOB )의 원리를 이해하고, 방어적 프로그래밍( Guard Clause )을 통해 안전하게 메모리를 다루는 실무적 시각을 입증.

---

### PRG 43162 - 네트워크
- **Topic:** Graph | Iterative DFS 
- **Folder:** `Week_03/03_Graph/`
- **Time Complexity:** O(N^2) ( 인접 행렬( Adjacency Matrix )의 모든 연결 상태를 확인 )
- **Space Complexity:** O(N) ( visited 배열 및 DFS 탐색용 std::stack 메모리 )

- **Key Idea:**
전체 노드( 컴퓨터 )를 순회하며 아직 방문하지 않은 노드가 발견될 때마다 새로운 네트워크 그룹으로 간주( 정답 + 1)하고, 해당 노드와 연결된 모든 노드를 스택 기반의 깊이 우선 탐색( DFS )으로 끝까지 파고들며 방문 처리함. ( 연결 요소 개수 찾기 )

- **Caution:**
스택을 활용한 반복문 DFS 구현 시, 바깥쪽 루프의 인덱스( i )와 큐/스택에서 꺼낸 현재 노드의 인덱스( cur )를 혼동하여 참조하면 무한 루프나 잘못된 탐색이 발생할 수 있으므로 변수 스코프 관리에 극도로 주의해야 함.

- **Improvement:**
구현이 쉬운 재귀( Recursive ) DFS를 사용하지 않고, 명시적인 std::stack 자료구조를 활용하여 OS 레벨의 스택 메모리 한계를 우회하는 안전한 루프 기반 로직으로 설계함.

- **Problem Hint:**
"A와 B가 연결되어 있고, B와 C가 연결되어 있으면 A와 C도 연결된 것.", " 네트워크 의 개수" -> 전형적인 '연결 요소( Connected Component )'의 개수를 구하는 그래프 탐색( DFS/BFS ) 문제임을 도출.

- **Portfolio Selling Point:**
대규모 데이터나 깊은 트리/그래프 구조를 다룰 때 발생할 수 있는 치명적인 콜 스택 오버플로우( Call Stack Overflow ) 크래시의 위험성을 인지하고, 이를 방지하기 위해 힙 메모리를 사용하는 std::stack 기반의 Iterative DFS를 직접 설계 및 디버깅해 낸 엔진 프로그래머로서의 메모리 안전성( Memory Safety ) 감각을 입증.

---

## 📅 2026-04-24
**PRG 43105 - 정수 삼각형**
**PRG 42895 - N으로 표현**

### PRG 43105 - 정수 삼각형
- **Topic:** DP | Bottom-Up | 1D Memoization
- **Folder:** `Week_03/04_DP/`
- **Time Complexity:** O(N^2) ( 삼각형의 모든 노드를 한 번씩 방문 )
- **Space Complexity:** O( 1차원 DP 배열 메모리 )

- **Key Idea:**
위에서 아래로 내려가는 대신, 바닥에서부터 꼭대기로 올라가는 바텀업( Bottom-Up ) 방식을 채택.
현재 층의 노드가 가질 수 있는 최댓값은 바로 아래층의 연결된 두 자식 노드 중 더 큰 값을 현재 노드의 값에 더하는 방식으로 누적함.

- **Caution:**
위에서 아래로( Top-Down ) 탐색할 경우, 삼각형의 가장 왼쪽 변과 오른쪽 변에서 배열 인덱스를 벗어나는 오류( Out of Bounds )가 발생하므로 이를 위한 예외 처리 분기문이 추가로 필요해짐.

- **Improvement:**
N 크기의 2차원 DP 배열( O( N^2 ))을 생성하지 않고, 크기 N의 차원 DP 배열( O( N )) 하나만 생성하여 이전 층의 결과를 덮어쓰는( In-place ) 방식으로 공간 복잡도를 획기적으로 낮춤.

- **Problem Hint:**
"삼각형의 꼭대기에서 바닥까지 이어지는 경로.", "거쳐간 숫자의 합이 가장 큰 경우" -> 경로의 부분합이 전체의 최적해를 구성하는 최적 부분 구조( Optimal Substructure )를 가짐을 파악하여 DP 알고리즘 도출.

- **Portfolio Selling Point:**
단순히 알고리즘을 푸는 것에 그치지 않고, 상태 전이의 규칙을 분석하여 2차원 배열을 1차원 배열로 압축하는 고도의 메모리 공간 최적화( Space Optimization ) 능력을 보여줌. 동시에 원본 인자( triangle )의 불변성( Immutability )을 유지하여 실무적인 API 설계 원칙을 준수하는 시각을 어필.

---

### PRG 42895 - N으로 표현
- **Topic:** DP | Set | Combinatorics
- **Folder:** `Week_03/04_DP/`
- **Time Complexity:** O(C) ( C는 N=8일 때 생성되는 모든 조합의 수, 상수에 가까움 )
- **Space Complexity:** O(K) ( K는 생성된 고유한 연산 결과값의 개수. unordered_set 메모리 )

- **Key Idea:**
숫자 N을 k번 사용해서 만들 수 있는 수의 집합을 DP[k]라고 할 때, DP[k]는 ( DP[i]의 원소 )와 ( DP[k-i]의 원소 )를 사칙연산한 결과들의 합집합임을 이용하여 상태 전이( State Transition )를 구현함. 추가로 N이 연속되는 수( N, NN, NNN... )를 미리 집합에 초기화함.

- **Caution:**
다중 루프가 5중으로 겹치기 때문에 인덱스 설계( 0-based 인덱스의 j와 i-j-1 분할 )가 하나라도 어긋나면 올바른 조합이 형성되지 않음. 또한, 메인 DP 연산뿐만 아니라 '연속된 숫지'를 배열에 초기화하는 단계에서도 목표 숫자( number )와 일치하는지 반드시 검사해야 함. 이를 누락하면 목표 숫자가 초기화 값( 예 : 55 )과 같을 때 정답을 무시하고 넘어가 오답( -1 )을 반환하는 논리적 오류가 발생함.

- **Improvement:**
가독성을 해치고 제어문 이탈 범위가 모호한 switch-case-break 구조를 if - else if - continue로 리팩토링하여 예기치 않은 쓰레기값 삽입 버그를 원천 차단함. 배열 초기화 구역에 단 한줄의 조기 탈출( Early Exit : if(nn = number ) return i + 1;) 코드를 추가하여 엣지 케이스 방어와 연산 속도 최적화를 동시에 달성함.

- **Problem Hint:**
"최솟값이 8보다 크면 -1을 return" -> 상태 공간( State Space )의 깊이가 8로 극단적으로 제한되어 있음을 파악하고, 깊이가 얕을 때는 다중 루프를 통한 모든 경우의 수 탐색( Exhaustive Search )과 DP의 결합이 최적의 해답임을 도출.

- **Portfolio Selling Point:**
단순히 알고리즘이 돌아가게 만드는 것을 넘어, 제어 흐름( Control Flow )을 실무 친화적으로 리팩토링하는 클린 코드 역량을 보여줌. 특히, 메인 루프에 진입하기 전 시스템의 '초기 상태( Initial State )'에 대한 검증 로직을 잊지 않고 구현하여, 놓치기 쉬운 엣지 케이스까지 완벽하게 잡아내는 꼼꼼한 QA( Quality Assurance ) 마인드를 입증함.

---

## 📅 2026-04-27
**PRG 12978 - 배달**
**PRG 72413 - 합승 택시 요금**

### PRG 12978 - 배달
- **Topic:** Graph | Dijkstra | Priority Queue
- **Folder:** `Week_04/01_Graph_Advanced/`
- **Time Complexity:** O(E log V) ( E는 간선의 개수, V는 마을의 개수. 힙 연산 기준 )
- **Space Complexity:** O(V + E) ( 인접 리스트 배열 및 우선순위 큐 메모리 )

- **Key Idea:**
마을 간의 이동 비용( 시간 )이 다르므로 일반적인 BFS가 아닌 다익스트라( Dijkstra ) 알고리즘을 사용. 최단 거리 테이블( visited )을 무한대( INF )로 초기화한 뒤, 1번 마을을 시작으로 우선순위 큐( Min-Heap )를 이용해 현재 가장 비용이 적게 드는 마을부터 순차적으로 탐색하며 연결된 마을들의 최단 거리를 갱신함.

- **Caution:**
두 마을을 연결하는 도로가 여러 개일 수 있다는 조건( 다중 간선 )이 있ㄴ으나, 다익스트라의 특성상 큐에 여러 간선 정보가 들어가더라도 최솟값을 먼저 꺼내어 테이블을 갱신( visited[nnode] = ncost )하고, 이후에 꺼내지는 더 큰 비용의 간선은 cost > visited[node] 조건에 의해 자동으로 필터링되므로 로직상 안전함.

- **Improvement:**
전역 공간( Data Segment )에 할당된 2차원 벡터 배열( adj )은 로컬 환경에서 함수가 연속 호출될 때 이전 데이터가 누적되는 부작용을 일으킴. 코딩 테스트상에선 안전하지만 테스트가 불편하다면 adj[i].clear( )를 명시적으로 호출하여 시스템의 상태를 안전하게 초기화하는 방어 코드를 추가할 수 있음.

- **Problem Hint:** 
"음식 배달이 가능한 마을의 개수", "도로를 지날 때 걸리는 시간" -> 간선에 양의 가중치가 존재하는 그래프에서 단일 출발점 최단 경로( Single-Source Shortest Path )를 찾는 전형적인 다익스트라 모델 도출.

- **Portfolio Selling Point:**
네비게이션 메시( NavMesh )나 AI 길찾기의 근간이 되는 다익스트라 알고리즘을 C++ prioirty_queue를 이용해 최적화된 형태로 구현함. 특히 로컬 테스트 중 발생한 메모리 잔존 문제( Data 영역 찌꺼기 )를 스스로 진단하고 해결함으로써, 메모리의 생명 주기와 엔진 런타임 환경에 대한 깊은 이해도를 증명.

---

### PRG 72413 - 합승 택시 요금
- **Topic:** Graph | Dijkstra | Multi-Source
- **Folder:** `Week_04/01_Graph_Advanved/`
- **Time Complexity:** O(E log V) ( 다익스트라 3회 호출. E는 간선, V는 노드 수 )
- **Space Complexity:** O(V + E)

- **Key Idea:**
특정 지점 i까지 합승한 뒤 흩어지는 것이 최소 비용이라고 가정할 때, 총비용은 `( S -> i ) + ( i -> A ) + ( i -> B )`가 됨. 무방향 그래프의 특성에 따라 `( i -> A )`는 `( A -> i)`와 같으므로, 출발점 S, 도착점 A, 도착점 B를 각각 시작점으로 삼아 다익스트라를 총 3번만 수행하면 모든 임의의 분기점 i에 대한 비용을 한 번의 O(N) 반복문으로 도출할 수 있음.

- **Caution:**
다익스트라 알고리즘 결과를 3개 합산( `FromS[i] + FromA[i] + FromB[i]` )할 때, 도달 불가능한 경로의 초기값( `INF` )이 너무 크면 C++의 int 자료형 상한선( 약 21억 )을 초과하여 음수로 오버플로우되는 치명적인 버그가 발생할 수 있으므로 안전한 한계산( `1e8` 등 )을 설정해야 함.

- **Improvement:**
다익스트라 알고리즘을 메인 함수 내부에 중복 작성하지 않고 별도의 모듈화된 함수( `vector<int> dijkstra(...)`)로 분리하여 유지보수성을 높이고 코드를 간결하게 리팩토링함.

- **Problem Hint:**
"합승을 하거나 하지 않고", "최저 예상 택시요금을 계산" -> 경로가 어디선가 갈라진다는 '분기점'의 개념을 도출하고, 모든 노드를 분기점 후보로 두고 탐색해야 함을 파악.

- **Portfolio Selling Point:**
알고리즘의 맹목적인 구현에 그치지 않고, 무방향 그래프의 성질을 수학적으로 분석하여 연산 횟수를 획기적으로 줄이는 최적화 사고력을 입증함. 또한 시스템 내부 데이터 타입( `int` )의 한계를 인지하고 오버플로우 방지 설계를 선제적으로 적용하는 등, 실무 지향적인 메모리 안전성 감각을 뽐냄.

---

## 📅 2026-04-28
**PRG 42861 - 섬 연결하기**

### PRG 42861 - 섬 연결하기
- **Topic:** Graph | MST | Kruskal | Union-Find
- **Folder:** `Week_04/02_MST/`
- **Time Complexity:** O(E log E) ( 간선( E )을 가중치 기준으로 정렬하는 데 걸리는 시간이 지배적 )
- **Space Complexity:** O(V) ( 노드( V )의 개수만큼 필요한 parent 배열 메모리 )

- **Key Idea:**
모든 섬을 최소 비용으로 연결하기 위해 크루스칼 알고리즘을 사용함. 간선 배열을 비용 기준으로 오름차순 정렬한 뒤, 비용이 적은 간선부터 순서대로 선택. 이때 두 섬이 이미 같은 그룹에 속해 있는지( 사이클 발생 여부 )를 유니온-파인드 자료구조로 검사하여, 다른 그룹일 때만 연결하고 합산함.

- **Caution:**
두 가지 치명적인 엣지 케이스 및 문법 함정에 주의해야 함. 첫째, unionParent 함수 내부에서 두 노드의 최상위 부모가 같을 때( 사이클 발생 시 ) 즉시 return false;로 함수를 종료해야 하며, 이를 누락할 경우 로직이 무너짐. 둘째, std::sort의 커스텀 정렬 함수로 클래스 내부의 일반 멤버 함수를 넘기면 인자 개수 불일치( this 포인터 포함 )로 컴파일 에러가 발생함.

- **Improvement:**
std::sort의 타입 충돌 문제를 피하기 위해 함수를 static으로 선언하거나, 더 직관적이고 캡슐화가 잘 되는 모던 C++의 람다식을 활용하여 인라인으로 정렬 로직을 깔끔하게 처리함.

- **Problem Hint:**
"모든 섬이 서로 통행 가능", "최소 비용" -> 전형적인 최소 신장 트리( MST ) 문제의 핵심 키워드임을 도출.

- **Portfolio Selling Point:**
알고리즘의 논리적 흐름( Kruskal )뿐만 아니라, C++ 객체지향 프로그래밍에서 클래스 인스턴스와 멤버 함수의 메모리 구조( this 포인터 동작 원리 )를 정확히 이해하고 트러블슈팅하는 능력을 보여줌. 제어문( return )의 미세한 누락이 전체 아키텍처에 미치는 영향을 파악하는 꼼꼼한 디버깅 감각.

---
