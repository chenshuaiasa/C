#include<stdlib.h>
#include<stdio.h>
#include<malloc.h>
#include<windows.h>

#define Max 100

typedef struct
{
	char name[3];
	int xuhao;
	float weight;
	int parent,lchild,rchild;
	int val;
	char bianma[27];
}HTNode;

typedef struct
{
	float w;
	int v;
}S;

S ss[50];

char cs[50];

typedef HTNode *HuffmanTree;
//typedef char *HufffmanCode;

typedef struct
{
	char yima[11];
}Y;



HuffmanTree HuffmanCoding(HuffmanTree HT,int n);    //用于初始化及建立哈夫曼树
void HuffmanBianma(HuffmanTree HT,int n);           //用于对文件中的字符串编码
void HuffmanYima(HuffmanTree HT,char a[],int n);    //用于对文件中的哈夫曼编码译码
float Select(HuffmanTree HT,int i);                 //对存储在ss数组中的权值进行排序并挑选出未被选择过的最小权值
int find(float s,HuffmanTree HT,int n);             //通过Select选择出的最小权值，来找到预期相对应的序号
void Screen(HuffmanTree HT);                        //以二叉树的形式打印在屏幕上
void printFILE(HuffmanTree HT);                     //打印在文件CodeFile中的译码
void qian();                                        //对存储译码的数组中的译码进行整理
void Print(HuffmanTree HT);							//向屏幕打印每个名称所对应的哈夫曼编码
int printplus(HuffmanTree HT,int x);                //在Screen中调用的递归函数

int main()
{
	int n;
	char c,cs[2],ch;
	int j,i,location;
	char a[300];
	FILE *fp;
	char cc[10];
	HuffmanTree HT;
	HT = (HuffmanTree)malloc((55)*sizeof(HTNode));
	/*fp = fopen("ToBeTran","r+");
	fgets(cc,15,fp);
	printf("%s\n",cc);
	fclose(fp);*/
	while(1)
	{
		printf("\n");
		printf("      *********************************      \n");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_BLUE|FOREGROUND_INTENSITY);
		printf("          I:初始化（用户从客户端输入并存入hufmtree文件）\n");
		printf("          L:初始化（直接打开hufmtree文件，并从中读取\n");
		printf("          E:编码\n");
		printf("          D:译码\n");
		printf("          S:打印每个名称所对应的哈夫曼编码\n");
		printf("          P:打印CodeFile文件中的译码\n");
		printf("          T:印哈夫曼树\n");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE);
		printf("      *********************************      \n");
		printf("输入需要进行功能的操作符\n");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_RED|FOREGROUND_BLUE|FOREGROUND_INTENSITY);
		fflush(stdin);
		scanf("%c",&c);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE);
		switch(c)
		{
			case 'I':
				printf("请输入叶子节点数：\n");
				scanf("%d",&n);
				HT = HuffmanCoding(HT,n);
				break;
			case 'L':
				fp = fopen("htmTree","a+");
				ch = fgetc(fp);
				rewind(fp);
				printf("已从文件hfmTree中读取哈夫曼树，如下： \n");
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_RED|FOREGROUND_INTENSITY);
				printf("名称 序号 父亲结点 左孩子 右孩子 权值\n");
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_INTENSITY);
				for(i = 0;ch !=EOF;i++)
				{
					fscanf(fp,"%s ",HT[i].name);
					//strcpy(HT[j].name,cc);
					fscanf(fp,"%d ",&HT[i].xuhao);
					//HT[j].xuhao=atoi(cc);
					fscanf(fp,"%d ",&HT[i].parent);
					//HT[j].parent=atoi(cc); 
					fscanf(fp,"%d ",&HT[i].lchild);
					//HT[j].lchild = atoi(cc); 
					fscanf(fp,"%d ",&HT[i].rchild);
					//HT[j].rchild = atoi(cc); 
					fscanf(fp,"%f ",&HT[i].weight);
					//HT[j].weight = atof(cc);
					fscanf(fp,"%d ",&HT[i].val);
					//HT[j].val = atoi(cc);
					location = ftell(fp);
					ch = fgetc(fp);
					fseek(fp,location,0);
					printf("%3s%5d%7d%8d%6d    %4.2f\n",HT[i].name,HT[i].xuhao,HT[i].parent,HT[i].lchild,HT[i].rchild,HT[i].weight);
					printf("\n");
				}
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE);
				n = (i+1)/2;
				printf("\n");
				fclose(fp);
				break;
			case 'E':
				HuffmanBianma(HT,n);
				break;
			case 'D':
				if((fp = fopen("CodeFile","a+"))==NULL)
				{
					printf("文件打开失败！\n");
					exit(0);
				}
				fgets(a,Max*2,fp);
				HuffmanYima(HT,a,n);
				fclose(fp);
				break;
			case 'P':
				printFILE(HT);
				break;
			case 'T':
				Screen(HT);
				break;
			case 'S':
				Print(HT);
		}
	}
	return 0;
}


