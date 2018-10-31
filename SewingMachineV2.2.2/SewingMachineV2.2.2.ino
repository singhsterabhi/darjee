#include <AccelStepper.h>
#include <Servo.h>

//Pin descriptions 

//Stepper motor for X motion (upper)
#define x_pul 42
#define x_dir 40
#define x_ena 38

//Stepper motor for Y motion (lower)
#define y_pul 36
#define y_dir 34
#define y_ena 32

//Stepper motor for sewing machine 
#define sm_pul 30
#define sm_dir 28
#define sm_ena 26

//Stepper motor for End Effector 
#define ef_pul 23
#define ef_dir 25
#define ef_ena 27

//Servo motor 
#define servo_1 31  //upper servo 
#define servo_2 33  //lower servo 

//Bump Sensors
#define B_X1  53 //0
#define B_X2  47 //end
#define B_Y1  49 //0
#define B_Y2  51 //end

//colour Sensor 
#define cs_s0 37
#define cs_s1 39
#define cs_s2 41
#define cs_s3 43
#define cs_out  45

//LED bed
#define led_r 3
#define led_g 4
#define led_b 5

//force sensor 
#define f_pin A15 

//Constant Values
#define data_size 8

#define XRange  600 //in mm 
#define YRange  326 //in mm 
#define mmStep 40 //number of steps for 1 mm movement 
 
//Define both Stepper motors 
AccelStepper stepperX(1,x_pul,x_dir); 
AccelStepper stepperY(1,y_pul,y_dir); 
Servo upperServo, lowerServo;



void CheckCommand(char data_proc[data_size]);
void StepperSetup(void);
void MoveStepperX(char pos[]);
void MoveStepperY(char pos[]);
void Ready();
void Busy();
void RunMotors();
void ReportError();
void MoveBoth(char val[]);
boolean ReadButton(char val[]);



void setup()
{
  Serial.begin(115200);
  Serial.println("Power On");
  Ready();
  StepperSetup();
  pinMode(B_X1, INPUT);
  stepperY.setPinsInverted(true,false,false );
  upperServo.attach(servo_1);
  lowerServo.attach(servo_2);
  upperServo.write(0);
  lowerServo.write(0);
  
}

void loop()
{
  if (Serial.available()>0)
  {
    
    String data_rc = Serial.readString();
    char command[data_size]  ;
    data_rc.toCharArray(command , data_size);
    
    CheckCommand(command);  
  }
}








