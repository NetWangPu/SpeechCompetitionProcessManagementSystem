#include <iostream>
using namespace std;
#include "speechManager.h"
int main()
{
	SpeechManager* speechManager = new SpeechManager();
	//����
	//speechManager->createSpeaker();
	//for (map<int, Speaker>::iterator it = speechManager->m_Speaker.begin(); it != speechManager->m_Speaker.end(); it++)
	//{
	//	cout << "ѡ�ֱ�ţ�" << it->first << " ������" << it->second.m_Name << " ������" << it->second.m_Score[0] << endl;
	//}
	int choice = 0;
	while (true)
	{
		speechManager->showMenu();
		cout << "���������ѡ��" << endl;
		cin >> choice;
		switch (choice)
		{
		case 1: //��ʼʱ����
			speechManager->startSpeech();
			break;
		case 2: //�鿴�������
			break;
		case 3: //��ձ���
			break;
		case 0: //�˳�����
			speechManager->exitSystem();
			break;
		default:
			break;
		}
	}
	system("pause");
	return 0;
}