#include <vector>
#include <cstring>
#include <cstdlib>
#include "Grammar.h"
#include "Token.h"
#include "ASTNode.h"
#include "Util.h"

#include <iostream>
#include <string>
#include "stdc++.h"

using namespace std;

int count1 = 1;
/**
*	Source : Grammar.h
*	Description: Provides the grammar to be used to parse the program. Provides interface for each non-terminal in the grammar. 
*				 Non-Terminal interfaces will validate the program usign the terminals of the grammar.

sc.range(10,100).map(i=>{val j = i*k;(i, if(j==q)i*w else i*y)}).collect()

<Program>        ::= <Program1>

<Program1>		 ::= sc.range(<number>,<number>)<MapOps>.collect() {sc}

<MapOps>         := <MapOps1>
				   |<MapOps2>

<MapOps1>		 ::= .map(<UDF>)<MapOps> {.map} 

<MapOps2>        ::= empty {.collect}

<UDF>            ::= <UDF1>

<UDF1>			 ::= <identifier> => <Expression> {'{', id, '(', if}

<Expression>     ::= <Expression1>
                    |<Expression2>

<Expression1>	 ::= {<ComplexExpr>}   {'{'}

<Expression2>    ::= <SimpleExpr>  {'(', id, if}

<SimpleExpr>     ::= <SimpleExpr1>
					|<SimpleExpr2>

<SimpleExpr1>	 ::= <PureExpr>     {'(', id, if} 

<SimpleExpr2>    ::= (<TupleExpr>) {'('}

<TupleExpr>      ::= <TupleExpr1>

<TupleExpr1>	 ::= <PureExpr>, <PureExpr> <TupleExprPrime> {'(', id, if}

<TupleExprPrime>   ::= <TupleExprPrime1> 
					  |<TupleExprPrime2> 

<TupleExprPrime1> ::= , <PureExpr> <TupleExprPrime> {','}
					 
<TupleExprPrime2> ::= empty     {')'}

<ComplexExpr>    ::= <ComplexExpr1>
					|<ComplexExpr2>

<ComplexExpr1>	 ::= <SimpleExpr>	{'(', id, if} 

<ComplexExpr2>	 ::= <AssignExprs>;<SimpleExpr>	{val}

<AssignExprs>	 ::= <AssignExprs1>

<AssignExprs1>   :=  <AssignExpr> <AssignExprsPrime> {val}

<AssignExprsPrime> ::= <AssignExprsPrime1>
					| <AssignExprsPrime2>

<AssignExprsPrime1> ::= ;<AssignExpr> <AssignExprsPrime> {;}
					   
<AssignExprsPrime2> ::=  empty {;}

<AssignExpr>     ::= <AssignExpr1>

<AssignExpr1>	 ::= val <identifier> = <PureExpr> {val}

<PureExpr>       ::= <PureExpr1>
					|<PureExpr2>
					|<PureExpr3>
					|<PureExpr4>


<PureExpr1>		 ::= <identifier> <temp> <PureExprPrime>	{id}

<PureExpr2>      ::= (<PureExpr>) <PureExprPrime> 			{'('}

<PureExpr3>      ::= if ( <CompExpr>) <PureExpr> else <PureExpr> <PureExprPrime>	{if}

<PureExpr4>      ::= <number> <PureExprPrime>  

<PureExprPrime>  ::= <PureExprPrime1>
					|<PureExprPrime2>

<PureExprPrime1>  ::= <Op> <PureExpr> <PureExprPrime> {+, -, *, %}

<PureExprPrime2>  ::= empty {;, ',' , ')', .collect}

<temp>      := <temp1>
              |<temp2>

<temp1>      := .<identifier> {'.'}

<temp2>      := empty  {+, -, *, %, ;, ',' , ')', .collect}

<CompExpr>		::= <CompExpr1>

<CompExpr1>		::= <PureExpr> <Comp> <PureExpr> {'(', id, if}

<Op>            ::= <Op1>

<Op1>			::= + | - | * | %

<Comp>          ::= <Comp1>

<Comp1>		    ::= == | < | > | != | >= | <=
*/

