#ifndef COMMONUTILS_HPP
#define COMMONUTILS_HPP

#ifdef _WIN32
#include <windows.h>
#endif

class CommonUtils
{
public:
    static CommonUtils &getInstance()
    {
        static CommonUtils instance;
        return instance;
    }

    void clearScreen()
    {
#ifdef _WIN32
        std::system("cls"); // Windows の場合
#else
        std::system("clear"); // Mac / Linux の場合
#endif
    }

    void setConsole()
    {
#ifdef _WIN32
        // Windows のコンソール文字コードをUTF-8に設定
        SetConsoleCP(CP_UTF8);  //input
        SetConsoleOutputCP(65001);  //output
        setvbuf(stdout, nullptr, _IOFBF, 1024);
        // SetConsoleOutputCP(932);
#endif
    }

private:
    CommonUtils() {}
    // シングルトン：コピー・代入を禁止
    CommonUtils(const CommonUtils &) = delete;
    CommonUtils &operator=(const CommonUtils &) = delete;
};
#endif // COMMONUTILS_HPP