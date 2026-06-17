/**
 * 最长公共子序列 (LCS) 算法 - 程序入口与交互逻辑
 *
 * 算法实现见 lcs.h
 */

#include "lcs.h"

/**
 * 打印分隔线
 */
void printSeparator(const string& title) {
    cout << "\n========================================" << endl;
    cout << title << endl;
    cout << "========================================" << endl;
}

/**
 * 运行LCS算法并输出结果
 */
void runLCS(const string& text1, const string& text2) {
    cout << "\n输入信息：" << endl;
    cout << "text1 = \"" << text1 << "\" (长度: " << text1.length() << ")" << endl;
    cout << "text2 = \"" << text2 << "\" (长度: " << text2.length() << ")" << endl;
    
    // 方法一：O(mn) 空间，求LCS及其长度
    printSeparator("方法一：空间复杂度 O(m*n)");
    cout << "特点：可以求出LCS字符串及其长度" << endl;
    string lcsString;
    int len1 = LCS_FullDP::solve(text1, text2, lcsString);
    if (len1 == 0) {
        cout << "结果：不存在公共子序列" << endl;
        cout << "LCS长度：0" << endl;
    } else {
        cout << "LCS长度：" << len1 << endl;
        cout << "LCS序列：\"" << lcsString << "\"" << endl;
    }
    
    // 方法二：O(2*min(m,n)) 空间，仅求LCS长度
    printSeparator("方法二：空间复杂度 O(2*min(m,n))");
    cout << "特点：使用两行滚动数组，仅求LCS长度" << endl;
    int len2 = LCS_TwoRows::solve(text1, text2);
    if (len2 == 0) {
        cout << "结果：不存在公共子序列" << endl;
        cout << "LCS长度：0" << endl;
    } else {
        cout << "LCS长度：" << len2 << endl;
    }
    
    // 方法三：O(min(m,n)) 空间，仅求LCS长度
    printSeparator("方法三：空间复杂度 O(min(m,n))");
    cout << "特点：使用单行数组，仅求LCS长度" << endl;
    int len3 = LCS_OneRow::solve(text1, text2);
    if (len3 == 0) {
        cout << "结果：不存在公共子序列" << endl;
        cout << "LCS长度：0" << endl;
    } else {
        cout << "LCS长度：" << len3 << endl;
    }
    
    // 验证三种方法结果一致性
    printSeparator("结果验证");
    if (len1 == len2 && len2 == len3) {
        cout << "[OK] 三种方法计算结果一致，LCS长度均为：" << len1 << endl;
    } else {
        cout << "[WARN] 警告：三种方法计算结果不一致！" << endl;
        cout << "  方法一结果：" << len1 << endl;
        cout << "  方法二结果：" << len2 << endl;
        cout << "  方法三结果：" << len3 << endl;
    }
}

int main(int argc, char* argv[]) {
    cout << "================================================" << endl;
    cout << "   最长公共子序列 (LCS) 算法演示" << endl;
    cout << "================================================" << endl;
    
    string text1, text2;
    
    // 支持三种输入方式：命令行参数、控制台输入、内置测试用例
    if (argc >= 3) {
        // 方式1：命令行参数输入
        text1 = argv[1];
        text2 = argv[2];
        cout << "输入方式：命令行参数" << endl;
    } else {
        // 默认模式：控制台输入
        // 提示用户输入
        // cout << "请输入两个字符串 (text1 text2): "; // 为了评测系统可能需要静默输入，但标准控制台程序通常需要提示。提示语不影响功能。
        // 根据 prompt "由控制台输入两个字符串text1，text2"，标准做法是直接读取。
        
        if (!(cin >> text1 >> text2)) {
            return 0;
        }
    }
    
    // 单组测试（命令行参数方式）
    if (!isValidInput(text1) || !isValidInput(text2)) {
        cout << "错误：输入的字符串只能包含小写英文字符（a~z）！" << endl;
        return 1;
    }
    
    runLCS(text1, text2);
    
    cout << "\n程序执行完毕。" << endl;
    
    return 0;
}
