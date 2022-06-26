void MosText() {
  MosDrive(MOS1_pin, OPEN); MosDrive(MOS2_pin, OPEN);
  delay(2000);
  MosDrive(MOS1_pin, CLOSE); MosDrive(MOS2_pin, CLOSE);
  delay(2000);
}
void MotorText(int a) {
  int i = 0;
  for (i; i < 2500; i++) { //360
    digitalWrite(Motor_1_PUL_pin, HIGH);
    delayMicroseconds(500);
    digitalWrite(Motor_1_PUL_pin, LOW);
    delayMicroseconds(500);
  }
  while (1);
}
//  int a = digitalRead(38);
//  int b = digitalRead(37);
//  int c = digitalRead(36);
//  if (a == 1) {
//    //    Serial.print("a");
//    Serial.write(0xcc);
//    //    Serial.write(0xcc);
//    //    Serial.print(0xcc);
//    Serial.write(0xcc);
//    while (1) {
//      Serial.write(0xcc);;
//    }
//  }
void test_moveed() {
  MotorMove(R_1);
  MotorMove(L_O);
  MotorMove(R_1);
  MotorMove(L_1);
  MotorMove(L_C);
  MotorMove(L_1);
  MotorMove(R_3);
  MotorMove(L_O);
  MotorMove(R_1);
  MotorMove(L_1);
  MotorMove(L_C);
  MotorMove(R_O);
  MotorMove(L_3);
  MotorMove(R_C);
  MotorMove(R_3);
  MotorMove(R_O);
  MotorMove(R_1);
  MotorMove(L_2);
  MotorMove(R_C);
  MotorMove(R_3);
  MotorMove(R_O);
  MotorMove(R_1);
  MotorMove(L_1);
  MotorMove(R_C);
  MotorMove(L_2);
  MotorMove(L_O);
  MotorMove(L_1);
  MotorMove(L_C);
  MotorMove(R_3);
  MotorMove(R_O);
  MotorMove(R_1);
  MotorMove(L_1);
  MotorMove(R_C);
  MotorMove(L_O);
  MotorMove(L_1);
  MotorMove(L_C);
  MotorMove(R_2);
  MotorMove(L_2);
  MotorMove(R_3);
  MotorMove(R_O);
  MotorMove(R_1);
  MotorMove(R_C);
  MotorMove(L_2);
  MotorMove(L_O);
  MotorMove(R_3);
  MotorMove(L_C);
  MotorMove(R_O);
  MotorMove(R_1);
  MotorMove(R_C);
  MotorMove(L_2);
  MotorMove(R_3);
  MotorMove(R_O);
  MotorMove(R_1);
  MotorMove(L_2);
  MotorMove(R_C);
  MotorMove(L_2);
  MotorMove(R_1);
  MotorMove(L_O);
  MotorMove(R_1);
  MotorMove(L_1);
  MotorMove(L_C);
  MotorMove(L_2);
  MotorMove(R_O);
  MotorMove(L_1);
  MotorMove(R_1);
  MotorMove(R_C);
  MotorMove(R_2);
  MotorMove(L_O);
  MotorMove(R_1);
  MotorMove(L_1);
  MotorMove(L_C);
  MotorMove(L_1);
  MotorMove(R_2);


  
  //  MotorMove(R_3); MotorMove(L_O); MotorMove(R_3); MotorMove(L_C); MotorMove(L_3); MotorMove(R_O); MotorMove(L_1); MotorMove(R_C); MotorMove(R_3);
}
