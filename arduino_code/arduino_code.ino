#include <LedControl.h>


LedControl ledControl = LedControl(12, 10, 11,0);

void setup() {
  ledControl.shutdown(0, false);
  ledControl.setIntensity(0, 5);
  ledControl.clearDisplay(0);

}


#define N 3
#define WAIT 1
#define HIT 10
#define QUEEN 100
#define NOSOL 1000
#define BREAK 1

/**
 * Trying to display an X if no solution was found
 */
void noSolution(int board[N][N]){
  for(int x = 0; x < 10; x++){
    int y = N-1;
    for(int i = 0; i < N; i++){
      if(x % 2 == 0){
        ledControl.setLed(0, i, i, 1);
        ledControl.setLed(0, i, y, 1);
      }else{
        ledControl.setLed(0, i, i, 0);
        ledControl.setLed(0, i, y, 0);
      }
      y--;
    }
    delay(NOSOL);
  }
}

/**
 * Breaks the loop making the solution permanently visible
 */
void breakLoop(){
  while(true){
    int a;
  }
}

/**
 * restart the grid, sets all LEDs off
 */
void restart(int board[N][N]){
  for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
          ledControl.setLed(0, i, j, 1);
        }
    }
    delay(WAIT);
    ledControl.clearDisplay(0);
}

/**
 * Searches for the current position of the queen on the grid
 * and turns that LED
 */
void printSolution(int board[N][N])
{
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
          int value = board[i][j];
          if(value){
            ledControl.setLed(0, i, j, 1); 
          }else{
            ledControl.setLed(0, i, j, 0); 
          }
        }
    }
    delay(WAIT);
}

/**
 * Makes final queens blink to show the solution
 */
void blinkWinner(int board[N][N]){
   for(int i = 0; i < 10; i++){
    ledControl.clearDisplay(0);
    delay(QUEEN);
    printSolution(board);
    delay(QUEEN);
  }
}

/**
 * Checks if the queen can be placed without coliding with another
 * queen
 */
bool isSafe(int board[N][N], int row, int col)
{
  printSolution(board);
    int i, j;
    for (i = 0; i < col; i++) {
        if (board[row][i]){
            ledControl.setLed(0, row, i, 1);
            ledControl.setLed(0, row, col, 1);
            delay(HIT);
            ledControl.setLed(0, row, i, 0);
            ledControl.setLed(0, row, col, 0);
            delay(HIT);
            ledControl.setLed(0, row, i, 1);
            ledControl.setLed(0, row, col, 1);
            delay(HIT);
            ledControl.setLed(0, row, i, 0);
            ledControl.setLed(0, row, col, 0);
            delay(HIT);
            return false;
        }
    }

    for (i=row, j=col; i>=0 && j>=0; i--, j--){
        if (board[i][j]) {
            ledControl.setLed(0, i, j, 1);
            ledControl.setLed(0, row, col, 1);
            delay(HIT);
            ledControl.setLed(0, i, j, 0);
            ledControl.setLed(0, row, col, 0);
            delay(HIT);
            ledControl.setLed(0, i, j, 1);
            ledControl.setLed(0, row, col, 1);
            delay(HIT);
            ledControl.setLed(0, i, j, 0);
            ledControl.setLed(0, row, col, 0);
            delay(HIT);
            return false;
        }
    }

    for (i=row, j=col; j>=0 && i<N; i++, j--) {
        if (board[i][j]) {
           ledControl.setLed(0, i, j, 1);
            ledControl.setLed(0, row, col, 1);
            delay(HIT);
            ledControl.setLed(0, i, j, 0);
            ledControl.setLed(0, row, col, 0);
            delay(HIT);
            ledControl.setLed(0, i, j, 1);
            ledControl.setLed(0, row, col, 1);
            delay(HIT);
            ledControl.setLed(0, i, j, 0);
            ledControl.setLed(0, row, col, 0);
            delay(HIT);
            return false;
        }
    }

    printSolution(board);

    return true;
}

/**
 * "Main loop" of the program, if it's safe to placed a queen
 * then go ahead and do it
 */
bool solveNQUtil(int board[N][N], int col){
  printSolution(board);
    if (col >= N)
        return true;

    for (int i = 0; i < N; i++)
    {
        if ( isSafe(board, i, col) )
        {
            board[i][col] = 1;

            if ( solveNQUtil(board, col + 1) )
                return true;

            board[i][col] = 0;
        }
    }
    return false;
}

/**
 * This function calls the main loop, it also creates the matrix
 * and 
 */
bool solveNQ()
{
    int board[N][N];
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            board[i][j] = 0;
        }
    }

    if ( solveNQUtil(board, 0) == false )
    {
        noSolution(board);
        return false;
    }

    printSolution(board);

    blinkWinner(board);

    //restart(board);
    
   return true;
}


void loop() {
  solveNQ();
  if(BREAK){
   breakLoop();
  }
}
