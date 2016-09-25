#pragma once

#include <iostream>

using namespace std;

class BTNode;

class CDecoderTree
{
public:
	CDecoderTree(void);
	~CDecoderTree(void);

  
  
  /**
   * Builds the tree that is used for encoding and decoding
   * secret messages.  The tree is defined by it's input alphabet
   * and then a series of mutations.
   * 
   * @param alphabet The set of characters that can be encoded by this
   *                 tree.  For the pruposes of this assignment, you
   *                 can assume that alphabet will always contain 30
   *                 characters.
   * 
   * @param mutations A string that specifies how the base tree should be 
   *                  mutated in order to form the final decoder tree.
   */
  virtual void BuildTree(string alphabet, string mutations) = 0;
  
  /** Uses the decoder tree to encode the input text specified
   * in <code>raw</code> and returns the enoded text as a string
   * of ones and zeros
   * 
   * @param raw The english text that should be encoded.
   * 
   * @return The input text encoded as a secret string of ones and zeros.
   */
  virtual string Encode(string raw) = 0;
  
  
  /** Uses the decoder tree to decode the input text specified
   * in <code>code</code> as a series of 1's and 0's and returns 
   * the decoded text as a string of plain english.
   * 
   * @param code The encoded message as a secret string of ones and zeros.
   * 
   * @return The english text that results from decoding the input.
   */
  virtual string Decode(string code) = 0;

  
  
  //Note:  The three methods above form the "natural" interface for this
  //class.  They define what the class really must do.  I would normally 
  //include only these methods in the interface.  The methods below are 
  //all methods that you need to implement, but would not normally be
  //public.  I am making them public as we will use them to test your
  //code.  You can also make use of them in your own test cases.
  
  
  
  /**
   * Returns the encoding (1's and 0's) for a single letter.
   * 
   * @param letter  The <code>letter</code> that should be encoded.
   * 
   * @return The string of 1's and 0's that encode <code>letter</code>.
   */
  virtual string GetCode(string letter) = 0;
  
  /**
   * Rotate the specified node left.
   * 
   * precondition:  The node with the given label exists.
   * 
   * @param nodeLabel The number that labels the node you should rotate.
   */
  virtual void RotateLeft(int nodeLabel) = 0;

  /**
   * Rotate the specified node right.
   * 
   * precondition:  The node with the given label exists.
   * 
   * @param nodeLabel The number that labels the node you should rotate.
   */
  virtual void RotateRight(int nodeLabel) = 0;
  
  /** Print the contents of me, in order. */
  virtual string InorderPrint() = 0;
  
  /** 
   * Print the letters on the leaves, in order.
   *
   * @return Returns the data that is printed out as a string.
   */
  virtual string InorderPrintLeafLetters() = 0;
  
  /** 
   * Gets the node with the given label. 
   * 
   * @return Returns the data that is printed out as a string.
   */
  virtual BTNode* GetNode(int label) = 0;


};
