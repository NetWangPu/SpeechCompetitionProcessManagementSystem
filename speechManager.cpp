#include "speechManager.h"

SpeechManager::SpeechManager()
{
	//// 初始化容器和属性
	this->initSpeech();
	//// 创建选手
	this->createSpeaker();
	//// 获取往届记录
	//this->loadRecord();
}

SpeechManager::~SpeechManager()
{

}

void SpeechManager::showMenu()
{
	cout << "********************************************" << endl;
	cout << "*************  欢迎参加演讲比赛 *************" << endl;
	cout << "*************  1.开始演讲比赛  *************" << endl;
	cout << "*************  2.查看往届记录  *************" << endl;
	cout << "*************  3.清空比赛记录  *************" << endl;
	cout << "*************  0.退出比赛程序  *************" << endl;
	cout << "********************************************" << endl;
	cout << endl;
}

void SpeechManager::initSpeech()
{
	this->v1.clear();
	this->v2.clear();
	this->vVictory.clear();
	this->m_Speaker.clear(); //clear the map
	this->m_Index = 1; //initialization the index
}

void SpeechManager::exitSystem()
{
	cout << "欢迎下次使用" << endl;
	system("pause");
	exit(0);
}

void SpeechManager::createSpeaker()
{
	string nameSeed = "ABCDEFGHIJKL";
	for (int i = 0; i < nameSeed.size(); i++)
	{
		string name = "选手";
		name += nameSeed[i];
		Speaker sp;
		sp.m_Name = name;
		for (int j = 0; j < 2; j++)
		{
			sp.m_Score[j] = 0;
		}
		// 12名选手编号
		this->v1.push_back(i + 10001);
		// 选手编号以及对应的选手
		this->m_Speaker.insert(make_pair(i + 10001, sp));
	}
}

void SpeechManager::startSpeech()
{
	//第一轮
	//1.抽签
	this->speechDraw();
	//2.比赛
	this->speechContest();
	//3.显示晋级结果
	this->showScore();
	this->m_Index++;
	//第二轮
	//1.抽签
	this->speechDraw();
	//2.比赛
	this->speechContest();
	//3.显示最终结果
	this->showScore();
	this->saveRecord();
}

void SpeechManager::speechDraw()
{
	//第一轮比赛选手抽签
	cout << "第 <<"<< this->m_Index <<" >> 轮比赛选手正在抽签" << endl;
	cout << "-----------------------" << endl;
	cout << "抽签后演讲顺序如下：" << endl;
	if (this->m_Index == 1)
	{
		random_shuffle(v1.begin(), v1.end());
		for (vector<int>::iterator it = v1.begin(); it != v1.end(); it++)
		{
			cout << *it << " ";
		}
		cout << endl;
	}
	else
	{
		random_shuffle(v2.begin(), v2.end());
		for (vector<int>::iterator it = v2.begin(); it != v2.end(); it++)
		{
			cout << *it << " ";
		}
		cout << endl;
	}
	cout << "-----------------------" << endl;
	system("pause");
	cout << endl;
}

