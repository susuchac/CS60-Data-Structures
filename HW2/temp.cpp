#include <iostream>
#include <string>
#include "DecoderTree.h"
#include "SecretDecoderTree.h"
using namespace std;

class Temp {
    public:
        CSecretDecoderTree t;
      Temp(string alphabet, string mutation) {
        t.BuildTree(alphabet, mutation); 
      }
};


int main () {

   Temp t("123456788012345678991234567890", ""); 


    return 0;
}
