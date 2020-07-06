#include<iostream> //登录名:admin   密码:123 
#include<fstream>//读入文件 
#include<string>
#include <vector>
#include <iterator>// 标准库函数begin(),end() 
using namespace std;


//学生类
class Student
{
public://访问说明符--成员可以在整个程序内被访问,public成员定义类的接口 
	Student()//
	{
 
	}

	Student(string szNum, string szName, string szSex) 
	{
		m_szNum = szNum;//初始化 传值   使用构造函数的参数作为成员的初始值 
		m_szName = szName;
		m_szSex = szSex;
		m_szPwd = "123";;
	}

public:
	string m_szNum;			//学号
	string m_szName;		//姓名
	string m_szSex;			//性别
	string m_szPwd;			//密码
};

//课程成绩类
class Course
{
public:
	Course()
	{
		m_nRank = 1;//成绩排名,初始化为1 
	}

	Course(string szCourseName, float fScore, string szTeacherName)
	{
		m_szCourseName = szCourseName;
		m_fScore = fScore;
		m_szTeacherName = szTeacherName;
		m_nRank = 1;
	}

public:
	string m_szCourseName;		//课程名称
	float m_fScore;				//成绩
	string m_szTeacherName;		//任课老师
	int m_nRank;				//等级
};

//学生课程成绩类
class Stu_Course
{
public:
	Stu_Course()
	{
		m_pStu = NULL;
	}

	Stu_Course(Student* &pStu)//声明指向Student的指针 pStu
	{
		m_pStu = pStu;//初始化 
	}

	~Stu_Course()//析构函数,释放内存,否则会内存泄漏 !! 
	{
		if (!m_pStu)
		{
			delete m_pStu;
			m_pStu = NULL;
		}
		for (size_t i = 0; i < m_vecCourse.size(); ++i)//size_t=sizetype 一种用来记录大小的数据类型
		{
			delete m_vecCourse.at(i);
		}
	}

	void AddCourse(Course* &pCourse)
	{
		m_vecCourse.push_back(pCourse);
	}

public:
	Student* m_pStu;					//学生类成员
	vector<Course*> m_vecCourse;		//该学生课程类数组成员
};

//学生课程成绩类数组
vector<Stu_Course*> vecStu_Course;

//从文件读取数据--- 
void ReadFile()
{
	FILE *fp;//文件指针
	int n;//文件行数计数
	if((fp=fopen("Scores.txt","r"))==NULL)//打开文件 库函数 FILE *fopen(const char *filename, const char *mode) "r"以只读方式打开文件 
	{
		return;//要返回错误代码 
	}
	for(n=0; !feof(fp); n++)//按行循环遍历文件  int feof(FILE *stream);检测文件是否结束 
	{
		Student* pStu = NULL;
		Course* pCourse = NULL;
		Stu_Course* pStu_Course = NULL;

		char szNum[50], szName[50], szSex[5], szPwd[50];// 
		float f1, f2, f3, f4;
		fscanf(fp, "%s\t%s\t%s\t%s\t%f\t%f\t%f\t%f\t", &szNum, &szName, &szSex, &szPwd, &f1, &f2, &f3, &f4);//int fscanf(FILE *stream, const char *format, ...) 

		pStu = new Student(szNum, szName, szSex);
		pStu->m_szPwd = szPwd;
		pStu_Course = new Stu_Course(pStu);

		pCourse = new Course("A", f1, "张三");
		pStu_Course->AddCourse(pCourse);
		pCourse = new Course("B", f2, "李四");
		pStu_Course->AddCourse(pCourse);
		pCourse = new Course("C", f3, "王五");
		pStu_Course->AddCourse(pCourse);
		pCourse = new Course("D", f4, "赵六");
		pStu_Course->AddCourse(pCourse);
		vecStu_Course.push_back(pStu_Course);
	}
	fclose(fp);//关闭文件
}

