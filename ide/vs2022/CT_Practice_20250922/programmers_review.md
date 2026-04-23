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

### PRG 01844 - 게임 맵  최단거리
- **Topic:** Graph ( BFS )
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
- **Topic:** Graph ( Iterative DFS )
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
