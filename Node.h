/*
 * Node.h
 * 
 * This file contains the declaration of the "Node" structure. It is part of
 * the assignment for the Compiler Construction course at the Leiden Institute
 * of Advanced Computer Science (LIACS), Leiden University.
 *
 * Note: when a Node is deleted, is does _not_ delete its children. Also the
 *       Symbol of a Node_Symbol object is preserved.
 */

#ifndef _NODE_H_
#define _NODE_H_

#include <cstdlib>
#include <cstdio>
#include "types.h"
#include "Symbol.h"

// ----------------------------------------------------------------------------
// N O D E   ( B A S E )
// ----------------------------------------------------------------------------

class Node {
	
  public:

    // constructor
    Node (void);
  
    // destructor
    virtual ~Node (void);
  
    // gets the node type
    NodeType GetNodeType (void);
    
    // sets the node type
    void SetNodeType (NodeType nodeType);
    
    // gets the return type
    ReturnType GetReturnType (void);
    
    // sets the return type
    void SetReturnType (ReturnType returnType);
    
    // dumps the node data
    virtual void Dump (FILE * file, int indent);
    
    // (empty) virtuals
    virtual Node * GetChild (void);
    virtual void SetChild (Node * node);
    virtual Node * GetLeftChild (void);
    virtual void SetLeftChild (Node * node);
    virtual Node * GetRightChild (void);
    virtual void SetRightChild (Node * node);
    
    virtual int GetIntValue (void);
    virtual void SetIntValue (int newvalue);
    virtual float GetRealValue (void);
    virtual void SetRealValue (float newvalue);
    virtual Symbol * GetSymbol (void);
    virtual void SetSymbol (Symbol * newsym);
    
  private:
    
    NodeType myNodeType;
    ReturnType myReturnType;
    
};



// ----------------------------------------------------------------------------
// N O D E   U N A R Y
// [ unary minus, "not x", etc.]
// ----------------------------------------------------------------------------
class Node_Unary: public Node {

  public:
  
    // constructor
    Node_Unary (void);

    // destructor
    ~Node_Unary (void);
  
    // gets the child
    Node * GetChild (void);
    
    // sets the child
    void SetChild (Node * node);
    
    // dumps the node data
    void Dump(FILE * file, int indent);
    
  private:
    
    Node * Child;
    
};



// ----------------------------------------------------------------------------
// N O D E   B I N A R Y
// ["while L do R", "A ; B", "4 * 3", etc.]
// ----------------------------------------------------------------------------
class Node_Binary: public Node {

  public:

    // constructor
    Node_Binary (void);
    
    // destructor
    ~Node_Binary (void);
  
    // gets the left child
    Node * GetLeftChild (void);
    
    // sets the left child
    void SetLeftChild (Node * node);
    
    // gets the right child
    Node * GetRightChild (void);
    
    // sets the right child
    void SetRightChild (Node * node);
    
    // dumps the node data
    void Dump (FILE * file, int indent);
    
  private:
    
    Node * leftChild;
    Node * rightChild;

};



// ----------------------------------------------------------------------------
// N O D E   I N T E G E R
// ----------------------------------------------------------------------------
class Node_Integer: public Node {
	
  public:
	  
    // gets the integer value
    int GetIntValue (void);
  
    // sets the integer value
    void SetIntValue (int value);
    
    // dumps the node data
    void Dump (FILE * file, int indent);
    
  private:
    
    int myValue;
    
};



// ----------------------------------------------------------------------------
// N O D E   R E A L
// ----------------------------------------------------------------------------
class Node_Real: public Node {

  public:

    // gets the real value
    float GetRealValue (void);
  
    // sets the real value
    void SetRealValue (float value);
    
    // dumps the node data
    void Dump (FILE * file, int indent);
    
  private:
    
    float myValue;
    
};



// ----------------------------------------------------------------------------
// N O D E   S Y M B O L
// ----------------------------------------------------------------------------
// symbol leaf
class Node_Symbol: public Node {

  public:

    // gets the symbol pointer
    Symbol * GetSymbol (void);
  
    // sets the symbol pointer
    void SetSymbol (Symbol * symbol);
    
    // dumps the node data
    void Dump (FILE * file, int indent);
    
  private:
    
    Symbol * mySymbol;
    
};

// ----------------------------------------------------------------------------
// U T I L I T Y
// ----------------------------------------------------------------------------
// utility function(s

// This deletes a node and all of its children recursivly
void DeleteNodeRecursive(Node*);

#endif

