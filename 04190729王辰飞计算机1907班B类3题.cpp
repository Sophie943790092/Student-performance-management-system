#include<iostream> //��¼��:admin   ����:123 
#include<fstream>//�����ļ� 
#include<string>
#include <vector>
#include <iterator>// ��׼�⺯��begin(),end() 
using namespace std;


//ѧ����
class Student
{
public://����˵����--��Ա���������������ڱ�����,public��Ա������Ľӿ� 
	Student()//
	{
 
	}

	Student(string szNum, string szName, string szSex) 
	{
		m_szNum = szNum;//��ʼ�� ��ֵ   ʹ�ù��캯���Ĳ�����Ϊ��Ա�ĳ�ʼֵ 
		m_szName = szName;
		m_szSex = szSex;
		m_szPwd = "123";;
	}

public:
	string m_szNum;			//ѧ��
	string m_szName;		//����
	string m_szSex;			//�Ա�
	string m_szPwd;			//����
};

//�γ̳ɼ���
class Course
{
public:
	Course()
	{
		m_nRank = 1;//�ɼ�����,��ʼ��Ϊ1 
	}

	Course(string szCourseName, float fScore, string szTeacherName)
	{
		m_szCourseName = szCourseName;
		m_fScore = fScore;
		m_szTeacherName = szTeacherName;
		m_nRank = 1;
	}

public:
	string m_szCourseName;		//�γ�����
	float m_fScore;				//�ɼ�
	string m_szTeacherName;		//�ο���ʦ
	int m_nRank;				//�ȼ�
};

//ѧ���γ̳ɼ���
class Stu_Course
{
public:
	Stu_Course()
	{
		m_pStu = NULL;
	}

	Stu_Course(Student* &pStu)//����ָ��Student��ָ�� pStu
	{
		m_pStu = pStu;//��ʼ�� 
	}

	~Stu_Course()//��������,�ͷ��ڴ�,������ڴ�й© !! 
	{
		if (!m_pStu)
		{
			delete m_pStu;
			m_pStu = NULL;
		}
		for (size_t i = 0; i < m_vecCourse.size(); ++i)//size_t=sizetype һ��������¼��С����������
		{
			delete m_vecCourse.at(i);
		}
	}

	void AddCourse(Course* &pCourse)
	{
		m_vecCourse.push_back(pCourse);
	}

public:
	Student* m_pStu;					//ѧ�����Ա
	vector<Course*> m_vecCourse;		//��ѧ���γ��������Ա
};

//ѧ���γ̳ɼ�������
vector<Stu_Course*> vecStu_Course;

//���ļ���ȡ����--- 
void ReadFile()
{
	FILE *fp;//�ļ�ָ��
	int n;//�ļ���������
	if((fp=fopen("Scores.txt","r"))==NULL)//���ļ� �⺯�� FILE *fopen(const char *filename, const char *mode) "r"��ֻ����ʽ���ļ� 
	{
		return;//Ҫ���ش������ 
	}
	for(n=0; !feof(fp); n++)//����ѭ�������ļ�  int feof(FILE *stream);����ļ��Ƿ���� 
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

		pCourse = new Course("A", f1, "����");
		pStu_Course->AddCourse(pCourse);
		pCourse = new Course("B", f2, "����");
		pStu_Course->AddCourse(pCourse);
		pCourse = new Course("C", f3, "����");
		pStu_Course->AddCourse(pCourse);
		pCourse = new Course("D", f4, "����");
		pStu_Course->AddCourse(pCourse);
		vecStu_Course.push_back(pStu_Course);
	}
	fclose(fp);//�ر��ļ�
}

