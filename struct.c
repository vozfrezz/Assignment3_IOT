#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_ROW 4
#define MAX_COL 4
#define MAX 10

typedef struct POINT {
  int row;
  int column;
  int value;
  bool visited;
  struct POINT *prev;
} point_t;

point_t matrix[MAX_ROW][MAX_COL];

void inputMatrixData() {
  for (int i = 0; i < MAX_ROW; i++) {
    for (int j = 0; j < MAX_COL; j++) {
      printf("\n Enter value of matrix[%d][%d](0 or 1): ", i, j);
      scanf("%d", &matrix[i][j].value);
      matrix[i][j].row = i;
      matrix[i][j].column = j;
    }
  }
}

void exportMatrixData() {
  for (int i = 0; i < MAX_ROW; i++) {
    printf("\n");
    for (int j = 0; j < MAX_COL; j++) {
      printf("%d\t", matrix[i][j].value);
    }
  }
}

typedef struct {
  point_t data[MAX];
  int front;
  int rear;
} Queue;

void initQueue(Queue *q) {
  q->front = 0;
  q->rear = -1;
}

int isEmpty(Queue q) { return (q.rear < q.front); }

int isFull(Queue q) {
  if ((q.rear - q.front) == MAX - 1) {
    return 1;
  } else {
    return 0;
  }
}

void enQueue(Queue *q, point_t x) {
  if (!isFull(*q)) {
    for (int i = q->front; i <= q->rear; i++) {
      q->data[i - q->front] = q->data[i];
    }
    q->rear = MAX - q->front - 1;
    q->front = 0;
  }
  q->rear = q->rear + 1;
  q->data[q->rear] = x;
}

point_t deQueue(Queue *q) {
  point_t d;
  if (!isEmpty(*q)) {
    d = q->data[q->front];
    q->front = q->front + 1;
  }
  if (q->front > q->rear) {
    initQueue(q);
  };
  return d;
}

/*bool checkCoordinate(int row, int col) {
  bool ret = false;
  if ((0 <= row < MAX_ROW) && (0 <= col < MAX_COL)) {
    ret = true;
  }
  return ret;
}*/

int main() {
  inputMatrixData();
  exportMatrixData();
  return 0;
}