string n1 = "$", n2 = "$";
map<string, string> m; 
bool Grammar::program()
{
	/**
	*<Program>        ::= <Program1>
	*/
	// std::cout << "program" << std::endl;
	return parse->SaveTokenIT() && program1();
}
bool Grammar::program1()
{
	/**
	*<Program1>      :=  sc.range(<number>,<number>)<MapOps>.collect()
	*/
	// std::cout << "program1" << std::endl;
	if (parse->curToken()
		&& parse->curToken()->getID() == Token::IDTYPE_RESERVEDWORD
		&& !strcmp(parse->curToken()->getTokenName().c_str(), "sc"))
		{  
           if(parse->nextToken()
		      && parse->curToken()->getID() == Token::IDTYPE_SYMBOL
		      && !strcmp(parse->curToken()->getTokenName().c_str(), ".")
		      && parse->nextToken()
		      && parse->curToken()->getID() == Token::IDTYPE_RESERVEDWORD
		      && !strcmp(parse->curToken()->getTokenName().c_str(), "range")
		      && parse->nextToken()
		      && parse->curToken()->getID() == Token::IDTYPE_SYMBOL
		      && !strcmp(parse->curToken()->getTokenName().c_str(), "(")
		      && parse->nextToken()
		      && number()
		      && parse->curToken()->getID() == Token::IDTYPE_SYMBOL
		      && !strcmp(parse->curToken()->getTokenName().c_str(), ",")
		      && parse->nextToken()
		      && number()
		      && parse->curToken()->getID() == Token::IDTYPE_SYMBOL
		      && !strcmp(parse->curToken()->getTokenName().c_str(), ")"))
           {	
           		*outFile<<"spark.range("<<n1<<","<<n2<<").selectExpr(\"id as _1\")";
           		if(parse->nextToken()
		        && MapOps()
		        && parse->curToken()->getID() == Token::IDTYPE_SYMBOL
		        && !strcmp(parse->curToken()->getTokenName().c_str(), ".")
		        && parse->nextToken()
		        && parse->curToken()->getID() == Token::IDTYPE_RESERVEDWORD
		        && !strcmp(parse->curToken()->getTokenName().c_str(), "collect")
		        && parse->nextToken()
		        && parse->curToken()->getID() == Token::IDTYPE_SYMBOL
		        && !strcmp(parse->curToken()->getTokenName().c_str(), "(")
		        && parse->nextToken()
		        && parse->curToken()->getID() == Token::IDTYPE_SYMBOL
		        && !strcmp(parse->curToken()->getTokenName().c_str(), ")"))
				{	*outFile<<".collect()";

					if(!parse->nextToken())
						return true;
				}
           }
       }
	
	 	return false;

}

bool Grammar::MapOps()
{
	/**
	*<MapOps>         := <MapOps1>
				   	  |<MapOps2>

	*/
	// std::cout << "MapOps" << std::endl;
	// std::vector<Token *>::iterator savedtokenIT;
	return (parse->SaveTokenIT() && MapOps1()) || (parse->BackTrack() && parse->SaveTokenIT() && MapOps2());
}

bool Grammar::MapOps1()
{
	/*
		<MapOps1>       ::= .map(<UDF>)
	*/

	// std::cout<<"Mapops1"<<" "<<parse->curToken()->getTokenName().c_str()<<std::endl;

	 if(parse->curToken()
	   && parse->curToken()->getID() == Token::IDTYPE_SYMBOL
	   && !strcmp(parse->curToken()->getTokenName().c_str(), ".")
	   && parse->nextToken())
	 {

	   if(parse->curToken()->getID() == Token::IDTYPE_RESERVEDWORD
	   && !strcmp(parse->curToken()->getTokenName().c_str(), "map")
	   && parse->nextToken()
	   && parse->curToken()->getID() == Token::IDTYPE_SYMBOL
	   && !strcmp(parse->curToken()->getTokenName().c_str(), "(")
	   && parse->nextToken())
	 {
	 	m.clear();
	 	if(UDF())
	 	{   

	 		if(parse->curToken()->getID() == Token::IDTYPE_SYMBOL
	           && !strcmp(parse->curToken()->getTokenName().c_str(), ")")
	           && parse->nextToken())
	 		{
	 			if(MapOps())
	 			{
	 				return true;
	 			}
	 		}
	 	}
	 }
	}

	return false;
}

bool Grammar::MapOps2()
{
	/*
		<MapOps2>       ::= empty
	*/
	// std::cout<<"Mapops2"<< " "<<" "<<parse->curToken()->getTokenName().c_str()<<std::endl;
	return true;
}

