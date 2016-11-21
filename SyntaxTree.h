/*
 * SyntaxTree.h
 * 
 * This file contains the declaration of the "Syntax Tree", an abstract
 * data structure. It is part of the assignment for the Compiler Construction
 * course at the Leiden Institute of Advanced Computer Science (LIACS), Leiden
 * University.
 */

#ifndef _SYNTAXTREE_H_
#define _SYNTAXTREE_H_

#include <cstdlib>
#include <string>
#include <vector>
#include <map>
#include "Node.h"

using namespace std;

// ----------------------------------------------------------------------------
// S Y N T A X   T R E E
// ----------------------------------------------------------------------------
class SyntaxTree {

  public:

    // constructor
    SyntaxTree (void);
  
    // destructor
    ~SyntaxTree (void);
    
    // gets the program name
    string GetProgramName (void);
    
    // sets the program name
    void SetProgramName (string name);
    
    // gets the root node of the program body
    Node * GetProgramBody (void);
    
    // sets the root node of the program body
    void SetProgramBody (Node * root);
    
    // gets the number of subprograms
    int GetSubprogramCount (void);
    
    // gets the root node of the i-th subprogram
    // 0 <= i < number of subprograms
    Node * GetSubprogram (unsigned int i);

    // gets the name of the i-th subprogram
    string GetSubprogramName (unsigned int i);
    
    // adds a subprogram
    void AddSubprogram (string name, Node * root);
    
    // creates an unary parent node
    Node * CreateParentNode (NodeType nodeType,
                             ReturnType returnType,
                             Node * child);
    
    // creates a binary parent node
    Node * CreateParentNode (NodeType nodeType,
                             ReturnType ret,
                             Node * leftChild,
                             Node * rightChild);

    // creates an integer leaf with node type NODE_NUM_INT
    Node * CreateLeaf (int value);
    
    // creates a real leaf with node type NODE_NUM_REAL
    Node * CreateLeaf (float value);
    
    // creates a symbol leaf with node type NODE_ID
    Node * CreateLeaf (Symbol * symbol);
    
    // creates a leaf with node type NODE_EMPTY
    Node * CreateLeaf ();

    // dumps the syntax tree
    void Dump (FILE * file);
    
  private:
    
    string programName;
    Node * programBody;
    vector<string> subprogramNames;
    vector<Node *> subprograms;
    void DeleteTree (Node * root);

};

#endif

