#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#include<conio.h>
#define N 300
struct student
{
	char num[10];
	char name[11];
	int money;
	time_t start;
	time_t end;
};
void print();
void creat();
void mystart();
void myend();
void add();
void del();
void addmoney();
void search();
 main()                                                                       //       0
{
	char choice='\0',judge='\0';
	do{
		print();
		choice=getch();
		switch(choice)
		{
			case '1':creat();break;
			case '2':mystart();break;
			case '3':myend();break;
			case '4':add();break;
			case '5':del();break;
			case '6':addmoney();break;
			case '7':search();break;
			case '0':printf("感谢使用本软件！已正常退出，按任意键结束。");exit(0);
			default :printf("非法输入！\n");break;
		}
		printf("\n是否返回主菜单（Y/N）？\n");
		do
		{
			judge=getch();
		}while(judge!='Y'&&judge!='y'&&judge!='N'&&judge!='n');

	}while(judge=='Y'||judge=='y');
}
void print()
{
	system("cls");
	printf("\t\t................................\n");
	printf("\t\t.    请输入选项编号(0~7):      .\n");
	printf("\t\t................................\n");
	printf("\t\t.    1——建立上机档案         .\n");
	printf("\t\t.    2——开始上机             .\n");
	printf("\t\t.    3——离开机房             .\n");
	printf("\t\t.    4——添加新档案           .\n");
	printf("\t\t.    5——注销旧档案           .\n");
	printf("\t\t.    6——续钱                 .\n");
	printf("\t\t.    7——显示所有用户信息     .\n");
	printf("\t\t.    0——退出系统             .\n");
	printf("\t\t................................\n");
}
void creat()                                                                     //        1
{
	struct student stu[30],*tu=stu;
	int i=0;
	FILE *fp=NULL;
	char judge='\0';
	system("cls");
	if((fp=fopen("duli16.3.dat","w"))==NULL){
        printf("Can not open file duli16.3.dat!\n");
        exit(0);
	}
	else
	{
		do{
			printf("请输入学号：");
			scanf("%s",tu->num);
			printf("请输入名字：");
			scanf("%s",tu->name);
			printf("充值金额：");
			scanf("%d",&tu->money);
			tu->start=0;
			tu->end=0;
			fprintf(fp,"%s %s %d %d %d\n",tu->num,tu->name,tu->money,tu->start,tu->end);
			tu++;
			i++;
			printf("\n是否需要继续注册？（Y/N）\n");
			do{
			judge=getch();
		}while(judge!='Y'&&judge!='y'&&judge!='N'&&judge!='n');
	}while(judge=='Y'||judge=='y');

	}
	fclose(fp);
}
void mystart()                                                                          //              2
{
	struct student stu[30]={0};
	int j=0,i=0,k=-1;
	char s[10];
	FILE *fp=NULL;
	printf("请输入上机学号：");
	scanf("%s",s);
	if((fp=fopen("duli16.3.dat","r"))==NULL)
	printf("查询不到此学生");
	while(feof(fp)==0)
	{
		fscanf(fp,"%s %s %d %d %d\n",stu[j].num,stu[j].name,&stu[j].money,&stu[j].start,&stu[j].end);
		j++;
	}
	fclose(fp);
	printf("\n");
	for(i=0;i<j;i++)
	{
		if(strcmp(stu[i].num,s)==0){
		k=i;
		break;}
	}
	if(k==-1)
	{
		
		printf("\n查询不到此学生,请重新输入");
		mystart();
	}
	else if(stu[k].money>=6)
	{
		time(&stu[k].start);
		printf("上机成功，欢迎使用！\n");
		printf("学号：%s  姓名：%s  余额：%d\n",stu[k].num,stu[k].name,stu[k].money);
		fp=fopen("duli16.3.dat","r+");
		for(i=0;i<j;i++)
        fprintf(fp,"%s %s %d %d %d\n",stu[i].num,stu[i].name,stu[i].money,stu[i].start,stu[i].end);
    fclose(fp);
	}

	else printf("\n余额不足，请充值！");
}
void myend()                                                                         //              3
{
	struct student stu[30]={0};
	int dif;
	int minute,hour,second;
	int usemoney;
	int j=0,i=0,k=-1;
	char s[10];
	FILE *fp=NULL;
	printf("请输入下机学号：");
	scanf("%s",s);
	if((fp=fopen("duli16.3.dat","r"))==NULL)
	printf("查询不到此学生");
	while(feof(fp)==0)
	{
		fscanf(fp,"%s %s %d %d %d\n",stu[j].num,stu[j].name,&stu[j].money,&stu[j].start,&stu[j].end);
		j++;
	}
	fclose(fp);
	printf("\n");
	for(i=0;i<j;i++)
	{
		if(strcmp(stu[i].num,s)==0){
		k=i;
		break;}
	}
	if(k==-1)
	{
		system("cls");
		printf("\n查询不到此学生,请重新输入");
		mystart();
	}
	else
	{
	time(&stu[k].end);
	printf("下机成功！欢迎下次使用。\n");
	dif=stu[k].end-stu[k].start;
	hour=dif/3600;
    minute=dif%3600/60;
    second=dif%60;
    if(second>0){
        minute++;
        second=0;
    }
    if(minute>30)
    {
        hour++;
        minute=0;
    }
    else if(minute>0)
        minute=30;
	usemoney=hour*2+minute*1/30;
	stu[k].money=stu[k].money-usemoney;
	printf("学号：%s  姓名：%s  余额：%d\n",stu[k].num,stu[k].name,stu[k].money);
	fp=fopen("duli16.3.dat","r+");
	for(i=0;i<j;i++)
        fprintf(fp,"%s %s %d %d %d\n",stu[i].num,stu[i].name,stu[i].money,stu[i].start,stu[i].end);
    fclose(fp);
	}
}
void add()                                                                            //              4
{
    struct student stu[30],st[30],*tu=stu;                                 //st读取文件数据，stu读取新增记录
    int i=0,j=0,k=0;
    FILE *fp=NULL;
	system("cls");
    char judge='Y',num[10];
	fp=fopen("duli16.3.dat","a+");
	while(feof(fp)==0)
	{
		fscanf(fp,"%s %s %d %d %d\n",st[j].num,st[j].name,&st[j].money,&st[j].start,&st[j].end);
		j++;
	}
	while(judge=='Y'||judge=='y')
	{
		system("cls");
	do
	{
		printf("请输入需要添加的学号：");
		scanf("%s",num);
		for(i=0;i<j;i++)
			if(strcmp(st[i].num,num)==0){
				i=1;
				system("cls");
				printf("此学号存在，请重新注册！\n");
				break;
			    }
	}while(i==1);
	strcpy(stu->num,num);
	printf("请输入名字：");
	scanf("%s",stu->name);
	printf("充值金额：");
	scanf("%d",&stu->money);
	stu->start=0;
	stu->end=0;
	fprintf(fp,"%s %s %d %d %d\n",stu->num,stu->name,stu->money,stu->start,stu->end);
	k++;
	printf("\n是否需要继续注册？（Y/N）\n");
	do{
		judge=getch();
	}while(judge!='Y'&&judge!='y'&&judge!='N'&&judge!='n');
	}
	fclose(fp);
}
void del()                                                                              //        5
{
    struct student stu[30]={0};
    int j=0,k=-1,i=0;
    char s[10];
    FILE *fp=NULL;
    printf("请输入要删除的学号：");
    scanf("%s",s);
    if((fp=fopen("duli16.3.dat","r"))==NULL)
	{
		printf("查询不到此学生");
	}
	while(feof(fp)==0)
    {
        fscanf(fp,"%s %s %d %d %d\n",stu[j].num,stu[j].name,&stu[j].money,&stu[j].start,&stu[j].end);
		j++;
    }
    fclose(fp);
    printf("\n");
    for(i=0;i<j;i++)
    {
        if(strcmp(stu[i].num,s)==0){
		k=i;
		break;}
	}
	if(k==-1)
	{
		system("cls");
		printf("\n查询不到此学生,请重新输入");
		del();
	}
	else{
        for(i=k;i<j-1;i++)
        {
            strcpy(stu[i].num,stu[i+1].num);
            strcpy(stu[i].name,stu[i+1].name);
            stu[i].money=stu[i+1].money;
        }
        printf("成功删除记录！\n");
	}
	fp=fopen("duli16.3.dat","w");
	for(i=0;i<j-1;i++)
        fprintf(fp,"%s %s %d %d %d\n",stu[i].num,stu[i].name,stu[i].money,stu[i].start,stu[i].end);
    fclose(fp);
}
void addmoney()                                                                     //           6
{
    struct student stu[30]={0};
    int j=0,i=0,k=-1,a=0,cmoney=0;
    char s[10];
    FILE *fp=NULL;
    printf("请输入需要充值的学号：");
    scanf("%s",s);
    if((fp=fopen("duli16.3.dat","r"))==NULL)
	printf("查询不到此学生");
	while(feof(fp)==0)
    {
        fscanf(fp,"%s %s %d %d %d\n",stu[j].num,stu[j].name,&stu[j].money,&stu[j].start,&stu[j].end);
		j++;
    }
    fclose(fp);
    printf("\n");
    for(i=0;i<j;i++)
    {
       if(strcmp(stu[i].num,s)==0)
		k=i;
	}
	if(k==-1)
	{
		system("cls");
		printf("\n查询不到此学生,请重新输入");
		addmoney();
	}
	else
	{
		printf("输入充值金额：");
		scanf("%d",&cmoney);
		stu[k].money=stu[k].money+cmoney;
		printf("学号：%s 姓名：%s 余额：%d\n",stu[k].num,stu[k].name,stu[k].money);
		fp=fopen("duli16.3.dat","r+");
		for(a=0;a<j;a++)
			fprintf(fp,"%s %s %d %d %d\n",stu[a].num,stu[a].name,stu[a].money,stu[a].start,stu[a].end);
		fclose(fp);
	}
}
void search()                                                                       //            7
{
    struct student stu[30]={0};
    int j=0,k=0;
    FILE *fp;
    if((fp=fopen("duli16.3.dat","r"))==NULL){
        printf("Can not open file duli16.3.dat!\n");
        exit(0);
	}
    while(feof(fp)==0)
    {
        fscanf(fp,"%s %s %d %d %d\n",stu[j].num,stu[j].name,&stu[j].money,&stu[j].start,&stu[j].end);
		j++;
    }
    system("cls");
    for(k=0;k<j;k++)
        printf("学号：%s 姓名：%s 余额：%d\n",stu[k].num,stu[k].name,stu[k].money);
}


