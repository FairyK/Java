#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define LEN 1000
void creat(int a);//输入函数
void show(void);//显示学生信息函数
void average(void);//求平均数函数
void print(void);//求综测期末最高分与最低分及其不及格的学生的函数
void rank(void);//学生排名函数
void search(void);//通过学号查找学生的函数
void revamp(void);//修改学生信息的函数
void expurgate(void);//删除某学生信息的函数
struct student
{
    int num;
    char name[15];
    double scoreMath;
    double scoreEnglish;
    double scoreComputer;
    double total;
};//定义学生成绩信息结构
struct student students[LEN];//学生结构数组，用于存储学生成绩信息
int i, r;
float a, b, c;//a为数学成绩所占百分比，b为英语成绩所占比， c为计算机成绩所占比
int much;//当前学生人数
void save()   //写入文件
{
    FILE* fp;
    int i;
    if ((fp = fopen("D:\\student.txt", "wb")) == NULL)
    {
        printf("cannot open file\n");
        return;
    }
    for (i = 0; i < much; i++)
        if (fwrite(&students[i], sizeof(struct student), 1, fp) != 1)
            printf("file write error\n");
    fclose(fp);
}

int main()
{  
    int mode;//为后面的模式选择
	 system("color b1");
    printf("请输入学生人数：");
   scanf_s("%d",&much);
	system("color f5");
    printf("请输入数学成绩所占比a:");
    scanf_s("%f", &a);
    printf("请输入英语成绩所占比b:");
    scanf_s("%f", &b);
    printf("请输入计算机成绩所占比c:");
    scanf_s("%f", &c);
	system("color a1");
    printf("模式1：输入学生信息\n");
    printf("模式2：显示所有学生的学号，各科成绩，总评成绩\n");
    printf("模式3：输出各科成绩平均分及总评成绩平均分\n");
    printf("模式4：输出总评成绩及格率，最高分，最低分\n");
    printf("模式5：排序\n");
    printf("模式6：查找\n");
    printf("模式7：修改\n");
    printf("模式8：删除\n");
    printf("请输入想用几个模式\n");
    scanf_s("%d", &r);
	 printf("请先选择模式1输入学生信息\n");
    for (i = 0; i < r; i++)
    {
        printf("请选择1~8中任意模式\n");
       
        scanf_s("%d", &mode);
        switch (mode)
        {
        case 1:creat(much); save(); break;//save()是为了把信息保存至磁盘文件中
        case 2:show(); break;
        case 3:average(); break;
        case 4:print(); break;
        case 5:rank(); break;
        case 6:search(); break;
        case 7:revamp(); break;
        case 8:expurgate(); break;
        }
    }
    return 0;
}
void creat(int much)
{
    for (i = 0; i < much; i++)
    {  system("color d0");
        printf("请输入学生学号: ");
        scanf_s("%d", &students[i].num);
        printf("请输入学生姓名：");
        scanf_s("%s", students[i].name,sizeof(students[i].name));
        printf("请输入数学成绩：");
        scanf_s("%lf", &students[i].scoreMath);
        printf("请输入英语成绩：");
        scanf_s("%lf", &students[i].scoreEnglish);
        printf("请输入计算机成绩：");
        scanf_s("%lf", &students[i].scoreComputer);
        students[i].total =( a * students[i].scoreMath) + (b * students[i].scoreEnglish) + (c * students[i].scoreComputer);
    }
}
void show(void)
{
    int i;
    for (i = 0; i < much; i++)
    {   system("color b5");
        printf("学号：%d\n", students[i].num);
        printf("姓名：%s\n", students[i].name);
        printf("数学成绩：%lf\n", students[i].scoreMath);
        printf("英语成绩：%lf\n", students[i].scoreEnglish);
        printf("计算机成绩：%lf\n", students[i].scoreComputer);
        printf("总评成绩：%lf\n", students[i].total);
    }
}
void average(void)
{
    int i;
    double m, n, q, u, sum, aver1, aver2, aver3, aver4;
    for (i = 0, sum = 0; i < much; i++)
    {
        m = students[i].scoreMath;
        sum = m + sum;
    }
    aver1 = sum / much;
	system("color e5");
    printf("数学平均分：%lf\n", aver1);
    for (i = 0, sum = 0; i < much; i++)
    {
        n = students[i].scoreEnglish;
        sum = n + sum;
    }
    aver2 = sum / much;

    printf("英语平均分：%lf\n", aver2);
    for (i = 0, sum = 0; i < much; i++)
    {
        q = students[i].scoreComputer;
        sum = q + sum;
    }
    aver3 = sum / much;

    printf("计算机平均分：%lf\n", aver3);
    for (i = 0, sum = 0; i < much; i++)
    {
        u = students[i].total;
        sum = u + sum;
    }
    aver4 = sum / much;

    printf("总评平均分：%lf\n", aver4);
}
void print(void)
{
    int i, j, k,t=0;
    double temp;
   int last;
   system("color d3");
    for (i = 0; i < much; i++)
    {
        if (students[i].total < 72)//总评成绩未达到72为不及格 
            printf("不及格%lf\n", students[i].total);
        else t++;
    }
    if (t == much)printf("没有不及格学生\n\n");
    for (i = 0; i < much - 1; i++)
    {
        k = i;
        for (j = i + 1; j < much; j++)
            if (students[j].total < students[k].total)
                k = j;
        temp = students[k].total;
        students[k].total = students[i].total;
        students[i].total = temp;
    }
	
     last = much - 1;
	
    printf("最高分%lf\n", students[last].total);

    printf("最低分%lf\n", students[0].total);
  
}
void rank(void)
{
    int i, k, j, m;
    double temp;
    char n= students[0].name[0];
	system("color f5");
    for (i = 0; i < much - 1; i++)
    {
        k = i;
        for (j = i + 1; j < much; j++)
        {
            if (students[j].total < students[k].total)
                k = j;
            temp = students[k].total;
            students[k].total = students[i].total;
            students[i].total = temp;
            m = students[k].num;
            students[k].num = students[i].num;
            students[i].num = m;
            students[k].num = students[i].num;
            for (j = 0; students[i].name[j] != '\0'; j++)
            {
                n = students[k].name[j];
                students[k].name[j] = students[i].name[j];
                students[i].name[j] = n;
            }
            students[i].name[j+1] = '\0';
        }
        }

    for (i = 0; i < much; i++)
    {
        printf("%d %s %lf\n", students[i].num, students[i].name, students[i].total);
    }
}
void search(void)
{
    int i, num;
   system("color b4");
    printf("请输入查找的学生学号：");
    scanf_s("%d", &num);
	system("color b3");
    printf("The information of the %d student are as follows\n", num);		
    for (i = 0; i < much; i++)
    {
        if (num == students[i].num)
        {
            printf("学号：%d\n姓名：%s\n数学成绩：%lf\n英语成绩：%lf\n计算机成绩：%lf\n总评成绩：%lf\n", students[i].num, students[i].name, students[i].scoreMath, students[i].scoreEnglish, students[i].scoreComputer, students[i].total);
            break;
        }
    }
}
void revamp(void)
{
    int i, num, mode,t=0;
    double m;
		system("color e8");
    printf("请输入需要修改的学生学号：");
    scanf_s("%d", &num);
    for (i = 0; i < much; i++)
    {
        if (num == students[i].num)
        {
            t = i;
            break;
        }
    }
    printf("模式1：修改数学成绩\n");
    printf("模式2：修改英语成绩\n");
    printf("模式3：修改计算机成绩\n");
    printf("请选择：");
    scanf_s("%d", &mode);
    switch (mode)
    {
    case 1:printf("修改数学成绩"); printf("请输入修改成绩为:"); scanf_s("%lf", &m); students[t].scoreMath=m; break;
    case 2:printf("修改英语成绩"); printf("请输入修改成绩为:"); scanf_s("%lf", &m); students[t].scoreEnglish = m; break;
    case 3:printf("修改计算机成绩"); printf("请输入修改成绩为:"); scanf_s("%lf", &m); students[t].scoreComputer = m; break;
    }
}
void expurgate(void)
{
    int i, num, t=0;
	system("color d3");
    printf("请输入需要删除的学生学号：");
    scanf_s("%d", &num);
    for (i = 0; i < much; i++)
    {
        if (num == students[i].num)
        {
            t = i;
            break;
        }
    }

    for (; t< much; t++)
        students[t] = students[t + 1];
	printf("修改后学生信息如下:\n");
	much=much-1;
    for (i = 0; i < much; i++)
    {   system("color b5");
        printf("学号：%d\n", students[i].num);
        printf("姓名：%s\n", students[i].name);
        printf("数学成绩：%lf\n", students[i].scoreMath);
        printf("英语成绩：%lf\n", students[i].scoreEnglish);
        printf("计算机成绩：%lf\n", students[i].scoreComputer);
        printf("总评成绩：%lf\n", students[i].total);
    }
}
