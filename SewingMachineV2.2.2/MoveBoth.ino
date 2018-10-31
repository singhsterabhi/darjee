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