float Select(HuffmanTree HT,int i)
{
	int j = 0;
	int k;
	S s;
	float s1;
	HuffmanTree p;
	p = HT;
	for(j=0;j<i;j++)
	{
		for(k=j+1;k<i;k++)
			{
				if(ss[j].w >= ss[k].w)
				{
					s = ss[j];
					ss[j] = ss[k];
					ss[k] = s;
				}
			}
	}
	for(j = 0;j <= i;j++)
	{
		//printf("%d\n",ss[j].w);
		if(ss[j].v==0)
		{
			s1 = ss[j].w;
			ss[j].v=1;
			//printf("%.2f\n",s1);
			break;
			
		}
	}
	return s1;
}

HuffmanTree HuffmanCoding(HuffmanTree HT,int n)
{	
	int m;
	int i,j;
	float s1,s2,w;
	int s11,s22;
	char s[200] = {0};
	FILE *fp;
	HuffmanTree p;
	m=2*n-1; 
	p = HT;
	printf("\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_RED|FOREGROUND_INTENSITY);
	printf("请先输入名称后再输入权值\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE);
	for(i=0;i<n;++i,++p,++w)
	{

		printf("请输入名称：");
		//fflush(stdin);
		scanf("%s",p->name);
		printf("请输入一个权值：");
		scanf("%f",&w);
		strcpy(p->bianma," ");
		p->xuhao = i+1;
		p->weight = w;
		p->parent = 0;
		p->lchild = 0;
		p->rchild = 0;
		p->val = 0;
	}
	for(i = n;i<m;++i,++p)
	{
		strcpy(p->name,"?");
		p->weight = 0;
		p->parent = 0;
		p->lchild = 0;
		p->rchild = 0;
		p->val = 0;
		p->xuhao = i+1;
	}
	p = HT;
	for(j=0;j<n;j++)
	{
		ss[j].w = p[j].weight;
		printf("%f\t",ss[j].w);
	}
	for(i = n;i<m;i++)
	{
		s1 = Select(HT,i);
		s2 = Select(HT,i);
		s11 = find(s1,HT,n);
		s22 = find(s2,HT,n);
		HT[s11].parent = i+1;
		HT[s22].parent = i+1;
		HT[i].lchild = s11+1;
		HT[i].rchild = s22+1;
		HT[i].weight = HT[s11].weight + HT[s22].weight;
		ss[i].w = HT[i].weight;
	}
	//printf("%d\3",ss[0]);
	if((fp = fopen("htmTree","w+"))==NULL)
	{
		printf("can not open this file\n");
		exit(0);
	}
	for(i=0;i<m;)
	{
		fputs(HT[i].name,fp);
		fputc('\t',fp);
		fputs(itoa(HT[i].xuhao,s,10),fp);
		fputc('\t',fp);
		fputs(itoa(HT[i].parent,s,10) ,fp);
		fputc('\t',fp);
		fputs(itoa(HT[i].lchild,s,10)  ,fp);
		fputc('\t',fp);
		fputs(itoa(HT[i].rchild ,s,10) ,fp);
		fputc('\t',fp);
		fprintf(fp,"%.2f",HT[i].weight);
		fputc('\t',fp);
		fputs(itoa(HT[i].val ,s,10),fp);
		i++;
		if(i<m)
			fputs("\n",fp);
	}
	fclose(fp);
	return HT;
}


int find(float s,HuffmanTree HT,int n)
{
	int i;
	for(i = 0;i<=(n*2);i++)
	{
		if((HT[i].weight == s)&&(HT[i].val == 0))
		{
			HT[i].val = 1;
			return i;
		}
	}
	return 0;
}

void HuffmanBianma(HuffmanTree HT,int n)
{
	int nu = 0;
	int start = n;
	int k,j;
	int i,c,f = 1;
	FILE *fp1;
	FILE *fp2;
	char a[Max*3];
	Y y[11];
	for(k=0;k<11;k++)
	{
		for(i = 0;i < sizeof(y[k].yima)/sizeof(y[k].yima[0]);i++)
		{
			y[k].yima[i] = '4';
		}
	}
	
	for(i = 0;i<n;i++)
	{
		cs[n+1] = '\0';
		start = n+1;
		f = HT[i].parent;
		for(c = i;f!=0;)
		{
			
			if(HT[f-1].lchild == c+1)
				cs[--start] = '0';
			else 
				cs[--start] = '1';
			c = f-1;
			f = HT[f-1].parent;	
		}
		qian(cs);
		strcpy(HT[i].bianma,cs);
		for(j = 0;j < sizeof(cs)/sizeof(cs[0]);j++)
		{
			cs[j] = '4';
		}
	}
	printf("\n");
	if((fp2 = fopen("ToBeTran","r+"))==NULL)
	{
		printf("文件打开失败！\n");
		exit(0);
	}
	if((fp1 = fopen("CodeFile","w+"))==NULL)
	{
		printf("文件打开失败！\n");
		exit(0);
	}
	Print(HT);	          //调用Print函数来输出各个名称的权值
	printf("\n");
	fgets(a,Max,fp2);
	printf("文件中的字符串为：\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_GREEN|FOREGROUND_BLUE|FOREGROUND_INTENSITY);
	printf("%s\n",a);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE);
	printf("对这段字符串的编码如下\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_GREEN|FOREGROUND_INTENSITY);
	for(k = 0;k<Max;k++)
	{
		for(j = 0;j<n;j++)
		{
			if(a[k]==HT[j].name[0])
			{
				if(nu > 50)
				{
					printf("\n");
					nu = 0;
				}
				else
				{
					printf("%s",HT[j].bianma);
					fputs(HT[j].bianma,fp1);
					nu +=strlen(HT[j].bianma);
				}
			}
		}
	}
	//fputs(HT[i].bianma,fp1);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_RED|FOREGROUND_INTENSITY);
	printf("\n");
	printf("对此段字符串的编码一存入文件CodeFile中！\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE);
	fclose(fp1);
	fclose(fp2);
}


void qian()
{
	int i = 0;
	int j = 0;
	int temp,x;
	for(i =0;i < sizeof(cs)/sizeof(cs[0]);i++)
	{
		if((cs[i]=='0')||(cs[i]=='1'))
		{
			x = i;
			break;
		}
	}
	for(j = x;j <= sizeof(cs)/sizeof(cs[0]);j++)
	{
		temp = cs[j];
		cs[j] = cs[j-x];
		cs[j-x] = temp;
	}

}


void Print(HuffmanTree HT)
{
	int i = 0;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_INTENSITY);
	for(i = 0;;i++)
	{
		if(HT[i].rchild>0)
			break;
		printf("名称为%s，权值为%.2f，的哈夫曼编码为：",HT[i].name,HT[i].weight);
		printf("%s",HT[i].bianma);
		printf("\n");
		
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE);
	printf("\n");
}


void HuffmanYima(HuffmanTree HT,char a[],int n)
{
	int i;
	int choose;
	int f = 2*n-1;
	int ji;
	char hand[300];
	printf("\n\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_RED|FOREGROUND_INTENSITY);
	printf("    1 ：手动输入    2：从文件中读入\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE);
	fflush(stdin);
	scanf("%d",&choose);
	if(choose == 1)
	{
		Print(HT);
		printf("请输入：\n");
		fflush(stdin);
		gets(hand);
		for(i = 0;(hand[i]==48)||(hand[i]==49);)
		{
			if((HT[f-1].lchild != 0)||(HT[f-1].rchild != 0))
			{	
				if(hand[i]==48)
				{
					f = HT[f-1].lchild;
					ji = f;
				}
				else if(hand[i]==49)
				{
					f = HT[f-1].rchild;
					ji = f;
				}
				i++;
			}
			else 
			{
				printf("%s",HT[f-1].name);
				f = 2*n-1;
			}
		}
		printf("%s",HT[ji-1].name);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE);
		printf("\n\n");
	}
	else
	{
		printf("CodeFile中的编码为：\n");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_GREEN|FOREGROUND_INTENSITY);
		printFILE(HT);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE);
		printf("\n");
		printf("译码后的结果为：\n");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_GREEN|FOREGROUND_BLUE|FOREGROUND_INTENSITY);
		for(i = 0;(a[i]==48)||(a[i]==49);)
		{
			if((HT[f-1].lchild != 0)||(HT[f-1].rchild != 0))
			{	
				if(a[i]==48)
				{
					f = HT[f-1].lchild;
				}
				else if(a[i]==49)
				{
					f = HT[f-1].rchild;
				}
				i++;
			}
			else 
			{
				printf("%s",HT[f-1].name);
				f = 2*n-1;
			}
		}
		printf("%s",HT[f-1].name);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE);
		printf("\n\n");
	}
}



