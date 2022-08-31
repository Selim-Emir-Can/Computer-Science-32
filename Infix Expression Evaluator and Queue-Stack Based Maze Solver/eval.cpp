#include <iostream>
#include <string>
#include <stack>
#include<cstddef>
#include<cstdlib>
#include <cassert>
#include<cctype>
using namespace std;

////////////////////////////////////////////////////////////// #INCLUDE /////////////////////////////////////////////////////////////////////
bool isValid(string& infix);

int precedence(char character);

void infixToPostfix(string infix, string& postfix);
/*
Initialize postfix to empty
Initialize the operator stack to empty
For each character ch in the infix string
Switch(ch)
		  case operand:
			  append ch to end of postfix
				  break
		  case '(':
			  push ch onto the operator stack
				  break
		  case ')':
			  // pop stack until matching '('
			  While stack top is not '('
				  append the stack top to postfix
				  pop the stack
				  pop the stack  // remove the '('
				  break
		  case operator:
			  While the stack is not empty and the stack top is not '('
				  and precedence of ch <= precedence of stack top
				  append the stack top to postfix
				  pop the stack
				  push ch onto the stack
				  break
				  While the stack is not empty
				  append the stack top to postfix
				  pop the stack
*/

int evaluate(string infix, string& postfix, bool& result);
// Evaluates a boolean expression
//   If infix is a syntactically valid infix boolean expression,
//   then set postfix to the postfix form of that expression, set
//   result to the value of the expression, and return zero.  If
//   infix is not a syntactically valid expression, return 1; in
//   that case, postfix may or may not be changed, but result must
//   be unchanged.
/*
Initialize the operand stack to empty
	For each character ch in the postfix string
		if ch is an operand
			push the value that ch represents onto the operand stack
		else // ch is a binary operator
			set operand2 to the top of the operand stack
		pop the stack
			set operand1 to the top of the operand stack
		pop the stack
		apply the operation that ch represents to operand1 and
				operand2, and push the result onto the stack
	When the loop is finished, the operand stack will contain one item,
	  the result of evaluating the expression
*/

////////////////////////////////////////////////////////////// DECLARATIONS /////////////////////////////////////////////////////////////////////
int evaluate(string infix, string& postfix, bool& result)
{
	if (!isValid(infix))
	{
		return(1);
	}

	infixToPostfix(infix, postfix);
	stack<char> Op;
	char ch = ' ';

	for (size_t i = 0; i < postfix.size(); i++)
	{
		ch = postfix.at(i);
		if ((ch == 'T') || (ch == 'F'))
		{
			Op.push(ch);
		}
		else if (ch == '!')
		{
			char op1 = Op.top();
			Op.pop();

			if (op1 == 'T')
			{
				Op.push('F');
			}
			else if (op1 == 'F')
			{
				Op.push('T');
			}
			else
			{
				exit(1);
			}
		}
		else // ch is a binary operator
		{
			char op2 = Op.top();
			Op.pop();
			char op1 = Op.top();
			Op.pop();

			if (ch == '|')
			{
				if ((op2 == 'T') || (op1 == 'T'))
				{
					Op.push('T');
				}
				else
				{
					Op.push('F');
				}
			}
			else if (ch == '&')
			{
				if ((op2 == 'T') && (op1 == 'T'))
				{
					Op.push('T');
				}
				else
				{
					Op.push('F');
				}
			}
			else
			{
				exit(1);
			}
		}
	}

	char top = Op.top();
	if (top == 'T')
	{
		result = true;
	}
	else if (top == 'F')
	{
		result = false;
	}

	return(0);
}

////////////////////////////////////////////////////////////// int evaluate(string infix, string& postfix, bool& result); /////////////////////////////////////////////////////////////////////

