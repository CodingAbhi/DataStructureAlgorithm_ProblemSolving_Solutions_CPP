#include<stdio.h>
void main()
{
 int op;
 int countAlphabets = 0;
 int countNumbers = 0;
 int countLines = 0;
 int countSpaces = 0;
 int countSChars = 0;
 FILE *fp;
 char ch;
 fp = fopen("C:/Users/Asus/Desktop/textabc.txt","r");
 printf("Select Option: \n");
 printf("1. Count no. of alphabets\n");
 printf("2. Count no. of numbers\n");
 printf("3. Count no. of special characters\n");
 printf("4. Count no. of spaces\n");
 printf("5. Count no. of lines\n");
 scanf("%d",&op); 
while((ch = getc(fp))!=EOF)
 {
 if((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z'))
 countAlphabets++;
 else if(ch >= '0' && ch <= '9')
 countNumbers++;
 else if(ch == ' ')
 countSpaces++;
 else if(ch == '\n')
 countLines++;
 else
 countSChars++;
 }
 countLines++; 
if(op == 1)
 printf("No. of Alphabets : %d",countAlphabets);
 else if(op == 2)
 printf("No. of Numbers : %d",countNumbers);
 else if(op == 3)
 printf("No. of Special Characters : %d",countSChars);
 else if(op == 4)
 printf("No. of Spaces : %d",countSpaces);
 else if(op == 5)
 printf("No. of Lines : %d",countLines);
 else
 printf("Wrong Option");
 fclose(fp);
} 