//将存储成绩信息的链表写入文件
void WriteFile()
{
	system("cls");
	FILE *fp;//文件指针
	fp=fopen("Scores.txt","w+");//打开可读写文件
	if (fp  == NULL)
	{
		return;
	}
	for (int i = 0; i < vecStu_Course.size(); ++i)
	{
		Student* pStu = vecStu_Course.at(i)->m_pStu;
		vector<Course*>* vectCourse = &vecStu_Course.at(i)->m_vecCourse;//c.at(n)返回下标为n的元素的引用,若下标越界,则抛出异常 
		
		float ff = vectCourse->at(0)->m_fScore;
		fprintf(fp, "%s\t%s\t%s\t%s\t%f\t%f\t%f\t%f\t", pStu->m_szNum.c_str(), pStu->m_szName.c_str(), pStu->m_szSex.c_str(), pStu->m_szPwd.c_str(), vectCourse->at(0)->m_fScore, vectCourse->at(1)->m_fScore, vectCourse->at(2)->m_fScore, vectCourse->at(3)->m_fScore);//将学生信息写入文件
		fputs("\n",fp);//文件指针指向下一行
	}
	fclose(fp);//关闭文件
}


//根据学号查询
int Search(string szNum)
{
	int nIndex ,nCount;
	nIndex = nCount = -1;
	vector<Stu_Course*>::iterator it = vecStu_Course.begin();
	for (; it != vecStu_Course.end(); ++it)//for(....;it !=  vecStu_Course.end() && it->empty();++it)//isspace应该也可以 
	{
		++nCount;
		string szCurNum = (*it)->m_pStu->m_szNum;
		if (szCurNum == szNum)
		{
			nIndex = nCount;
			break;
		}
	}
	return nIndex;
}

//登录
int Login()
{
	int nType = -1;	//初始化为(-1)代表还未运行	//用户类型-- 0：管理员；1：普通用户
	while(1)
	{
		cout << endl << endl;
		cout << "**********************************************************************" << endl;
		cout << "***                      欢迎进入成绩管理系统		           ***" << endl;
		cout << "**********************************************************************" << endl << endl << endl; 
		cout << "\t\t\t   请输入用户名：";//注意对好位置 
		string szName, szPwd;
		cin >> szName;
		cout << "\t\t\t   请输入密码：";
		cin >> szPwd;
		if (szName == "admin")
		{
			if (szPwd == "123")
			{
				nType = 0;
				break;
			}
			cout << "\t\t\t   密码错误！" << endl;
		}
		else
		{
			//用户是否存在
			bool bFound = false;
			for (size_t i = 0; i < vecStu_Course.size(); ++i)
			{
				string szTempName = vecStu_Course.at(i)->m_pStu->m_szName;
				if (szTempName == szName)
				{
					bFound = true;
					break;
				}
			}
			if (bFound)		//如果用户存在
			{
				if (szPwd == "123")
				{
					nType = 1;
					break;
				}
				cout << "\t\t\t   密码错误！" << endl;
			}
			else			//如果用户不存在
			{
				cout << "\t\t\t   用户名不存在！" << endl;
			}
		}
	}
	return nType;
}

//主菜单
int Menu(int nType)
{
	system("cls");
	int nSelect = -1;//初始化输入值 
	if (nType == 0)			//如果该用户是管理员，进入后台
	{
		cout << "**********************************************************************" << endl;
		cout << "***                         成绩管理系统		           ***" << endl;
		cout << "**********************************************************************" << endl;
		cout << "[1]添加学生信息" << endl;
		cout << "[2]删除学生信息" << endl;
		cout << "[3]修改学生信息" << endl;
		cout << "[4]查询指定科目分数最高和最低的学生的个人信息和单科成绩与全科成绩与等级" << endl;
		cout << "[5]查询指定学生的科目中多次考试中的最高分和最低分与平均成绩" << endl;
		cout << "[6]查询指定学生的单科班级成绩排名与总分成绩排名" << endl;
		cout << "[7]查询指定科目的各个等级段的学生人数与姓名和成绩" << endl;
		cout << "[0]退出" << endl;
		cout << "**********************************************************************" << endl;
		cout << "请输入数字0-7选择对应的功能" << endl; 
		cin >> nSelect;
		while(nSelect < 0 || nSelect > 7)
		{
			cout << "输入错误，请重新输入(0-7):" << endl;
			cin >> nSelect;
		}
	}
	else if (nType == 1)		//如果该用户是普通用户，进入客户端(btw好像不太行) 
	{
		cout << "**********************************************************************" << endl;
		cout << "***                         成绩管理系统		           ***" << endl;
		cout << "**********************************************************************" << endl;
		cout << "[1]查询指定科目分数最高和最低的学生的个人信息和单科成绩与全科成绩与等级 " << endl;
		cout << "[2]查询指定学生的科目中多次考试中的最高分和最低分与平均成绩" << endl;
		cout << "[3]查询指定学生的单科班级成绩排名与总分成绩排名" << endl;
		cout << "[4]查询指定科目的各个等级段的学生人数与姓名和成绩" << endl;
		cout << "[0]退出" << endl;
		cout << "**********************************************************************" << endl;
		cout << "请输入数字0-4选择对应的功能" << endl; 
		cin >> nSelect;
		while(nSelect < 0 || nSelect > 4) 
		{
			cout << "输入错误，请重新输入(0-4):" << endl;
			cin >> nSelect;
		}
		if (nSelect != 0)
		{
			nSelect += 3;//因为除0外总共有7种选择 
		}
	}
	return nSelect;
}