bool isValid(string& infix)
{
	int binary_operator_count = 0, open_p_count = 0, close_p_count = 0, operand_count = 0;
	string infixed = "", infixer = "";
	bool correct_binary = true, correct_unary = true, correct_p = true;
	for (size_t i = 0;(i < infix.size()); i++)
	{
		if (infix.at(i) != ' ')
		{
			infixer = infixer + infix.at(i);
		}
	}

	infix = infixer;

	for (size_t i = 0; correct_unary && correct_p && correct_binary && (i < infix.size()); i++)
	{
		if ((infix.at(i) == 'T') || (infix.at(i) == 'F'))
		{
			if ((i >= 1) && ((infix.at(i - 1) == ')') || (infix.at(i - 1) == 'T') || (infix.at(i - 1) == 'F'))) // can't have FF, )F , TF // can have !F, &F , |F, (F
			{
				correct_p = false;
				correct_binary = false;
			}
			
			if ((i != (infix.size() - 1)) && ((infix.at(i + 1) == '!') || (infix.at(i + 1) == '(') || (infix.at(i + 1) == 'F') || (infix.at(i + 1) == 'T'))) // can't have F!, F( , FF, FT // can have F& , F|, F)
			{
				correct_p = false;
				correct_binary = false;
			}
			operand_count++;
			infixed = infixed + infix.at(i);
		}
		else if ((infix.at(i) == '|') || (infix.at(i) == '&'))
		{
			if ((i == 0) || i == (infix.size() - 1))
			{
				correct_binary = false;
			}
			
			if ((i >= 1) && (i < (infix.size() - 1)))
			{
				if (((infix.at(i - 1) != 'T') && (infix.at(i - 1) != 'F') && (infix.at(i - 1) != ')')) || ((infix.at(i + 1) != '(') && (infix.at(i + 1) != 'T') && (infix.at(i + 1) != 'F') && (infix.at(i + 1) != '!')))
				{
					correct_binary = false;
				}
			}
			binary_operator_count++;
			infixed = infixed + infix.at(i);
			
		}
		else if (infix.at(i) == '!')
		{
			if (i == (infix.size() - 1))
			{
				correct_unary = false;
			}
			
			if ((i >= 1) && ((infix.at(i - 1) == ')') || (infix.at(i - 1) == 'T') || (infix.at(i - 1) == 'F'))) // can't have )! , T!, F! // can have !!, (! , |!, &!
			{
				correct_unary = false;
			}
			
			if ((i < (infix.size() - 1)) && ((infix.at(i + 1) == ')') || (infix.at(i + 1) == '|') && (infix.at(i + 1) == '&'))) // can't have !) , !|, !& // can have !!, !T , !F, !(
			{
				correct_unary = false;
			}

			infixed = infixed + infix.at(i);
		}
		else if (infix.at(i) == '(')
		{
			open_p_count++;
			infixed = infixed + infix.at(i);

			if (i == (infix.size() - 1))
			{
				correct_p = false;
			}
			
			if ((i >= 1) && ((infix.at(i - 1) == ')') || (infix.at(i - 1) == 'T') || (infix.at(i - 1) == 'F')))	 // can't have )(, T(, F( //can have !(, ((, &(, |(
			{
				correct_p = false;
			}
			
			if ((i < (infix.size() - 1)) && ((infix.at(i + 1) == ')') || (infix.at(i + 1) == '|') || (infix.at(i + 1) == '&')))	// can't have (|, (&, () // can have (F, (T, (!, ((
			{
				correct_p = false;
			}
		}
		else if (infix.at(i) == ')')
		{
			if (i == 0)
			{
				correct_p = false;
			}
			
			if ((i >= 1) && ((infix.at(i - 1) == '(') || (infix.at(i - 1) == '!') || (infix.at(i - 1) == '|') || (infix.at(i - 1) == '&'))) // can't have (), !), |), &) //can have )), T), F)
			{
				correct_p = false;
			}
			
			if((i < (infix.size() - 1)) && ((infix.at(i + 1) == '(') || (infix.at(i + 1) == 'T') || (infix.at(i + 1) == 'F') || (infix.at(i + 1) == '!'))) // can't have )(, )!, )T, )F //can have )), )|, )&
			{
				correct_p = false;
			}

			close_p_count++;
			infixed = infixed + infix.at(i);
			
		}
	}
	bool p_diff_zero = (close_p_count == open_p_count);
	bool bin_op_diff_zero = ((operand_count == (1 + binary_operator_count)));
	bool expression_valid = ((operand_count == 1) && (binary_operator_count == 0));

	if (correct_p && correct_unary && correct_binary && p_diff_zero && (expression_valid || bin_op_diff_zero))
	{
		infix = infixed;
		return(true);
	}
	else
	{
		return(false);
	}
}

