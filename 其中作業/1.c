#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

// Token的種類
typedef enum {
    T_NUMBER,   // 數字
    T_PLUS,     // '+'
    T_MINUS,    // '-'
    T_TIMES,    // '*'
    T_DIVIDE,   // '/'
    T_LPAREN,   // '('
    T_RPAREN,   // ')'
    T_EOF       // End of File
} TokenKind;

// Token的結構
typedef struct {
    TokenKind kind; // Token的種類
    int value;      // Token的值（只有kind為T_NUMBER時有效）
} Token;

// 全局變數，用來存儲當前token
Token current_token;

// 函數原型
void next_token();
int expression();
int term();
int factor();

// 函數：解析下一個token
void next_token() {
    int c = getchar();

    if (c == EOF) {
        current_token.kind = T_EOF;
    } else if (c == '+') {
        current_token.kind = T_PLUS;
    } else if (c == '-') {
        current_token.kind = T_MINUS;
    } else if (c == '*') {
        current_token.kind = T_TIMES;
    } else if (c == '/') {
        current_token.kind = T_DIVIDE;
    } else if (c == '(') {
        current_token.kind = T_LPAREN;
    } else if (c == ')') {
        current_token.kind = T_RPAREN;
    } else if (isdigit(c)) {
        current_token.kind = T_NUMBER;
        ungetc(c, stdin); // 把數字放回stdin
        scanf("%d", &current_token.value);
    } else {
        // 非法字符或其他情況
        // 這裡可以擴展錯誤處理的邏輯
        current_token.kind = T_EOF;
    }
}

// 函數：解析表達式
int expression() {
    int result = term();

    while (current_token.kind == T_PLUS || current_token.kind == T_MINUS) {
        if (current_token.kind == T_PLUS) {
            next_token();
            result += term();
        } else if (current_token.kind == T_MINUS) {
            next_token();
            result -= term();
        }
    }

    return result;
}

// 函數：解析項
int term() {
    int result = factor();

    while (current_token.kind == T_TIMES || current_token.kind == T_DIVIDE) {
        if (current_token.kind == T_TIMES) {
            next_token();
            result *= factor();
        } else if (current_token.kind == T_DIVIDE) {
            next_token();
            int divisor = factor();
            if (divisor != 0) {
                result /= divisor;
            } else {
                // 處理除以零的錯誤
                // 這裡可以擴展錯誤處理的邏輯
                printf("Error: Division by zero.\n");
                exit(1);
            }
        }
    }

    return result;
}

// 函數：解析因子
int factor() {
    int result;

    if (current_token.kind == T_NUMBER) {
        result = current_token.value;
        next_token();
    } else if (current_token.kind == T_LPAREN) {
        next_token();
        result = expression();
        if (current_token.kind == T_RPAREN) {
            next_token();
        } else {
            // 缺少右括號
            // 這裡可以擴展錯誤處理的邏輯
            printf("Error: Missing closing parenthesis.\n");
            exit(1);
        }
    } else {
        // 非法因子
        // 這裡可以擴展錯誤處理的邏輯
        printf("Error: Invalid expression.\n");
        exit(1);
    }

    return result;
}

// 主函數
int main() {
    printf("Enter an expression: ");

    // 初始化第一個token
    next_token();

    // 計算並輸出結果
    int result = expression();
    printf("Result: %d\n", result);

    return 0;
}
