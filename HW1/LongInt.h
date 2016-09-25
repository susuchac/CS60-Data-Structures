// Programmers; Susie Chac , Jonathan Hoeck

#include <iostream>
#include <string>

using namespace std;

class LongInt
{
    private:
        string num;
    public:
        LongInt();
        LongInt( string n );
        friend istream &operator>>( istream &input, LongInt &li );
        friend LongInt operator+( const LongInt &lhs, const LongInt &rhs );
        friend ostream &operator<<( ostream &output, LongInt &li );
        string getNum( ) const;
};
string add( const string num1, const string num2 );
