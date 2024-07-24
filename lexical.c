#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
int iskeyword(char buffer[])
{
char keywords[32][10]={"auto","else","case","break","continue","if","int","for","goto","do","double","long","float","while","char","switch"};
int i,flag=0;
for(i=0;i<32;++i)
{
if(strcmp(keywords[i],buffer)==0)
{
flag=1;
break;
}
}
return flag;
}
int main()
{
char ch,buffer[15],operator[]="+-*/%=",specialch[]=",;[]{}",num[]="1234567890",buf[10];
FILE *fp;
int i,j=0,k=0;
fp=fopen("program.txt","r");
if(fp==NULL)
{
printf("Error while opening the file\n");
exit(0);
}
while((ch=fgetc(fp))!=EOF)
{
for(i=0;i<6;++i)
{
if(ch==operator[i])
{
printf("%c is operator\n",ch);
}
if(ch==specialch[i])
{
printf("%c is special character\n",ch);
}
}
if(isalpha(ch))
{
buffer[j++]=ch;
}
if(isdigit(ch))
{
buf[k++]=ch;
}
else if((ch==' '||ch=='\n')&&(j!=0))
{
buffer[j]='\0';
j=0;
if(iskeyword(buffer)==1)
printf("%s is keyword\n",buffer);
else
{
printf("%s is identifier\n",buffer);
printf("%s is constant\n",buf);
}
}
fclose(fp);
return 0;
}
}