//���洢�ɼ���Ϣ������д���ļ�
void WriteFile()
{
	system("cls");
	FILE *fp;//�ļ�ָ��
	fp=fopen("Scores.txt","w+");//�򿪿ɶ�д�ļ�
	if (fp  == NULL)
	{
		return;
	}
	for (int i = 0; i < vecStu_Course.size(); ++i)
	{
		Student* pStu = vecStu_Course.at(i)->m_pStu;
		vector<Course*>* vectCourse = &vecStu_Course.at(i)->m_vecCourse;//c.at(n)�����±�Ϊn��Ԫ�ص�����,���±�Խ��,���׳��쳣 
		
		float ff = vectCourse->at(0)->m_fScore;
		fprintf(fp, "%s\t%s\t%s\t%s\t%f\t%f\t%f\t%f\t", pStu->m_szNum.c_str(), pStu->m_szName.c_str(), pStu->m_szSex.c_str(), pStu->m_szPwd.c_str(), vectCourse->at(0)->m_fScore, vectCourse->at(1)->m_fScore, vectCourse->at(2)->m_fScore, vectCourse->at(3)->m_fScore);//��ѧ����Ϣд���ļ�
		fputs("\n",fp);//�ļ�ָ��ָ����һ��
	}
	fclose(fp);//�ر��ļ�
}


