/*
 * types.h - Various type definitions
 *
 * Part of the assignment of the Compiler Construction course
 * LIACS, Leiden University
 */

#ifndef _TYPES_H_
#define _TYPES_H_

#include <string>

using namespace std;

// Return type of a node
typedef enum __returntype {
  RT_UNKNOWN,               // Not (yet) known
  RT_ERROR,                 // Error
  RT_VOID,                  // Void
  RT_INT,                   // Integer
  RT_REAL,                  // Floating point
  RT_BOOL                   // Boolean expression
} ReturnType;


// Type of a symbol
typedef enum __symboltype {
  ST_UNKNOWN,               // Unknown (yet)
  ST_ERROR,                 // Error
  ST_VARIABLE,              // Variable
  ST_PARAMETER,             // Function/Procedure parameter
  ST_PROCEDURE,             // Procedure
  ST_FUNCTION,              // Function
  ST_PROGRAM,               // Program body
  ST_TEMPVAR,               // Temporary variable (not used before assignment 3)
  ST_LABEL                  // Label (not used before assignment 3)
} SymbolType;


// Type of a node in the syntax tree
typedef enum __nodetype {
  /* Meta */
  NODE_UNKNOWN,             // Unknown (yet)
  NODE_ERROR,               // Error
  
  /* Statement list
     left child     One of: NODE_ASSIGNMENT, NODE_IF, NODE_WHILE,
                    NODE_PROCCALL, NODE_FUNCTIONCALL, NODE_STATEMENT_LIST.
     right child    One of: NODE_ASSIGNMENT, NODE_IF, NODE_WHILE,
                    NODE_PROCCALL, NODE_FUNCTIONCALL, NODE_STATEMENT_LIST, or
                    NODE_EMPTY if no more statements follow. */
  NODE_STATEMENT_LIST,

  /* Assignment
     left child     A NODE_ID that identifies the destination variable
     right child    A subtree representing an expression */
  NODE_ASSIGNMENT,

  /* If statement
     left child     A NODE_BOOLEXPR that provides the if condition
     right child    A NODE_IF_TARGETS subtree (if there is an else clause) or
                    a subtree consisting of statements (if there's no else) */
  NODE_IF,

  /* Targets of an if-else-statement
     left child     The statements that have to be executed when the condition
                    of the parent if-statement is true.
     right child    The statements that have to be executed when the condition
                    of the parent if-statement is false, that is, the else
                    part. */
  NODE_IF_TARGETS,

  /* While loop
     left child     A NODE_BOOLEXPR that provides the loop condition
     right child    A subtree consisting of statements */
  NODE_WHILE,

  /* Subprogram calls
     left child     A NODE_ID that identifies the called function/procedure
     right child    A NODE_EXPRLIST that specifies the actual arguments, or
                    NODE_EMPTY if no arguments required. */
  NODE_PROCCALL,
  NODE_FUNCTIONCALL,

  /* Expression list
     left child     A subtree representing an expression
     right child    A subtree representing an expression, another
                    NODE_EXPRLIST, or NODE_EMPTY if no more expressions follow
                    in the expression list. */
  NODE_EXPRLIST,

  /* Boolean-like expression
     child          A subtree with any NODE_REL_ node as parent */
  NODE_BOOLEXPR,

  /* Relational operators
     left child     Left-hand side of the comparison
     right child    Right-hand side of the comparison */
  NODE_REL_EQUAL,           //  = operator
  NODE_REL_LT,              //  < operator
  NODE_REL_GT,              //  > operator
  NODE_REL_LTE,             //  <= operator
  NODE_REL_GTE,             //  >= operator
  NODE_REL_NOTEQUAL,        //  <> operator

  /* Binary arithmetic & logic operations
     left child     Left-hand side of the operation
     right child    Right-hand side of the operation */
  NODE_ADD,                 // Add
  NODE_SUB,                 // Subtract
  NODE_OR,                  // OR operation
  NODE_MUL,                 // Multiply
  NODE_DIV,                 // Divide
  NODE_IDIV,                // Integer division
  NODE_MOD,                 // Modulo
  NODE_AND,                 // AND operation

  /* Leafs
     these nodes have no child nodes */
  NODE_NUM_INT,             // Integer number
  NODE_NUM_REAL,            // Real number
  NODE_ID,                  // Identifier
  NODE_EMPTY,               // Empty leaf (terminates lists etc.)

  /* Unary nodes
     child          The subtree to which the operation has to be applied */
  NODE_NOT,                 // NOT operation
  NODE_SIGNPLUS,            // Unary plus
  NODE_SIGNMINUS,           // Unary minus
  NODE_COERCION             // Int to Real coercion
} NodeType;


/* Prototypes */
const char * ReturnTypeToString (ReturnType returntype);
const char * SymbolTypeToString (SymbolType symboltype);
const char * NodeTypeToString (NodeType nodetype);

#endif
