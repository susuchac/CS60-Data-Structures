// Programmer: Susie Chac 
// Course: ECS 60
// Date: 08/13/2016
// Objective: This program builds a decoder tree used for encoding
//            and decoding secret messages.

#include "SecretDecoderTree.h"
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <cstdlib>

using namespace std;

//***************CSecretDecoderTree()*******************
/** Empty constructor for class CSecretDecoderTree
 */
CSecretDecoderTree::CSecretDecoderTree()
{
}

//***************BuildTree()****************************
/** Builds a tree that is used as a key to encode and decode messages.
 * Input for tree is a 30 character alphabet and a string of mutations.
 * First 28 leaf nodes labelled from 10 to 280, and last 2 leaf nodes 
 * labelled 300 and 310.
 * Builds tree, sets root node, mutates tree.
 */
void CSecretDecoderTree::BuildTree( string alphabet, string mutations )
{
    for( int i = 0; i < alphabet.length(); i++ )
    {
        for( int j = i + 1; j < alphabet.length(); j++ )
        {
            if( alphabet[i] == alphabet[j] )
            {
                cout << "Alphabet not unique. Tree not created." << endl;
                exit(0);
            }
        }
    }

    vector<BTNode*> children, parents; 

    for( int i = 0; i < alphabet.length(); i++)
    {
	BTNode *node = new BTNode();
	if( i < alphabet.length() - 2 )
	{
	    // e.g. i=0 -> 10 and i=20 -> 200
	    node->m_label = ( i + 1 )*10;
	}
	else 
	{
	    // e.g. i=28 -> 300 and i=29 -> 310
	    node->m_label = ( i + 2 )*10;
	}
	// char to string.
	string temp( 1, alphabet[i] );
	node->SetChar( temp );
	children.push_back( node );
    }
    do
    {
        parents.clear();
        for( int i = 0; i < children.size(); i+=2 )
        {
            // if odd number of children.
	    if ( i == children.size() - 1 ) 
            {
	        parents.push_back( children[i] );
	    }
	    else
	    {
	        BTNode *node = new BTNode();
	        node->m_label = ( children[i]->m_label +
                    children[i+1]->m_label )/2;
		node->m_left = children[i];
		node->m_right = children[i+1];
		children[i]->m_parent = node;
		children[i+1]->m_parent = node;
		parents.push_back( node );
	    }   
        }
        children = parents;
    } while( parents.size()!=1 );
    root = parents[0];
    Mutate( mutations );
}

//***************Encode()*******************************
/** Uses the tree to encode a raw message into a coded message
 * Coded message made of string of 0s and 1s
 * Gets code for each letter and appends to coded message
 */
string CSecretDecoderTree::Encode( string raw )
{
    string code;
    for( int i = 0; i < raw.length(); i++ )
    {
    	string s( 1, raw[i] );
	code += GetCode( s );
    }
    return code;
}

//***************Decode()*******************************
/** Uses the tree to decode the coded message.
 *  Follows path from string of 0s and 1s to decode a letter,
 *  and appends to message.
 *  If node is NULL, or if leaf node, set equal to root.
 */
string CSecretDecoderTree::Decode( string code )
{
    string msg;
    BTNode* temp = root;
    for( int i = 0; i < code.length(); i++ )
    {
    	if( code[i] == '0' )
	{
            temp = temp->m_left;
	}
	else // if( code[i] == '1' )
	{
	    temp = temp->m_right;
	}
	if( temp == NULL )
	{
	    temp = root;
	}
	if( temp->m_left == NULL && temp->m_right == NULL )
	{
	    msg += temp->GetChar();
	    temp = root;
	}
    }
    return msg;
}

//**************GetCode()*******************************
/** Uses helper function GetCodeHelper() to get the code for
 *  a letter in a string of 0s and 1s.
 */
string CSecretDecoderTree::GetCode( string letter )
{
    string code; // bottom up gives code in reverse order
    GetCodeHelper( root, &code, letter );
    return code;
}

//**************RotateLeft()****************************
/** Does a left (counterclockwise) rotation on the node labelled 
 *  with input nodeLabel, and changes all of the parent-child 
 *  connections between the nodes involved.
 */
void CSecretDecoderTree::RotateLeft( int nodeLabel )
{
    BTNode* node = GetNode( nodeLabel );
    if( ( node == NULL ) 
        || ( node->m_left == NULL && node->m_right == NULL )
	|| ( ( node->m_left->m_left == NULL 
            && node->m_left->m_right == NULL )
    	|| ( node->m_right->m_left == NULL 
            && node->m_right->m_right == NULL ) ) )
    {
		return;
    }

    BTNode* oldChild = node->m_right;
    BTNode* newChild = node->m_right->m_left;
    BTNode* oldParent = node->m_parent;

    if( node->m_parent == NULL )
    {
	oldChild->m_parent = NULL;
	root = oldChild;
    }
    else
    {
	if( oldParent->m_left == node )
	{
            oldParent->m_left = oldChild;
	}
	else // if( oldParent->m_right == node )
	{
	    oldParent->m_right = oldChild;
	}
	oldChild->m_parent = oldParent;
    }
	
    node->m_parent = oldChild;
    oldChild->m_left = node;

    node->m_right = newChild;
    newChild->m_parent = node;
}

//**************RotateRight()***************************
/** Does a right (clockwise) rotation on the node labelled with
 *  input nodeLabel, and Changes all of the parent-child connections 
 *   between the nodes involved.
 */
