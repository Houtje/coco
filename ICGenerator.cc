/*
 * ICGenerator.cc - Implementation of the ICGenerator class
 *
 * Part of the assignment of the Compiler Construction course
 * LIACS, Leiden University
 *
 * This file will contain most of your work for assignment 3.
 */

#include "ICGenerator.h"
#include <iostream>
#include <string>
#include <sstream>

// Constructor
ICGenerator::ICGenerator() {
  tempCount = 0;
  labelCount = 0;
}

// Destructor
ICGenerator::~ICGenerator() {

}

// Preprocesses the syntax tree; this method is called before
// GenerateIntermediateCode() if optimizations are enabled
void ICGenerator::Preprocess (SyntaxTree * tree, SymbolTable * symtab) {

}

IOperand *ICGenerator::traverse_tree(Node *n, IntermediateCode *icode){
  IOperand *lc = NULL;
  IOperand *rc = NULL;
  IOperand *res = NULL;
  IStatement *istmt = NULL;
  
  if(n->GetNodeType() == NODE_IF){
    traverse_tree(n->GetLeftChild()->GetChild(), icode);
    istmt = icode->GetStatement(icode->GetStatementCount() - 1);
    IOperand *l1 = new IOperand_Symbol(GenerateLabel());
    IOperand *l2 = new IOperand_Symbol(GenerateLabel());
    istmt->SetResult(l1);
    if(n->GetRightChild()->GetNodeType() == NODE_IF_TARGETS){
      traverse_tree(n->GetRightChild()->GetRightChild(), icode);
      icode->AppendStatement(new IStatement(IOP_GOTO, l2, NULL, NULL));
      icode->AppendStatement(new IStatement(IOP_LABEL, l1->Clone(), NULL, NULL));
      traverse_tree(n->GetRightChild()->GetLeftChild(), icode);
    }
    else{
      icode->AppendStatement(new IStatement(IOP_GOTO, l2, NULL, NULL));
      icode->AppendStatement(new IStatement(IOP_LABEL, l1->Clone(), NULL, NULL));
      traverse_tree(n->GetRightChild(), icode);
    }
    icode->AppendStatement(new IStatement(IOP_LABEL, l2->Clone(), NULL, NULL));
    return NULL;
  }
  
  else if(n->GetNodeType() == NODE_WHILE){
    IOperand *l1 = new IOperand_Symbol(GenerateLabel());
    IOperand *l2 = new IOperand_Symbol(GenerateLabel());
    IOperand *l3 = new IOperand_Symbol(GenerateLabel());
    icode->AppendStatement(new IStatement(IOP_LABEL, l3, NULL, NULL));
    traverse_tree(n->GetLeftChild()->GetChild(), icode);
    istmt = icode->GetStatement(icode->GetStatementCount() - 1);
    istmt->SetResult(l1);
    icode->AppendStatement(new IStatement(IOP_GOTO, l2, NULL, NULL));
    icode->AppendStatement(new IStatement(IOP_LABEL, l1->Clone(), NULL, NULL));
    traverse_tree(n->GetRightChild(), icode);
    icode->AppendStatement(new IStatement(IOP_GOTO, l3->Clone(), NULL, NULL));
    icode->AppendStatement(new IStatement(IOP_LABEL, l2->Clone(), NULL, NULL));
    return NULL;
  }
  
  if(n->GetChild() != NULL)
    lc = traverse_tree(n->GetChild(), icode);
  else if(n->GetLeftChild() != NULL)
    lc = traverse_tree(n->GetLeftChild(), icode);
  
  if(n->GetNodeType() == NODE_EXPRLIST){
    if(n->GetLeftChild()->GetReturnType() == RT_INT)
      istmt = new IStatement(IOP_PARAM_I, lc->Clone(), NULL, NULL);
    else
      istmt = new IStatement(IOP_PARAM_R, lc->Clone(), NULL, NULL);
    icode->AppendStatement(istmt);
  }
  
  if(n->GetRightChild() != NULL)
    rc = traverse_tree(n->GetRightChild(), icode);
  
  if(n->GetNodeType() == NODE_STATEMENT_LIST 
  || n->GetNodeType() == NODE_EXPRLIST)
    return NULL;
    
  else if(lc != NULL && rc != NULL){
    switch(n->GetNodeType()){
      case NODE_ADD:
        if(n->GetReturnType() == RT_INT){
          res = new IOperand_Symbol(GenerateTempVar(RT_INT));
          istmt = new IStatement(IOP_ADD_I, lc->Clone(), rc->Clone(), res);
        }
        else{
          res = new IOperand_Symbol(GenerateTempVar(RT_REAL));
          istmt = new IStatement(IOP_ADD_R, lc->Clone(), rc->Clone(), res);
        }
        break;
        
      case NODE_SUB:
        if(n->GetReturnType() == RT_INT){
          res = new IOperand_Symbol(GenerateTempVar(RT_INT));
          istmt = new IStatement(IOP_SUB_I, lc->Clone(), rc->Clone(), res);
        }
        else{
          res = new IOperand_Symbol(GenerateTempVar(RT_REAL));
          istmt = new IStatement(IOP_SUB_R, lc->Clone(), rc->Clone(), res);
        }
        break;
        
      case NODE_MUL:
        if(n->GetReturnType() == RT_INT){
          res = new IOperand_Symbol(GenerateTempVar(RT_INT));
          istmt = new IStatement(IOP_MUL_I, lc->Clone(), rc->Clone(), res);
        }
        else{
          res = new IOperand_Symbol(GenerateTempVar(RT_REAL));
          istmt = new IStatement(IOP_MUL_R, lc->Clone(), rc->Clone(), res);
        }
        break;
        
      case NODE_DIV:
        res = new IOperand_Symbol(GenerateTempVar(RT_REAL));
        istmt = new IStatement(IOP_DIV_R, lc->Clone(), rc->Clone(), res);
        break;
      
      case NODE_IDIV:
        res = new IOperand_Symbol(GenerateTempVar(RT_INT));
        istmt = new IStatement(IOP_DIV_I, lc->Clone(), rc->Clone(), res);
        break;
      
      case NODE_MOD:
        res = new IOperand_Symbol(GenerateTempVar(RT_INT));
        istmt = new IStatement(IOP_MOD, lc->Clone(), rc->Clone(), res);
        break;
      
      case NODE_AND:
        res = new IOperand_Symbol(GenerateTempVar(RT_INT));
        istmt = new IStatement(IOP_AND, lc->Clone(), rc->Clone(), res);
        break;
      
      case NODE_OR:
        res = new IOperand_Symbol(GenerateTempVar(RT_INT));
        istmt = new IStatement(IOP_OR, lc->Clone(), rc->Clone(), res);
        break;
      
      case NODE_ASSIGNMENT:
        res = lc;
        if(n->GetRightChild()->GetReturnType() == RT_INT)
          istmt = new IStatement(IOP_ASSIGN_I, rc->Clone(), NULL, lc->Clone());
        else
          istmt = new IStatement(IOP_ASSIGN_R, rc->Clone(), NULL, lc->Clone());
        break;
      
      case NODE_REL_EQUAL:
        if(n->GetRightChild()->GetReturnType() == RT_INT)
          istmt = new IStatement(IOP_BEQ_I, lc->Clone(), rc->Clone(), NULL);
        else
          istmt = new IStatement(IOP_BEQ_R, lc->Clone(), rc->Clone(), NULL);
        break;
      
      case NODE_REL_GT:
        if(n->GetRightChild()->GetReturnType() == RT_INT)
          istmt = new IStatement(IOP_BGT_I, lc->Clone(), rc->Clone(), NULL);
        else
          istmt = new IStatement(IOP_BGT_R, lc->Clone(), rc->Clone(), NULL);
        break;
      
      case NODE_REL_LT:
        if(n->GetRightChild()->GetReturnType() == RT_INT)
          istmt = new IStatement(IOP_BLT_I, lc->Clone(), rc->Clone(), NULL);
        else
          istmt = new IStatement(IOP_BLT_R, lc->Clone(), rc->Clone(), NULL);
        break;
      
      case NODE_REL_GTE:
        if(n->GetRightChild()->GetReturnType() == RT_INT)
          istmt = new IStatement(IOP_BGE_I, lc->Clone(), rc->Clone(), NULL);
        else
          istmt = new IStatement(IOP_BGE_R, lc->Clone(), rc->Clone(), NULL);
        break;
      
      case NODE_REL_LTE:
        if(n->GetRightChild()->GetReturnType() == RT_INT)
          istmt = new IStatement(IOP_BLE_I, lc->Clone(), rc->Clone(), NULL);
        else
          istmt = new IStatement(IOP_BLE_R, lc->Clone(), rc->Clone(), NULL);
        break;
      
      case NODE_REL_NOTEQUAL:
        if(n->GetRightChild()->GetReturnType() == RT_INT)
          istmt = new IStatement(IOP_BNE_I, lc->Clone(), rc->Clone(), NULL);
        else
          istmt = new IStatement(IOP_BNE_R, lc->Clone(), rc->Clone(), NULL);
        break;
      
      case NODE_FUNCTIONCALL:
        res = new IOperand_Symbol(GenerateTempVar(n->GetReturnType()));
        istmt = new IStatement(IOP_FUNCCALL, lc->Clone(), NULL, res);
        break;
        
      case NODE_PROCCALL:
        istmt = new IStatement(IOP_PROCCALL, lc->Clone(), NULL, NULL);
        break;
      
      default:
        istmt = new IStatement(IOP_UNKNOWN);
    }
    icode->AppendStatement(istmt);
    return res;
  }
  
  else if(n->GetChild() != NULL || (lc != NULL && rc == NULL)){
    switch(n->GetNodeType()){
      case NODE_COERCION:
        res = new IOperand_Symbol(GenerateTempVar(RT_REAL));
        istmt = new IStatement(IOP_INT_TO_REAL, lc->Clone(), NULL, res);
        break;
        
      case NODE_SIGNMINUS:
        if(n->GetChild()->GetReturnType() == RT_INT){
          res = new IOperand_Symbol(GenerateTempVar(RT_INT));
          istmt = new IStatement(IOP_UNARY_MINUS_I, lc->Clone(), NULL, res);
        }
        else{
          res = new IOperand_Symbol(GenerateTempVar(RT_REAL));
          istmt = new IStatement(IOP_UNARY_MINUS_R, lc->Clone(), NULL, res);
        }
        break;
        
      case NODE_FUNCTIONCALL:
        res = new IOperand_Symbol(GenerateTempVar(n->GetReturnType()));
        istmt = new IStatement(IOP_FUNCCALL, lc->Clone(), NULL, res);
        break;
        
      case NODE_NOT:
        res = new IOperand_Symbol(GenerateTempVar(RT_INT));
        istmt = new IStatement(IOP_NOT, lc->Clone(), NULL, res);
        break;
        
      case NODE_PROCCALL:
        istmt = new IStatement(IOP_PROCCALL, lc->Clone(), NULL, NULL);
        break;
      
      default:
        istmt = new IStatement(IOP_UNKNOWN);
    }
    icode->AppendStatement(istmt);
    return res;
  }
  
  else if(lc == NULL && rc == NULL){
    if(n->GetNodeType() == NODE_NUM_INT)
      return new IOperand_Int(n->GetIntValue());
    else if(n->GetNodeType() == NODE_NUM_REAL)
      return new IOperand_Real(n->GetRealValue());
    else if(n->GetNodeType() == NODE_ID)
      return new IOperand_Symbol(n->GetSymbol());
    else
      return NULL;
  }
  
  return NULL;
}

