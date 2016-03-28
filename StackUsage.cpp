#include <string>
#include <cctype>

#include "Stack.hpp"
#include "StackUsage.h"

/**
* @brief Checks wether given character is operand.
* @param[in] i_ch Character to be checked.
*/
bool isOperand(char i_ch)
{
    return (i_ch >= 'a' && i_ch <= 'z') || (i_ch >= 'A' && i_ch <= 'Z');
}

/**
* @brief Find precedence of operator.
* @param[in] i_op Operator.
* @return Precedence of input operator.
*/
int precedence(char i_op)
{
    switch (i_op)
    {
    case '+':
    case '-':
        return 1;

    case '*':
    case '/':
        return 2;

    case '^':
        return 3;
    }

    return -1;
}

/**
* @brief Converts expression from infix to postfix.
* @param[in] i_infix Expression in infix form.
* @return Expression in postfix form.
*/
std::string infixToPostfix(const std::string & i_infix)
{
    // resulting expression
    std::string postfix;

    // auxiliary data structure
    Stack<char> stack;

    for (std::size_t pos = 0; pos < i_infix.size(); pos++)
    {
        // if character is operand add it to resulting string
        if (isOperand(i_infix[pos]))
        {
            postfix += i_infix[pos];
        }
        else if (i_infix[pos] == '(')
        {
            stack.push(i_infix[pos]);
        }
        else if (i_infix[pos] == ')')
        {
            // go to '('
            while (!stack.empty() && stack.top() != '(')
            {
                postfix += stack.top();
                stack.pop();
            }
            if (!stack.empty() && stack.top() != '(')
            {
                return std::string("Invalid expression!");
            }
            // remove '('
            else
            {
                stack.pop();
            }
        }
        // operator was found
        else
        {
            while (!stack.empty() && precedence(i_infix[pos]) <= precedence(stack.top()))
            {
                postfix += stack.top();
                stack.pop();
            }
            stack.push(i_infix[pos]);
        }
    }

    // pop all operators from stack
    while (!stack.empty())
    {
        postfix += stack.top();
        stack.pop();
    }

    return postfix;
}

/**
* @brief Evaluates expression written in postfix form.
* @param[in] i_postfix Expression written in postfix form.
* @return Value of given expression.
*/
int evalPostfix(const std::string & i_postfix)
{
    Stack<int> stack;

    for (std::size_t pos = 0; pos < i_postfix.size(); pos++)
    {
        // if digit is meet push it onto stack
        if (isdigit(i_postfix[pos]))
        {
            stack.push(static_cast<int>(i_postfix[pos] - '0'));
        }
        // pop two top operands, evaluate and push result onto stack 
        else
        {
            // extract right operand
            int right = stack.top();
            stack.pop();
            
            // extract right operand
            int left = stack.top();
            stack.pop();

            // push result of left op right
            switch (i_postfix[pos])
            {
            case '+': stack.push(left + right); break;
            case '-': stack.push(left - right); break;
            case '*': stack.push(left * right); break;
            case '/': stack.push(left / right); break;
            }
        }
    }

    return stack.top();
}

/**
* @brief Reverses string.
* @param[in] i_str String to be reversed.
* @return Reversed string.
*/
std::string reverseString(const std::string & i_str)
{
    // resulting string
    std::string res;

    // auxiliary data structure
    Stack<char> stack;
    // push string data onto stack
    for (std::size_t pos = 0; pos < i_str.size(); pos++)
    {
        stack.push(i_str[pos]);
    }

    // get characters in reversed order
    for (std::size_t pos = 0; pos < i_str.size(); pos++)
    {
        res += stack.top();
        stack.pop();
    }

    return res;
}

/**
* @brief Checks wether pair is matching. Matching pairs: '{' and '}', '[' and ']' or '(' and ')'.
* @param[in] i_left Left character.
* @param[in] i_right Right character.
* @return True if pair is matching and False otherwise.
*/
bool isMatchingPair(char i_left, char i_right)
{
    return (i_left == '(' && i_right == ')') || (i_left == '[' && i_right == ']') || (i_left == '{' && i_right == '}');
}

/**
* @brief Checks wether parantesis in expression are balanced.
* @param[in] i_expr Input expression.
* @return True if parantesis in expression are balanced and False otherwise.
*/
bool balancedParantesis(const std::string & i_expr)
{
    // auxiliary data structure
    Stack<char> stack;

    // traverse expression
    for (std::size_t pos = 0; pos < i_expr.size(); pos++)
    {
        // found opening parantesis
        if (i_expr[pos] == '(' || i_expr[pos] == '[' || i_expr[pos] == '{')
        {
            stack.push(i_expr[pos]);
        }
        else if (i_expr[pos] == ')' || i_expr[pos] == ']' || i_expr[pos] == '}')
        {
            // wrong expression
            if (stack.empty())
            {
                return false;
            }
            
            const char left = stack.top();

            // check if pair is matching
            if (isMatchingPair(left, i_expr[pos]))
            {
                stack.pop();
            }
            // otherwise parantesis not balanced
            else
            {
                return false;
            }
        }
    }

    // parantesis in expression are balanced
    if (stack.empty())
    {
        return true;
    }

    return false;
}