void CSecretDecoderTree::RotateRight( int nodeLabel )
{
    BTNode* node = GetNode( nodeLabel );
    if( ( node == NULL ) 
        || ( node->m_left == NULL && node->m_right == NULL )
	|| ( ( node->m_left->m_left == NULL 
            && node->m_left->m_right == NULL )
	|| ( node->m_right->m_left == NULL 
            && node->m_right->m_right == NULL ) ) )
    {
		return;
    }

    BTNode* oldChild = node->m_left;
    BTNode* newChild = node->m_left->m_right;
    BTNode* oldParent = node->m_parent;

    if( node->m_parent == NULL )
    {
    	oldChild->m_parent = NULL;
	root = oldChild;
    }
    else
    {
	if( oldParent->m_left == node )
	{
            oldParent->m_left = oldChild;
	}
    	else // if( oldParent->m_right == node )
	{
	    oldParent->m_right = oldChild;
	}
	oldChild->m_parent = oldParent;
    }
	
    node->m_parent = oldChild;
    oldChild->m_right = node;

    node->m_left = newChild;
    newChild->m_parent = node;
}

//**************InorderPrint()**************************
/** Uses helper function InorderPrintHelper() to print the
 *  labels at each node, in order.
 */
string CSecretDecoderTree::InorderPrint()
{
    if( root == NULL )
    {
    	cout << "Root is NULL" << endl;
    }
    string labels = " " + InorderPrintHelper( root );
    cout << labels << endl;
    return InorderPrintHelper( root ); 
}

//**************InorderPrintLeafLetters()***************
/** Uses helper function InorderPrintLeafHelper() to print the
 *  letters on the leaf nodes, in order.
 */
string CSecretDecoderTree::InorderPrintLeafLetters()
{
    if( root == NULL )
    {
    	cout << "Root is NULL" << endl;
    }
    string leaves = " " + InorderPrintLeafHelper( root );
    cout << leaves << endl;
    return leaves;
}

//**************GetNode()*******************************
/** Uses helper function BinarySearch() to search for the node
 *  with the input label, and returns it.
 */
BTNode* CSecretDecoderTree::GetNode( int label )
{
    return BinarySearch( root, label );
}
//**************InorderPrintHelper()********************
/** Recursively traverses tree in order, and prints and returns
 *  the labels at each node.
 */
string CSecretDecoderTree::InorderPrintHelper( BTNode* node )
{
    if( node == NULL )
    {
	return "";
    }
    stringstream ss;
    ss << node->m_label;
    return InorderPrintHelper( node->m_left ) 
      + ss.str() + " " + InorderPrintHelper( node->m_right );
}

//**************InorderPrintLeafHelper()****************
/** Recursively traverses tree in order, and prints and returns 
 *  the letter on each leaf node.
 */
string CSecretDecoderTree::InorderPrintLeafHelper( BTNode* node )
{
    if( node->m_left == NULL && node->m_right == NULL )
    {
    	return node->GetChar() + " "; // if leaf node
    }
    return InorderPrintLeafHelper( node->m_left ) 
        + InorderPrintLeafHelper( node->m_right );
}

//**************GetCodeHelper()*************************
/** Recursively traverses tree and appends 0s and 1s to a string
 *   to get the code for input letter.
 */
bool CSecretDecoderTree::GetCodeHelper( BTNode* node, string* code, 
    string letter )
{
    if( node->m_left == NULL && node->m_right == NULL )
    {
	return( node->GetChar() == letter );
    }
    
    *code += "0"; // appends 0
    
    if( GetCodeHelper( node->m_left, code, letter ) )
    {
	return true;
    }

    // pop off last char of code aka goes back up one node
    code->erase( code->length() - 1 );
    *code += "1"; // appends 1
    
    if( GetCodeHelper( node->m_right, code, letter ) )
    {
	return true;
    }	
    
    // pops off last char of code aka goes back up one node
    code->erase( code->length() - 1 ); 
    return false;
}

//**************BinarySearch()**************************
/** Recursively traverses tree in search of node with input label.
 */
BTNode* CSecretDecoderTree::BinarySearch( BTNode* node, int label )
{
    if( node == NULL )
    {
	return NULL;
    }
    if( node->m_label == label )
    {
    	return node;
    }
    else if( node->m_label > label )
    {
    	return BinarySearch( node->m_left, label );
    }
    else //if (node->m_label < label)
    {
    	return BinarySearch( node->m_right, label );
    }
}

//**************Mutate()********************************
/** Checks if each mutation in string is made up of 4  valid characters,
 *  and ignores mutation if not valid.
 *  Uses RotateLeft() and RotateRight() based on the 4th character 
 *  in mutation string (L or R).
 */
void CSecretDecoderTree::Mutate( string mutations )
{
    for( int i = 0; i < mutations.length(); i+=4 )
    {
	if( i + 3 > mutations.length() )
	{
            break;
	}
	if( !( isdigit( mutations[i] ) && isdigit( mutations[i+1] )
            && isdigit( mutations[i+2] ) ) )
	{
            continue;
	}
	int lbl = ( mutations[i]-'0' )*100 + ( mutations[i+1] - '0' )*10
            + ( mutations[i+2] - '0' );
	if( mutations[i+3] == 'L' )
	{
	    RotateLeft( lbl );
	}
	else if( mutations[i+3] == 'R' )
	{
	    RotateRight( lbl );
	}
	else
	{
	    continue;
	}
    }
}
