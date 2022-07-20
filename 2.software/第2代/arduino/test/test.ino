byte command[150];
#define NO_DATA      0
#define SECOND_CAP   1
#define MOVE         2
int count = 0;
void setup()
{
  Serial.begin(115200);
  command_init();
}
void loop()
{
    LOOP();
//  Serial.write(0xCC);
//  while (1);
}
void command_init()
{
  for (int i = 0; i < 150; i++)
    command[i] = 0;
}
int getcommand()
{
  while (Serial.available() > 0)
  {
    command[count] = Serial.read();
    delay(1);
    count++;
    if (count == 150)count = 0;
  }
  if ((command[0] == 0xAA) && (command[149] == 0xBB))
  {
    if (command[1] == 0XFF && (command[2] == 0xFF))
      return SECOND_CAP;
    else
    {
      for (int j = 1; j < 149; j++)
      {
        if (command[j] == 0XBB)
          break;
        return MOVE;
      }
    }
  }
  return NO_DATA;
}
void LOOP()
{
  int getcommandReturn = getcommand();
  if (getcommandReturn == NO_DATA);
  else if (getcommandReturn == SECOND_CAP)
  {
    Serial.write(0xCC);
    command_init();
  }
  else if (getcommandReturn == MOVE )
    Serial.write(0xDD);
}