bool Grammar::UDF()
{
	/**
	*<UDF>            ::= <UDF1>
	*/
	// std::cout<<"UDF"<<" "<<parse->curToken()->getTokenName().c_str()<<std::endl;
	return parse->SaveTokenIT() && UDF1();
}

bool Grammar::UDF1()
{
	/*
		<UDF1>			 ::= <identifier> => <Expression>
	*/

	// std::cout<<"UDF1"<<" "<<parse->curToken()->getTokenName().c_str()<<std::endl;
	string exp;
	string id;
	count1 = 1;
	if(identifier(id))
	{  
	   m[id] = "_1";
	   if(parse->curToken()
	   && parse->curToken()->getSymType() == Token::SYMTYPE_IMPLIES
	   && parse->nextToken()
	   && Expression(exp))
		{
			*outFile<<".selectExpr("<<exp<<")"<<endl;
			return true;
		}
	}

	return false;

}

bool Grammar::Expression(string& exp)
{
	/**
	*

	<Expression>     ::= <Expression1>
                    	|<Expression2>

	*/
	// std::cout<<"Expression"<<" "<<parse->curToken()->getTokenName().c_str()<<std::endl;
	return (parse->SaveTokenIT() && Expression1(exp)) || (parse->BackTrack() && parse->SaveTokenIT() && Expression2(exp));	
}

bool Grammar::Expression1(string& exp)
{
	/*
		<Expression1>	 ::= {<ComplexExpr>}   {'{'}


	*/
	  // std::cout<<"Expression1"<<" "<<parse->curToken()->getTokenName().c_str()<<std::endl;
	  if(parse->curToken()
	   && parse->curToken()->getID() == Token::IDTYPE_SYMBOL
	   && !strcmp(parse->curToken()->getTokenName().c_str(), "{")
	   && parse->nextToken())
	  { 
	  	if(ComplexExpr(exp))
	  	{
	  		// std::cout<<"Inside Expression1"<<std::endl;
	       if( parse->curToken()
	       && parse->curToken()->getID() == Token::IDTYPE_SYMBOL
	       && !strcmp(parse->curToken()->getTokenName().c_str(), "}"))
	       {
	       	parse->nextToken();
	       	//std::cout<<"Expression End"<<" "<<parse->curToken()->getTokenName().c_str()<<std::endl;
	       	return true;
	       }
	  	}	  	
	  }
	  // else if(SimpleExpr())
	  // {
	  // 		std::cout<<"Expression End"<<" "<<parse->curToken()->getTokenName().c_str()<<std::endl;
	  // 		return true;
	  // }
	  // else return false; 
	  return false;

}

bool Grammar::Expression2(string& exp)
{
	/**
	*<Expression2>    ::= <SimpleExpr>  {'(', id, if}


	*/
	// std::cout<<"Expression2"<< " "<<" "<<parse->curToken()->getTokenName().c_str()<<std::endl;
	return SimpleExpr(exp);

}

bool Grammar::SimpleExpr(string& exp)
{
	/**
	*<SimpleExpr>     ::= <SimpleExpr1>
					|<SimpleExpr2>

	*/
	std::vector<Token *>::iterator savedtokenIT = parse->SaveTokenIT2();
	string s1, s2;


	bool a = (SimpleExpr1(s1));
	
	if(a)
	{
		exp = exp + s1;
		return true;
	}
	else
	{
		
		bool b = parse->BackTrack(savedtokenIT);
		// std::cout<<"SimpleExpr: Saved Token= "<<parse->curToken()->getTokenName().c_str()<<std::endl;
		b = (b && parse->SaveTokenIT() && SimpleExpr2(s2));
		exp = exp + s2;
		return b;
	}

	return false;
	// std::cout<<"SimpleExpr"<<" "<<parse->curToken()->getTokenName().c_str()<<std::endl;

	// return (parse->SaveTokenIT() && SimpleExpr1()) || (parse->BackTrack() && parse->SaveTokenIT() && SimpleExpr2());		
}

