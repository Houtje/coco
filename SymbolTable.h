/*
 * SymbolTable.h
 *
 * This file contains the declaration of the "SymbolTable" structure.
 * It is part of the assignment for the Compiler Construction course at the
 * Leiden Institute of Advanced Computer Science (LIACS), Leiden University.
 *
 * Note: when a SymbolTable is deleted, all Scope objects contained in that
 *       SymbolTable are also deleted.
 */

#ifndef _SYMBOLTABLE_H_
#define _SYMBOLTABLE_H_

#include <cstdio>
#include <string>
#include <vector>

#include "Scope.h"
#include "Symbol.h"

using namespace std;

class SymbolTable {
  public:
    // Constructor
    SymbolTable ();

    // Destructor: deletes all Scopes contained in this SymbolTable
    ~SymbolTable ();

    // Creates a new Scope with the given name and sets it as current scope.
    // Returns NULL if the name is already used.
    Scope * AddScope (string scope);

    // Returns a pointer to the Scope object with the given name
    Scope * GetScope (string scope);

    // Returns a pointer to the root scope
    Scope * GetRootScope ();

    // Set the current scope
    // Returns -1 on error
    int SetCurrentScope (string scope);

    // Get the current scope name
    string GetCurrentScopeName ();

    // Adds a symbol to the current scope
    // Returns -1 on error
    int AddSymbol (Symbol * symbol);

    // Adds a symbol to the given scope
    // Returns -1 on error
    int AddSymbol (string scope, Symbol * symbol);

    // Find a symbol in the current scope, or look in the parent scope, if it
    // cannot be found in the current one.
    // Returns NULL if the symbol cannot be found anywhere.
    Symbol * GetSymbol (string name);

    // Find a symbol in the given scope; optionally look in the parent scope,
    // if it cannot be found in the given one.
    // Returns NULL if the symbol cannot be found.
    Symbol * GetSymbol (string scope, string name, bool lookInParentScope);

    // Dump the contents of the symbol table
    void Dump (FILE * file);

  private:
    int myCurrentScope;
    vector<Scope *> myScopes;
};//SymbolTable

#endif

