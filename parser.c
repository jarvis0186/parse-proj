#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
int isdig(char);
int isletter(char);
void lex(char *);
void parse();
void fail(void);
void keyword(char *);
void myinput(void);
char punc[12]={'#','$', ';', '\'', '\"', ',', ';'}, str[32],in[200], s;
int i=-1, flag=0, r=-1,q2=0,a=0, temp=0, p1=0, o1=0,p2=0,o2=0,p3=0,o3=0,p4=0, o4=0,p5=0, o5=0,p6=0, o6=0,q1=0,flags[10]={0},v=0,w=0 ;
char key[32][10] = {"auto","break","case", "char", "const", "continue", "default", "do","double",
 "else", "enum", "extern", "float", "for", "goto", "if", "int",
 "long", "register", "return", "short", "signed", "static",
"sizeof", "struct", "switch", "typedef", "union", "unsigned", "void", "volatile", "while"};
char oper[9]={'+', '-', '/', '%', '*', '>', '<', '=', '&'},
seps[6]={'{', '}', '[', ']', '(', ')'} , fs[10],id[50], header[20][100],ident[10][50], sp[50],macro[20][100],op[20][100],numb[20][100],pu[20], string[20][100],temps[10][50];
char ar1[100]={"MQSHLBEDVCAYFXG"}, ar2[100]={"897(){};+=*>,\"=&$"}, ar3[100][300]={"Q8\0", "}S{)(9\0","H8", "L9\0", "S;V\0","S}S{B\0", "SA\0",
 "S;E=\0", "D9\0", "D7\0", "DE+\0", "DE-\0", "DE*\0", "DE>\0", "C9\0", "CV,\0", ";)Y\"6\"(\0", "F,\0", "Y9\0", "Y9&\0", "G9\0", "G7\0", "X\0", "XD\0", ")E(\0"};