bool Grammar:: SimpleExpr1(string& exp)
{
	/*
	<SimpleExpr1>	 ::= (<TupleExpr>)
	*/
	// std::cout<<"SimpleExpr1"<<" "<<parse->curToken()->getTokenName().c_str()<<std::endl;
	if(parse->curToken()
	   && parse->curToken()->getID() == Token::IDTYPE_SYMBOL
	   && !strcmp(parse->curToken()->getTokenName().c_str(), "(")
	   && parse->nextToken())
	  {
	  	if(TupleExpr(exp))
	  	{
	       if( parse->curToken()
	       && parse->curToken()->getID() == Token::IDTYPE_SYMBOL
	       && !strcmp(parse->curToken()->getTokenName().c_str(), ")"))
	       {
	       	parse->nextToken();
	       	return true;
	       }
	       // else return false;
	  	}
	  	// else return false;
	  }
	  // else if(PureExpr())
	  // {
	  // 		return true;
	  // }
	  // else return false; 
	  return false;
}

bool Grammar::SimpleExpr2(string& exp)
{
	/*
	<SimpleExpr2>	 ::= <PureExpr>     {'(', id, if} 
	*/
	// std::cout<<"SimpleExpr2"<<" "<<parse->curToken()->getTokenName().c_str()<<std::endl;
	string x1; 
	int n1 = count1;
	count1++;
	if(PureExpr(x1))
	{
		exp = exp + "\"" + x1 + " as _" + to_string(n1) + "\"";
		return true;
	}
	count1--;
	return false;

}

bool Grammar::TupleExpr(string& exp)
{
	/**
	*<TupleExpr>      ::= <TupleExpr1>
	*/
	// std::cout<<"TupleExpr"<<" "<<parse->curToken()->getTokenName().c_str()<<std::endl;
	return (parse->SaveTokenIT() && TupleExpr1(exp));
}

bool Grammar::TupleExpr1(string& exp)
{
/*
	<TupleExpr1>	 ::= <PureExpr>, <PureExpr> <TupleExprPrime> {'(', id, if}

*/
	// std::cout<<"TupleExpr1"<<" "<<parse->curToken()->getTokenName().c_str()<<std::endl;
	string x1, x2, x3;
	int n1 = count1;
	int n2 = count1 + 1;
	count1 = count1 + 2;
	if(PureExpr(x1))
	{
		if(parse->curToken()
	   && parse->curToken()->getID() == Token::IDTYPE_SYMBOL
	   && !strcmp(parse->curToken()->getTokenName().c_str(), ",")
	   && parse->nextToken())
		{
			
			if(PureExpr(x2))
			{   
				
				if(TupleExprPrime(x3))
				{
					exp = exp + "\"" + x1 + " as _" + to_string(n1) + "\"";
					exp = exp + " ," + "\"" + x2 + " as _" + to_string(n2) + "\"" + x3;
					return true;
				}
				// else return false;
			}
			// else return false;
		}
		// else return false;
	}
	count1 = count1-2; 
	return false;
}

bool Grammar::TupleExprPrime(string& exp)
{
	/**
	<TupleExprPrime>   ::= <TupleExprPrime1> 
					  |<TupleExprPrime2> 


	*/
	// std::cout<<"TupleExprPrime"<<" "<<parse->curToken()->getTokenName().c_str()<<std::endl;

	return (parse->SaveTokenIT() && TupleExprPrime1(exp)) || (parse->BackTrack() && parse->SaveTokenIT() && TupleExprPrime2(exp));
}

bool Grammar::TupleExprPrime1(string& exp)
{
	/**
	<TupleExprPrime1> ::= , <PureExpr> <TupleExprPrime> {','}
					 

	*/
	// std::cout<<"TupleExprPrime1"<<" "<<parse->curToken()->getTokenName().c_str()<<std::endl;
	string x1, x2;
	int n1 = count1;
	count1++;
	if(parse->curToken()
	   && parse->curToken()->getID() == Token::IDTYPE_SYMBOL
	   && !strcmp(parse->curToken()->getTokenName().c_str(), ",")
	   && parse->nextToken())
	{
		if(PureExpr(x1))
		{
			
			if(TupleExprPrime(x2))
			{
				exp = exp + "," + "\"" + x1 + " as _" + to_string(n1) + "\"" + x2;
				return true;
			}

		}
		//else return false;
	}
	count1--;
    return false;

}

bool Grammar::TupleExprPrime2(string& exp)
{
	/**
	*<TupleExprPrime2> ::= empty     {')'}

	*/
	// std::cout<<"TupleExprPrime2"<<" "<<parse->curToken()->getTokenName().c_str()<<std::endl;
	return true;
}

