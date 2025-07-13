using System;
using System.Collections.Generic;
using System.Globalization;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace SummerPractice
{
    public static class StringToFormula
    {
        private static readonly string[] operators = { "+", "-", "/", "%", "*", "^"};
        private static readonly string[] functions = {"sin", "cos", "tan", "cot"};
        private static readonly Func<double, double, double>[] operations = {
        (a1, a2) => a1 + a2,
        (a1, a2) => a1 - a2,
        (a1, a2) => a1 / a2,
        (a1, a2) => a1 % a2,
        (a1, a2) => a1 * a2,
        (a1, a2) => Math.Pow(a1, a2),
    };
        private static readonly Func<double, double>[] trigonometryOperations = {
        (a1) => Math.Sin(a1),
        (a1) => Math.Cos(a1),
        (a1) => Math.Tan(a1),
        (a1) => Math.Cos(a1) / Math.Sin(a1),
    };

        public static bool TryEval(string expression, out double value)
        {
            try
            {
                value = Eval(expression);
                return true;
            }
            catch
            {
                value = 0.0;
                return false;
            }
        }

        public static double Eval(string expression)
        {
            if (string.IsNullOrEmpty(expression))
                return 0.0;

            if (double.TryParse(expression, out double value))
                return value;

            List<string> tokens = GetTokens(expression);
            tokens.Add("$"); // Append end of expression token
            Stack<double> operandStack = new Stack<double>();
            Stack<string> operatorStack = new Stack<string>();
            int tokenIndex = 0;

            while (tokenIndex < tokens.Count - 1)
            {
                string token = tokens[tokenIndex];
                string nextToken = tokens[tokenIndex + 1];

                switch (token)
                {
                    case "(":
                        {
                            string subExpr = GetSubExpression(tokens, ref tokenIndex);
                            operandStack.Push(Eval(subExpr));
                            continue;
                        }
                    case ")":
                        throw new ArgumentException("Mis-matched parentheses in expression");

                    case "sin":
                    case "cos":
                    case "tan":
                    case "cot":
                        if (nextToken == "(")
                        {
                            int newIndex = tokenIndex + 1;
                            string subExpr = GetSubExpression(tokens, ref newIndex);
                            double computedValue = trigonometryOperations[Array.IndexOf(functions, token)](Eval(subExpr));
                            operandStack.Push(computedValue);
                            tokenIndex = newIndex;
                        }
                        else
                        {
                            string computableNumber = nextToken;
                            if (nextToken == "-")
                            {
                                computableNumber += tokens[tokenIndex + 2];
                                tokenIndex++;
                            }
                            double computedValue = trigonometryOperations[Array.IndexOf(functions, token)](double.Parse($"{computableNumber}", CultureInfo.InvariantCulture));
                            operandStack.Push(computedValue);
                            tokenIndex += 2;
                        }
                        continue;

                    // Handle unary ops
                    case "-":
                    case "+":
                        {
                            if (!IsOperator(nextToken) && operatorStack.Count == operandStack.Count)
                            {
                                operandStack.Push(double.Parse($"{token}{nextToken}", CultureInfo.InvariantCulture));
                                tokenIndex += 2;
                                continue;
                            }
                        }
                        break;
                }

                if (IsOperator(token))
                {
                    while (operatorStack.Count > 0 && OperatorPrecedence(token) <= OperatorPrecedence(operatorStack.Peek()))
                    {
                        if (!ResolveOperation())
                        {
                            throw new ArgumentException(BuildOpError());
                        }
                    }
                    operatorStack.Push(token);
                }
                else
                {
                    operandStack.Push(double.Parse(token, CultureInfo.InvariantCulture));
                }
                tokenIndex += 1;
            }

            while (operatorStack.Count > 0)
            {
                if (!ResolveOperation())
                    throw new ArgumentException(BuildOpError());
            }

            return operandStack.Pop();

            bool IsOperator(string token)
            {
                return Array.IndexOf(operators, token) >= 0;
            }
            int OperatorPrecedence(string op)
            {
                switch (op)
                {
                    case "^":
                        return 3;
                    case "*":
                    case "/":
                    case "%":
                        return 2;

                    case "+":
                    case "-":
                        return 1;
                    default:
                        return 0;
                }
            }

            string BuildOpError()
            {
                string op = operatorStack.Pop();
                string rhs = operandStack.Any() ? operandStack.Pop().ToString() : "null";
                string lhs = operandStack.Any() ? operandStack.Pop().ToString() : "null";
                return $"Operation not supported: {lhs} {op} {rhs}";
            }

            bool ResolveOperation()
            {
                string op = operatorStack.Pop();
                double rhs = operandStack.Pop();
                double lhs = operandStack.Pop();
                operandStack.Push(operations[Array.IndexOf(operators, op)](lhs, rhs));
                Console.WriteLine($"Resolve {lhs} {op} {rhs} = {operandStack.Peek()}");
                return true;
            }
        }

        private static string GetSubExpression(List<string> tokens, ref int index)
        {
            StringBuilder subExpr = new StringBuilder();
            int parenlevels = 1;
            index += 1;
            while (index < tokens.Count && parenlevels > 0)
            {
                string token = tokens[index];
                switch (token)
                {
                    case "(": parenlevels += 1; break;
                    case ")": parenlevels -= 1; break;
                }

                if (parenlevels > 0)
                    subExpr.Append(token);

                index += 1;
            }

            if (parenlevels > 0)
                throw new ArgumentException("Ошибка в расстановке скобок");

            return subExpr.ToString();
        }

        private static List<string> GetTokens(string expression)
        {
            string operators = "()^*/%+-";
            string digits = "0123456789.,";
            string[] funcs = { 
                "sin",
                "cos",
                "tan",
                "cot"
            };
            List<string> tokens = new List<string>();
            StringBuilder sb = new StringBuilder();
            expression = expression.Replace(" ", string.Empty);
            for(int i = 0; i < expression.Length; i++)
            {
                char c = expression[i];
                if (operators.IndexOf(c) >= 0)
                {
                    if ((sb.Length > 0))
                    {
                        tokens.Add(sb.ToString());
                        sb.Length = 0;
                    }
                    tokens.Add(c.ToString());
                }
                else if(digits.IndexOf(c) == -1 && i+2 < expression.Length)
                {
                    string func = expression.Substring(i, 3);
                    if(Array.IndexOf(funcs, func) >= 0) //got func
                    {
                        if ((sb.Length > 0))
                        {
                            tokens.Add(sb.ToString());
                            sb.Length = 0;
                        }
                        tokens.Add(func);
                    }
                }
                else if (digits.IndexOf(c) >= 0)
                {
                    sb.Append(c);
                }
                else
                {
                    throw new ArgumentException("Лишние символы в функции");
                }
            }

            if ((sb.Length > 0))
            {
                tokens.Add(sb.ToString());
            }
            return tokens;
        }
    }
}
