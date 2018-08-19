#define rightPWM 2
#define leftPWM 3
#define rightForward 26
#define rightBackward 28
#define leftForward 9
#define leftBackward 10
#define start 5
#define led 6
#define lsaJunction 33

bool flag_1, flag = 0;
float sensorReading = 0;
char lsaJunctiontion = 'S';

int pid();
void halt();
void lsaRead();
void writeSpeed();
void followLine();
void offset();
void rightturn();
void leftturn();
void back();
void lsaDetectJunction();
void lsaJunctionTest();

void setup() {
  Serial.begin(9600);
  pinMode(lsaJunction, INPUT);
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(26, OUTPUT);
  pinMode(28, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(led, OUTPUT);
  pinMode(start, INPUT);
}

void loop() {
  flag_1 = digitalRead(start);
  if (!flag_1)
  {
    flag = !flag;
    delay(2000);
  }
  if (flag)
  {
    lsaJunctionTest();
  }
  else
  {
    halt();
  }
}

void halt()
{
  digitalWrite(rightForward, HIGH);
  digitalWrite(rightBackward, HIGH);
  digitalWrite(leftBackward, HIGH);
  digitalWrite(leftForward, HIGH);
  analogWrite(rightPWM, 255);
  analogWrite(leftPWM, 255);
  delay(500);
}
void lsaRead()
{
  sensorReading = (float(analogRead(A11)) * 70) / 921;
}

int pid()
{
  static int error = 0;
  static int errorLast = 0;
  int referncePosition = 35; //referncePositionerence position
  float kp = 0.65, kd = 25.8; //proportional gain
  lsaRead();
  errorLast = error;
  error = sensorReading - referncePosition;
  if (error < -35 || error > 35) error = errorLast;
  Serial.println(error);
  return (error * kp + kd * (error - errorLast));
}

void writeSpeed()
{
  int referncePositionSpeed = 150;//line at center
  int leftSpeed = 0, rightSpeed = 0;
  leftSpeed = referncePositionSpeed + pid();
  rightSpeed = referncePositionSpeed - pid();
  analogWrite(rightPWM, rightSpeed);
  analogWrite(leftPWM, leftSpeed);
}

void followLine()
{
  digitalWrite(rightBackward, LOW);
  digitalWrite(rightForward, HIGH);
  digitalWrite(leftForward, HIGH);
  digitalWrite(leftBackward, LOW);
  writeSpeed();
}

void offset()
{
  int referncePositionSpeed = 50; //Refernce Position speed for turning
  int timer = 1000;               //time for which it turns
  digitalWrite(rightBackward, LOW);
  digitalWrite(rightForward, HIGH);
  digitalWrite(leftForward, HIGH);
  digitalWrite(leftBackward, LOW);
  analogWrite(rightPWM, referncePositionSpeed);
  analogWrite(leftPWM, referncePositionSpeed);
  delay(timer);
  halt();
}

void rightturn()
{
  int referncePositionSpeed = 90; //refernce Position speed for turning
  halt();
  digitalWrite(rightForward, LOW);
  digitalWrite(rightBackward, HIGH);
  digitalWrite(leftBackward, LOW);
  digitalWrite(leftForward, HIGH);
  analogWrite(rightPWM, referncePositionSpeed);
  analogWrite(leftPWM, referncePositionSpeed);
  while (sensorReading <= 30 || sensorReading >= 40) lsaRead();
  //halt();
}

void leftturn()
{
  int referncePositionSpeed = 90; //refernce Position speed for turning
  halt();
  digitalWrite(rightForward, HIGH);
  digitalWrite(rightBackward, LOW);
  digitalWrite(leftBackward, HIGH);
  digitalWrite(leftForward, LOW);
  analogWrite(rightPWM, referncePositionSpeed);
  analogWrite(leftPWM, referncePositionSpeed);
  while (sensorReading <= 30 || sensorReading >= 40) lsaRead();
  //halt();
}


void back()
{
  int referncePositionSpeed = 50; //refernce Position speed for turning
  int timer = 6000;               //time for which it turns
  digitalWrite(rightForward, HIGH);
  digitalWrite(rightBackward, LOW);
  digitalWrite(leftBackward, HIGH);
  digitalWrite(leftForward, LOW);
  analogWrite(rightPWM, referncePositionSpeed);
  analogWrite(leftPWM, referncePositionSpeed);
  delay(timer);
  halt();
}

void lsaDetectJunction()
{
  lsaRead();
  if (digitalRead(lsaJunction) && sensorReading <= 40)
  {
    lsaJunctiontion = 'L';
  }
  else if (digitalRead(lsaJunction) && sensorReading >= 30)
  {
    lsaJunctiontion = 'R';
  }
  else if (!(digitalRead(lsaJunction)) && sensorReading > 70 )
  {
    lsaJunctiontion = 'N';
  }
  else lsaJunctiontion = 'S';
}

void lsaJunctionTest()
{
  lsaDetectJunction();
  if (lsaJunctiontion == 'S')
  {
    followLine();
    Serial.println('S');
  }
  else if (lsaJunctiontion == 'L')
  {
    leftturn();
    Serial.println('L');
  }
  else if (lsaJunctiontion == 'R')
  {
    rightturn();
    Serial.println('R');
  }
  else
  {
    leftturn();         //Left Priority
    Serial.println('N');
  }
}
