/*
 * 需要将\hardware\arduino\avr\cores\arduino\HardwareSerial.h
 * 文件中做如下修改，因为一个解算指令包含150Byte，需要串口接收缓存区大于150Byte
 * #if !defined(SERIAL_RX_BUFFER_SIZE)
 * #if ((RAMEND - RAMSTART) < 1023)
 * #define SERIAL_RX_BUFFER_SIZE 256//16
 * #else
 * #define SERIAL_RX_BUFFER_SIZE 256//64 
 * #endif
 * #endif
*/
//电磁阀
#define MOS1_pin 5
#define MOS2_pin 4
#define OPEN 1
#define CLOSE 0
//电机
#define Motor_1_PUL_pin 11
#define Motor_1_DIR_pin 31
#define Motor_1_ENA_pin 30
#define Motor_2_PUL_pin 13
#define Motor_2_DIR_pin 37
#define Motor_2_ENA_pin 36
#define MOTOR1 1
#define MOTOR2 2
#define CW 1
#define CCW 0
#define TURN180 5000//degerr number
#define TURN90 2500//degree number
//#define speedNumMin 3//motor speed control number
//#define speedNumMax 20//motor speed control number//80
#define speedNumMin 6//motor speed control number//3
#define speedNumMax 40//motor speed control number//20
#define speedCut 10
#define Pi 3.14
//其他
#define Function_1 6
#define Function_2 7
#define Function_3 8
#define Function_4 9
#define Function_5 10

#define NO_DATA      0
#define SECOND_CAP   1
#define MOVE         2

#define L_C 0
#define L_O 1
#define L_1 2
#define L_2 3
#define L_3 4

#define R_C 5
#define R_O 6
#define R_1 7
#define R_2 8
#define R_3 9



byte command[150];
byte MechSteps[150];
void setup() {
  pinMode(MOS1_pin, OUTPUT);
  pinMode(MOS2_pin, OUTPUT);
  pinMode(Motor_1_PUL_pin, OUTPUT);
  pinMode(Motor_1_DIR_pin, OUTPUT);
  pinMode(Motor_1_ENA_pin, OUTPUT);
  pinMode(Motor_2_PUL_pin, OUTPUT);
  pinMode(Motor_2_DIR_pin, OUTPUT);
  pinMode(Motor_2_ENA_pin, OUTPUT);
  digitalWrite(Motor_1_ENA_pin, LOW);//protect
  digitalWrite(Motor_2_ENA_pin, LOW);
  delay(3);
  digitalWrite(Motor_1_DIR_pin, LOW);
  digitalWrite(Motor_2_DIR_pin, LOW);
  delay(3);
  digitalWrite(Motor_1_PUL_pin, LOW);
  digitalWrite(Motor_2_PUL_pin, LOW);//protect
  delay(3);
  Serial.begin(115200);
  Serial2.begin(9600);
  MechSteps_init();
  command_init();
  MotorMove(R_C);
  MotorMove(L_C);

}

void loop() {
//  MotorMove(L_3);
  second();
  test_moveed();
//MotorMove(R_3);
//MotorMove(R_2);
//test_moveed();
while(1);
//delay(500);

//MotorMove(L_2);
//delay(3);
//    second();
//    delay(500);
//    test_moveed();
//    while (1);
}