/**
* @brief Find next greater element for each element in array.
* @param[in] i_buf Input array.
* @return Buffer with Next Greater elements.
*/
std::vector<int> findNextGreater(const std::vector<int> & i_buf)
{
    // resulting buffer
    std::vector<int> res(i_buf.size());

    // auxiliary data structure (pair is (value, position))
    Stack<std::pair<int, int>> stack;

    // push first element
    stack.push(std::make_pair(i_buf[0], 0));
    // traverse buffer
    for (std::size_t pos = 1; pos < i_buf.size(); pos++)
    {
        // next greater
        int curr_ng = i_buf[pos];
        
        // check if stack is not empty
        if (!stack.empty())
        {
            // extract top element from stack
            std::pair<int, int> curr = stack.top();
            stack.pop();

            // pop elements while less then current next greater
            while (curr.first < curr_ng)
            {
                // add next greater for current element
                res[curr.second] = curr_ng;

                // check wether stack is empty
                if (stack.empty())
                {
                    break;
                }

                // extract new element
                curr = stack.top();
                stack.pop();
            }

            // push back element greater then current next greater
            if (curr.first > curr_ng)
            {
                stack.push(curr);
            }
        }

        // push current element
        stack.push(std::make_pair(curr_ng, pos));
    }

    // for remaning element next greater will be -1
    while (!stack.empty())
    {
        std::pair<int, int> elem = stack.top();
        res[elem.second] = -1;
        stack.pop();
    }

    return res;
}

/**
* @brief Insert element at a bottom of stack.
* @param[in,out] io_stack Stack with items.
* @param[in] i_data Data to be inserted at a bottom of a stack.
*/
void insertAtBottom(Stack<int> & io_stack, int i_data)
{
    // if stack is empty simply push item
    if (io_stack.empty())
    {
        io_stack.push(i_data);
    }
    else
    {
        // extract top element
        int item = io_stack.top();
        io_stack.pop();

        // recursively call, store all items from stack in stack frame
        insertAtBottom(io_stack, i_data);

        // push back extracted item
        io_stack.push(item);
    }
}

/**
* @brief Reverses stack.
* @param[in,out] io_stack Stack to be reversed.
*/
void reverse(Stack<int> & io_stack)
{
    // check wether stack is not empty
    if (!io_stack.empty())
    {
        // extract top element
        int item = io_stack.top();
        io_stack.pop();

        // recursively call reverse
        reverse(io_stack);

        // insert items at the bottom of stack (from stack frame)
        insertAtBottom(io_stack, item);
    }
}

/**
* @brief Insert item in sorted stack.
* @param[in,out] io_stack Stack where to add new item.
* @param[in] i_data Item to be inserted.
*/
void sortedInsert(Stack<int> & io_stack, int i_data)
{
    // if stack is empty or values smaller then input value simply push new value
    if (io_stack.empty() || i_data > io_stack.top())
    {
        io_stack.push(i_data);
    }
    else
    {
        // extract topmost item, store in stack frame
        int temp = io_stack.top();
        io_stack.pop();

        // recursively call insert
        sortedInsert(io_stack, i_data);

        // push back extracted values from stack frame
        io_stack.push(temp);
    }
}

/**
* @brief Sorts stack using recursion.
* @param[in,out] io_stack Stack to be sorted.
*/
void sortStack(Stack<int> & io_stack)
{
    // check if stack is not empty
    if (!io_stack.empty())
    {
        // extract topmost item, store in stack frame
        int temp = io_stack.top();
        io_stack.pop();

        // recursively call sort
        sortStack(io_stack);

        // push item in sorted order
        sortedInsert(io_stack, temp);
    }
}

/**
* @brief Calculates the stock span.
* @param[in] i_price Stock prices.
* @return Stock spans.
*/
std::vector<int> stockSpanProblem(const std::vector<int> & i_price)
{
    // resulting spans
    std::vector<int> span;

    // auxiliary data structure (contains days)
    Stack<int> stack;

    // span for first stock is always 1
    span.push_back(1);
    // push first day
    stack.push(0);

    // traverse stock prices
    for (std::size_t pos = 1; pos < i_price.size(); pos++)
    {
        // extract days where stock prices were less or equal to current price
        while (!stack.empty() && i_price[stack.top()] <= i_price[pos])
        {
            stack.pop();
        }

        // new span: if stack is empty then current price is greater or equal then all previous
        int s = stack.empty() ? (pos + 1) : (pos - stack.top());
        span.push_back(s);

        // push current day
        stack.push(pos);
    }

    return span;
}
