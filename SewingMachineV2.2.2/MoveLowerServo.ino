void MoveLowerServo(char val[])
{
  int angle = atoi(val);
  
  if (val[0]=='C')
  {
    Serial.println(lowerServo.read());
  }
  else 
  {
    lowerServo.write(angle);
  }
  /*else if (val[0]=='F')
  {
    char v[] = {val[1],val[2],val[3],'\0'};
    X_Step = atoi(v);
    stepperX.move(X_Step*mmStep);
    RunMotors();
  }
  
  else if (val[0]=='B')
  {
    char v[] = {val[1],val[2],val[3],'\0'};
    X_Step = atoi(v);
    stepperX.move(-(X_Step*mmStep));
    RunMotors();
    
  }
  
  else if (val[0]=='H')
  {
      stepperX.setSpeed(-500);
      while ((ReadButton("1")))
      {
       stepperX.runSpeed();
       Busy();
      }
      stepperX.stop();
      stepperX.setCurrentPosition(0);
      stepperX.move(5*mmStep);
  
      RunMotors();
      Ready();    
  }
  else if (val[0]=='E')
  {
      stepperX.setSpeed(500);
      while ((ReadButton("2")))
      {
       stepperX.runSpeed();
       Busy();
      }
      stepperX.stop();
      stepperX.setCurrentPosition(XRange*mmStep);
      stepperX.move(-(5*mmStep));
      RunMotors();
      Ready();    
  }  
  else if ((X_Step>=0)&&(X_Step<=XRange))
  {
    
    Serial.println(X_Step*mmStep);
    stepperX.moveTo(X_Step*mmStep);
    RunMotors();
  }
  
  else
    ReportError();
}*/
}