//添加学生信息
void InputFromKeyboard()
{
	int nStuCount = 0;//初始化输入值 
	cout << "请输入你要添加的学生的个数：" << endl;
	cin >> nStuCount;
	cout << endl;
	for(int i = 0;i < nStuCount; ++i)
	{
		Student* pStu = NULL;//定义指向student结构体的指针 ,都先定义成空指针 
		Course* pCourse = NULL;
		Stu_Course* pStu_Course = NULL;

		string szNum, szName, szSex;
		int nCourseCount = 0;

		cout << "请输入该学生的学号：" << endl;
		cin >> szNum;
		int nIndex =Search(szNum);//查询当前学号的学生信息
		while(nIndex >= 0)
		{
			cout << "该学号已存在，请重新输入：" << endl;
			cin >> szNum;
			nIndex = Search(szNum);//查询当前学号的学生信息
		}

		//如果不存在，则输入的学生信息
		cout << "请输入该学生的姓名：" << endl;
		cin >> szName;

		cout << "请输入该学生的性别：" << endl;
		cin >> szSex;

		pStu = new Student(szNum, szName, szSex);
		pStu_Course = new Stu_Course(pStu);

		cout << "请输入该生的课程数" << endl; 
		cin >> nCourseCount;

		for (int j = 0; j < nCourseCount; ++j)
		{
			string szCourseName, szTeacherName;//课程名,该课程任课老师名 
			float fScore;

			cout << "请输入第" << j + 1 << "科课程名称：" << endl;
			cin >> szCourseName;

			cout << "请输入该课程分数：" << endl;
			cin >> fScore;//课程分数 

			cout << "请输入该课程任课老师：" << endl;
			cin >> szTeacherName;

			pCourse = new Course(szCourseName, fScore, szTeacherName);
			pStu_Course->AddCourse(pCourse);
		}
		vecStu_Course.push_back(pStu_Course);//向vector容器中添加信息 
	}
}

//创建输入学生信息函数 
void Input()
{
	system("cls");
	printf("**********************************************************************\n");
	printf("                    [1]文件输入			  	           \n");
	printf("                    [2]键盘输入        	       \n");
	printf("**********************************************************************\n");
	printf("请输入数字1-2选择输入方式：");
	int nInputType;
	scanf("%d",&nInputType);//用C语言来控制格式化输入输出出会方便一点 
	while(nInputType < 1 || nInputType > 2)
	{
		printf("输入错误，请重新输入(1-2):");
		scanf("%d",&nInputType);
	}

	if (nInputType == 1)
	{
		ReadFile();
	}
	else if (nInputType == 2)
	{
		InputFromKeyboard();
	}

	printf("录入完成！\n");
} 

