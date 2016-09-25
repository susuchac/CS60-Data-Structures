// Programmers: Susie Chac, Jonathan Hoeck 

#include <iostream>
#include <fstream>
#include <string>
#include "CPUTimer.h"
#include "LinkedList.h"
#include "CursorList2.h"
#include "QueueAr.h"
#include "SkipList.h"
#include "StackAr.h"
#include "StackLi.h"
#include "vector.h"
#include <iomanip>

using namespace std;

void LLHelper( string filename );
void CLHelper( string filename );
void StkArHelper( string filename );
void StkLiHelper( string filename );
void QAHelper( string filename );
void SkLiHelper( string filename );

vector< CursorNode < int > > cursorSpace;
const int MAX_SIZE = 1000001;

int main()
{
    ifstream file;
    string fname;
    int choice;
    CPUTimer cpt;
    double t1, t2;
    cout << "Filename >> ";
    cin >> fname;
    do
    {
        cout << "\n      ADT Menu" << endl;
        cout << "0. Quit" << endl;
        cout << "1. LinkedList" << endl;
        cout << "2. CursorList" << endl;
        cout << "3. StackAr" << endl;
        cout << "4. StackLi" << endl;
        cout << "5. QueueAr" << endl;
        cout << "6. SkipList" << endl;
        cout << "Your choice >> ";
        cin >> choice;
        t1 = cpt.cur_CPUTime(); // time before operation
        switch( choice )
        {
            cout << "Choice: " << choice << endl;
            case 0:
                return 0;
            case 1:
                LLHelper( fname ); break; 
            case 2:
                CLHelper( fname ); break;
            case 3:
                StkArHelper( fname ); break;
            case 4:
                StkLiHelper( fname ); break;
            case 5:
                QAHelper( fname ); break;
            case 6:
                SkLiHelper( fname ); break;
        }
        t2 = cpt.cur_CPUTime(); // time after operation
        cout << "CPU time: ";
        cout << setw(10) << t2-t1 << endl; // time width 10
    } while( choice > 0 );
    return 0; 
}

void LLHelper( string filename )
{
    List< int > list;
    ListItr< int > itr = list.zeroth();
    
    ifstream infile( filename.c_str() );
    string line;
    getline(infile, line); // skip first line
    
    char c; // store command
    int n; // store number
    while( infile  >> c >> n )
    {
        if( c == 'i' )
        {
            list.insert( n, itr );
        }
        else if( c == 'd' )    
        {
            list.remove( n );
        } 
        else
        {
            break;
        }
    }
}

void CLHelper( string filename )
{
    CursorList< int > list( cursorSpace );
    CursorListItr< int > itr = list.zeroth();
    
    ifstream infile( filename.c_str() );
    string line;
    getline(infile, line); 
   
    char c;
    int n;
    while( infile  >> c >> n )
    {
        if( c == 'i' )
        {
            list.insert( n, itr );
        }
        else if( c == 'd' )    
        {
            list.remove( n );
        }
        else
        {
          break;
        }
    }
}

void StkArHelper( string filename )
{
    StackAr< int > stk( MAX_SIZE ); 
    
    ifstream infile( filename.c_str() );
    string line;
    getline(infile, line);
    
    char c;
    int n;
    while( infile  >> c >> n )
    {
        if( c == 'i' )
        {
            stk.push( n );
        }
        else if( c == 'd' )    
        {
            if(!stk.isEmpty())
            {
                stk.pop( );
            }
        } 
        else 
        {
          break;
        }
    }
}

void StkLiHelper( string filename )
{
    StackLi< int > stk;

    ifstream infile( filename.c_str() );
    string line;
    getline(infile, line);

    char c;
    int n;
    while( infile  >> c >> n )
    {
        if( c == 'i' )
        {
            stk.push( n );
        }
        else if( c == 'd' )    
        {
            if(!stk.isEmpty())
            {
                stk.pop( );
            }
        }
        else
        {
            break;
        }
    }
}

void QAHelper( string filename )
{
    Queue< int > q( MAX_SIZE );

    ifstream infile( filename.c_str() );
    string line;
    getline(infile, line);

    char c;
    int n;
    while( infile  >> c >> n )
    {
        if( c == 'i' )
        {
            q.enqueue( n );
        }

        else if( c == 'd' )    
        {
            q.dequeue( );
        }
        else
        {
            break;
        }
    }
}

void SkLiHelper( string filename )
{
    SkipList< int > list( 0, MAX_SIZE );

    ifstream infile( filename.c_str() );
    string line;
    getline(infile, line);

    char c;
    int n;
    while( infile  >> c >> n )
    {
        if( c == 'i' )
        {
            list.insert( n );
        }

        else if( c == 'd' )    
        {
            list.deleteNode( n );
        }
        else
        {
            break;
        }
    }
}