void push(char *);
void pop();
char stack[100];
int state=0;
int top=-1, top1=-1;
void main(int argc, char* argv[])
{
  char *h;
  h=argv[1];
lex(h);//calling the lexer also stores in the input file as an array while the lexer executes
parse();//compares the stack with start state and every top element of the input array
  }
  //!!!! L-E-X-E-R !!!!

  void lex(char *y)
  {
    printf("\n.......This is the lexical analyser that arranges the tokens.......\n");
    sleep(1);
    FILE *b;
    char f, p,m;
    b=fopen(y, "r");
      while((f=getc(b))!=EOF)//scanning of file till the end
      {
        flag=0;
          if(f=='#')
          {
              //printf("This is a header file:");

              do
              {
              //  printf("%c", f);
                f=getc(b);

              }while(f!='>');
            // printf("%c\n", f);
             f=getc(b);
           }

         if(f=='\"')
           {
             //printf("This is a punctuation:%c\n", f);
            in[++top1]=f;
             //printf("This is an argument:" );
            while((f=getc(b))!='\"')
            {
              //printf("%c", f);
              if(f=='%')
              {
              //  fs[++r]=f;

                f=getc(b);
              //  printf("%c", f);

              }

            }
            in[++top1]='6';
            //printf("\nThis is a punctuation:%c\n",f);
            in[++top1]=f;
           f=getc(b);

          /*  printf("This is a format specifier:");
            for(int z=4; z<6; z++)
            {
              printf("%c", fs[z]);
              fs[z]='\0';
            }
            printf("\n");*///if need be then more of the same loops

            //r=-1;

          }

         if(isletter(f)==1)
          {
            do
            {
                str[++i]=f;
                f=getc(b);

            }while(isletter(f)==1||isdig(f)||f=='_');
            str[++i]='\0';
            i=-1;
            keyword(str);

          }
          if(isdig(f)==1)
          {
            //printf("This is a number:");
            do
            {
            //  printf("%c", f);
              in[++top1]=f;
              f=getc(b);
            } while(isdig(f)==1);
          //printf("\n");
          }

          for(int h=0; h<12; h++)
          {
            if(f==punc[h])
            {
            //printf("This is a punctuation:%c\n", f);
            in[++top1]=f;
            break;
          }
          }

          if(f=='+'||f=='-'||f=='>'||f=='<'||f=='*'||f=='='||f=='&'||f=='!')
          {
            //printf("This is an operator:%c\n", f);
            in[++top1]=f;
            f=getc(b);
            if(isletter(f)==1)
            {
              //printf("This is an identifier:%c\n", f);
              in[++top1]='9';
            }
            else if(isdig(f)==1)
            {
              //printf("This is a number:%c\n", f);
              in[++top1]='7';
            }



            //printf("This is an operator: %c", s);
            for(int k=0; k<8; k++)
            {
            if(f==oper[k])
            {
              //printf("%c", f);
              in[++top1]=f;
            }
            /*else
            {
            printf("This is a punctuation:%c\n", f);
              printf("%c\n", s);
              break;
            }*/
          }
        //  printf("\n");
        }
          for(int v=0; v<12; v++)
          {
            if(f==seps[v])
            {
            //  printf("This is a separator:%c\n", f);
              in[++top1]=f;
              break;
            }
          }
        }
        in[++top1]='$';
        fclose(b);
      //  myinput();
  }
  //!!!!!  P-A-R-S-E-R !!!!!!!
  void parse()
  {
    printf("\n.......Parser begins.......\n");
    sleep(1);
    top1=0;
    stack[++top]='$';
    stack[++top]=ar1[0];
    while(top1!=-1)
    {
    switch(state)
    {
      case 0:if(stack[top]==ar1[0]&&in[top1]=='8')
              {
              pop();
              push(ar3[0]);
              state=1;
              //printf("YAY\n");
              //printf("%c\n", in[0]);
             //printf("%c\n", stack[2]);

              //break;
              }
              else
              fail();
              break;

      case 1: if(stack[top]==in[top1])
              {
                pop();
                top1++;
                //printf("YAY@\n");
                //  break;
              }
              if(stack[top]==ar1[1]&&in[top1]=='9')
              {
                pop();
                push(ar3[1]);
                state=2;
              //  printf("YAY!!!!!\n");
              }
              else fail();
              break;
      case 2:if(stack[top]==in[top1])
              {
              while(stack[top]==in[top1])
              {
                pop();
                top1++;
                //printf("WOHOO!\n");
              }
            }
            else fail();
              if(stack[top]==ar1[2]&&in[top1]=='8')
              {
                pop();
                push(ar3[2]);
                state=3;
                //printf("YIPEEE\n");
              }
             else fail();
              break;
    case 3:   if(stack[top]==in[top1])
              {
                pop();
                top1++;
                //printf("WORKS?!\n");
              }
              if(stack[top]==ar1[3]&&in[top1]=='9')
              {
                pop();
                push(ar3[4]);
                //printf("!AGAIN?!\n");
                if(stack[top]==ar1[8]&&in[top1]=='9')
                {
                  pop();
                  push(ar3[14]);
                  state=4;
                //  printf("AND THIS?!\n");
                }
              }
              else fail();
              break;
  case 4:     if(stack[top]==in[top1])
              {
                pop();
                top1++;
                //printf("PHEW\n");
              }
              if(stack[top]==ar1[9]&&in[top1]==',')
              {
                pop();
                push(ar3[15]);
                state=5;
                //printf("SOTHIS WORKS\n");
              }
              else state=6;
              break;
  case 5:
              if(stack[top]==in[top1])
              {
                    pop();
                    top1++;
                  //  printf("THISPOPS!\n");
              }
              if(stack[top]==ar1[8]&&in[top1]=='9')
              {
                pop();
                push(ar3[14]);
                state=4;
              }
              else fail();
              break;
    case 6:   if(stack[top]==in[top1])
              {
                pop();
                top1++;
                state=7;
                //printf("This shouldnthappen\n%c\n%c\n", stack[top],in[top1]);
              }
            // else fail();
              while(stack[top]==ar1[9]&&in[top1]==';')
              {
                pop();
                state=6;
              }
              break;
    case 7:   if(stack[top]==ar1[2]&&in[top1]=='9')
              {
                pop();
                push(ar3[3]);
                state=8;
                //printf("HELLO BITCH\n");
              }
              else fail();
              break;
    case 8:   if(stack[top]==in[top1])
              {
                  pop();
                  top1++;
                  //printf("STEP BY STEP!!!\n");
              }
              if(stack[top]==ar1[4]&&in[top1]=='(')
              {
                pop();
                push(ar3[6]);
                //printf("AND MAYBE THIS!\n%c\n%c\n", stack[top], in[top1]);
                if(stack[top]==ar1[10]&&in[top1]=='(')
                {
                  pop();
                  push(ar3[16]);
                  state=9;
                  //printf("THIS TOO!!!\n%c\n%c", stack[top], in[top1]);
                }
              }
             else fail();
              break;
    case 9:  if(stack[top]==in[top1])
              {
              while(stack[top]==in[top1])
              {
                //printf("\n%c\n%c", stack[top], in[top1]);
                pop();

                top1++;
                //printf("Just need a count!!\n%c\n%c\n", in[top1], stack[top]);
              }
            }
            else fail();
              if(stack[top]==ar1[11]&&in[top1]==')')
              {
                pop();
                state=9;
                //printf("Jus need to know if this happens!!!\n%c\n%c\n", in[top1], stack[top]);
            //    break;
              }
              else if(stack[top]==ar1[11]&&in[top1]==',')
              {
                pop();
                push(ar3[17]);
                state=11;
              //  printf("DOES THIS GO ANYWHERE!??\n%c\n%c\n", stack[top], in[top1]);
              }
              else state=10;
              break;
  case 10:  if(stack[top]==ar1[2]&&in[top1]=='9')
            {
              state=7;
              //printf("DOES THIS HAPPEN!!!???\n");
            }
            else state=13;
            break;
  case 11:  if(stack[top]==in[top1])
            {
              pop();
              top1++;
              //printf("What about this?!?!\n%c\n%c\n", stack[top], in[top1] );
            }
              else if(stack[top]==ar1[12]&&(in[top1]=='&'||in[top1]=='9'))
            {
              pop();
              push(ar3[19]);
              state=12;
              //printf("AND THIS?!>!?!>\n%c\n%c\n", stack[top], in[top1]);
            }
            else fail();
            break;
  case 12:  if(stack[top]==in[top1])
            {
            while(stack[top]==in[top1])
            {
              pop();
              top1++;
            //  printf("This too!!\n\n%c\n%c\n", stack[top], in[top1]);
            }
          }
            else fail();
            if(stack[top]==ar1[11]&&in[top1]==')')
            {
              pop();
              state=12;
              //printf("Different stuff here\n");
            }
            if(stack[top]==ar1[2]&&in[top1]=='9')
            {
              pop();
              push(ar3[3]);
              state=13;
              //printf("AND AGAIN HERE!!\n");
            }
          // else fail();
            break;
  case 13:  if(stack[top]==in[top1])
            {
              pop();
              top1++;
              //printf("Giving it more tries\n");
            }
            if(stack[top]==ar1[4]&&in[top1]=='=')
            {
              pop();
              push(ar3[7]);
              state=14;
            //  printf("And will keep trying!!!\n%c\n%c\n", stack[top], in[top1]);
            }
            else fail();
            break;
  case 14:  if(stack[top]==in[top1])
            {
            //  printf("%c\n%c\n", stack[top], in[top1]);
              pop();
              top1++;

              //printf("Just more n more!\n%c\n%c\n", stack[top], in[top1]);
            }
            else fail();
            if(stack[top]==ar1[6]&&in[top1]=='9')
            {
              pop();
              push(ar3[8]);
              state=14;
            }
            else if(stack[top]==ar1[7]&&in[top1]=='*')
            {
              pop();
              push(ar3[12]);
              state=14;
            }
            else if(stack[top]==ar1[7]&&in[top1]=='+')
            {
              pop();
              push(ar3[10]);
              state=14;
            }
            else state=15;
            break;
  case 15:  while(stack[top]==ar1[7]&&in[top1]==';')
            {
              pop();
              //printf("How many times does this happen?\n");
            }
            if(stack[top]==in[top1])
            {
              //printf("%c\n%c\n", stack[top], in[top1]);
              pop();
              top1++;
              state=16;
              //printf("Then this should also happen!!!\n%c\n%c\n", stack[top], in[top1]);
            }
            else fail();
            break;
  case 16:  if(stack[top]==ar1[2]&&in[top1]=='8')
            {
              pop();
              push(ar3[2]);
              state=17;
              //printf("If such then this should also work!!\n%c\n%c\n", stack[top], in[top1]);
            }
            else fail();
            break;
  case 17:  if(stack[top]==in[top1])
            {
              pop();
              top1++;
              ///printf("Again should fucking work!\n%c\n%c\n", stack[top], in[top1]);
            }
            if(stack[top]==ar1[3]&&in[top1]=='(')
            {
              pop();
              push(ar3[5]);
              //printf("This should also work then!\n%c\n%c\n", stack[top], in[top1]);
              if(stack[top]==ar1[5]&&in[top1]=='(')
              {
                pop();
                push(ar3[24]);
                state=18;
                //printf("And its all fun!!\n%c\n%c\n", stack[top], in[top1]);
              }
            }
            else fail();
            break;
  case 18:  if(stack[top]==in[top1])
            {
              pop();
              top1++;
              //printf("And idk where am going!\n%c\n%c\n", stack[top], in[top1]);
            }
            if(stack[top]==ar1[6]&&in[top1]=='9')
            {
              pop();
              push(ar3[8]);
              state=19;
              //printf("Am in state fucking 19!!\n%c\n%c\n", stack[top], in[top1]);
            }
            else fail();
            break;
  case 19:  if(stack[top]==in[top1])
            {
              //printf("%c\n%c\n", stack[top], in[top1]);
              pop();
              top1++;
              //printf("bullshit it is!\n%c\n%c\n", stack[top], in[top1]);
            }
            if(stack[top]==ar1[7]&&in[top1]=='>')
            {
              pop();
              push(ar3[13]);
              state=19;
              //printf("bullshit it is again!!!!\n%c\n%c\n", stack[top], in[top1]);
            }
            else if(stack[top]==ar1[6]&&in[top1]=='9')
            {
              pop();
              push(ar3[8]);
              state=19;
              //printf("bullshit it is again!!!!\n%c\n%c\n", stack[top], in[top1]);
            }
            else if(stack[top]==ar1[7]&&in[top1]==')')
            {
              state=20;
              //printf("In the end this should work!\n%c\n%c\n", stack[top], in[top1]);
            }
            else fail();
            break;
  case 20:  while(stack[top]==ar1[7]&&in[top1]==')')
            {
              //printf("%c\n%c\n", stack[top], in[top1]);
              pop();
              //printf("this tooooo!!!!\n%c\n%c\n", stack[top], in[top1]);
            }
            while(stack[top]==in[top1])
            {
              //printf("%c\n%c\n", stack[top], in[top1]);
                pop();
                top1++;
              //  printf("They're same yo!\n%c\n%c\n", stack[top], in[top1]);
            }
            if(stack[top]==ar1[2]&&in[top1]=='9')
            {
              pop();
              push(ar3[3]);
              state=21;
              //printf("This should also work then!\n%c\n%c\n", stack[top], in[top1]);
            }
            else fail();
            break;
  case 21:  if(stack[top]==in[top1])
            {
              pop();
              top1++;
              //printf("y not this?!\n%c\n%c\n", stack[top], in[top1]);
            }
            if(stack[top]==ar1[4]&&in[top1]=='=')
            {
              pop();
              push(ar3[7]);
              state=22;
              //printf("i dont get it!\n%c\n%c\n", stack[top], in[top1]);
            }
           else fail();
            break;
  case 22:  if(stack[top]==in[top1])
            {
              //printf("%c\n%c\n", stack[top], in[top1]);
              pop();
              top1++;
              //printf("This too??\n%c\n%c\n", stack[top], in[top1]);
            }
            if(stack[top]==ar1[6]&&in[top1]=='9')
            {
              pop();
              push(ar3[8]);
              state=22;
              //printf("YAYAYAYAY!!!!!\n%c\n%c\n", stack[top], in[top1]);
            }
            else if(stack[top]==ar1[7]&&in[top1]=='+')
            {
              pop();
              push(ar3[10]);
              state=22;
              //printf("Again a YYAYAYAYAYAYAY!!!\n%c\n%c\n", stack[top], in[top1]);
            }
            else state=23;
            break;
  case 23:  while(stack[top]==ar1[7]&&in[top1]==';')
            {
              pop();
              //printf("Obviously this!!\n%c\n%c\n", stack[top], in[top1]);
            }
            if(stack[top]==in[top1])
            {
              pop();
              top1++;
              //printf("Has to be this!\n%c\n%c\n", stack[top], in[top1]);
            }
            if(stack[top]==ar1[2]&&in[top1]=='9')
            {
              pop();
              push(ar3[3]);
              state=24;
              //printf("How about this guy yo?!\n%c\n%c\n", stack[top], in[top1]);
            }
            else fail();
            break;
  case 24:    if(stack[top]==in[top1])
              {
                //printf("\n%c\n%c\n", stack[top], in[top1]);
                pop();
                top1++;
                //printf("Then it obviously goes in here!\n%c\n%c\n", stack[top], in[top1]);
              }
              if(stack[top]==ar1[4]&&in[top1]=='=')
              {
                pop();
                push(ar3[7]);
                state=24;
              //  printf("case 24 yoyo!\n%c\n%c\n", stack[top], in[top1]);
              }
              else if(stack[top]==ar1[6]&&in[top1]=='9')
              {
                pop();
                push(ar3[8]);
                state=24;
                //printf("case 24 yoyo!\n%c\n%c\n", stack[top], in[top1]);
              }
              else if(stack[top]==ar1[7]&&in[top1]=='+')
              {
                pop();
                push(ar3[10]);
                state=24;
                ///printf("case 24 yoyo!\n%c\n%c\n", stack[top], in[top1]);

              }
              else if(stack[top]==ar1[6]&&in[top1]=='7')
              {
                pop();
                push(ar3[9]);
                state=24;
              //  printf("case 24 yoyo!\n%c\n%c\n", stack[top], in[top1]);

              }
              else state=25;
              break;
case 25:      while(stack[top]==ar1[7]&&in[top1]==';')
              {
                pop();
                //printf("Has to be here yo!\n%c\n%c\n", stack[top], in[top1]);

              }
              if(stack[top]==in[top1])
              {
                pop();
                top1++;
                state=26;
                //printf("And here too!!\n%c\n%c\n", stack[top], in[top1]);

              }
              else fail();
              break;
case 26:      if(stack[top]==ar1[2]&&in[top1]=='}')
              {
                //printf("%c\n%c\n", stack[top], in[top1]);

                pop();
               //printf("Does this happen now!?\n%c\n%c\n", stack[top], in[top1]);
              }
              else if((stack[top]==in[top1])&&(stack[top]!='$'))
              {
              //  printf("%c\n%c\n", stack[top], in[top1]);
                pop();
                top1++;
                state=26;
            //  printf("What about this?!\n%c\n%c\n", stack[top], in[top1]);
              }

              else if(stack[top]=='$')
              state=27;
             else fail();

              break;
case 27:      if(stack[top]=='$'&&in[top1]=='$')
              {
                printf("\n!Parse Ends!\n");
               printf("VALID INPUT\n");
               }
              //else fail();
              top1=-1;
              break;
default:     // printf("Waddup\n");
             continue;
              break;
    }
    }
  }
