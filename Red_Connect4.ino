// Red_Connect4_Final.ino
const int rows = 5;
const int cols = 6;

// Grids
int redGrid[rows][cols]    = {0};
int yellowGrid[rows][cols] = {0};
bool occupied[rows][cols]  = {0};

// LED pin mapping (same on both boards)
int ledPins[rows][cols] = {
  {22, 23, 24, 25, 26, 27},  // Row 4 (Top)
  {28, 29, 30, 31, 32, 33},  // Row 3
  {34, 35, 36, 37, 38, 39},  // Row 2
  {40, 41, 42, 43, 44, 45},  // Row 1
  {46, 47, 48, 49, 50, 51}   // Row 0 (Bottom)
};

bool myTurn = true;  // Red goes first

// Check 4‑in‑a‑row in any direction
bool checkWin(int grid[rows][cols]) {
  // Horizontal
  for (int r = 0; r < rows; r++)
    for (int c = 0; c <= cols - 4; c++)
      if (grid[r][c] && grid[r][c+1] && grid[r][c+2] && grid[r][c+3])
        return true;
  // Vertical
  for (int r = 0; r <= rows - 4; r++)
    for (int c = 0; c < cols; c++)
      if (grid[r][c] && grid[r+1][c] && grid[r+2][c] && grid[r+3][c])
        return true;
  // Diagonal up‑right
  for (int r = 0; r <= rows - 4; r++)
    for (int c = 0; c <= cols - 4; c++)
      if (grid[r][c] && grid[r+1][c+1] && grid[r+2][c+2] && grid[r+3][c+3])
        return true;
  // Diagonal down‑right
  for (int r = 3; r < rows; r++)
    for (int c = 0; c <= cols - 4; c++)
      if (grid[r][c] && grid[r-1][c+1] && grid[r-2][c+2] && grid[r-3][c+3])
        return true;
  return false;
}

// Blink all of player’s LEDs 3× on win
void animateWin(int grid[rows][cols]) {
  for (int k = 0; k < 3; k++) {
    // OFF
    for (int r = 0; r < rows; r++)
      for (int c = 0; c < cols; c++)
        if (grid[r][c]) digitalWrite(ledPins[r][c], LOW);
    delay(300);
    // ON
    for (int r = 0; r < rows; r++)
      for (int c = 0; c < cols; c++)
        if (grid[r][c]) digitalWrite(ledPins[r][c], HIGH);
    delay(300);
  }
}

void setup() {
  Serial.begin(9600);
  Serial1.begin(9600);
  for (int r = 0; r < rows; r++)
    for (int c = 0; c < cols; c++)
      pinMode(ledPins[r][c], OUTPUT);
}

void loop() {
  // 1) Receive Yellow’s move over Serial1
  if (Serial1.available()) {
    int colY = Serial1.parseInt();
    if (colY >= 0 && colY < cols) {
      for (int r = 0; r < rows; r++) {
        int row = rows - 1 - r; // bottom-up
        if (!occupied[row][colY]) {
          occupied[row][colY] = true;
          yellowGrid[row][colY] = 1;
          myTurn = true;       // now Red’s turn
          break;
        }
      }
    }
  }

  // 2) Red’s turn via Serial Monitor
  if (myTurn && Serial.available()) {
    int colR = Serial.parseInt();
    if (colR >= 0 && colR < cols) {
      for (int r = 0; r < rows; r++) {
        int row = rows - 1 - r;
        if (!occupied[row][colR]) {
          occupied[row][colR] = true;
          redGrid[row][colR] = 1;
          digitalWrite(ledPins[row][colR], HIGH);
          Serial1.println(colR); // send to Yellow
          // Check Red win
          if (checkWin(redGrid)) {
            animateWin(redGrid);
            while (true); // halt
          }
          myTurn = false;  // hand over to Yellow
          break;
        }
      }
    } else {
      Serial.println("Invalid column (0–5)");
    }
  }
}
