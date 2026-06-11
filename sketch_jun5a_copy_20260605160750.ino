// ==========================================
// Arduino -> Unity 控制程式 (全按鈕版本)
// 傳送格式： move,jump
// move = -1(左) / 0(停) / 1(右)
// jump = 0 / 1
// ==========================================

const int leftBtnPin  = 3;   // 左移按鈕 (接 GND)
const int rightBtnPin = 4;   // 右移按鈕 (接 GND)
const int jumpBtnPin  = 2;   // 跳躍按鈕 (接 GND)

int moveState = 0;           // -1 / 0 / 1
int jumpState = 0;           // 0 / 1

void setup() {
  Serial.begin(9600);
  
  // 全部使用內建上拉電阻，沒按下時是 HIGH(1)，按下時是 LOW(0)
  pinMode(leftBtnPin, INPUT_PULLUP);
  pinMode(rightBtnPin, INPUT_PULLUP);
  pinMode(jumpBtnPin, INPUT_PULLUP);
}

void loop() {
  // -------- 讀取按鈕狀態 (! 邏輯反轉，讓 1 代表按下) --------
  int leftPressed  = !digitalRead(leftBtnPin);
  int rightPressed = !digitalRead(rightBtnPin);
  jumpState        = !digitalRead(jumpBtnPin);

  // -------- 判斷左右移動狀態 --------
  if (leftPressed && !rightPressed) {
    moveState = -1;  // 只按左
  } 
  else if (rightPressed && !leftPressed) {
    moveState = 1;   // 只按右
  } 
  else {
    moveState = 0;   // 沒按，或者兩邊同時按著不放
  }

  // -------- 傳送給 Unity --------
  Serial.print(moveState);
  Serial.print(",");
  Serial.println(jumpState);

  delay(20); // 每 20ms 發送一次，保持與原本相同的同步率
}