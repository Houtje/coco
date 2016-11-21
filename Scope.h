/*
 * Scope.h
 *
 * This file contains the declaration of the "Scope" structure.
 * It is part of the assignment for the Compiler Construction course at the
 * Leiden Institute of Advanced Computer Science (LIACS), Leiden University.
 *
 * Note: when a Scope object is deleted, all Symbol objects contained in that
 *       Scope are also deleted.
 */

#ifndef _SCOPE_H_
#define _SCOPE_H_

#include <cstdio>
#include <string>
#include <vector>

#include "Symbol.h"

using namespace std;

// Class representing a scope
class Scope {
  public:
    // Constructor
    Scope (string scope);

    // Destructor: deletes all Symbols contained in this Scope
    ~Scope ();

    // Sets the name of the scope
    void SetName(string name);

    // Gets the name of the scope
    string GetName ();

    // Adds the given symbol to this scope
    // Returns -1 if the symbol could not be added
    int AddSymbol (Symbol * symbol);

    // Returns the symbol identified by <name> in this scope.
    // Returns NULL if the symbol cannot be found.
    Symbol * GetSymbol (string name);

    // Returns the i-th symbol of this scope.
    Symbol * GetSymbol (unsigned int i);

    // Returns the number of symbols in this scope
    unsigned int GetNumberOfSymbols ();

    // Dumps the contents of this scope
    void Dump (FILE * file, int indent);

  private:
    string myName;
    vector<Symbol *> mySymbols;
};//Scope

#endif

