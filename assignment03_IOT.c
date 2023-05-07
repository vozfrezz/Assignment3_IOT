#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
// define constants for 2D array.
#define MAX_ROW 9
#define MAX_COL 9
#define MAX 10

// Define the point structure
typedef struct POINT {
  int row;
  int column;
  int value;
  bool visited;
  struct POINT *prev;
} point_t;

// Declare a global 2D array of point_t structures representing the matrix with
// dimensions MAX_ROW x MAX_COL.
point_t matrix[MAX_ROW][MAX_COL];
void setUpGrid();
void initMatrix(int data[MAX_ROW][MAX_COL]);
void setUpGrid() {
  // Declare a 2D array for the input value of matrix array purpose.
  int data[MAX_ROW][MAX_COL] = {
      {1, 1, 0, 1, 1, 0, 1, 1, 0}, {1, 1, 0, 1, 1, 0, 1, 1, 0},
      {0, 1, 1, 0, 1, 1, 1, 0, 0}, {1, 1, 1, 1, 1, 1, 1, 1, 0},
      {1, 1, 0, 1, 1, 0, 1, 1, 0}, {1, 0, 1, 1, 1, 0, 1, 1, 0},
      {0, 1, 1, 0, 1, 0, 1, 1, 0}, {1, 1, 0, 1, 0, 1, 1, 1, 0},
      {1, 1, 0, 1, 0, 1, 1, 1, 0},
  };
  initMatrix(data);
}

// Input matrix data from a predefined a 2D array.
void initMatrix(int data[MAX_ROW][MAX_COL]) {
  // Iterate through the properties in 2D matrix array.
  for (int i = 0; i < MAX_ROW; i++) {
    for (int j = 0; j < MAX_COL; j++) {
      matrix[i][j].row = i;
      matrix[i][j].column = j;
      matrix[i][j].value = data[i][j];
      matrix[i][j].visited = false;
      matrix[i][j].prev = NULL;
    }
  }
}

// Print a 2D matrix array to the terminal.
void exportMatrixData() {
  for (int i = 0; i < MAX_ROW; i++) {
    printf("\n");
    for (int j = 0; j < MAX_COL; j++) {
      printf("%d\t", matrix[i][j].value);
    }
  }
}

// Declare a struct for creating queue purposes.
typedef struct {
  point_t *data[MAX]; // using pointer instead of normal because we must modify
                      // point_t in matrix"unvisited -> visited"
  int front;
  int rear;
} Queue;

// Initialize the queue with a pointer truct parameter and initialize the front
// and rear.
void initQueue(Queue *q) {
  q->front = 0;
  q->rear = -1;
}
// Check if the queue is empty
int isEmpty(Queue q) { return (q.rear < q.front); }
// Check if the queue is full
int isFull(Queue q) {
  if ((q.rear - q.front) == MAX - 1) {
    return 1;
  } else {
    return 0;
  }
}
// Add an element to the queue
void enQueue(Queue *q, point_t *x) {
  if (!isFull(*q)) {
    if (q->rear == MAX - 1) {
      for (int i = q->front; i <= q->rear; i++) {
        q->data[i - q->front] = q->data[i];
      }
      q->rear = MAX - q->front - 1;

      q->front = 0;
    }
    q->rear = q->rear + 1;
    q->data[q->rear] = x;
  }
}

// Remove an element from the queue
point_t *deQueue(Queue *q) {
  point_t *d = NULL;
  if (!isEmpty(*q)) {
    d = q->data[q->front];
    q->front = q->front + 1;
  }
  if (q->front > q->rear) {
    initQueue(q);
  };
  return d;
}

// Check if the given coordinates are within the matrix.
bool checkCoordinate(int row, int col) {
  bool ret = false;
  if ((0 <= row && row < MAX_ROW) && (0 <= col && col < MAX_COL)) {
    ret = true;
  }
  return ret;
}

