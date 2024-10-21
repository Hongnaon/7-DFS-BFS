#include <stdio.h>
#include <stdbool.h>

#define MAX 11  // 그래프에서 사용될 최대 노드 수

// 스택을 위한 구조체 (DFS용)
typedef struct {
    int items[MAX];
    int top;
} Stack;

// 스택 초기화
void initStack(Stack* s) {
    s->top = -1;
}

// 스택이 비어있는지 확인
bool isEmpty(Stack* s) {
    return s->top == -1;
}

// 스택에 값 추가
void push(Stack* s, int value) {
    if (s->top < MAX - 1) {
        s->items[++(s->top)] = value;
    }
}

// 스택에서 값 제거 및 반환
int pop(Stack* s) {
    if (!isEmpty(s)) {
        return s->items[(s->top)--];
    }
    return -1;
}

// 스택의 최상단 값 반환
int peek(Stack* s) {
    if (!isEmpty(s)) {
        return s->items[s->top];
    }
    return -1;
}

// 큐를 위한 구조체 (BFS용)
typedef struct {
    int items[MAX];
    int front;
    int rear;
} Queue;

// 큐 초기화
void initQueue(Queue* q) {
    q->front = 0;
    q->rear = -1;
}

// 큐가 비어있는지 확인
bool isQueueEmpty(Queue* q) {
    return q->front > q->rear;
}

// 큐에 값 추가
void enqueue(Queue* q, int value) {
    if (q->rear < MAX - 1) {
        q->items[++(q->rear)] = value;
    }
}

// 큐에서 값 제거 및 반환
int dequeue(Queue* q) {
    if (!isQueueEmpty(q)) {
        return q->items[(q->front)++];
    }
    return -1;
}

// 그래프 저장용 2차원 배열과 방문 여부 확인 배열
int graph[MAX][MAX];
bool visited[MAX];
Stack stack;  // DFS용 스택
Queue queue;  // BFS용 큐

// DFS 함수 (스택 사용, 방문 경로 출력)
void DFS(int start, int target) {
    int visitedCount = 0;  // 방문한 노드 개수
    initStack(&stack);
    push(&stack, start);
    visited[start] = true;
    visitedCount++;  // 시작 노드 방문 카운트 증가
    printf("%d ", start);  // 시작 노드 출력

    while (!isEmpty(&stack)) {
        int current = peek(&stack);
        bool hasUnvisitedNeighbor = false;  // 인접 노드 방문 여부 플래그

        // 인접 노드 중 방문하지 않은 노드 찾기
        for (int i = 0; i < MAX; i++) {
            if (graph[current][i] && !visited[i]) {
                push(&stack, i);  // 스택에 노드 추가
                visited[i] = true;  // 노드 방문 처리
                visitedCount++;  // 방문한 노드 카운트 증가
                printf("%d ", i);  // 방문한 노드 출력
                hasUnvisitedNeighbor = true;  // 방문한 노드 있음 표시

                // 목표 노드에 도달한 경우
                if (i == target) {
                    printf("\n탐색 성공: %d\n", target);
                    printf("방문한 노드 개수: %d\n", visitedCount - 1);  // 시작 노드 제외
                    return;  // 탐색 종료
                }
                break;  // 다음 인접 노드 탐색을 위해 루프 종료
            }
        }

        // 더 이상 방문할 인접 노드가 없으면 스택에서 pop
        if (!hasUnvisitedNeighbor) {
            int lastVisited = pop(&stack);
            printf("%d ", lastVisited);  // 백트래킹할 때 노드 출력

            // 돌아가는 노드도 방문한 것으로 처리
            if (lastVisited != -1 && !visited[lastVisited]) {
                visited[lastVisited] = true;
                visitedCount++;  // 돌아가는 노드 카운트 증가
            }
        }
    }

    // 탐색 종료 후 목표 노드에 도달하지 못한 경우
    printf("\n탐색 실패: %d에 도달하지 못했습니다.\n", target);
    printf("방문한 노드 개수: %d\n", visitedCount - 1);  // 시작 노드 제외
}

