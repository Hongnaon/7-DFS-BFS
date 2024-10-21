#include <stdio.h>
#include <stdbool.h>

#define MAX 11  // �׷������� ���� �ִ� ��� ��

// ������ ���� ����ü (DFS��)
typedef struct {
    int items[MAX];
    int top;
} Stack;

// ���� �ʱ�ȭ
void initStack(Stack* s) {
    s->top = -1;
}

// ������ ����ִ��� Ȯ��
bool isEmpty(Stack* s) {
    return s->top == -1;
}

// ���ÿ� �� �߰�
void push(Stack* s, int value) {
    if (s->top < MAX - 1) {
        s->items[++(s->top)] = value;
    }
}

// ���ÿ��� �� ���� �� ��ȯ
int pop(Stack* s) {
    if (!isEmpty(s)) {
        return s->items[(s->top)--];
    }
    return -1;
}

// ������ �ֻ�� �� ��ȯ
int peek(Stack* s) {
    if (!isEmpty(s)) {
        return s->items[s->top];
    }
    return -1;
}

// ť�� ���� ����ü (BFS��)
typedef struct {
    int items[MAX];
    int front;
    int rear;
} Queue;

// ť �ʱ�ȭ
void initQueue(Queue* q) {
    q->front = 0;
    q->rear = -1;
}

// ť�� ����ִ��� Ȯ��
bool isQueueEmpty(Queue* q) {
    return q->front > q->rear;
}

// ť�� �� �߰�
void enqueue(Queue* q, int value) {
    if (q->rear < MAX - 1) {
        q->items[++(q->rear)] = value;
    }
}

// ť���� �� ���� �� ��ȯ
int dequeue(Queue* q) {
    if (!isQueueEmpty(q)) {
        return q->items[(q->front)++];
    }
    return -1;
}

// �׷��� ����� 2���� �迭�� �湮 ���� Ȯ�� �迭
int graph[MAX][MAX];
bool visited[MAX];
Stack stack;  // DFS�� ����
Queue queue;  // BFS�� ť

// DFS �Լ� (���� ���, �湮 ��� ���)
void DFS(int start, int target) {
    int visitedCount = 0;  // �湮�� ��� ����
    initStack(&stack);
    push(&stack, start);
    visited[start] = true;
    visitedCount++;  // ���� ��� �湮 ī��Ʈ ����
    printf("%d ", start);  // ���� ��� ���

    while (!isEmpty(&stack)) {
        int current = peek(&stack);
        bool hasUnvisitedNeighbor = false;  // ���� ��� �湮 ���� �÷���

        // ���� ��� �� �湮���� ���� ��� ã��
        for (int i = 0; i < MAX; i++) {
            if (graph[current][i] && !visited[i]) {
                push(&stack, i);  // ���ÿ� ��� �߰�
                visited[i] = true;  // ��� �湮 ó��
                visitedCount++;  // �湮�� ��� ī��Ʈ ����
                printf("%d ", i);  // �湮�� ��� ���
                hasUnvisitedNeighbor = true;  // �湮�� ��� ���� ǥ��

                // ��ǥ ��忡 ������ ���
                if (i == target) {
                    printf("\nŽ�� ����: %d\n", target);
                    printf("�湮�� ��� ����: %d\n", visitedCount - 1);  // ���� ��� ����
                    return;  // Ž�� ����
                }
                break;  // ���� ���� ��� Ž���� ���� ���� ����
            }
        }

        // �� �̻� �湮�� ���� ��尡 ������ ���ÿ��� pop
        if (!hasUnvisitedNeighbor) {
            int lastVisited = pop(&stack);
            printf("%d ", lastVisited);  // ��Ʈ��ŷ�� �� ��� ���

            // ���ư��� ��嵵 �湮�� ������ ó��
            if (lastVisited != -1 && !visited[lastVisited]) {
                visited[lastVisited] = true;
                visitedCount++;  // ���ư��� ��� ī��Ʈ ����
            }
        }
    }

    // Ž�� ���� �� ��ǥ ��忡 �������� ���� ���
    printf("\nŽ�� ����: %d�� �������� ���߽��ϴ�.\n", target);
    printf("�湮�� ��� ����: %d\n", visitedCount - 1);  // ���� ��� ����
}

// BFS �Լ� (ť ���, �湮 ��� ���)
void BFS(int start, int target) {
    int visitedCount = 0;  // �湮�� ��� ����
    initQueue(&queue);
    enqueue(&queue, start);
    visited[start] = true;
    visitedCount++;  // ���� ��� �湮 ī��Ʈ ����
    printf("%d ", start);  // ���� ��� ���

    while (!isQueueEmpty(&queue)) {
        int current = dequeue(&queue);
        bool hasUnvisitedNeighbor = false;  // ���� ��� �湮 ���� �÷���

        // ���� ��� �� �湮���� ���� ��� ã��
        for (int i = 0; i < MAX; i++) {
            if (graph[current][i] && !visited[i]) {
                enqueue(&queue, i);  // ť�� ��� �߰�
                visited[i] = true;  // ��� �湮 ó��
                visitedCount++;  // �湮�� ��� ī��Ʈ ����
                printf("%d ", i);  // �湮�� ��� ���
                hasUnvisitedNeighbor = true;  // �湮�� ��� ���� ǥ��

                // ��ǥ ��忡 ������ ���
                if (i == target) {
                    printf("\nŽ�� ����: %d\n", target);
                    printf("�湮�� ��� ����: %d\n", visitedCount - 1);  // ���� ��� ����
                    return;  // Ž�� ����
                }
            }
        }
    }

    // Ž�� ���� �� ��ǥ ��忡 �������� ���� ���
    printf("\nŽ�� ����: %d�� �������� ���߽��ϴ�.\n", target);
    printf("�湮�� ��� ����: %d\n", visitedCount - 1);  // ���� ��� ����
}

// �׷��� �ʱ�ȭ �� Ž�� �Լ�
int main() {
    // �׷��� �ʱ�ȭ (����ڰ� �ֽ� �׷��� ������ ���缭 ����)
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
        // �湮 �迭 �ʱ�ȭ
        for (int i = 0; i < MAX; i++) {
            visited[i] = false;
        }

        // ����ڷκ��� �������� ��ǥ�� �Է� �ޱ�
        printf("1: ���� �켱 Ž�� (DFS)\n");
        printf("2: �ʺ� �켱 Ž�� (BFS)\n");
        printf("3: ����\n");
        printf("�����ϼ���: ");

        int choice;
        scanf_s("%d", &choice); // ���� �Է� �ޱ�

        if (choice == 3) {
            break; // ����
        }

        printf("���� ���� ��ǥ ��带 �Է��ϼ��� (0 ~ 10): ");
        scanf_s("%d %d", &startNode, &targetNode); // ���� ���� ��ǥ ��� �Է� �ޱ�

        // �Է� ��ȿ�� �˻�
        if (startNode < 0 || startNode >= MAX || targetNode < 0 || targetNode >= MAX) {
            printf("�߸��� �Է��Դϴ�. ���� 0���� 10 ���̿��� �մϴ�.\n");
            continue; // ��ȿ���� ���� ��� �ٽ� ����
        }

        // ���ÿ� ���� Ž�� ����
        if (choice == 1) {
            printf("DFS ���: ");
            DFS(startNode, targetNode); // DFS ����
        }
        else if (choice == 2) {
            printf("BFS ���: ");
            BFS(startNode, targetNode); // BFS ����
        }
        else {
            printf("�߸��� �����Դϴ�.\n");
        }
        printf("\n");
    }

    return 0;
}
