#include <Servo.h>

#define ENABLEPIN 5
#define SERVOPIN 8
#define DCPIN_P 9
#define DCPIN_M 10

Servo servo;
int input;
int angle;
int speeds;

void setup()
{
  Serial.begin(9600);
  pinMode(ENABLEPIN, OUTPUT);
  pinMode(SERVOPIN, OUTPUT);
  pinMode(DCPIN_P, OUTPUT);
  pinMode(DCPIN_M, OUTPUT);
  servo.attach(SERVOPIN);
  reset();

  Serial.print("W:forward S:backward A:left D:right SPACE:stop\nQ:speed+ E:speed-");
}

void loop()
{
  while(Serial.available()){
    input = Serial.read();
    switch(input)
    {
      case 'w':
      digitalWrite(DCPIN_P, HIGH);
      digitalWrite(DCPIN_M, LOW);
      break;

      case 32:
      digitalWrite(DCPIN_P, LOW);
      digitalWrite(DCPIN_M, LOW);
      break;
      //space

      case 's':
      digitalWrite(DCPIN_P, LOW);
      digitalWrite(DCPIN_M, HIGH);
      break;

      case 'a':
      angle -= 10;
      break;

      case 'd':
      angle += 10;
      break;

      case 'q':
      if(speeds > 235)
        speeds = 255;
      else
        speeds += 20;
      break;

      case 'e':
      if(speeds < 100)
        speeds = 80;
      else
        speeds -= 20;
      break;

      case 'f':
      reset();
      break;

      default:
      break;
    }
    servo.write(angle);
    analogWrite(ENABLEPIN, speeds);
  }
}

void reset()
{
  angle = 115;
  speeds = 130;
  digitalWrite(DCPIN_P, LOW);
  digitalWrite(DCPIN_M, LOW);
  servo.write(angle);
  analogWrite(ENABLEPIN, speeds);
}