bool Grammar::ComplexExpr(string& exp)
{
	/**
	*<ComplexExpr>    ::= <ComplexExpr1>
					|<ComplexExpr2>

	*/
	// std::cout<<"ComplexExpr"<<" "<<parse->curToken()->getTokenName().c_str()<<std::endl;
	return (parse->SaveTokenIT() && ComplexExpr1(exp)) || (parse->BackTrack() && parse->SaveTokenIT() && ComplexExpr2(exp));
}

bool Grammar::ComplexExpr1(string& exp)
{
	/*
		<ComplexExpr1>	 ::= <SimpleExpr>	{'(', id, if} 

	*/
	// std::cout<<"ComplexExpr1"<<" "<<parse->curToken()->getTokenName().c_str()<<std::endl;
	return SimpleExpr(exp);
}

bool Grammar::ComplexExpr2(string& exp)
{
	/**
	*<ComplexExpr2>	 ::= <AssignExprs>;<SimpleExpr>	{val}


	*/

	// std::cout<<"ComplexExpr2"<<" "<<parse->curToken()->getTokenName().c_str()<<std::endl;
 	if(AssignExprs())
	 {  
	   //std::cout<<"Inside:           ComplexExpr2"<<std::endl;
	   if(parse->curToken()
	   && parse->curToken()->getID() == Token::IDTYPE_SYMBOL
	   && !strcmp(parse->curToken()->getTokenName().c_str(), ";")
	   && parse->nextToken())
		{
			if(SimpleExpr(exp))
			{
				return true;
			}
			// else return false;
		} 
		// else return false; 
	} 
	return false;

}

bool Grammar::AssignExprs(string& exp)
{
	/**
	*<AssignExprs>	 ::= <AssignExprs1>
	*/
	// std::cout<<"AssignExprs"<<" "<<parse->curToken()->getTokenName().c_str()<<std::endl;
	return (parse->SaveTokenIT() && AssignExprs1());
}

bool Grammar::AssignExprs1(string& exp)
{
	/**
	<AssignExprs1>  ::= <AssignExpr> <AssignExprsPrime> {val}
	*/
	// std::cout<<"AssignExprs1"<<" "<<parse->curToken()->getTokenName().c_str()<<std::endl;
	return AssignExpr() && AssignExprsPrime();

}

bool Grammar::AssignExprsPrime(string& exp)
{
	/**
	<AssignExprsPrime> ::= <AssignExprsPrime1>
	                       |<AssignExprsPrime2>
	*/

	// std::cout<<"AssignExprsPrime"<<" "<<parse->curToken()->getTokenName().c_str()<<std::endl;
	std::vector<Token *>::iterator savedtokenIT = parse->SaveTokenIT2();
	bool a = (AssignExprsPrime1());
	if(a)
		{
			return true;
		}
	else
		{
			bool b = parse->BackTrack(savedtokenIT);
			// std::cout<<"AssignExprsPrime: Saved Token= "<<parse->curToken()->getTokenName().c_str()<<std::endl;
			return (b && parse->SaveTokenIT() && AssignExprsPrime2());
		}
}

bool Grammar::AssignExprsPrime1(string& exp)
{
	/**
	*<AssignExprsPrime1> ::= ;<AssignExpr> <AssignExprsPrime> {;}
	*/
	// std::cout<<"AssignExprsPrime1"<<" "<<parse->curToken()->getTokenName().c_str()<<std::endl;
	if(parse->curToken()
	   && parse->curToken()->getID() == Token::IDTYPE_SYMBOL
	   && !strcmp(parse->curToken()->getTokenName().c_str(), ";")
	   && parse->nextToken())
		{
			if(AssignExpr())
			{
				if(AssignExprsPrime())
				{
					return true;
				}
				// else return false;
			}
			// else return false;
		}

	 return false;
}

bool Grammar::AssignExprsPrime2(string& exp)
{
	/**
	*<AssignExprsPrime2> ::=  empty {;}
	*/
	// std::cout<<"AssignExprsPrime2"<<" "<<parse->curToken()->getTokenName().c_str()<<std::endl;
	return true;
}

bool Grammar::AssignExpr(string& exp)
{
	/**
	*<AssignExpr>     ::= <AssignExpr1>

	*/
	// std::cout<<"AssignExpr"<<" "<<parse->curToken()->getTokenName().c_str()<<std::endl;
	return (parse->SaveTokenIT() && AssignExpr1());
}

