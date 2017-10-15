// General pin assignment
#define led1          0     // Yelow
#define led2          1     // Green
#define button_1      2     // Start Button

// QTR8 SETUP
#define EMITTER_PIN   23    //  QTR8 emmiter pin setup 1
//#define EMITTER_PIN   31    //  QTR8 emmiter pin setup 2
#define NUM_SENSORS   8     //  Number of Sensors used
#define TIMEOUT       2500  //  length of time in microseconds beyond which you consider the sensor reading completely black
#define CENTER_POINT  3500  //  Center point for eight sensors (7000/2=3500)
QTRSensorsRC qtrrc((unsigned char[]) {24, 25, 26, 27, 28, 29, 30, 31}   // Pin setup 1, PORTA of 1284p.
//QTRSensorsRC qtrrc((unsigned char[]) {16, 17, 18, 19, 20, 21, 22, 23}   // Pin setup 2 PORTC of 1284p.
,NUM_SENSORS, TIMEOUT, EMITTER_PIN);

// TB6612FNG SETUP
  #define STBY  13            //standby 
  //Motor1 (Left)
  #define PWMA  3             //Speed control 
  #define AIN1  12            //Direction
  #define AIN2  10            //Direction
  //Motor2 (Right)
  #define PWMB  15            //Speed control
  #define BIN1  14            //Direction
  #define BIN2  11            //Direction
  // Motor direction
  const int offsetA =  1;     //Default motor direction, change values to make
  const int offsetB = -1;     //your motors run in the apropiate direction. Can be 1 or -1
  // Initializing motors.
    Motor motor1 = Motor(AIN1, AIN2, PWMA, offsetA, STBY);
    Motor motor2 = Motor(BIN1, BIN2, PWMB, offsetB, STBY);
