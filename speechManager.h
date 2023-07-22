#pragma once
#include <iostream>
#include <vector>
#include <map>
using namespace std;
#include "speaker.h"
#include <algorithm>
#include <deque>
#include <functional>
#include <numeric>
#include <fstream>
#include <string>

class SpeechManager
{
public:
	SpeechManager(); // constructor
	~SpeechManager(); //destructor
	void initSpeech(); //initialize speech
	void showMenu(); //show menu
	void exitSystem(); //exit system
	void createSpeaker(); //create speaker
	void startSpeech(); //start speech
	void speechDraw(); //
	void speechContest();
	void showScore();
	void saveRecord();
	void loadRecord();
	bool fileIsEmpty;
	int m_Index;
	vector<int> v1; //the frist round
	vector<int> v2; //the second round
	vector<int> vVictory; //the final round 
	map<int, Speaker> m_Speaker; //the map of speaker
};
