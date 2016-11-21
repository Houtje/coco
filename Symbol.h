/*
 * Symbol.h
 * 
 * This file contains the declaration of the "Symbol" abstract
 * data structure. It is part of the assignment for the Compiler Construction
 * course at the Leiden Institute of Advanced Computer Science (LIACS), Leiden
 * University.
 */

#ifndef _SYMBOL_H_
#define _SYMBOL_H_

#include <string>
#include <vector>
#include <cstdio>

#include "types.h"

using namespace std;

// The base class for Symbols
class Symbol {
  public:
    // Constructor/Destructor
    Symbol (void);
    virtual ~Symbol (void);

    // Set the identifier text
    void SetName (string name);

    // Get the identifier text
    string GetName (void);

    // Set declaration line
    void SetLine (int line);

    // Get declaration line
    int GetLine (void);

    // Set return type
    void SetReturnType (ReturnType type);

    // Get return type
    ReturnType GetReturnType (void);

    // Set symbol type
    void SetSymbolType (SymbolType type);

    // Get symbol type
    SymbolType GetSymbolType (void);

    // Get offset (used during code generation)
    int GetOffset();
    
    // Set offset (used during code generation)
    void SetOffset(int offset);
    
    // Dump the contents
    virtual void Dump (FILE * file, int indent);

    // Virtuals (empty for this base class)
    virtual void AddParameter (Symbol * symbol);
    virtual int GetParameterCount (void);
    virtual Symbol * GetParameter (unsigned int num);

  private:
    string myName;
    int myLine;
    ReturnType myReturnType;
    SymbolType mySymbolType;
    int myOffset;
};//Symbol



// Extended symbol class for functions and procedures
class Symbol_Subprogram : public Symbol {
  public:
    // Destructor
    ~Symbol_Subprogram (void);

    // Add a parameter to the end of the parameter list
    void AddParameter (Symbol * symbol);

    // Get number of parameters
    int GetParameterCount (void);

    // Get the num-th argument
    Symbol * GetParameter (unsigned int num);

    // Dump
    void Dump (FILE * file, int indent);

  private:
    vector<Symbol *> parameters;
};//Symbol_Subprogram

#endif

