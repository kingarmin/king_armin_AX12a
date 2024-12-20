#include "king_armin_AX12.h"
#define baudrate 1000000
#define motor_id 5
AX12 motor(Serial1, baudrate);
void setup() {
  Serial.begin(9600);
  motor.Init();
  motor.LED(motor_id, 1);
  delay(1000);
  motor.LED(motor_id, 0);
  motor.set_speed(motor_id, 500);
}
void loop() {
}