bool Grammar::AssignExpr1(string& exp)
{
	/**
	*<AssignExpr1>	 ::= val <identifier> = <PureExpr> {val}
	*/
	// std::cout<<"AssignExpr1"<<" "<<parse->curToken()->getTokenName().c_str()<<std::endl;
	 string x1, x2;
	 if(parse->curToken()
		&& parse->curToken()->getID() == Token::IDTYPE_RESERVEDWORD
		&& !strcmp(parse->curToken()->getTokenName().c_str(), "val")
		&& parse->nextToken())
	 {
	 	if(identifier(x1, 'A'))
	 	{
	 		if(parse->curToken()
	        && parse->curToken()->getID() == Token::IDTYPE_SYMBOL
	        && !strcmp(parse->curToken()->getTokenName().c_str(), "=")
	        && parse->nextToken())
	 		{
	 			if(PureExpr(x2))
	 			{
	 				m[x1] = x2;
	 				//cout<<x1<<" "<<x2<<endl;
	 				return true;
	 			}
	 			// else return false;
	 		}
	 		// else return false;
	 	}
	 	// else return false;
	 }
	 return false;
}

bool Grammar:: PureExpr(string& exp)
{
	/*
	<PureExpr>       ::= <PureExpr1>
					|<PureExpr2>
					|<PureExpr3>
					|<PureExpr4>
	*/
	// std::cout<<"PureExpr"<<" "<<parse->curToken()->getTokenName().c_str()<<std::endl;
	if ((parse->SaveTokenIT() && PureExpr1(exp))
		|| (parse->BackTrack() && parse->SaveTokenIT() && PureExpr2(exp)) 
		|| (parse->BackTrack() && parse->SaveTokenIT() && PureExpr3(exp))
		|| (parse->BackTrack() && parse->SaveTokenIT() && PureExpr4(exp)))
		{
			return true;
		};

	return false;
}

bool Grammar:: PureExpr1(string& exp)
{
	/**
	<PureExpr1>		 ::= <identifier> <temp> <PureExprPrime>	{id}
	*/
	// std::cout<<"PureExpr1"<<" "<<parse->curToken()->getTokenName().c_str()<<std::endl;
	string x1,x2 = "",x3;
	if( identifier(x1) && temp(x2) && PureExprPrime(x3))
	{   
		//cout<<"           "<<x1<< "="<<m[x1]<<endl;
		if(x2 == "")
		exp = exp + m[x1] + x2 + x3;
		else
		exp = exp + x2 + x3;
		return true;
	}

	return false;
	
}

bool Grammar:: PureExpr2(string& exp)
{
	/**
	<PureExpr2>      ::= (<PureExpr>) <PureExprPrime> 			{'('}
	*/
	// std::cout<<"PureExpr2"<<" "<<parse->curToken()->getTokenName().c_str()<<std::endl;
	string x1, x2;
	if(parse->curToken()
	&& parse->curToken()->getID() == Token::IDTYPE_SYMBOL
	&& !strcmp(parse->curToken()->getTokenName().c_str(), "(")
	&& parse->nextToken())
	{   

		if(PureExpr(x1))
		{
			if(parse->curToken()
	        && parse->curToken()->getID() == Token::IDTYPE_SYMBOL
	        && !strcmp(parse->curToken()->getTokenName().c_str(), ")")
	        && parse->nextToken())
			{
				if(PureExprPrime(x2))
				{
					exp = exp + "(" + x1 + ")" + x2;
					return true;
				}
				
			}
			// else return false;
		}
		// else return false;
	}
	return false;
}

bool Grammar:: PureExpr3(string& exp)
{
	/**
	<PureExpr3>      ::= if ( <CompExpr>) <PureExpr> else <PureExpr> <PureExprPrime>	{if}
	*/
	// std::cout<<"PureExpr3"<<" "<<parse->curToken()->getTokenName().c_str()<<std::endl;
	string condition, statements1, statements2, x1;
	if(parse->curToken()
		&& parse->curToken()->getID() == Token::IDTYPE_RESERVEDWORD
		&& !strcmp(parse->curToken()->getTokenName().c_str(), "if")
		&& parse->nextToken())
	 {	 
	 	 if(parse->curToken()
	        && parse->curToken()->getID() == Token::IDTYPE_SYMBOL
	        && !strcmp(parse->curToken()->getTokenName().c_str(), "(")
	        && parse->nextToken())
		{   
			if(CompExpr(condition))
			{
				if(parse->curToken()
	        	&& parse->curToken()->getID() == Token::IDTYPE_SYMBOL
	        	&& !strcmp(parse->curToken()->getTokenName().c_str(), ")")
	        	&& parse->nextToken())
				{
					
					if(PureExpr(statements1))
					{
						if(parse->curToken()
		                   && parse->curToken()->getID() == Token::IDTYPE_RESERVEDWORD
		                   && !strcmp(parse->curToken()->getTokenName().c_str(), "else")
		                   && parse->nextToken())
						{   
							if(PureExpr(statements2))
							{
								
								if(PureExprPrime(x1))
								{
									exp = exp + "if(" + condition + "," + statements1 + "," + statements2 + ")" + x1;
									return true;

								}
								
							}
							// else return false;
						}
						// else return false;
					}
					// else return false;
				}
				// else return false;
			}
			// else return false;
		}
		// else return false;
	 }
	 return false;
}