//删除学生信息
void Delete()
{
	int n = -1;
	system("cls");
	string szNum;
	cout << "请输入该学生的学号：" << endl;
	cin >> szNum;
	int nIndex = Search(szNum);//查询当前学号的学生信息
	if (nIndex < 0)		//未查询到该学生的信息
	{
		cout << "未查询到该学生的信息！" << endl;
	}
	else//查询到当前学号的学生信息
	{
		Stu_Course* pStu_Course = vecStu_Course.at(nIndex);
		//打印该学生的信息
		cout << "该学生的信息为：" << endl;
		cout << "==========================================" << endl;
		cout << "学号：" << pStu_Course->m_pStu->m_szNum << endl;//指针操作成员变量的成员变量 
		cout << "姓名：" <<pStu_Course->m_pStu->m_szName << endl;
		cout << "性别：" << pStu_Course->m_pStu->m_szSex << endl;
		cout << "确定要删除该学生的信息吗？" << endl;
		cout << "如果是请输入'y',如果不是请按任意键！" << endl;
		char a;
		cin >> a;
		if(a == 'y')//确认删除该学生的信息
		{
			vecStu_Course.erase(vecStu_Course.begin() + nIndex, vecStu_Course.begin() + nIndex + 1);//erase(b,e) 删除迭代器b和e所指定范围内的元素,返回一个迭代器 
			cout << "已删除该学生的信息！！" << endl;
		} 
		else
		{
			cout << "已经取消删除！！" << endl;
			fflush(stdin);//清空输入缓存区 
		}
	}
}

//修改学生信息
void Modify()
{
	int n = -1;
	system("cls");
	string szNum;
	cout << "请输入该学生的学号：" << endl;
	cin >> szNum;
	int nIndex = Search(szNum);//查询当前学号的学生信息
	if (nIndex < 0)//未查询到该学生的信息
	{
		cout << "未查询到该学生的信息！" << endl;
	}
	else//查询到当前学号的学生信息
	{
		Stu_Course* pStu_Course = vecStu_Course.at(nIndex);
		//打印该学生的信息
		cout << "该学生的信息为：" << endl;
		cout << "==========================================" << endl;
		cout << "学号：" << pStu_Course->m_pStu->m_szNum << endl;
		cout << "姓名：" << pStu_Course->m_pStu->m_szName << endl;
		cout << "性别：" << pStu_Course->m_pStu->m_szSex << endl;

		vector<Course*>* pVect = &pStu_Course->m_vecCourse;//最终还是指针取地址 
		while(1)
		{
			//选择要修改成绩的课程
			cout << "**********************************************************************" << endl;
			for (size_t i = 0; i < pVect->size(); ++i)
			{
				string szCourseName =pVect->at(i)->m_szCourseName;
				cout << "[" << i + 1 << "]\t\t" << szCourseName << endl;
			}
			cout << "\t\t[0]回到上一级菜单" << endl;
			cout << "**********************************************************************" << endl;
			cout << "请输入数字1-" << pVect->size() << "选择要修改成绩信息的课程（回到上一级菜单请输入0）：" << endl;
			int nCourse;
			cin >> nCourse;//要修改成绩信息的课程
			while(nCourse < 0 || nCourse > pVect->size())
			{
				cout << "输入错误，请重新输入(0-" << pVect->size() << "):" << endl;
				cin >> nCourse;//要修改成绩信息的课程
			}
			if (nCourse == 0)
			{
				system("cls");
				break;
			}
			cout << "请输入该课程成绩：" << endl;
			float fScore;
			cin >> fScore;//输入的课程成绩
			Course* pCourse = pVect->at(nCourse - 1);
			pCourse->m_fScore = fScore;

			//打印该学生修改后的信息
			cout << "该学生修改后的信息为：" << endl;
			cout << "==========================================" << endl;
			cout << "学号：" << pStu_Course->m_pStu->m_szNum << endl;
			cout << "姓名：" << pStu_Course->m_pStu->m_szName << endl;
			cout << "性别：" << pStu_Course->m_pStu->m_szSex << endl;
			for (size_t i = 0; i < pVect->size(); ++i)
			{
				string szCourseName =pVect->at(i)->m_szCourseName;
				cout << szCourseName << "\t\t";
			}
			cout << endl;
			for (size_t i = 0; i < pVect->size(); ++i)
			{
				float fScore =pVect->at(i)->m_fScore;
				cout << fScore << "\t\t";
			}
			cout << endl;
		}
	}
}

