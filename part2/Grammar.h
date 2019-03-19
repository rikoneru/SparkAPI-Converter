/**
*	Source : Grammar.h
*	Description: Provides the grammar to be used to parse the program. Provides interface for each non-terminal in the grammar. 
*				 Non-Terminal interfaces will validate the program usign the terminals of the grammar.
<Program>		 ::= sc.range(<number>,<number>)<MapOps>.collect()
<MapOps>		 ::= ∅ | <MapOps>.map(<UDF>)
<UDF>			 ::= <identifier> => <Expression>
<Expression>	 ::= {<ComplexExpr>} | <SimpleExpr>
<SimpleExpr>	 ::= <PureExpr> | (<TupleExpr>)
<TupleExpr>	     ::= <PureExpr>, <PureExpr> <TupleExprPrime>
<TupleExprPrime> ::= , <PureExpr> <TupleExprPrime>
<ComplexExpr>	 ::= <SimpleExpr> | <AssignExprs>;<SimpleExpr>
<AssignExprs>	 ::= <AssignExpr> <AssignExprsPrime>
<AssignExprsPrime> ::= ;<AssignExpr> <AssignExprsPrime>
<AssignExpr>	 ::= val <identifier> = <PureExpr>
<PureExpr>		 ::= <temp> <PureExprPrime>
<PureExprPrime>  ::= <Op> <PureExpr> <PureExprPrime>
<temp>           ::= <identifier> <tempPrime>|    				
    				(<PureExpr>) | 
    				if ( <CompExpr>) <PureExpr> else <PureExpr>
<tempPrime>      := .<identifier> | empty  
<CompExpr>		::= <PureExpr> <Comp> <PureExpr>
<Op>			::= + | - | * | %
<Comp>		::= == | < | > | != | >= | <=
*/
#ifndef _GRAMMAR_H
#define _GRAMMAR_H
#include <fstream>
#include "Parser.h"
#include "Function.h"
#include "ASTNode.h"
#include "stdc++.h"

using namespace std;
class Token;
class Parser;
static string str_def = ""; 
class Grammar
{
public:
	/*Interfaces for each of the non-terminal in the grammar*/
	bool program();

	bool program1();

	bool MapOps();

	bool MapOps1();

	bool MapOps2();

	bool UDF();

	bool UDF1();

	bool Expression(string& exp = str_def);

	bool Expression1(string& exp = str_def);

	bool Expression2(string& exp = str_def);

	bool SimpleExpr(string& exp = str_def);

	bool SimpleExpr1(string& exp = str_def);

	bool SimpleExpr2(string& exp = str_def);

	bool TupleExpr(string& exp = str_def);

	bool TupleExpr1(string& exp = str_def);

	bool TupleExprPrime(string& exp = str_def);

	bool TupleExprPrime1(string& exp = str_def);

	bool TupleExprPrime2(string& exp = str_def);

	bool ComplexExpr(string& exp = str_def);

	bool ComplexExpr1(string& exp = str_def);

	bool ComplexExpr2(string& exp = str_def);

	bool AssignExprs(string& exp = str_def);

	bool AssignExprs1(string& exp = str_def);

	bool AssignExprsPrime(string& exp = str_def);

	bool AssignExprsPrime1(string& exp = str_def);

	bool AssignExprsPrime2(string& exp = str_def);

	bool AssignExpr(string& exp = str_def);

	bool AssignExpr1(string& exp = str_def);

	bool PureExpr(string& exp = str_def);

	bool PureExpr1(string& exp = str_def);

	bool PureExpr2(string& exp = str_def);

	bool PureExpr3(string& exp = str_def);

	bool PureExpr4(string& exp = str_def);

	bool PureExprPrime(string& exp = str_def);

	bool PureExprPrime1(string& exp = str_def);

	bool PureExprPrime2(string& exp = str_def);

	bool temp(string& exp = str_def);

	bool temp1(string& exp = str_def);

	bool temp2(string& exp = str_def);

	bool CompExpr(string& exp = str_def);

	bool CompExpr1(string& exp = str_def);

	bool Op(string& exp = str_def);

	bool Op1(string& exp = str_def);

	bool Comp(string& exp = str_def);

	bool Comp1(string& exp = str_def);

	bool identifier(string& exp = str_def, char type = 'B');

	bool identifier1(string& exp = str_def, char type = 'B');

	bool number(string& exp = str_def);

	bool number1(string& exp = str_def);

	void instanciateParser(Parser* newParser);

private:
	Parser *parse;

public:
		std::ofstream *outFile;

		Grammar(std::ofstream *newOutFile)
		{
			outFile = newOutFile;
		}

};
#endif

	

	

	

	

	

	

	

	

	

	

	