// BFS 함수 (큐 사용, 방문 경로 출력)
void BFS(int start, int target) {
    int visitedCount = 0;  // 방문한 노드 개수
    initQueue(&queue);
    enqueue(&queue, start);
    visited[start] = true;
    visitedCount++;  // 시작 노드 방문 카운트 증가
    printf("%d ", start);  // 시작 노드 출력

    while (!isQueueEmpty(&queue)) {
        int current = dequeue(&queue);
        bool hasUnvisitedNeighbor = false;  // 인접 노드 방문 여부 플래그

        // 인접 노드 중 방문하지 않은 노드 찾기
        for (int i = 0; i < MAX; i++) {
            if (graph[current][i] && !visited[i]) {
                enqueue(&queue, i);  // 큐에 노드 추가
                visited[i] = true;  // 노드 방문 처리
                visitedCount++;  // 방문한 노드 카운트 증가
                printf("%d ", i);  // 방문한 노드 출력
                hasUnvisitedNeighbor = true;  // 방문한 노드 있음 표시

                // 목표 노드에 도달한 경우
                if (i == target) {
                    printf("\n탐색 성공: %d\n", target);
                    printf("방문한 노드 개수: %d\n", visitedCount - 1);  // 시작 노드 제외
                    return;  // 탐색 종료
                }
            }
        }
    }

    // 탐색 종료 후 목표 노드에 도달하지 못한 경우
    printf("\n탐색 실패: %d에 도달하지 못했습니다.\n", target);
    printf("방문한 노드 개수: %d\n", visitedCount - 1);  // 시작 노드 제외
}

// 그래프 초기화 및 탐색 함수
int main() {
    // 그래프 초기화 (사용자가 주신 그래프 구조에 맞춰서 설정)
    graph[1][4] = graph[4][1] = 1;
    graph[4][0] = graph[0][4] = 1;
    graph[0][2] = graph[2][0] = 1;
    graph[2][3] = graph[3][2] = 1;
    graph[3][5] = graph[5][3] = 1;
    graph[0][5] = graph[5][0] = 1;
    graph[4][6] = graph[6][4] = 1;
    graph[6][7] = graph[7][6] = 1;
    graph[7][10] = graph[10][7] = 1;
    graph[6][8] = graph[8][6] = 1;
    graph[8][9] = graph[9][8] = 1;

    int startNode, targetNode;

    while (1) {
        // 방문 배열 초기화
        for (int i = 0; i < MAX; i++) {
            visited[i] = false;
        }

        // 사용자로부터 시작점과 목표점 입력 받기
        printf("1: 깊이 우선 탐색 (DFS)\n");
        printf("2: 너비 우선 탐색 (BFS)\n");
        printf("3: 종료\n");
        printf("선택하세요: ");

        int choice;
        scanf_s("%d", &choice); // 선택 입력 받기

        if (choice == 3) {
            break; // 종료
        }

        printf("시작 노드와 목표 노드를 입력하세요 (0 ~ 10): ");
        scanf_s("%d %d", &startNode, &targetNode); // 시작 노드와 목표 노드 입력 받기

        // 입력 유효성 검사
        if (startNode < 0 || startNode >= MAX || targetNode < 0 || targetNode >= MAX) {
            printf("잘못된 입력입니다. 노드는 0에서 10 사이여야 합니다.\n");
            continue; // 유효하지 않은 경우 다시 선택
        }

        // 선택에 따라 탐색 실행
        if (choice == 1) {
            printf("DFS 경로: ");
            DFS(startNode, targetNode); // DFS 실행
        }
        else if (choice == 2) {
            printf("BFS 경로: ");
            BFS(startNode, targetNode); // BFS 실행
        }
        else {
            printf("잘못된 선택입니다.\n");
        }
        printf("\n");
    }

    return 0;
}