//(2)可输出指定科目分数最高和最低的学生的个人信息和单科成绩与全科成绩与等级
void Func_1()
{
	system("cls");
	while(1)
	{
		int n = -1;
		string szCourseName;
		cout << "请输入要查找的课程名称：（回到上一级菜单请输入0）" << endl;
		cin >> szCourseName;
		if (szCourseName == "0")
		{
			break;
		}
		//该课程分数最高和最低的学生课程成绩类
		Stu_Course* pMax, *pMin;
		pMax = pMin = NULL;
		//该课程最高分数和最低分数
		float fMax, fMin;
		fMax = -9999.0;
		fMin = 9999.0;
		for (int i = 0; i < vecStu_Course.size(); ++i)
		{
			//当前学生课程数组
			vector<Course*> vectCourse = vecStu_Course.at(i)->m_vecCourse;
			for (int j = 0; j < vectCourse.size(); ++j)
			{
				if (vectCourse.at(j)->m_szCourseName == szCourseName)
				{
					if (vectCourse.at(j)->m_fScore > fMax)
					{
						fMax = vectCourse.at(j)->m_fScore;
						pMax = vecStu_Course.at(i);
					}
					if (vectCourse.at(j)->m_fScore < fMin)
					{
						fMin = vectCourse.at(j)->m_fScore;
						pMin = vecStu_Course.at(i);
					}
					break;
				}
			}
		}

		if (pMax == NULL)//未查询到该学生的信息
		{
			cout << "未查询到该课程最高分的学生信息！" << endl;
			return;
		}
		if (pMin == NULL)//未查询到该学生的信息
		{
			cout << "未查询到该课程最低分的学生信息！" << endl;
			return;
		}
		//打印该学生的信息
		cout << szCourseName << "分数最高的学生信息为：" << endl;
		cout << "==========================================" << endl;
		cout << "学号：" << pMax->m_pStu->m_szNum << endl;
		cout << "姓名：" << pMax->m_pStu->m_szName << endl;
		cout << "性别：" << pMax->m_pStu->m_szSex << endl;

		for (int i = 0; i < pMax->m_vecCourse.size(); ++i)
		{
			string szCourseName = pMax->m_vecCourse.at(i)->m_szCourseName;
			cout << szCourseName << "\t\t";
		}
		cout << endl;
		for (int i = 0; i < pMax->m_vecCourse.size(); ++i)
		{
			float fScore = pMax->m_vecCourse.at(i)->m_fScore;
			cout << fScore << "\t\t";
		}
		cout << endl;

		cout << szCourseName << "分数最低的学生信息为：" << endl;
		cout << "==========================================" << endl;
		cout << "学号：" << pMin->m_pStu->m_szNum << endl;
		cout << "姓名：" << pMin->m_pStu->m_szName << endl;
		cout << "性别：" << pMin->m_pStu->m_szSex << endl;

		for (int i = 0; i < pMin->m_vecCourse.size(); ++i)
		{
			string szCourseName = pMin->m_vecCourse.at(i)->m_szCourseName;
			cout << szCourseName << "\t\t";
		}
		cout << endl;
		for (int i = 0; i < pMin->m_vecCourse.size(); ++i)
		{
			float fScore = pMin->m_vecCourse.at(i)->m_fScore;
			cout << fScore << "\t\t";
		}
		cout << endl;
	}
}