bool Grammar::PureExpr4(string& exp)
{
	return number(exp) && PureExprPrime(exp);
}

bool Grammar::PureExprPrime(string& exp)
{
	/*
	<PureExprPrime>  ::= <PureExprPrime1>
					|<PureExprPrime2>

	*/
	// std::cout<<"PureExprPrime"<<" "<<parse->curToken()->getTokenName().c_str()<<std::endl;
	return (parse->SaveTokenIT() && PureExprPrime1(exp)) || (parse->BackTrack() && parse->SaveTokenIT() && PureExprPrime2(exp));
}


bool Grammar:: PureExprPrime1(string& exp)
{
	/**
	<PureExprPrime1>  ::= <Op> <PureExpr> <PureExprPrime> {+, -, *, %}

	*/
	// std::cout<<"PureExprPrime1"<<" "<<parse->curToken()->getTokenName().c_str()<<std::endl;
	string x1, x2, x3;
	if(Op(x1) && PureExpr(x2) && PureExprPrime(x3))
	{
		exp = exp + x1 + x2 + x3;
		return true;
	}
	return false;
}

bool Grammar:: PureExprPrime2(string& exp)
{
	/**
	<PureExprPrime2>  ::= empty {;, ',' , ')', .collect}
	*/
	// std::cout<<"PureExprPrime2"<<" "<<parse->curToken()->getTokenName().c_str()<<std::endl;
	return true;
}

bool Grammar::temp(string& exp)
{
	/**
	
	<temp>      := <temp1>
              	|<temp2>
	*/
	// std::cout<<"temp"<<" "<<parse->curToken()->getTokenName().c_str()<<std::endl;

	return (parse->SaveTokenIT() && temp1(exp)) || (parse->BackTrack() && parse->SaveTokenIT() && temp2(exp));
}

bool Grammar::temp1(string& exp)
{
	/*
	<temp1>      := .<identifier> {'.'}
	*/
	// std::cout<<"temp1"<<" "<<parse->curToken()->getTokenName().c_str()<<std::endl;
	string x1;
	if(parse->curToken()
	   && parse->curToken()->getID() == Token::IDTYPE_SYMBOL
	   && !strcmp(parse->curToken()->getTokenName().c_str(), ".")
	   && parse->nextToken())
	{
		if(identifier(x1))
		{
			exp = exp + x1;
			return true;
		}
	// return false;
	}

	return false;
}

bool Grammar::temp2(string &exp)
{
	/**
	<temp2>      := empty  {+, -, *, %, ;, ',' , ')', .collect}
	*/
	// std::cout<<"temp2"<<" "<<parse->curToken()->getTokenName().c_str()<<std::endl;
	return true;
}

bool Grammar::CompExpr(string& exp)
{
	/*
		<CompExpr>		::= <CompExpr1>
	*/
	// std::cout<<"CompExpr"<<" "<<parse->curToken()->getTokenName().c_str()<<std::endl;
	return (parse->SaveTokenIT() && CompExpr1(exp));
}

bool Grammar::CompExpr1(string& exp)
{
	/**
	
<CompExpr1>		::= <PureExpr> <Comp> <PureExpr> {'(', id, if}
	*/
	// std::cout<<"CompExpr1"<<" "<<parse->curToken()->getTokenName().c_str()<<std::endl;
	string expr1, comp , expr2;
	if(PureExpr(expr1) && Comp(comp) && PureExpr(expr2))
		{
			exp = exp + expr1 + comp + expr2;
			return true;
		}
	return false;
}

