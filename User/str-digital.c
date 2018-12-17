unsigned int StrToDigital(char *digit) /*-----字符串转化为数字-----*/
{
 unsigned int num = 0;

 while(*digit != '\0')
 {
  if(*digit >= '0' && *digit <= '9')
     {
      num = num * 10 + (*digit - '0');
      digit++;
     }              
     else
     {
      num = 0;
      break;
     }
    }
 return(num);
}


