#include <iostream>
using namespace std;
#include "speechManager.h"
int main()
{
	SpeechManager* speechManager = new SpeechManager();
	//测试
	//speechManager->createSpeaker();
	//for (map<int, Speaker>::iterator it = speechManager->m_Speaker.begin(); it != speechManager->m_Speaker.end(); it++)
	//{
	//	cout << "选手编号：" << it->first << " 姓名：" << it->second.m_Name << " 分数：" << it->second.m_Score[0] << endl;
	//}
	int choice = 0;
	while (true)
	{
		speechManager->showMenu();
		cout << "请输入你的选择：" << endl;
		cin >> choice;
		switch (choice)
		{
		case 1: //开始时比赛
			speechManager->startSpeech();
			break;
		case 2: //查看往届比赛
			break;
		case 3: //清空比赛
			break;
		case 0: //退出程序
			speechManager->exitSystem();
			break;
		default:
			break;
		}
	}
	system("pause");
	return 0;
}