//(3)可输出指定学生的科目中多次考试中的最高分和最低分与平均成绩
void Func_2()
{
	system("cls");
	while(1)
	{
		int n = -1;
		string szNum;
		cout << "请输入要查找的学生学号：（回到上一级菜单请输入0）" << endl;
		cin >> szNum;
		if (szNum == "0")
		{
			break;
		}
		Stu_Course* pStu_Course = NULL;
		for (int i = 0; i < vecStu_Course.size(); ++i)
		{
			if (vecStu_Course.at(i)->m_pStu->m_szNum == szNum)
			{
				pStu_Course = vecStu_Course.at(i);
				break;
			}
		}

		if (pStu_Course == NULL)//未查询到该学生的信息
		{
			cout << "未查询到该学生信息！" << endl;
		}
		else
		{
			//打印该学生的信息
			cout << "该学生信息为：" << endl;
			cout << "==========================================" << endl;
			cout << "学号：" << pStu_Course->m_pStu->m_szNum << endl;
			cout << "姓名：" << pStu_Course->m_pStu->m_szName << endl;
			cout << "性别：" << pStu_Course->m_pStu->m_szSex << endl;

			float fMax, fMin, fSum;
			fMax = -9999.0;
			fMin = 9999.0;
			fSum = 0.0;
			vector<Course*> vectCourse = pStu_Course->m_vecCourse;
			for (int i = 0; i < vectCourse.size(); ++i)
			{
				fSum += vectCourse.at(i)->m_fScore;
				if (vectCourse.at(i)->m_fScore > fMax)
				{
					fMax = vectCourse.at(i)->m_fScore;
				}
				if (vectCourse.at(i)->m_fScore < fMin)
				{
					fMin = vectCourse.at(i)->m_fScore;
				}
			}
			cout << "各科最高分：" << fMax << endl;
			cout << "各科最低分：" << fMin << endl;
			cout << "平均成绩：" << fSum / vectCourse.size()<< endl;
			cout << endl;
		}
	}
}

//(4)可输出指定学生的单科班级成绩排名与总分成绩排名
void Func_3()
{
	system("cls");
	while(1)
	{
		int n = -1;
		string szNum;
		cout << "请输入要查找的学生学号：（回到上一级菜单请输入0）" << endl;
		cin >> szNum;
		if (szNum == "0")
		{
			break;
		}
		Stu_Course* pStu_Course = NULL;
		for (int i = 0; i < vecStu_Course.size(); ++i)
		{
			if (vecStu_Course.at(i)->m_pStu->m_szNum == szNum)
			{
				pStu_Course = vecStu_Course.at(i);
				break;
			}
		}

		if (pStu_Course == NULL)//未查询到该学生的信息
		{
			cout << "未查询到该学生信息！" << endl;
		}
		else
		{
			//打印该学生的信息
			cout << "该学生信息为：" << endl;
			cout << "==========================================" << endl;
			cout << "学号：" << pStu_Course->m_pStu->m_szNum << endl;
			cout << "姓名：" << pStu_Course->m_pStu->m_szName << endl;
			cout << "性别：" << pStu_Course->m_pStu->m_szSex << endl;

			vector<Course*> vectCourse = pStu_Course->m_vecCourse;
			int nCourseCount = vectCourse.size();
			int nSumRank = 1;
			for (int i = 0; i < vecStu_Course.size(); ++i)
			{
				vector<Course*> vectTempCourse = vecStu_Course.at(i)->m_vecCourse;
				int nTempSum = 0;
				int nSum = 0;
				for (int j = 0; j < nCourseCount; ++j)
				{
					nSum += vectCourse.at(j)->m_fScore;
					nTempSum += vectTempCourse.at(j)->m_fScore;
					if (vectCourse.at(j)->m_fScore < vectTempCourse.at(j)->m_fScore)
					{
						++vectCourse.at(j)->m_nRank;
					}
				}
				if(nSum < nTempSum)
				{
					++nSumRank;
				}
			}
			//输出单科班级成绩排名与总分成绩排名
			for (int i = 0; i < vectCourse.size(); ++i)
			{
				string szCourseName = vectCourse.at(i)->m_szCourseName;
				cout << szCourseName << "\t\t";
			}
			cout << "总成绩" << endl;
			for (int i = 0; i < vectCourse.size(); ++i)
			{
				int nRank = vectCourse.at(i)->m_nRank;
				cout << nRank << "\t\t";//单科成绩排名 
			}
			cout << nSumRank << endl;//总分成绩排名 
		}
	}
}

