decode.out : main.o SecretDecoderTree.o DecoderTree.o BTNode.o
	g++ -o decode.out main.o SecretDecoderTree.o DecoderTree.o BTNode.o

main.o : main.cpp SecretDecoderTree.h
	g++ -c main.cpp

DecoderTree.o : DecoderTree.cpp DecoderTree.h BTNode.h
	g++ -c DecoderTree.cpp

SecretDecoderTree.o : SecretDecoderTree.cpp SecretDecoderTree.h BTNode.h
	g++ -c SecretDecoderTree.cpp

BTNode.o : BTNode.cpp BTNode.h
	g++ -c BTNode.cpp

Test.o : Test.cpp Test.h
	g++ -o Test.cpp

clean: 
	rm *.o *.out