bool Grammar::Op(string& exp)
{
	
	/**
	<Op>            ::= <Op1>
	*/
	// std::cout<<"Op"<<" "<<parse->curToken()->getTokenName().c_str()<<std::endl;
	return (parse->SaveTokenIT() && Op1(exp));
}
bool Grammar::Op1(string& exp)
{
	/**
	<Op1>			::= + | - | * | %
	*/
	// std::cout<<"Op1"<<" "<<parse->curToken()->getTokenName().c_str()<<std::endl;
	if (parse->curToken()
		&& (parse->curToken()->getSymType() == Token::SYMTYPE_PLUS
		|| parse->curToken()->getSymType() == Token::SYMTYPE_MINUS
		|| parse->curToken()->getSymType() == Token::SYMTYPE_STAR
		|| parse->curToken()->getSymType() == Token::SYMTYPE_MOD
		))
	{
		exp = exp + parse->curToken()->getTokenName();
		parse->nextToken();
		return true;
	}

	return false;
}

bool Grammar::Comp(string& exp)
{
	/**
	<Comp>          ::= <Comp1>
	*/
	// std::cout<<"Comp"<<" "<<parse->curToken()->getTokenName().c_str()<<std::endl;

	return (parse->SaveTokenIT() && Comp1(exp));
}

bool Grammar::Comp1(string& exp)
{
	/**	
	<Comp1>		    ::= == | < | > | != | >= | <=
	*/
	// std::cout<<"Comp1"<<" "<<parse->curToken()->getTokenName().c_str()<<std::endl;
	if (parse->curToken()
		&& (parse->curToken()->getSymType() == Token::SYMTYPE_DOUBLE_EQUAL
		|| parse->curToken()->getSymType() == Token::SYMTYPE_NT_EQUAL
		|| parse->curToken()->getSymType() == Token::SYMTYPE_GT
		|| parse->curToken()->getSymType() == Token::SYMTYPE_GT_EQUAL
		|| parse->curToken()->getSymType() == Token::SYMTYPE_LT
		|| parse->curToken()->getSymType() == Token::SYMTYPE_LT_EQUAL))
	{
		exp = exp + parse->curToken()->getTokenName();
		parse->nextToken();
		return true;
	}

	return false;
}

bool Grammar::identifier(string& exp, char type)
{
	/**
	*<identifier>      :=  <identifier1>
	*/
	// std::cout<<"identifier"<<" "<<parse->curToken()->getTokenName().c_str()<<std::endl;
	return (parse->SaveTokenIT() && identifier1(exp, type));
}

bool Grammar::identifier1(string& exp, char type)
{
	// std::cout<<"identifier1"<<" "<<parse->curToken()->getTokenName().c_str()<<std::endl;

	if(parse->curToken()
		&& parse->curToken()->getID() == Token::IDTYPE_IDENTIFIER)
	{
		//if(type == 'A')
		//{
		//	if(m.find(parse->curToken()->getTokenName()) == m.end())
			//{
				// string x = to_string(count1);
				// count1++;
				// m[parse->curToken()->getTokenName()] = "_" + x;
				exp = parse->curToken()->getTokenName();
		//	}
		//}
		//else
		//{
			//cout<<"id = "<< parse->curToken()->getTokenName()<<endl;
		//	exp = exp + m[parse->curToken()->getTokenName()];
		//}
		//exp = exp + m[parse->curToken()->getTokenName()];
		parse->nextToken();
		return true;
	}
	return false;
}

bool Grammar::number(string& exp)
{
	/**
	<number>      :=  <number1>
	*/
	// std::cout<<"number"<<" "<<parse->curToken()->getTokenName().c_str()<<std::endl;
	return (parse->SaveTokenIT() && number1(exp));
}

bool Grammar::number1(string& exp)
{
	/**
	*<number1>      :=  number
	*/
	// std::cout << "number1" << std::endl;
	if(parse->curToken()
		&& parse->curToken()->getID() == Token::IDTYPE_NUMBER)
	{
		
		if(n1 == "$")
		{
			n1 = parse->curToken()->getTokenName();
		}
		else if(n2 == "$")
		{
			n2 = parse->curToken()->getTokenName();
		}
		exp = exp + parse->curToken()->getTokenName();
		parse->nextToken();
		return true;
	}

	return false;
}

void Grammar::instanciateParser(Parser* newParser)
{

	parse = newParser;
}
