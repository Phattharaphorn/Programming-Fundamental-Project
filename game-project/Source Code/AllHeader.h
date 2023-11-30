#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

using namespace sf; // sfml
using namespace std; // standard

extern int heart;
extern int score;
extern int state;
#define MenuState 0
#define GameState 1
#define OverState 2
#define ScoreState 3

inline Vector2f normalize(Vector2f vec) //แปลงเป็น unit vector 
{
	float len = sqrtf(vec.x * vec.x + vec.y * vec.y);
	if (len != 0)
		return vec / len;
	return vec;
}

// return random number in range [start, stop] 
inline int randint(int start, int stop)
{
	return rand() % (stop - start + 1) + start;
}

// collect name and score
struct ScoreData
{
	string name;
	int score;
};
// collect score top 5 + 1 
extern ScoreData scoredata[6];

// เรียงคะแนน
inline void sortscore()
{
	for (int i = 0; i < 6; i++)
	{
		for (int j = i + 1; j < 6; j++)
		{
			if (scoredata[j].score > scoredata[i].score)
			{
				ScoreData temp = scoredata[i];
				scoredata[i] = scoredata[j];
				scoredata[j] = temp;
			}
		}
	}
}
#define FILENAME "saveScore.txt"
// อ่านคะแนนจากไฟล์
inline void readScoreFile()
{
	fstream file(FILENAME, ios::app | ios::in);
	for (int i = 0; i < 5; i++)
	{
		string tempname;
		string tempscore;
		if (!getline(file, tempname))
		{
			return; // fail
		}
		if (!getline(file, tempscore))
		{
			return; // fail
		}
		scoredata[i].name = tempname;
		scoredata[i].score = stoi(tempscore);
	}
	sortscore();
	file.close();
}

inline void addAndSaveScore(string name, int score)
{
	scoredata[5].name = name;
	scoredata[5].score = score;
	sortscore();
	fstream file(FILENAME, ios::out);
	for (int i = 0; i < 5; i++)
	{
		file << scoredata[i].name << endl << scoredata[i].score << endl;
	}
	file.close();
}