//����ѧ�Ų�ѯ
int Search(string szNum)
{
	int nIndex ,nCount;
	nIndex = nCount = -1;
	vector<Stu_Course*>::iterator it = vecStu_Course.begin();
	for (; it != vecStu_Course.end(); ++it)//for(....;it !=  vecStu_Course.end() && it->empty();++it)//isspaceӦ��Ҳ���� 
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

//��¼
int Login()
{
	int nType = -1;	//��ʼ��Ϊ(-1)����δ����	//�û�����-- 0������Ա��1����ͨ�û�
	while(1)
	{
		cout << endl << endl;
		cout << "**********************************************************************" << endl;
		cout << "***                      ��ӭ����ɼ�����ϵͳ		           ***" << endl;
		cout << "**********************************************************************" << endl << endl << endl; 
		cout << "\t\t\t   �������û�����";//ע��Ժ�λ�� 
		string szName, szPwd;
		cin >> szName;
		cout << "\t\t\t   ���������룺";
		cin >> szPwd;
		if (szName == "admin")
		{
			if (szPwd == "123")
			{
				nType = 0;
				break;
			}
			cout << "\t\t\t   �������" << endl;
		}
		else
		{
			//�û��Ƿ����
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
			if (bFound)		//����û�����
			{
				if (szPwd == "123")
				{
					nType = 1;
					break;
				}
				cout << "\t\t\t   �������" << endl;
			}
			else			//����û�������
			{
				cout << "\t\t\t   �û��������ڣ�" << endl;
			}
		}
	}
	return nType;
}

//���˵�
int Menu(int nType)
{
	system("cls");
	int nSelect = -1;//��ʼ������ֵ 
	if (nType == 0)			//������û��ǹ���Ա�������̨
	{
		cout << "**********************************************************************" << endl;
		cout << "***                         �ɼ�����ϵͳ		           ***" << endl;
		cout << "**********************************************************************" << endl;
		cout << "[1]���ѧ����Ϣ" << endl;
		cout << "[2]ɾ��ѧ����Ϣ" << endl;
		cout << "[3]�޸�ѧ����Ϣ" << endl;
		cout << "[4]��ѯָ����Ŀ������ߺ���͵�ѧ���ĸ�����Ϣ�͵��Ƴɼ���ȫ�Ƴɼ���ȼ�" << endl;
		cout << "[5]��ѯָ��ѧ���Ŀ�Ŀ�ж�ο����е���߷ֺ���ͷ���ƽ���ɼ�" << endl;
		cout << "[6]��ѯָ��ѧ���ĵ��ư༶�ɼ��������ֳܷɼ�����" << endl;
		cout << "[7]��ѯָ����Ŀ�ĸ����ȼ��ε�ѧ�������������ͳɼ�" << endl;
		cout << "[0]�˳�" << endl;
		cout << "**********************************************************************" << endl;
		cout << "����������0-7ѡ���Ӧ�Ĺ���" << endl; 
		cin >> nSelect;
		while(nSelect < 0 || nSelect > 7)
		{
			cout << "�����������������(0-7):" << endl;
			cin >> nSelect;
		}
	}
	else if (nType == 1)		//������û�����ͨ�û�������ͻ���(btw����̫��) 
	{
		cout << "**********************************************************************" << endl;
		cout << "***                         �ɼ�����ϵͳ		           ***" << endl;
		cout << "**********************************************************************" << endl;
		cout << "[1]��ѯָ����Ŀ������ߺ���͵�ѧ���ĸ�����Ϣ�͵��Ƴɼ���ȫ�Ƴɼ���ȼ� " << endl;
		cout << "[2]��ѯָ��ѧ���Ŀ�Ŀ�ж�ο����е���߷ֺ���ͷ���ƽ���ɼ�" << endl;
		cout << "[3]��ѯָ��ѧ���ĵ��ư༶�ɼ��������ֳܷɼ�����" << endl;
		cout << "[4]��ѯָ����Ŀ�ĸ����ȼ��ε�ѧ�������������ͳɼ�" << endl;
		cout << "[0]�˳�" << endl;
		cout << "**********************************************************************" << endl;
		cout << "����������0-4ѡ���Ӧ�Ĺ���" << endl; 
		cin >> nSelect;
		while(nSelect < 0 || nSelect > 4) 
		{
			cout << "�����������������(0-4):" << endl;
			cin >> nSelect;
		}
		if (nSelect != 0)
		{
			nSelect += 3;//��Ϊ��0���ܹ���7��ѡ�� 
		}
	}
	return nSelect;
}

//���ѧ����Ϣ
void InputFromKeyboard()
{
	int nStuCount = 0;//��ʼ������ֵ 
	cout << "��������Ҫ��ӵ�ѧ���ĸ�����" << endl;
	cin >> nStuCount;
	cout << endl;
	for(int i = 0;i < nStuCount; ++i)
	{
		Student* pStu = NULL;//����ָ��student�ṹ���ָ�� ,���ȶ���ɿ�ָ�� 
		Course* pCourse = NULL;
		Stu_Course* pStu_Course = NULL;

		string szNum, szName, szSex;
		int nCourseCount = 0;

		cout << "�������ѧ����ѧ�ţ�" << endl;
		cin >> szNum;
		int nIndex =Search(szNum);//��ѯ��ǰѧ�ŵ�ѧ����Ϣ
		while(nIndex >= 0)
		{
			cout << "��ѧ���Ѵ��ڣ����������룺" << endl;
			cin >> szNum;
			nIndex = Search(szNum);//��ѯ��ǰѧ�ŵ�ѧ����Ϣ
		}

		//��������ڣ��������ѧ����Ϣ
		cout << "�������ѧ����������" << endl;
		cin >> szName;

		cout << "�������ѧ�����Ա�" << endl;
		cin >> szSex;

		pStu = new Student(szNum, szName, szSex);
		pStu_Course = new Stu_Course(pStu);

		cout << "����������Ŀγ���" << endl; 
		cin >> nCourseCount;

		for (int j = 0; j < nCourseCount; ++j)
		{
			string szCourseName, szTeacherName;//�γ���,�ÿγ��ο���ʦ�� 
			float fScore;

			cout << "�������" << j + 1 << "�ƿγ����ƣ�" << endl;
			cin >> szCourseName;

			cout << "������ÿγ̷�����" << endl;
			cin >> fScore;//�γ̷��� 

			cout << "������ÿγ��ο���ʦ��" << endl;
			cin >> szTeacherName;

			pCourse = new Course(szCourseName, fScore, szTeacherName);
			pStu_Course->AddCourse(pCourse);
		}
		vecStu_Course.push_back(pStu_Course);//��vector�����������Ϣ 
	}
}

//��������ѧ����Ϣ���� 
void Input()
{
	system("cls");
	printf("**********************************************************************\n");
	printf("                    [1]�ļ�����			  	           \n");
	printf("                    [2]��������        	       \n");
	printf("**********************************************************************\n");
	printf("����������1-2ѡ�����뷽ʽ��");
	int nInputType;
	scanf("%d",&nInputType);//��C���������Ƹ�ʽ������������᷽��һ�� 
	while(nInputType < 1 || nInputType > 2)
	{
		printf("�����������������(1-2):");
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

	printf("¼����ɣ�\n");
} 

//ɾ��ѧ����Ϣ
void Delete()
{
	int n = -1;
	system("cls");
	string szNum;
	cout << "�������ѧ����ѧ�ţ�" << endl;
	cin >> szNum;
	int nIndex = Search(szNum);//��ѯ��ǰѧ�ŵ�ѧ����Ϣ
	if (nIndex < 0)		//δ��ѯ����ѧ������Ϣ
	{
		cout << "δ��ѯ����ѧ������Ϣ��" << endl;
	}
	else//��ѯ����ǰѧ�ŵ�ѧ����Ϣ
	{
		Stu_Course* pStu_Course = vecStu_Course.at(nIndex);
		//��ӡ��ѧ������Ϣ
		cout << "��ѧ������ϢΪ��" << endl;
		cout << "==========================================" << endl;
		cout << "ѧ�ţ�" << pStu_Course->m_pStu->m_szNum << endl;//ָ�������Ա�����ĳ�Ա���� 
		cout << "������" <<pStu_Course->m_pStu->m_szName << endl;
		cout << "�Ա�" << pStu_Course->m_pStu->m_szSex << endl;
		cout << "ȷ��Ҫɾ����ѧ������Ϣ��" << endl;
		cout << "�����������'y',��������밴�������" << endl;
		char a;
		cin >> a;
		if(a == 'y')//ȷ��ɾ����ѧ������Ϣ
		{
			vecStu_Course.erase(vecStu_Course.begin() + nIndex, vecStu_Course.begin() + nIndex + 1);//erase(b,e) ɾ��������b��e��ָ����Χ�ڵ�Ԫ��,����һ�������� 
			cout << "��ɾ����ѧ������Ϣ����" << endl;
		} 
		else
		{
			cout << "�Ѿ�ȡ��ɾ������" << endl;
			fflush(stdin);//������뻺���� 
		}
	}
}

//�޸�ѧ����Ϣ
void Modify()
{
	int n = -1;
	system("cls");
	string szNum;
	cout << "�������ѧ����ѧ�ţ�" << endl;
	cin >> szNum;
	int nIndex = Search(szNum);//��ѯ��ǰѧ�ŵ�ѧ����Ϣ
	if (nIndex < 0)//δ��ѯ����ѧ������Ϣ
	{
		cout << "δ��ѯ����ѧ������Ϣ��" << endl;
	}
	else//��ѯ����ǰѧ�ŵ�ѧ����Ϣ
	{
		Stu_Course* pStu_Course = vecStu_Course.at(nIndex);
		//��ӡ��ѧ������Ϣ
		cout << "��ѧ������ϢΪ��" << endl;
		cout << "==========================================" << endl;
		cout << "ѧ�ţ�" << pStu_Course->m_pStu->m_szNum << endl;
		cout << "������" << pStu_Course->m_pStu->m_szName << endl;
		cout << "�Ա�" << pStu_Course->m_pStu->m_szSex << endl;

		vector<Course*>* pVect = &pStu_Course->m_vecCourse;//���ջ���ָ��ȡ��ַ 
		while(1)
		{
			//ѡ��Ҫ�޸ĳɼ��Ŀγ�
			cout << "**********************************************************************" << endl;
			for (size_t i = 0; i < pVect->size(); ++i)
			{
				string szCourseName =pVect->at(i)->m_szCourseName;
				cout << "[" << i + 1 << "]\t\t" << szCourseName << endl;
			}
			cout << "\t\t[0]�ص���һ���˵�" << endl;
			cout << "**********************************************************************" << endl;
			cout << "����������1-" << pVect->size() << "ѡ��Ҫ�޸ĳɼ���Ϣ�Ŀγ̣��ص���һ���˵�������0����" << endl;
			int nCourse;
			cin >> nCourse;//Ҫ�޸ĳɼ���Ϣ�Ŀγ�
			while(nCourse < 0 || nCourse > pVect->size())
			{
				cout << "�����������������(0-" << pVect->size() << "):" << endl;
				cin >> nCourse;//Ҫ�޸ĳɼ���Ϣ�Ŀγ�
			}
			if (nCourse == 0)
			{
				system("cls");
				break;
			}
			cout << "������ÿγ̳ɼ���" << endl;
			float fScore;
			cin >> fScore;//����Ŀγ̳ɼ�
			Course* pCourse = pVect->at(nCourse - 1);
			pCourse->m_fScore = fScore;

			//��ӡ��ѧ���޸ĺ����Ϣ
			cout << "��ѧ���޸ĺ����ϢΪ��" << endl;
			cout << "==========================================" << endl;
			cout << "ѧ�ţ�" << pStu_Course->m_pStu->m_szNum << endl;
			cout << "������" << pStu_Course->m_pStu->m_szName << endl;
			cout << "�Ա�" << pStu_Course->m_pStu->m_szSex << endl;
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

//(2)�����ָ����Ŀ������ߺ���͵�ѧ���ĸ�����Ϣ�͵��Ƴɼ���ȫ�Ƴɼ���ȼ�
void Func_1()
{
	system("cls");
	while(1)
	{
		int n = -1;
		string szCourseName;
		cout << "������Ҫ���ҵĿγ����ƣ����ص���һ���˵�������0��" << endl;
		cin >> szCourseName;
		if (szCourseName == "0")
		{
			break;
		}
		//�ÿγ̷�����ߺ���͵�ѧ���γ̳ɼ���
		Stu_Course* pMax, *pMin;
		pMax = pMin = NULL;
		//�ÿγ���߷�������ͷ���
		float fMax, fMin;
		fMax = -9999.0;
		fMin = 9999.0;
		for (int i = 0; i < vecStu_Course.size(); ++i)
		{
			//��ǰѧ���γ�����
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

		if (pMax == NULL)//δ��ѯ����ѧ������Ϣ
		{
			cout << "δ��ѯ���ÿγ���߷ֵ�ѧ����Ϣ��" << endl;
			return;
		}
		if (pMin == NULL)//δ��ѯ����ѧ������Ϣ
		{
			cout << "δ��ѯ���ÿγ���ͷֵ�ѧ����Ϣ��" << endl;
			return;
		}
		//��ӡ��ѧ������Ϣ
		cout << szCourseName << "������ߵ�ѧ����ϢΪ��" << endl;
		cout << "==========================================" << endl;
		cout << "ѧ�ţ�" << pMax->m_pStu->m_szNum << endl;
		cout << "������" << pMax->m_pStu->m_szName << endl;
		cout << "�Ա�" << pMax->m_pStu->m_szSex << endl;

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

		cout << szCourseName << "������͵�ѧ����ϢΪ��" << endl;
		cout << "==========================================" << endl;
		cout << "ѧ�ţ�" << pMin->m_pStu->m_szNum << endl;
		cout << "������" << pMin->m_pStu->m_szName << endl;
		cout << "�Ա�" << pMin->m_pStu->m_szSex << endl;

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

//(3)�����ָ��ѧ���Ŀ�Ŀ�ж�ο����е���߷ֺ���ͷ���ƽ���ɼ�
void Func_2()
{
	system("cls");
	while(1)
	{
		int n = -1;
		string szNum;
		cout << "������Ҫ���ҵ�ѧ��ѧ�ţ����ص���һ���˵�������0��" << endl;
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

		if (pStu_Course == NULL)//δ��ѯ����ѧ������Ϣ
		{
			cout << "δ��ѯ����ѧ����Ϣ��" << endl;
		}
		else
		{
			//��ӡ��ѧ������Ϣ
			cout << "��ѧ����ϢΪ��" << endl;
			cout << "==========================================" << endl;
			cout << "ѧ�ţ�" << pStu_Course->m_pStu->m_szNum << endl;
			cout << "������" << pStu_Course->m_pStu->m_szName << endl;
			cout << "�Ա�" << pStu_Course->m_pStu->m_szSex << endl;

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
			cout << "������߷֣�" << fMax << endl;
			cout << "������ͷ֣�" << fMin << endl;
			cout << "ƽ���ɼ���" << fSum / vectCourse.size()<< endl;
			cout << endl;
		}
	}
}

//(4)�����ָ��ѧ���ĵ��ư༶�ɼ��������ֳܷɼ�����
void Func_3()
{
	system("cls");
	while(1)
	{
		int n = -1;
		string szNum;
		cout << "������Ҫ���ҵ�ѧ��ѧ�ţ����ص���һ���˵�������0��" << endl;
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

		if (pStu_Course == NULL)//δ��ѯ����ѧ������Ϣ
		{
			cout << "δ��ѯ����ѧ����Ϣ��" << endl;
		}
		else
		{
			//��ӡ��ѧ������Ϣ
			cout << "��ѧ����ϢΪ��" << endl;
			cout << "==========================================" << endl;
			cout << "ѧ�ţ�" << pStu_Course->m_pStu->m_szNum << endl;
			cout << "������" << pStu_Course->m_pStu->m_szName << endl;
			cout << "�Ա�" << pStu_Course->m_pStu->m_szSex << endl;

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
			//������ư༶�ɼ��������ֳܷɼ�����
			for (int i = 0; i < vectCourse.size(); ++i)
			{
				string szCourseName = vectCourse.at(i)->m_szCourseName;
				cout << szCourseName << "\t\t";
			}
			cout << "�ܳɼ�" << endl;
			for (int i = 0; i < vectCourse.size(); ++i)
			{
				int nRank = vectCourse.at(i)->m_nRank;
				cout << nRank << "\t\t";//���Ƴɼ����� 
			}
			cout << nSumRank << endl;//�ֳܷɼ����� 
		}
	}
}

//(5)�����ָ����Ŀ�ĸ����ȼ��ε�ѧ�������������ͳɼ�
void Func_4()
{
	system("cls");
	while(1)
	{
		int n = -1;
		string szCourseName;
		cout << "������Ҫ���ҵĿγ����ƣ����ص���һ���˵�������0��" << endl;
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
			//��ǰѧ���γ�����
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

		//��ӡ��ѧ������Ϣ
		cout << "==========================================" << endl;
		cout << "<60��\t" << vect1.size() << "��" << endl;
		for (int i = 0; i < vect1.size(); ++i)
		{
			string szName = (vect1.at(i))->m_pStu->m_szName;
			cout << szName << "\t";
		}
		cout << endl << endl;

		cout << "60-79��\t" << vect2.size() << "��" << endl;
		for (int i = 0; i < vect2.size(); ++i)
		{
			string szName = (vect2.at(i))->m_pStu->m_szName;
			cout << szName << "\t";
		}
		cout << endl << endl;

		cout << "80-89��\t" << vect3.size() << "��" << endl;
		for (int i = 0; i < vect3.size(); ++i)
		{
			string szName = (vect3.at(i))->m_pStu->m_szName;
			cout << szName << "\t";
		}
		cout << endl << endl;

		cout << ">=90��\t" << vect4.size() << "��" << endl;
		for (int i = 0; i < vect4.size(); ++i)
		{
			string szName = (vect4.at(i))->m_pStu->m_szName;
			cout << szName << "\t";
		}
		cout << endl << endl;
	}
}

//�������˳�
void End()
{
	system("cls");
	WriteFile();//д��txt 
	cout << "ллʹ�ã�" << endl;
	exit(0);//�˳� void exit(int);���������������˳�����,���Ը���ϰ�����ò�ͬ��ֵ��ʾ��ͬԭ֪����˳�,exit(0)�����������˳��γ��������,��exit(1)�������ڴ����µĽ���.exit(3)Ҳ�а� 

}

int main()
{
	//Init();					//��ʼ��ѧ���γ̳ɼ�������
	int nType = Login();	//��¼
	while(1)
	{
		int n = Menu(nType);//�˵�
		switch(n)
		{
		case 1:
			{
				Input();	//(1)�Ը����е�ʵ�ֽ������
				break;
			}
		case 2:
			{
				Delete();	//�Ը����е�ʵ�ֽ���ɾ��
				break;
			}
		case 3:
			{
				Modify();	//�Ը����е�ʵ�ֽ����޸�
				break;
			}
		case 4:
			{
				Func_1();	//(2)�����ָ����Ŀ������ߺ���͵�ѧ���ĸ�����Ϣ�͵��Ƴɼ���ȫ�Ƴɼ���ȼ�
				break;
			}
		case 5:
			{
				Func_2();	//(3)�����ָ��ѧ���Ŀ�Ŀ�ж�ο����е���߷ֺ���ͷ���ƽ���ɼ�
				break;
			}
		case 6:
			{
				Func_3();	//(4)�����ָ��ѧ���ĵ��ư༶�ɼ��������ֳܷɼ�����
				break;
			}
		case 7:
			{
				Func_4();	//(5)�����ָ����Ŀ�ĸ����ȼ��ε�ѧ�������������ͳɼ�
				break;
			}
		case 0:
			{
				End();		//�������˳�
			}
		}
	}
	system("pause");
	return 0;
}
