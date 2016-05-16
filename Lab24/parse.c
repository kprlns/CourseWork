#include <stdio.h>

typedef struct elem
{
    char op;
    int val;
}elem;

/*______________________Для стэка______________________*/
/******************************************************/
int priority(char a)
{
    if(a=='(') return 1;
    if(a=='+') return 2;
    if(a=='-') return 2;
    if(a=='*') return 3;
    if(a=='/') return 3;
    if(a=='^') return 4;
    return 0;
}

/*
typedef struct stack
{
    elem l;
    stack* next;
}stack;

stack push(stack* s, char x, int v)
{
    stack* new=(stack*)malloc(sizeof(stack))
    new->l->oper=x;
    new->l->val=v;
    new->next=s;
    return new;
}

elem top(stack* s)
{
    return(s->l);
}

elem pop(stack* s)
{
    elem e;
    e.oper=s->l->oper;
    e.value=s->l->value;

    if(s->next!=NULL)
    {
        stack* del=s;
        s=s->next;
        free(del);
    }
    else
    {
        s->l=NULL;
    }
    return e;
}

int empty(stack* s)
{
    if(s->l==NULL && s->next==NULL) return 1;
    return 0;
}
*/

 /*****************************************************/
/*___________________________________________________*/

  /*____________________Для парсинга____________________*/
 /******************************************************/
int isoper(char a)
{
    if(a=='+' || a=='-' || a=='/' || a=='*' || a=='^' ) return 1;
    return 0;
}

int isopen(char a)
{
    if(a=='(') return 1;
    return 0;
}

int isclose(char a)
{
    if(a==')') return 1;
    return 0;
}

int isnum(char a)
{
    if( a>=48 && a<=57 ) return 1;
    return 0;
}

int istemp(char a)
{
    if(a>=65 && a<=90) return 1;
    if(a>=97 && a<=122) return 1;
    return 0;
}
 /******************************************************/
