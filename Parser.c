#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#define SIZE 100000
struct ele1
{
    int ln;
    char str[30];
};
struct ele1 stack1[500];
int top1=-1;
struct string1
{
    int line;
    char no[20];
};
struct string2
{
    int line;
    char yes[20];
};
int flag=0,fl=0,rootDetect=0,rootLineNo,lastLineNo,fla=0;
char rootOpen[20];
int k=0,k1=0,okRule;
struct string1 str1[500];
struct string2 str2[500];
int top=-1;
//char stack[SIZE];
struct ele
{
    int line;
    char s;
};
struct ele stack[SIZE];
void pop();
void push(char item,int no);
void StringAnalyser();
void StringAnalyserTag();
//void slashAnalyser();
void poper(char str[],int no);
void pusher(char st[],int no);
void CharAnalyser(char element[],int LineNo);
void RootAnalyser();
struct XMLDOC
{
    char source[SIZE];
}doc;
int main()
{ 

    //opening the xml file
    FILE *fp;
    fp = fopen("TheFile.xml","r"); 
    if (fp==NULL)
    {
        printf("CouldNot load file");
    }
    //setting the read cursor to the end of the file
    fseek(fp,0,SEEK_END);
    //to find the size of the file
    int size = ftell(fp);
    //set the read cursor to the start of the file 
    fseek(fp,0,SEEK_SET);
    int count = fread(doc.source,sizeof(char),size,fp);//read the file content to the char pointer doc.source
    int len = strlen(doc.source);
    doc.source[len+1]='\0';
    fclose(fp);
    printf("The XML code is..\n");
    printf("%s",doc.source);
    printf("\nThe no of Elemnts read = ");
    printf("%d\n",count);
    
    
    StringAnalyserTag();
    

    StringAnalyser();
   
        
    
    
    
    
        
       if (top1>=-1)
        {
     
            for (int i = 0; i <=top1; i++)
            {
                fla=1;
                printf("\nLine No : %d -> Tag <%s> do not have matching </CLOSE> tag",stack1[i].ln,stack1[i].str);
            }
        }
        
        if (fla!=1)
        {
            if (rootLineNo!=lastLineNo)
            {
                printf("\nError : Root element not Found");
            }
            else if(flag==0)
            {
                printf("\nSuccessfully Compiled..NO ERRORS");
            }
            
        }
        
    
    //printf("\n%d\n",top1);
   //printf("\nRoot = %s",rootOpen);
}
void poper(char str3[],int no)
{
    
        if (top1==-1)
        {
            fla=1;
            printf("\nLine No : %d -> Tag </%s> do not have matching <OPEN> tag\n",no,str3);
            fl=1;
        }
        else
        {
            
            
            int i=0,f=0;
            for (i = 0; i <= top1; i++)
            {
            
                int val = strcmp(str3,stack1[i].str);
                if (val==0)
                {
                
                    f=1;
                    break;
                }
            }
            /*int val1 = strcmp(str3,stack1[top1].str);
            if (f==1 && val1!=0)//venel mati
            {
                    printf("\nokRUle : %d",okRule);
                    fl=1;
                    printf("\nLine No : %d -> The closing Tag of <%s> should be in place of <%s>",no,stack1[i].str,stack1[i+1].str);
                    //top1--;
                
            }//venel mati*/
            
            if (f==0)
            {
                fla=1;
                printf("\nLine No : %d -> Tag </%s> do not have matching <OPEN> tag",no,str3);
                fl=1;
            }
            else
            {
                lastLineNo = stack1[i].ln;
                if (top1==i)
                {
                    top1--;
                }
                else
                {
                    for (i;i <top1;i++)
                    {
                        stack1[i] = stack1[i+1];
                    }
                    top1--;
                }
            }     
    
        }
        
        
           
}
void pusher(char st[],int num)
{
    
    if (top1>=SIZE-1)
    {
        printf("Stack overflow");
    }
    else
    {
        if (top1==-1)
        {
            top1++;
            strcpy(stack1[top1].str,st);
            stack1[top1].ln = num;
        }
        else
        {
            top1++;
            strcpy(stack1[top1].str,st);
            stack1[top1].ln = num;
        }
        
    }
}
void StringAnalyser()
{
    int i=0,j=0,k1=0,lnNo=1,y1=0,y=0;
    while (doc.source[i]!='\0')
    {
        if (doc.source[i]=='\n')
        {
            lnNo++;
        }
        
        if (doc.source[i]=='<')
        {
            int check=0;
            if (doc.source[i+1]!='/')
            {
                if (doc.source[i+1]=='>')
                {
                    printf("\nLine No : %d -> invalid tag <>",lnNo);
                }
                else
                {
                    if (doc.source[i+1]==' ')
                    {
                        i++;
                        check=1;
                        printf("cool");
                        
                    }
                    else
                    {
                        check=0;
                    }
                    
                    
                    i++;
                    while (doc.source[i]!='>' && doc.source[i]!=' ')
                    {
                        str1[k1].line=lnNo;
                        str1[k1].no[y1] = doc.source[i];
                        i++;
                        y1++;
                    }
                    if (check==1)
                    {
                        printf("Line No : %d -> space not allowed at begginning of Tag %s",lnNo,str1[k1].no);
                        k1++;
                        y1=0;
                        fla=1;
                        i++;
                        continue;
                    }
                    
                    CharAnalyser(str1[k1].no,lnNo);
                    if (okRule!=3)
                    {
                        if (rootDetect==0)
                        {
                            strcpy(rootOpen,str1[k1].no);
                            rootLineNo = lnNo;
                            rootDetect=1;
                        }
                        
                        pusher(str1[k1].no,lnNo);
                        
                    }
                    
                    k1++;
                    y1=0;
                }
                

            }else
            {
                if (doc.source[i+2]=='>')
                {
                    printf("\nLine No : %d -> invalid tag </>",lnNo);
                }
                else
                {
                    i=i+2;
                    int check1=0;
                    while (doc.source[i]!='>')
                    {
                        str2[k].line=lnNo;
                        str2[k].yes[y] = doc.source[i];
                        i++;
                        y++;
                        if (doc.source[i]=='\n' || doc.source[i]=='<' || doc.source[i]==' ')
                        {
                        check1 = 1;
                        fla=1;
                        printf("\nLine No : %d -> Invalid </CLOSE> Tag %s",lnNo,str2[k].yes);
                        break;
                        }else
                        {
                            check1=0;
                        }
                        
                        
                        

                    }
                    CharAnalyser(str2[k].yes,lnNo);
                    if (okRule!=3 && check1==0)
                    {
                        poper(str2[k].yes,lnNo);
                    }
                    
                    
                    k++;
                    y=0;
                }
                
                
                    
            }
     
        }
        i++;
    }
      
    
    
}
/*void slashAnalyser()
{
     int i=0,lineNo=0;
     int count_o=0,count_s=0;

        while (doc.source[i]!='\0')
        {
           if (doc.source[i]=='<')
            {

                count_o++;  
                if (doc.source[i+1]=='/')
                {
                    count_s++;
                } 

            }
            i++;     
        }
            if((count_o/2)!=count_s)
            {
                printf("\n '/' missing\n "); 
                
            } 

}*/
void StringAnalyserTag()
{
    int i=0,lineNo=1;
        while (doc.source[i]!='\0')
        {
            if (doc.source[i]=='\n')
            {
                lineNo++;
            }
            
           if (doc.source[i]=='<')
            {

                 push(doc.source[i],lineNo);
                 

            }
            else if (doc.source[i]=='>')
            {   
                if (stack[top].s == '<' && stack[top].line==lineNo)
                {
                    pop(); 
                }
                else
                {
                    flag = 1;
                    printf("\nLine No : %d -> Tag not closed '<' missing",lineNo);
                }
                
            }
            i++;   
        }
        if (top!=-1)
        {
            flag=1;
            for (int i = 0; i <= top; i++)
            {
                printf("\nLine No : %d -> Tag not closed '>' missing",stack[i].line);
            }
            
        }
        
       
}
void pop()
{
    if (top==-1)
    {
        printf("stack underflow");
    }
    else
    {
        top--;
    }
    
    
        
}
void push(char item,int no)
{
    if (top>=SIZE-1)
    {
        printf("Stack overflow");
    }
    else
    {
        if (top==-1)
        {
            top++;
            stack[top].s = item;
            stack[top].line = no;
        }
        else
        {
            top++;
            stack[top].s=item;
            stack[top].line = no;
        }
        
    }
}
void CharAnalyser(char element[],int LineNo)
{
    if (element[0]=='_' || ((element[0] >= 'a' && element[0] <= 'z') || (element[0] >= 'A' && element[0] <= 'Z')))
    {
        okRule = 2;
    }
    else
    {
        printf("\nLine No : %d -> Tag <%s> not allowed",LineNo,element);
        flag=1;
        okRule = 3;
    }
    
    
}
