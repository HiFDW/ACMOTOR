unsigned int StrToDigital(char *digit) /*-----�ַ���ת��Ϊ����-----*/
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


