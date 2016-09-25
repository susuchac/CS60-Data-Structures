#pragma once

#include <iostream>

using namespace std;

class BTNode
{
public:
	BTNode();
	BTNode(int l);
	~BTNode(void);


	string GetChar();
	void SetChar(string c);


	int m_label;

	BTNode *m_left;
	BTNode *m_right;
	BTNode *m_parent;



private:
	string m_char;
};
