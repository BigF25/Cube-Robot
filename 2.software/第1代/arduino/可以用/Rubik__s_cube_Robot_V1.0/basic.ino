void MosDrive(int mosNum_pin, int a) {//function to drive solenoid valve
  digitalWrite(mosNum_pin, a);
  delay(100);//protect
}
void MotorDrive(int motorNum, int dir, int degree) {//function to drive Stepmotor
  int key_DIR_pin = 0;
  int key_PUL_pin = 0;
  switch (motorNum) {
    case 1: key_DIR_pin = Motor_1_DIR_pin; key_PUL_pin = Motor_1_PUL_pin; break;
    case 2: key_DIR_pin = Motor_2_DIR_pin; key_PUL_pin = Motor_2_PUL_pin; break;
    default: break;
  }
  digitalWrite(key_DIR_pin, dir);
  delayMicroseconds(3);
  for (int j = 1; j <= degree; j++) {
    int speedNum;
    if (j % speedCut == 1) {
      speedNum = speedNumMax * sin(Pi / degree * j); //motor speed control variable
      speedNum = speedNumMin + speedNumMax - speedNum;
    }
    digitalWrite(key_PUL_pin, HIGH);
    delayMicroseconds(speedNum);
    digitalWrite(key_PUL_pin, LOW);
    delayMicroseconds(speedNum);
  }
}