void printFILE(HuffmanTree HT)
{
	FILE *fp;
	int i;
	char a[Max*3];
	if((fp = fopen("CodeFile","r+"))==NULL)
	{
		printf("文件打开失败！\n");
		exit(0);
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_GREEN|FOREGROUND_INTENSITY);
	fgets(a,Max*3,fp);
	printf("\n\n");
	for(i = 0;(a[i]==49)||(a[i]==48);)
	{
		printf("%c",a[i]);

		i++;
		if(i%50==0)
		{
			printf("\n");
		}
	}
	printf("\n\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE);
	fclose(fp);
}

void Screen(HuffmanTree HT)
{
	int i,x;
	int ll,rr;
	int f = 1,p = 1;
	
	for( i = 0;;i++)
	{
		if(HT[i].parent == 0)
		{
			x = i;
			break;
		}
		HT[i].val = 0;
	}
	printf("\n\n");
	printf("二叉树的凹入表如下：\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_INTENSITY);
	printf("(");
	printplus(HT,x+1);
	printf(")");
	printf("\n\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE);
}

int printplus(HuffmanTree HT,int x)
{
	printf("%.2f ",HT[x-1].weight);
	if((HT[x-1].lchild == 0)&&(HT[x-1].val == 0))
	{	
		return 0;
	}
	printf("(");
	HT[x-1].val = 1;
	printplus(HT,HT[x-1].lchild);
	printf(",");
	printplus(HT,HT[x-1].rchild);
	printf(")");
	return 0;
}