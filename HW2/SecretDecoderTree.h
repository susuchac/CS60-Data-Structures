// Programmer: Susie Chac 
// Course: ECS 60
// Date: 08/13/2016

#include "DecoderTree.h"
#include "BTNode.h"

class CSecretDecoderTree: public CDecoderTree
{
    public:
    	CSecretDecoderTree( );
    	void BuildTree( string alphabet, string mutations );
        string Encode( string raw );
        string Decode( string code );
        string GetCode( string letter );
        void RotateLeft( int nodeLabel );
        void RotateRight( int nodeLabel );
        string InorderPrint();
        string InorderPrintLeafLetters();
        BTNode* GetNode( int label );
        
        string InorderPrintHelper( BTNode* node);
        string InorderPrintLeafHelper( BTNode* node );
        bool GetCodeHelper( BTNode* node, string* code, string letter);
        BTNode* BinarySearch( BTNode* node, int label );
        void Mutate(string mutations);
   
    private:
    	BTNode* root;
        
};
