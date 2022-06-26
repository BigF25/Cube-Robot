void command_init() {
  for (int i = 0; i < 150; i++)
    command[i] = 0;
}
void MechSteps_init() {
  for (int i = 0; i < 150; i++)
    MechSteps[i] = -1;
}
int getcommand() {
  int count = 0;
  while (Serial.available() > 0) {
    command[count] = Serial.read();
    //    Serial2.print(count);
    //    Serial2.print(':');
    //    Serial2.println(command[count], HEX);
    delay(1);
    count++;
    if (count == 150)count = 0;
  }
  int i;
  for (i = 0; i < 150; i++) {
    //    Serial2.print("i:");
    //    Serial2.println(i);
    if ((command[i] == 0xAA) && (command[i + 149] == 0xBB)) {
      //      Serial2.println("if1111111111111111111111111111111111111111111111111111111111111111");
      if (command[i + 1] == 0XFF) {
        //        Serial2.println("iffvvvvvvvvvfvvvvvvvvvvvvvvvvvvv2");
        return SECOND_CAP;
      }
      else {
        //        Serial2.println("iffvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv3");
        for (int j = 0; j < 148; j++) {

          if (command[i + j + 1] == 0XBB)
            break;
          else
            MechSteps[j] = command[i + j + 1];
        }
        return MOVE;
      }
    }
    //    Serial2.println("forend");
  }
  return NO_DATA;
}
void LOOP() {
  int getcommandReturn = getcommand();
  //  Serial2.println(getcommandReturn);
  if (getcommandReturn == NO_DATA);
  else if (getcommandReturn == SECOND_CAP) {
    second();
//    delay(1000);
    //发送结束标志
    Serial.write(0xCC);
    //    Serial2.println("0XCC");
    command_init();
  }
  else if (getcommandReturn == MOVE ) {
    for (int i = 0; i < 150; i++) {
      if (MechSteps[i] == -1)
        break;
      else
        MotorMove(MechSteps[i]);
    }
    Serial.write(0xDD);
    //    Serial2.println("0XDD");
    command_init();
    MechSteps_init();
    //    for (int i = 0; i < 150; i++)
    //      Serial2.println(command[i]);
  }
}
