#include "BTNode.h"

BTNode::BTNode()
{
	m_label = -1;
	m_left=NULL;
	m_right=NULL;
	m_parent=NULL;
}
BTNode::BTNode(int l)
{
	m_label = l;
	m_left=NULL;
	m_right=NULL;
	m_parent=NULL;
}

BTNode::~BTNode(void)
{
}


string BTNode::GetChar()
{
	return m_char;
}

void BTNode::SetChar(string c)
{
	m_char = c;
}