/*____________________________________________________*/
int main()
{
    char input[100];
    elem output[100];
    scanf("%s",input);
    int cnt=0;
int open=0, close=0; int count=0;
    for(int i=0;input[i+1]!='\0';i++)
    {count=i;
        if(isopen(input[i]))
        {open++; printf("1");
            if( !(input[i+1]=='-' || isnum(input[i+1]) || istemp(input[i+1]) || isopen(input[i+1]))  ) {printf("Wrong input\n"); return 0;}
            continue;
        }
        if(isclose(input[i]))
        {close++; printf("2");
            if( !(isoper(input[i+1]) || isclose(input[i+1]) || isnum(input[i+1]) || istemp(input[i+1])) ) {printf("Wrong input\n"); return 0;}
            continue;
        }
        if(isoper(input[i]))
        {printf("3");
            if( isclose(input[i+1]) ) {printf("Wrong input\n"); return 0;}
            continue;
        }
        if(isnum(input[i]))
        {printf("4");
            if( istemp(input[i+1]) || isopen(input[i+1]) ) {printf("Wrong input\n"); return 0;}
            continue;
        }
        if(istemp(input[i]))
        {printf("5");
            if( istemp(input[i+1]) ) {printf("Wrong input, name of variables must consist of 1 char"); return 0;}
            if( isnum(input[i+1]) || isopen(input[i+1]) ) {printf("Wrong input\n"); return 0;}
            continue;
        }

    }
    if(isclose(input[count+1])) close++;
    if(isopen(input[count])) {printf("Wrong input, name of variables must consist of 1 char"); return 0;}
    printf("%d  %d",open, close);
if(open!=close) {printf("Wrong input\n"); return 0;}
    for (int i=0;input[i]!='\0';i++)
    {printf("\n%d\n",i);
        if(i==0)
        {
            if(istemp(input[i]))
            {
                output[cnt].op=input[i];
                cnt++;
                continue;
            }
                if( isnum(input[i]) )
                {
                    int res=0;
                    while(isnum(input[i]))
                    {
                        res*=10;
                        res+=(input[i]-'0');
                        i++;
                    }
                    output[cnt].op='?';
                    output[cnt].val=res; cnt++;
                    i--; continue;
                }
                if( input[i]=='-' )
                {
                    i++;
                    if( isnum(input[i]) )
                    {
                        int res=0;
                        while(isnum(input[i]))
                        {
                            res*=10;
                            res+=(input[i]-'0');
                            i++;
                        }
                        output[cnt].op='?';
                        output[cnt].val=(-1)*res; cnt++;
                        i--; continue;
                    }
                    if(istemp(input[i]))
                    {
                        output[cnt].op=input[i];
                        cnt++;
                        continue;
                    }

                }

                if( input[i]!='-' && !isopen(input[i]) ) {printf("Wrong input\n"); return 0;}
        }



        if(input[i]=='(') {output[cnt].op='('; cnt++; continue;}
        if(input[i]==')') {output[cnt].op=')'; cnt++; continue;}

        if(  (isnum(input[i-1]) || istemp(input[i-1])) && input[i]=='/' && (isnum(input[i+1]) || istemp(input[i+1]) ) ) {output[cnt].op='/'; cnt++; continue;}
        if(  (isnum(input[i-1]) || istemp(input[i-1])) && input[i]=='/' && isopen(input[i+1]) )                         {output[cnt].op='/'; cnt++; continue;}
        if(                        isclose(input[i-1]) && input[i]=='/' && (isnum(input[i+1]) || istemp(input[i+1])) )  {output[cnt].op='/'; cnt++; continue;}
        if(                        isopen(input[i+1])  && input[i]=='/' && isclose(input[i-1]))                         {output[cnt].op='/'; cnt++; continue;}
        if(  (isnum(input[i-1]) || istemp(input[i-1])) && input[i]=='/' && input[i+1]=='-' )                            {output[cnt].op='/'; cnt++; continue;}
        if(                       isclose(input[i-1])  && input[i]=='/' && input[i+1]=='-' )                            {output[cnt].op='/'; cnt++; continue;}

        if(  (isnum(input[i-1]) || istemp(input[i-1])) && input[i]=='*' && (isnum(input[i+1]) || istemp(input[i+1])) )  {output[cnt].op='*'; cnt++; continue;}
        if(  (isnum(input[i-1]) || istemp(input[i-1])) && input[i]=='*' && isopen(input[i+1]) )                         {output[cnt].op='*'; cnt++; continue;}
        if(                        isclose(input[i-1]) && input[i]=='*' && (isnum(input[i+1]) || istemp(input[i+1])) )  {output[cnt].op='*'; cnt++; continue;}
        if(                        isopen(input[i+1])  && input[i]=='*' && isclose(input[i-1]))                         {output[cnt].op='*'; cnt++; continue;}
        if(  (isnum(input[i-1]) || istemp(input[i-1])) && input[i]=='*' && input[i+1]=='-' )                            {output[cnt].op='*'; cnt++; continue;}
        if(                       isclose(input[i-1])  && input[i]=='*' && input[i+1]=='-' )                            {output[cnt].op='*'; cnt++; continue;}


        if(  (isnum(input[i-1]) || istemp(input[i-1])) && input[i]=='+' && (isnum(input[i+1]) || istemp(input[i+1])) )  {output[cnt].op='+'; cnt++; continue;}
        if(  (isnum(input[i-1]) || istemp(input[i-1])) && input[i]=='+' && isopen(input[i+1]) )                         {output[cnt].op='+'; cnt++; continue;}
        if(                        isclose(input[i-1]) && input[i]=='+' && (isnum(input[i+1]) || istemp(input[i+1])) )  {output[cnt].op='+'; cnt++; continue;}
        if(                        isopen(input[i+1])  && input[i]=='+' && isclose(input[i-1]))                         {output[cnt].op='+'; cnt++; continue;}
        if(  (isnum(input[i-1]) || istemp(input[i-1])) && input[i]=='+' && input[i+1]=='-' )                            {output[cnt].op='+'; cnt++; continue;}
        if(                       isclose(input[i-1])  && input[i]=='+' && input[i+1]=='-' )                            {output[cnt].op='+'; cnt++; continue;}


        if(  (isnum(input[i-1]) || istemp(input[i-1])) && input[i]=='-' && (isnum(input[i+1]) || istemp(input[i+1])) )  {output[cnt].op='-'; cnt++; continue;}
        if(  (isnum(input[i-1]) || istemp(input[i-1])) && input[i]=='-' && isopen(input[i+1]) )                         {output[cnt].op='-'; cnt++; continue;}
        if(                        isclose(input[i-1]) && input[i]=='-' && (isnum(input[i+1]) || istemp(input[i+1])) )  {output[cnt].op='-'; cnt++; continue;}
        if(                        isopen(input[i+1])  && input[i]=='-' && isclose(input[i-1]))                         {output[cnt].op='-'; cnt++; continue;}
        if(  (isnum(input[i-1]) || istemp(input[i-1])) && input[i]=='-' && input[i+1]=='-' )                            {output[cnt].op='-'; cnt++; continue;}
        if(                       isclose(input[i-1])  && input[i]=='-' && input[i+1]=='-' )                            {output[cnt].op='-'; cnt++; continue;}


        if(  (isnum(input[i-1]) || istemp(input[i-1])) && input[i]=='^' && (isnum(input[i+1]) || istemp(input[i+1])) )  {output[cnt].op='^'; cnt++; continue;}
        if(  (isnum(input[i-1]) || istemp(input[i-1])) && input[i]=='^' && isopen(input[i+1]) )                         {output[cnt].op='^'; cnt++; continue;}
        if(                        isclose(input[i-1]) && input[i]=='^' && (isnum(input[i+1]) || istemp(input[i+1])) )  {output[cnt].op='^'; cnt++; continue;}
        if(                         isopen(input[i-1]) && input[i]=='^' && isclose(input[i+1]))                         {output[cnt].op='^'; cnt++; continue;}
        if(  (isnum(input[i-1]) || istemp(input[i-1])) && input[i]=='^' && input[i+1]=='-' )                            {output[cnt].op='^'; cnt++; continue;}
        if(                        isclose(input[i-1]) && input[i]=='^' && input[i+1]=='-' )                            {output[cnt].op='^'; cnt++; continue;}

        if( (isoper(input[i-1]) || isopen(input[i-1])) && input[i]=='-' && isnum(input[i+1]) )
        {
            int res=0;
            i++;
            while(isnum(input[i]))
            {
                res*=10;
                res+=(input[i]-'0');
                i++;
            }
            output[cnt].op='?';
            output[cnt].val=(-1)*res; cnt++;
            i--; continue;

        }

        if( (isoper(input[i-1]) || isopen(input[i-1])) && input[i]=='-' && istemp(input[i+1]) )
        {
            output[cnt].op='(';
            cnt++;
            output[cnt].op='?';
            output[cnt].val=0;
            cnt++;
            output[cnt].op='-';
            cnt++;
            output[cnt].op=input[i+1];
            cnt++;
            output[cnt].op=')';
            cnt++;
            i++; continue;
        }

        if( (isopen(input[i-1]) || isoper(input[i-1])) && isnum(input[i]) )
        {
            int res=0;
            while(isnum(input[i]))
            {
                res*=10;
                res+=(input[i]-'0');
                i++;
            }
            output[cnt].op='?';
            output[cnt].val=res; cnt++;
            i--; continue;

        }

        if( (isopen(input[i-1]) || isoper(input[i-1])) && istemp(input[i]) )
        {
                output[cnt].op=input[i];
                cnt++;
                continue;
        }

        if( isopen(input[i-2]) && input[i-1]=='-' && isnum(input[i]) )
        {
            int res=0;
            while(isnum(input[i]))
            {
                res*=10;
                res+=(input[i]-'0');
                i++;
            }
            output[cnt].op='?';
            output[cnt].val=(-1)*res; cnt++;
            i--; continue;
        }

        if( isoper(input[i-2])&& input[i-1]=='-' && isnum(input[i]) )
        {
            int res=0;
            while(isnum(input[i]))
            {
                res*=10;
                res+=(input[i]-'0');
                i++;
            }
            output[cnt].op='?';
            output[cnt].val=(-1)*res; cnt++;
            i--; continue;

        }

        if( isoper(input[i-2]) && input[i-1]=='-' && istemp(input[i]) )
        {
            output[cnt].op='(';
            cnt++;
            output[cnt].op='?';
            output[cnt].val=0;
            cnt++;
            output[cnt].op='-';
            cnt++;
            output[cnt].op=input[i+1];
            cnt++;
            output[cnt].op=')';
            cnt++;
            i++; continue;
        }


        if( (isnum(input[i-1]) || istemp(input[i-1]) || isclose(input[i-1])) && isoper(input[i]) && (input[i+1]=='-') )
        {
            continue;
        }


        printf("Error, wrong input\n"); return 0;
    }
    printf("\nExpression was parsed. Print parsed version?[Y/n]\n");
    char c[3];
    scanf("%s",c);
    if(c[0]=='Y' || c[0]=='y')
    {
        for(int i=0;i<cnt;i++)
        {
            if(output[i].op=='?') printf("%d ",output[i].val);
            else printf("%c ",output[i].op);

        }
    }
    elem new[100];
    char stack[100];
    int stack_cnt=0;
    int new_cnt=0;
    for(int i=0;i<cnt;i++)
    {
        if(output[i].op=='?' || istemp(output[i].op))
        {
            new[new_cnt].op=output[i].op;
            if(output[i].op=='?') new[new_cnt].val=output[i].val;
            new_cnt++;
            continue;
        }
        if(output[i].op=='(')
        {
            stack[stack_cnt]='(';
            stack_cnt++;
            continue;
        }

        if(isoper(output[i].op))
        {
            if( (priority(output[i].op)<=priority(stack[stack_cnt-1])) && stack_cnt!=0)
            {
                new[new_cnt].op=stack[stack_cnt-1];
                new_cnt++;
                stack[stack_cnt-1]=output[i].op;
                continue;
            }
            if(priority(stack[stack_cnt])<priority(output[i].op))
            {
                stack[stack_cnt]=output[i].op;
                stack_cnt++;
                continue;
            }
            if(!stack_cnt)
            {
                stack[stack_cnt]=output[i].op;
                stack_cnt++;
            }
        }

        if(isclose(output[i].op))
        {
            while(stack_cnt>0 && stack[stack_cnt-1]!='(')
            {
                new[new_cnt].op=stack[stack_cnt-1];
                new_cnt++;
                stack_cnt--;
            }
            if(stack_cnt) stack_cnt--;

        }

    }
    while(stack_cnt>0)
    {
        new[new_cnt].op=stack[stack_cnt-1];
        new_cnt++;
        stack_cnt--;
    }
    printf("\nExpression was brought to postfix form. Print new version?[Y/n]\n");
    char cc[3];
    scanf("%s",cc);
    if(cc[0]=='Y' || cc[0]=='y')
    {
        for(int i=0;i<new_cnt;i++)
        {
            if(new[i].op=='?') printf("%d ",new[i].val);
            else printf("%c ",new[i].op);

        }
    }
}