int precedence(char character)
{
	if (character == '!')
	{
		return(3);
	}
	else if (character == '&')
	{
		return(2);
	}
	else if (character == '|')
	{
		return(1);
	}
	else if((character == 'T') || (character == 'F'))
	{
		return(0);
	}

	exit(1);
	return(-1);
}

void infixToPostfix(string infix, string& postfix)
{
	postfix = "";
	char ch = ' ';
	stack<char> Op; // empty string stack
	for (size_t i = 0; i < infix.size(); i++)
	{
		ch = infix.at(i);
		switch (ch)
		{
		case('T'):
		case('F'):
			postfix = postfix + ch;
			break;
		case('('):
			Op.push(ch);
			break;
		case(')'):
			while (Op.top() != '(')
			{
				postfix = postfix + Op.top();
				Op.pop();
			}
			Op.pop();
			break;
		case('|'):
		case('&'):
			while ((Op.size() != 0) && (Op.top() != '(') && (precedence(ch) <= precedence(Op.top())))
			{
				postfix = postfix + Op.top();
				Op.pop();
			}
			Op.push(ch);
			break;
		case('!'):
			while ((Op.size() != 0) && (Op.top() != '(') && (precedence(ch) < precedence(Op.top())))
			{
				if (precedence(ch) == precedence(Op.top()))	// case of repeating !
				{
					Op.pop();
					break;
				}
				postfix = postfix + Op.top();
				Op.pop();
			}
			Op.push(ch);
			break;
		default:
			exit(1);
			break;
		}
	}

	while (Op.size() != 0)
	{
		postfix = postfix + Op.top();
		Op.pop();
	}
}

////////////////////////////////////////////////////////////// DEFINITIONS /////////////////////////////////////////////////////////////////////


int main()
{
	string pf;
	bool answer;
	evaluate("T| F", pf, answer);
	assert(evaluate("T| F", pf, answer) == 0 && pf == "TF|" && answer);
	infixToPostfix("(((!!T)&T)&(T&F&T)&F|T)|F", pf);
	assert(evaluate("(((!!T)&T)&(T&F&T)&F|T)|F", pf, answer) == 0 && answer);

	assert(evaluate("T|F||F", pf, answer) == 1);
	assert(evaluate("T| F", pf, answer) == 0 && pf == "TF|" && answer);
	assert(evaluate("T|", pf, answer) == 1);
	assert(evaluate("F F", pf, answer) == 1);
	assert(evaluate("TF", pf, answer) == 1);
	assert(evaluate("()", pf, answer) == 1);
	assert(evaluate("()T", pf, answer) == 1);
	assert(evaluate("T(F|T)", pf, answer) == 1);
	assert(evaluate("T(&T)", pf, answer) == 1);
	assert(evaluate("(T&(F|F)", pf, answer) == 1);
	assert(evaluate("T+F", pf, answer) == 1);
	assert(evaluate("", pf, answer) == 1);
	assert(evaluate("F  |  !F & (T&F) ", pf, answer) == 0
		&& pf == "FF!TF&&|" && !answer);
	assert(evaluate(" F  ", pf, answer) == 0 && pf == "F" && !answer);
	assert(evaluate("((T))", pf, answer) == 0 && pf == "T" && answer);
	cout << "Passed all tests" << endl;




	cout << "Passed all tests" << endl;
	return(0);
}