//ALPHABETS
int isletter(char m)
{
  for(char h='a'; h<='z'; h++)
    {
      if(m==h)
      return 1;
    }
   return 0;
}

//NUMBERS
int isdig(char n)
{
	for(char e='0'; e<='9'; e++)
	if(e==n)
	{
		return 1;
		break;
	}
  return 0;
}
void keyword(char *s)
{

  for(int u=0; u<32; u++)
  {
  while(!strcmp(s, key[u]))
  {
    flag=1;
  //printf("This is a keyword: %s", key[u]);
  break;
}
}
if(flag==1)
{
  in[++top1]='8';
}
if(flag==0)
{
  //printf("This is an identifier: %s", s);
  in[++top1]='9';
}
//printf("\n");
//in[++top]='9';
//return 0;
}



//PUSH AND POP OPERATIONS
void push(char *s)
{
  char temp[100][300];
  int a=0;
  ///top++;
  strcpy(temp[a], s);
  for(int k=0; k<=strlen(temp[0]); k++)
  {

    stack[++top]=temp[a][k];

  //  printf("%c\n", stack[k]);
  }
  top--;
  //for(int k=0; k<=strlen(in); k++)
  //printf("%c\n", in[1]);

  a++;
}

void pop()
{
  top--;
}
void fail()
{
  printf("\n!Parser Ends!\n");
  printf("INVALID INPUT!\n");
  top1=-1;
}
