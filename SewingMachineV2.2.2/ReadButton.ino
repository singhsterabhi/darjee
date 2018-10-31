boolean ReadButton(char val[])
{
  int b_no = atoi(val);
  boolean answer; 
  
  switch(b_no)
  {
    case 1: if(digitalRead(B_X1))
              answer =  true;
            else 
              answer =  false;
            break;
            
    case 2: if(digitalRead(B_X2))
              answer =  true;
            else 
              answer =  false;
            break;
    
    case 3: if(digitalRead(B_Y1))
              answer =  true;
            else 
              answer =  false;
            break;
            
    case 4: if(digitalRead(B_Y2))
              answer =  true;
            else 
              answer =  false;
            break;
                   
    default: ReportError();
             break;
  }
  
  return answer;
}
