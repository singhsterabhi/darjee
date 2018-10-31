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
    stepperY.move(Y_Step*mmStep);
    RunMotors();
  }
  
  else if (val[0]=='B')
  {
    char v[] = {val[1],val[2],val[3],'\0'};
    Y_Step = atoi(v);
    stepperY.move(-(Y_Step*mmStep));
    RunMotors();
    
  }
  else if (val[0]=='H')
  {
      stepperY.setSpeed(-500);
      while ((ReadButton("3")))
      {
       stepperY.runSpeed();
       Busy();
      }
      stepperY.stop();
      stepperY.setCurrentPosition(0);
      stepperY.move(5*mmStep);
  
      RunMotors();
      Ready();    
  }
  else if (val[0]=='E')
  {
      stepperY.setSpeed(500);
      while ((ReadButton("4")))
      {
       stepperY.runSpeed();
       Busy();
      }
      stepperY.stop();
      stepperY.setCurrentPosition(YRange*mmStep);
      stepperY.move(-(5*mmStep));
      RunMotors();
      Ready();    
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
