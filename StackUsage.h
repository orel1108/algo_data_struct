#pragma once

#include <string>
#include <vector>

#include "Stack.hpp"

/**
 * @brief Checks wether given character is operand.
 * @param[in] i_ch Character to be checked.
 */
bool isOperand(char i_ch);

/**
 * @brief Find precedence of operator.
 * @param[in] i_op Operator.
 * @return Precedence of input operator.
 */
int precedence(char i_op);

/**
 * @brief Converts expression from infix to postfix.
 * @param[in] i_infix Expression in infix form.
 * @return Expression in postfix form.
 */
std::string infixToPostfix(const std::string & i_infix);

/**
 * @brief Evaluates expression written in postfix form.
 * @param[in] i_postfix Expression written in postfix form.
 * @return Value of given expression.
 */
int evalPostfix(const std::string & i_postfix);

/**
 * @brief Reverses string.
 * @param[in] i_str String to be reversed.
 * @return Reversed string.
 */
std::string reverseString(const std::string & i_str);

/**
 * @brief Checks wether pair is matching. Matching pairs: '{' and '}', '[' and ']' or '(' and ')'.
 * @param[in] i_left Left character.
 * @param[in] i_right Right character.
 * @return True if pair is matching and False otherwise.
 */
bool isMatchingPair(char i_left, char i_right);

/**
 * @brief Checks wether parantesis in expression are balanced.
 * @param[in] i_expr Input expression.
 * @return True if parantesis in expression are balanced and False otherwise.
 */
bool balancedParantesis(const std::string & i_expr);

/**
 * @brief Find next greater element for each element in array.
 * @param[in] i_buf Input array.
 * @return Buffer with Next Greater elements.
 */
std::vector<int> findNextGreater(const std::vector<int> & i_buf);

/**
 * @brief Insert element at a bottom of stack.
 * @param[in,out] io_stack Stack with items.
 * @param[in] i_data Data to be inserted at a bottom of a stack.
 */
void insertAtBottom(Stack<int> & io_stack, int i_data);

/**
 * @brief Reverses stack.
 * @param[in,out] io_stack Stack to be reversed.
 */
void reverse(Stack<int> & io_stack);

/**
 * @brief Insert item in sorted stack.
 * @param[in,out] io_stack Stack where to add new item.
 * @param[in] i_data Item to be inserted.
 */
void sortedInsert(Stack<int> & io_stack, int i_data);

/**
 * @brief Sorts stack using recursion.
 * @param[in,out] io_stack Stack to be sorted.
 */
void sortStack(Stack<int> & io_stack);

/**
 * @brief Calculates the stock span.
 * @param[in] i_price Stock prices.
 * @return Stock spans.
 */
std::vector<int> stockSpanProblem(const std::vector<int> & i_price);
