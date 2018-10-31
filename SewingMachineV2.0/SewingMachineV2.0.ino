#include <AccelStepper.h>

#define data_size 8

#define stepperX_pul 9
#define stepperX_dir 8
#define stepperY_pul 7
#define stepperY_dir 6
#define B1Pin 2

#define ReadyString "ready"
#define BusyString "busy"
#define ErrorString "error"

#define XRange  500 
#define YRange  400

#define mmStep 40 
 
AccelStepper stepperX(1,stepperX_pul,stepperX_dir); 
AccelStepper stepperY(1,stepperY_pul,stepperY_dir); 


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
  pinMode(B1Pin, INPUT);
  
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

void StepperSetup()
{
  stepperX.setMaxSpeed(500);
  stepperX.setAcceleration(400);
  stepperX.setMinPulseWidth(100);
  stepperX.setCurrentPosition(0);

  stepperY.setMaxSpeed(500);
  stepperY.setAcceleration(400);
  stepperY.setMinPulseWidth(100);
  stepperY.setCurrentPosition(0);
}

void Ready(void)
{
  Serial.println(ReadyString);
}

void ReportError(void)
{
  Serial.println(ErrorString);
}

void Busy()
{
  Serial.println(BusyString);
}

void MoveStepperX(char val[])
{
  
  int X_Step = atoi(val);
  
  if (val[0]=='C')
  {
    Serial.println(stepperX.currentPosition()/mmStep);
  }
  
  else if (val[0]=='F')
  {
    char v[] = {val[1],val[2],val[3],'\0'};
    X_Step = atoi(v);
    if ((stepperX.currentPosition()/mmStep)+(X_Step) <=XRange)
    {
      stepperX.moveTo(stepperX.currentPosition()+X_Step*mmStep);
      RunMotors();
    }
    else 
      ReportError();
    
  }
  
  else if (val[0]=='B')
  {
    char v[] = {val[1],val[2],val[3],'\0'};
    X_Step = atoi(v);
    if ((stepperX.currentPosition()/mmStep)-(X_Step) >=0)
    {
      stepperX.moveTo(stepperX.currentPosition()-X_Step*mmStep);
      RunMotors();
    }
    else 
      ReportError();
    
  }
    
  else if ((X_Step>=0)&&(X_Step<=XRange))
  {
    
    Serial.println(X_Step*mmStep);
    stepperX.moveTo(X_Step*mmStep);
    RunMotors();
  }
  
  else
    ReportError();
}

void MoveStepperY(char val[])
{
  
  int Y_Step = atoi(val);
  
  if (val[0]=='C')
  {
    Serial.println(stepperY.currentPosition()/mmStep);
  }
  
  else if (val[0]=='F')
  {
    char v[] = {val[1],val[2],val[3],'\0'};
    Y_Step = atoi(v);
    if ((stepperY.currentPosition()/mmStep)+(Y_Step) <=YRange)
    {
      stepperY.moveTo(stepperY.currentPosition()+(Y_Step*mmStep));
      RunMotors();
    }
    else 
      ReportError();    
  }
  
  else if (val[0]=='B')
  {
    char v[] = {val[1],val[2],val[3],'\0'};
    Y_Step = atoi(v);
    if ((stepperY.currentPosition()/mmStep)-(Y_Step) >=0)
    {
      stepperY.moveTo(stepperY.currentPosition()-Y_Step*mmStep);
      RunMotors();
    }
    else 
      ReportError();
    
  }
    
  else if ((Y_Step>=0)&&(Y_Step<=XRange))
  {
    
    Serial.println(Y_Step);
    stepperY.moveTo(Y_Step*mmStep);
    RunMotors();
    
  }
  
  else
    ReportError();
}

void MoveBoth(char val[])
{
  char X_val[] = {val[0],val[1],val[2],'\0'};
  char Y_val[] = {val[3],val[4],val[5],'\0'}; 
  Serial.println(X_val);
  Serial.println(Y_val);
  int X_Step = atoi(X_val);
  int Y_Step = atoi(Y_val);
  
  if ((X_Step>=0)&&(X_Step<=XRange))
  {
    Serial.println(X_Step);
    stepperX.moveTo(X_Step*mmStep);
  }
  else  
    ReportError();

  if ((Y_Step>=0)&&(Y_Step<=XRange))
  {
    Serial.println(Y_Step);
    stepperY.moveTo(Y_Step*mmStep);
  }
  else  
    ReportError();
    
    
  RunMotors();
}

void HomeX()
{
  stepperX.setSpeed(-500);
  while (!(ReadButton("1")))
  {
    stepperX.runSpeed();
    Busy();
  }
  stepperX.stop();
  stepperX.setCurrentPosition(0);
  stepperX.moveTo(200);
  
  RunMotors();
  Ready();
}

void RunMotors(void)
{  
  
  while ((stepperX.targetPosition()!=stepperX.currentPosition())||(stepperY.targetPosition()!=stepperY.currentPosition()))
  {
    stepperX.run();
    stepperY.run();
    Busy();
  }
  Serial.println("Reached");
  Serial.println(stepperX.currentPosition()/mmStep);
  Serial.println(stepperY.currentPosition()/mmStep);
  Ready();
}

boolean ReadButton(char val[])
{
  int b_no = atoi(val);
  boolean answer; 
  switch(b_no)
  {
    case 1: if(digitalRead(B1Pin))
              answer =  true;
            else 
              answer =  false;
            break;

    default: ReportError();
             break;
  }
  
  return answer;
}

void CheckCommand(char data_proc[data_size])
{
    char com_type = data_proc[0];
    char value[data_size-1];
    for (int i=0 ; i<(data_size-2); i++)
    {
      value[i] = data_proc[i+1] ;
    }
    value[data_size-2] = '\0';
    switch(com_type)
    {
      case 'A': Ready();
              break;

      case 'B': Serial.println(ReadButton(value));    
              break;

      case 'C': HomeX();
              break;

      case 'D':
              break;

      case 'E':
              break;

      case 'F':
              break;

      case 'G':
              break;

      case 'H':
              break;

      case 'I':
              break;

      case 'J':
              break;

      case 'K':
              break;

      case 'L':
              break;

      case 'M':
              break;

      case 'N':
              break;                                                                                                                                                                                      
              
      case 'O': Serial.println(value);
                MoveBoth(value);
              break;

      case 'P':
              break;

      case 'Q':
              break;

      case 'R':
              break;

      case 'S':
              break;

      case 'T':
              break;

      case 'U':
              break;

      case 'V':
              break;

      case 'W':
              break;

      case 'X': MoveStepperX(value);
              break;

      case 'Y': MoveStepperY(value);
              break;

      case 'Z':
              break;                                                                                                                                                                
    
    }
}