// Find surrounding points with a value of 1.
void findSurroundingPoint(int rows, int cols, point_t SurroundingPnt[4],
                          int *count) {
  int tempCount = 0;
  if (checkCoordinate(rows, cols + 1) && matrix[rows][cols + 1].value == 1) {
    SurroundingPnt[tempCount] = matrix[rows][cols + 1];
    tempCount++;
  }
  if (checkCoordinate(rows + 1, cols) && matrix[rows + 1][cols].value == 1) {
    SurroundingPnt[tempCount] = matrix[rows + 1][cols];
    tempCount++;
  }
  if (checkCoordinate(rows, cols - 1) && matrix[rows][cols - 1].value == 1) {
    SurroundingPnt[tempCount] = matrix[rows][cols - 1];
    tempCount++;
  }
  if (checkCoordinate(rows - 1, cols) && matrix[rows - 1][cols].value == 1) {
    SurroundingPnt[tempCount] = matrix[rows - 1][cols];
    tempCount++;
  }
  *count = tempCount;
}

// Find the shortest path from (0, 0) to target point.
bool findShortestPath(int rows, int cols) {
  // Declare a queue and make it empty.
  Queue queue;
  initQueue(&queue);

  // Mark the starting point as visited and enqueue it
  matrix[0][0].visited = true;
  enQueue(&queue, &matrix[0][0]);

  // Declare a found variable to check when the target point has been found.
  bool found = false;
  point_t *currentPoint;
  point_t surroundingPoint[4];
  int count = 0;
  // Continue searching until the queue is empty or the target point is found
  while ((isEmpty(queue) == false) && (found == false)) {
    currentPoint = deQueue(&queue);
    findSurroundingPoint(currentPoint->row, currentPoint->column,
                         surroundingPoint, &count);
    // Iterate through the surrounding points
    for (int i = 0; i < count; i++) {
      if (matrix[surroundingPoint[i].row][surroundingPoint[i].column].visited ==
          false) {
        matrix[surroundingPoint[i].row][surroundingPoint[i].column].visited =
            true;
        matrix[surroundingPoint[i].row][surroundingPoint[i].column].prev =
            &matrix[currentPoint->row][currentPoint->column];
        if (matrix[surroundingPoint[i].row][surroundingPoint[i].column].row ==
                rows &&
            matrix[surroundingPoint[i].row][surroundingPoint[i].column]
                    .column == cols) {
          found = true;
          break;
        } else {
          enQueue(&queue,
                  &matrix[surroundingPoint[i].row][surroundingPoint[i].column]);
        }
      }
    }
  }
  //  printf("\nNot found path fromt O(0;0) to A(%d;%d)", rows, cols);
  return found;
}

void printThePath(int rows, int cols) {
  // Print the message indicating the path was found
  printf("\n The coordinate points from O(0;0) to A(%d,%d)", rows, cols);
  point_t *pnt = &matrix[rows][cols];
  // Create an array to store the points in the path, and an index to keep
  // track of the currentPoint position
  point_t nodePrint[30];
  int nodePrintIndex = 0;
  // Iterate through the path from the target point back to the starting point
  while (pnt != NULL) {
    nodePrint[nodePrintIndex] = *pnt;
    // printf("\"%d:%d\"->", pnt->row, pnt->column);
    pnt = pnt->prev;
    nodePrintIndex++;
  }
  // Print the path in reverse order (starting point to target point)
  for (int i = nodePrintIndex - 1; i >= 0; i--) {
    printf("\"%d:%d\"->", nodePrint[i].row, nodePrint[i].column);
  }
}

int main() {
  setUpGrid();
  exportMatrixData();

  int targetRow, targetCol;
  bool isValid;

  do {
    printf("\nEnter the target point coordinates (row, col): ");
    scanf("%d %d", &targetRow, &targetCol);

    isValid = checkCoordinate(targetRow, targetCol);
    if (!isValid) {
      printf("Invalid coordinates: (%d, %d). Please try again.\n", targetRow,
             targetCol);
    }
  } while (!isValid);

  bool result = findShortestPath(targetRow, targetCol);

  if (result == true) {
    printThePath(targetRow, targetCol);
  } else {

    printf("\nNot found path fromt O(0;0) to A(%d;%d)", targetRow, targetCol);
  }

  return 0;
}