// Takes a SyntaxTree and converts it into an IntermediateCode structure
IntermediateCode * ICGenerator::GenerateIntermediateCode (SyntaxTree * inputTree, SymbolTable * symtab) {
  IntermediateCode * icode;
  IStatement * istmt;
  icode = new IntermediateCode;
  
  Node *n = inputTree->GetProgramBody();
  traverse_tree(n, icode);
    
  /* Indicate end of program body */
  istmt = new IStatement (IOP_RETURN);
  icode->AppendStatement(istmt);

  /* Now walk through the list of subprograms, and process them one by one */
  for (int i = 0; i < inputTree->GetSubprogramCount(); i++) {
    n = inputTree->GetSubprogram(i);
    Symbol *sym = symtab->GetSymbol(inputTree->GetSubprogramName(i));
    IOperand *sub_name = new IOperand_Symbol(sym);
    istmt = new IStatement(IOP_SUBPROG, sub_name, NULL, NULL);
    icode->AppendStatement(istmt);
    traverse_tree(n, icode);
    if(sym->GetSymbolType() == ST_FUNCTION){
      if(sym->GetReturnType() == RT_INT)
        istmt = new IStatement(IOP_RETURN_I, sub_name->Clone(), NULL, NULL);
      else
        istmt = new IStatement(IOP_RETURN_R, sub_name->Clone(), NULL, NULL);
    }
    else
      istmt = new IStatement(IOP_RETURN);
    icode->AppendStatement(istmt);
  }
  return icode;
}


// Postprocesses the intermediate code; this method is called after
// GenerateIntermediateCode() if optimizations are enabled
void ICGenerator::Postprocess (IntermediateCode * code, SymbolTable * symtab) {

}


// Generate a temporary symbol
Symbol * ICGenerator::GenerateTempVar(ReturnType type) {
  Symbol *sym = new Symbol();
  string s = static_cast<ostringstream*>(&(ostringstream() << ++tempCount))->str();
  sym->SetName("t" + s);
  sym->SetSymbolType(ST_TEMPVAR);
  sym->SetReturnType(type);
  return sym;
}

// Generates a Symbol for a label
Symbol * ICGenerator::GenerateLabel() {
  Symbol *sym = new Symbol();
  string s = static_cast<ostringstream*>(&(ostringstream() << ++labelCount))->str();
  sym->SetName("l" + s);
  sym->SetSymbolType(ST_LABEL);
  return sym;
}
