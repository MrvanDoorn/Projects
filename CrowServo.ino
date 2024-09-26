/* 
 *  Crow Servo by Dan Teeter
*/

#include <Servo.h>

Servo myservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards

int pos = 0;  // variable to store the servo position
int speed = 1;
int moveInterval = 3;
int maxPos = 150;
int minPos = 30;

void setup() {
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object
  pinMode(12, OUTPUT);
  digitalWrite(12, HIGH);
}

void loop() {

  int delayTime = random(800, 3000);
  delay(delayTime);

  int target = random(minPos, maxPos);
  birdMove(target);

  maybeTwitch();
  maybeBlink();
}

void maybeBlink() {
  int shouldBLink = random(0, 1);
  if (shouldBLink == 0) {
    delay(1000);
    blink();
    int blinkTwice = random(1, 6);
    if (blinkTwice == 1) {
      delay(500);
      blink();
    }
  }
}

void blink() {
  digitalWrite(12, LOW);
  delay(300);
  digitalWrite(12, HIGH);
}

void maybeTwitch() {
  int shouldTwitch = random(1, 3);
  if (shouldTwitch == 3) {
    int timesTwitch = random(3, 5);
    int twitchCount = 0;
    for (twitchCount = 0; twitchCount <= timesTwitch; twitchCount += 1) {
      int min = pos - 10;
      int max = pos + 10;

      if (min < minPos) {
        min = minPos;
      }
      if (max > maxPos) {
        max = maxPos;
      }
      int target = random(min, max);
      birdMove(target);
    }
  }
}


void birdMove(int dest) {
  int start = myservo.read();

  if (dest - start > 0) {
    for (pos = start; pos <= dest; pos += speed) {
      myservo.write(pos);  // tell servo to go to position in variable 'pos'
      delay(moveInterval);
    }
  } else {
    for (pos = start; pos >= dest; pos -= speed) {
      myservo.write(pos);  // tell servo to go to position in variable 'pos'
      delay(moveInterval);
    }
  }
}