//(5)可输出指定科目的各个等级段的学生人数与姓名和成绩
void Func_4()
{
	system("cls");
	while(1)
	{
		int n = -1;
		string szCourseName;
		cout << "请输入要查找的课程名称：（回到上一级菜单请输入0）" << endl;
		cin >> szCourseName;
		if (szCourseName == "0")
		{
			break;
		}
		vector<Stu_Course*> vect1;		//<60
		vector<Stu_Course*> vect2;		//60-79
		vector<Stu_Course*> vect3;		//80-89
		vector<Stu_Course*> vect4;		//>=90
		int nNum[4] = {0};
		for (int i = 0; i < vecStu_Course.size(); ++i)
		{
			//当前学生课程数组
			vector<Course*> vectCourse = vecStu_Course.at(i)->m_vecCourse;
			for (int j = 0; j < vectCourse.size(); ++j)
			{
				if (vectCourse.at(j)->m_szCourseName == szCourseName)
				{
					if (vectCourse.at(j)->m_fScore < 60.0)
					{
						vect1.push_back(vecStu_Course.at(i));
						++nNum[0];
					}
					else if (vectCourse.at(j)->m_fScore >= 60.0 && vectCourse.at(j)->m_fScore < 80.0)
					{
						vect2.push_back(vecStu_Course.at(i));
						++nNum[1];
					}
					else if (vectCourse.at(j)->m_fScore >= 80.0 && vectCourse.at(j)->m_fScore < 90.0)
					{
						vect3.push_back(vecStu_Course.at(i));
						++nNum[2];
					}
					else
					{
						vect4.push_back(vecStu_Course.at(i));
						++nNum[3];
					}
					break;
				}
			}
		}

		//打印该学生的信息
		cout << "==========================================" << endl;
		cout << "<60：\t" << vect1.size() << "人" << endl;
		for (int i = 0; i < vect1.size(); ++i)
		{
			string szName = (vect1.at(i))->m_pStu->m_szName;
			cout << szName << "\t";
		}
		cout << endl << endl;

		cout << "60-79：\t" << vect2.size() << "人" << endl;
		for (int i = 0; i < vect2.size(); ++i)
		{
			string szName = (vect2.at(i))->m_pStu->m_szName;
			cout << szName << "\t";
		}
		cout << endl << endl;

		cout << "80-89：\t" << vect3.size() << "人" << endl;
		for (int i = 0; i < vect3.size(); ++i)
		{
			string szName = (vect3.at(i))->m_pStu->m_szName;
			cout << szName << "\t";
		}
		cout << endl << endl;

		cout << ">=90：\t" << vect4.size() << "人" << endl;
		for (int i = 0; i < vect4.size(); ++i)
		{
			string szName = (vect4.at(i))->m_pStu->m_szName;
			cout << szName << "\t";
		}
		cout << endl << endl;
	}
}

//结束、退出
void End()
{
	system("cls");
	WriteFile();//写回txt 
	cout << "谢谢使用！" << endl;
	exit(0);//退出 void exit(int);作用是无条件的退出程序,可以根据习惯设置不同的值表示不同原知因的退出,exit(0)可以在正常退出次程序的运行,而exit(1)的是由于错误导致的结束.exit(3)也行啊 

}

int main()
{
	//Init();					//初始化学生课程成绩类数组
	int nType = Login();	//登录
	while(1)
	{
		int n = Menu(nType);//菜单
		switch(n)
		{
		case 1:
			{
				Input();	//(1)对各类中的实现进行添加
				break;
			}
		case 2:
			{
				Delete();	//对各类中的实现进行删除
				break;
			}
		case 3:
			{
				Modify();	//对各类中的实现进行修改
				break;
			}
		case 4:
			{
				Func_1();	//(2)可输出指定科目分数最高和最低的学生的个人信息和单科成绩与全科成绩与等级
				break;
			}
		case 5:
			{
				Func_2();	//(3)可输出指定学生的科目中多次考试中的最高分和最低分与平均成绩
				break;
			}
		case 6:
			{
				Func_3();	//(4)可输出指定学生的单科班级成绩排名与总分成绩排名
				break;
			}
		case 7:
			{
				Func_4();	//(5)可输出指定科目的各个等级段的学生人数与姓名和成绩
				break;
			}
		case 0:
			{
				End();		//结束，退出
			}
		}
	}
	system("pause");
	return 0;
}
