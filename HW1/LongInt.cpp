// Programmers: Susie Chac , Jonathan Hoeck 

#include "LongInt.h"
#include "StackLi.h"

using namespace std;

LongInt::LongInt()
{
    // empty constructor
}
LongInt::LongInt( string n )
{
    this->num = n; 
}
istream &operator>>( istream &input, LongInt &li )
{
    input >> li.num;
    return input;
}
LongInt operator+( const LongInt &lhs, const LongInt &rhs )
{
    return LongInt( add( lhs.getNum( ), rhs.getNum( ) ) );
}
ostream &operator<<( ostream &output, LongInt &li )
{
    output << li.num;
    return output;
}
string LongInt::getNum( ) const
{
    return num;
}
string add( string n1, string n2 )
{
    StackLi< char > stk1;
    StackLi< char > stk2;
    string output;
    for( int i = 0; i < n1.length(); i++ )
    {
        stk1.push( n1[i] );
    }
    for( int i = 0; i < n2.length(); i++ )
    {
        stk2.push( n2[i] );
    }
    int carryOver = 0; // roll-over digits
    while( !stk1.isEmpty() || !stk2.isEmpty() )
    {
        if( stk1.isEmpty() )
        {
            int tmp = stk2.top() - '0'; // char to int
            tmp += carryOver;
            carryOver = tmp / 10;
            char temp = ( tmp % 10 ) + '0';
            output = temp + output; // int to char. output on rhs
            stk2.pop();
        }
        else if( stk2.isEmpty() )
        {
            int tmp = stk1.top() - '0';
            tmp += carryOver;
            carryOver = tmp / 10;
            char temp = ( tmp % 10 ) + '0';
            output = temp + output;
            stk1.pop();
        }
        else
        {
            int tmp = ( stk1.top() - '0' ) + ( stk2.top() - '0' );
            tmp += carryOver;
            carryOver = tmp / 10;
            char temp = ( tmp % 10 ) + '0';
            output = temp + output;
            stk1.pop();
            stk2.pop();
        }
    }
    return output;
}
