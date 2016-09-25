// Programmer: Susie Chac
// Course: ECS 60
// Date: 08/13/2016
// Objective: This program tests SecretDecoderTree.cpp 
//            and SecretDecoderTree.h
//
// Notes: I had problems writing test.cpp and test.h
//        because I couldn't get test.cpp to compile.
//        For some reason, when I tried to create an
//        object of SecretDecoderTree, test.cpp would
//        not compile. The error message told me that
//        I was making an undefined reference to
//        SecretDecoderTree.
//
//        Because I was unable to get Test.cpp to compile, I did
//        all of my error checking inside main.cpp instead.
//
// If my program had compiled:
//
//        I would check to see if an error would be thrown
//        on input of invalid mutation strings. In my progrsm, my
//        intentions were to skip over invalid mutations and to
//        handle the next mutations.
//        
//        I would check how SecretDecoderTree handles an input
//        alphabet that has some repeated characters. In my program,
//        I exited if the alphabet contained repeats because it
//        would create an invalid tree.
//
//        I would check how invalid rotations are handled. In my
//        program, my intentions were to skip over invalid rotations
//        and to handle the next rotations.
//
//        I would check to make sure that my leaf nodes never 
//        change despite undergoing multiple rotstions. Only the
//        codes for letter should be changing, so I would check to
//        make sure those are changing properly as well.

#include <iostream>
#include <string>
#include "Test.h"

using namespace std;

Test::Test( string a, string m, string c, string msg )
{
	alphabet = a;
//	cout << "After alphabet: " << alphabet << endl;
	mutations = m;
//	cout << "After mutations: " << mutations << endl;
	code = c;
//	cout << "After code: " << code << endl;
	correct_msg = msg;
//	cout << "After correct_msg: " << msg << endl;
	t.BuildTree( alphabet, mutations );
	// cout << "After BuildTree()" << endl;
}
/*
bool Test::DoTest() {

  return true;
}
*/
int main()
{
	Test tst( "qwe,.?rtyuiopasdfghjklzxc;vbnm", 
		"070L155R225Lxyz3145L085L285R165L",
		"011110101000011110010110100111110001010110011101",
		 "Testing this program now" );
        //cout << "T/F: " << tst.DoTest() << endl;
        // tst->alphabet = "qwe,.?rtyuiopasdfghjklzxc;vbnm";
	// tst->mutations = "070L155R225Lxyz3145L085L285R165L";
	// // tst->code = "011110101000011110010110100111110001010110011101";
	// tst->correct_msg = "Testing this program now";
	// tst->t->InorderPrintLeafLetters();
	// tst->t->InorderPrint();
    return 0;
}