void SpeechManager::speechContest()
{
	cout << "第 <<" << this->m_Index << ">> 轮比赛正式开始！" << endl;
	multimap<double, int, greater<double>> groupScore; //临时容器，保存key分数 value选手编号
	int num = 0; //记录人员数，6个人一组
	vector<int> v_src; //比赛选手容器
	if (this->m_Index == 1)
	{
		v_src = v1;
	}
	else
	{
		v_src = v2;
	}
	//遍历所有参赛选手
	for (vector<int>::iterator it = v_src.begin(); it != v_src.end(); it++)
	{
		num++;
		//评委打分
		deque<double> d;
		for (int i = 0; i < 10; i++)
		{
			double score = (rand() % 401 + 600) / 10.f; //600-1000
			d.push_back(score);
		}
		sort(d.begin(), d.end(), greater<double>()); //从大到小排序
		d.pop_front(); //去掉最高分
		d.pop_back(); //去掉最低分
		double sum = accumulate(d.begin(), d.end(), 0.0f); //求和
		double avg = sum / (double)d.size(); //求平均分
		//cout << "选手编号： "<< *it << " 平均分： " << avg << endl;
		//将平均分放入到map容器中
		this->m_Speaker[*it].m_Score[this->m_Index - 1] = avg;
		//将打分放入到临时小组容器中
		groupScore.insert(make_pair(avg, *it));
		//每6人取出前三名
		if (num % 6 == 0)
		{
			cout << "第 <<" << num / 6 << ">> 小组比赛名次如下：" << endl;
			for (multimap<double, int, greater<double>>::iterator it = groupScore.begin(); it != groupScore.end(); it++)
			{
				cout << "选手编号： " << it->second << " 姓名： " << this->m_Speaker[it->second].m_Name << " 成绩： " << this->m_Speaker[it->second].m_Score[this->m_Index - 1] << endl;
			}
			//取前三名
			int count = 0;
			for (multimap<double, int, greater<double>>::iterator it = groupScore.begin(); it != groupScore.end() && count < 3; it++, count++)
			{
				if (this->m_Index == 1)
				{
					v2.push_back((*it).second);
				}
				else
				{
					vVictory.push_back((*it).second);
				}
			}
			groupScore.clear(); //清空临时容器
			cout << endl;
		}
	}
	cout << "第 <<"  << this->m_Index <<" >> 轮比赛完毕！" << endl;
	system("pause");
	cout << endl;

}

void SpeechManager::showScore()
{
	cout << "-----------------------" << endl;
	cout << "第 <<" << this->m_Index << ">> 轮晋级选手如下：" << endl;
	vector<int> v;
	if (this->m_Index == 1)
	{
		v = v2;
	}
	else
	{
		v = vVictory;
	}
	for (vector<int>::iterator it = v.begin(); it != v.end(); it++)
	{
		cout << "选手编号： " << *it << " 姓名： " << this->m_Speaker[*it].m_Name << " 成绩： " << this->m_Speaker[*it].m_Score[this->m_Index - 1] << endl;
	}
	cout << endl;
	system("pause");
	cout << endl;
	/*if (this->m_Index < 3)
	{
		this->m_Index++;
		this->speechContest();
	}
	else
	{
		cout << "比赛结束，获得前三名的选手如下：" << endl;
		this->showScore();
		this->saveRecord();
		this->initSpeech();
		this->createSpeaker();
		this->loadRecord();
		this->showMenu();
	}*/
}

void SpeechManager::saveRecord()
{
	ofstream ofs;
	ofs.open("speech.csv", ios::out | ios::app); //用追加的方式写文件
	for (vector<int>::iterator it = vVictory.begin(); it != vVictory.end(); it++)
	{
		ofs << *it << "," << this->m_Speaker[*it].m_Score[1] << ",";
	}
	ofs << endl;
	ofs.close();
	cout << "记录已经保存" << endl;
	this->fileIsEmpty = false;
}

void SpeechManager::loadRecord()
{
	ifstream ifs("speech.csv", ios::in);
	if (!ifs.is_open())
	{
		this->fileIsEmpty = true;
		//cout << "文件不存在" << endl;
		ifs.close();
		return;
	}
	char ch;
	ifs >> ch;
	if (ifs.eof())
	{
		//cout << "文件为空" << endl;
		this->fileIsEmpty = true;
		ifs.close();
		return;
	}
	this->fileIsEmpty = false;
	ifs.putback(ch);
	string data;
	int index = 0;
	while (ifs >> data)
	{
		//cout << data << endl;
		vector<string> v;
		int pos = -1;
		int start = 0;
		while (true)
		{
			pos = data.find(",", start);
			if (pos == -1)
			{
				break;
			}
			string temp = data.substr(start, pos - start);
			//cout << temp << endl;
			v.push_back(temp);
			start = pos + 1;
		}
		//this->m_Record.insert(make_pair(index, v));
		index++;
	}
	ifs.close();
	/*for (map<int, vector<string>>::iterator it = m_Record.begin(); it != m_Record.end(); it++)
		{
				cout << it->first << "号" << "\t" << "第一轮成绩： " << it->second[0] << "\t" << "第二轮成绩： " << it->second[1] << endl;
					}*/	
}