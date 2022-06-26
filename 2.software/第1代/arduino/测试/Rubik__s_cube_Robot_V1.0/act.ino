void MotorMove(int a) {
  switch (a) {
    case L_1:
      MotorDrive(MOTOR2, CW, TURN90);
      delay(80);
      break;
    case L_2:
      MotorDrive(MOTOR2, CW, TURN180);
      delay(150);
      break;
    case L_3:
      MotorDrive(MOTOR2, CCW, TURN90);
      delay(80);
      break;
    case L_O:
      MosDrive(MOS2_pin, OPEN);
      delay(100);
      break;
    case L_C:
      MosDrive(MOS2_pin, CLOSE);
      delay(100);
      break;
    case R_1:
      MotorDrive(MOTOR1, CW, TURN90);
      delay(80);
      break;
    case R_2:
      MotorDrive(MOTOR1, CW, TURN180);
      delay(150);
      break;
    case R_3:
      MotorDrive(MOTOR1, CCW, TURN90);
      delay(80);
      break;
    case R_O:
      MosDrive(MOS1_pin, OPEN);
      delay(100);
      break;
    case R_C:
      MosDrive(MOS1_pin, CLOSE);
      delay(100);
      break;
  }
}
void second() {
  MotorMove(R_O);
  MotorMove(L_3);
  MotorMove(R_C);
  MotorMove(L_O);
  MotorMove(L_1);
  MotorMove(L_C);
}
