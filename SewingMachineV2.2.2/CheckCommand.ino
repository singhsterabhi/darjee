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

      case 'C': 
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

      case 'M': MoveLowerServo(value);
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

