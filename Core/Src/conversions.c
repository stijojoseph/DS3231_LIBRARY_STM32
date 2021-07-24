/*
 * conversions.c
 *
 *  Created on: Jul 11, 2021
 *      Author: HP
 */


int char_to_int(char *f)
{
int p=0;
int i=0;
while(f[i]!='\0')
{
p=p*10+(f[i]-'0');
i++;

}



return p;
}

char *int_to_char(int c)
{
 char s[100];

 int rem;
 int i=0;
 if(c==0)
 return "0";

while(c!=0)
{

rem=c%10;
s[i]=rem + '0';

c=c/10;
i++;
}
s[i]='\0';
//printf(" ********%s******* ",s);
char u[10];
char *k=u;
for(int i=0;s[i]!='\0';i++){}
//printf(" %c ",s[i]);
//printf(" %s ",s);
i--;
int j=0;
for(j=0;i>=0;i--,j++)
{
 u[j]=s[i];


}

u[j]='\0';

//printf(" %s ",k);
return k;
}
int string_to_hex(char *hex)
{

int p=strlen(hex);
int c=0;
int j=0;
for(int i=p-1;i>1;i--,j++)
{
if(hex[i]>='A' && hex[i]<='F')
{
c+=(hex[i]-'A'+10)*pow(16,j) ;
//printf("%d ",c);
}
else if(hex[i]>='a' && hex[i]<='f')
{
c+=(hex[i]-'a'+10)*pow(16,j) ;
//printf("%d ",c);
}
else if(hex[i]>='0' && hex[i]<='9')
{
c+=(hex[i]-'0')*pow(16,j) ;
//printf("%d ",c);
}


}

return c;
}
int integer_to_bcd(int num)
{

int ones=num%10;
int tens=num/10;

num=(tens<<4)|ones;


return num;
}

int bcd_to_integer(int num)
{

	int ones=(num & 0x0F);
	int tens=(num & 0xF0);
tens=tens>>4;
	return (tens*10+ones);



}
