#include "input/ConsoleInput.hpp"
#include <windows.h>

// std::string ConsoleInput::shiftJisToUtf8(const std::string& sjis) {
//     // 1) Shift-JIS -> WideChar
//     int wsize = MultiByteToWideChar(CP_ACP, 0, sjis.c_str(), -1, nullptr, 0);
//     std::wstring wbuf(wsize, L'\0');
//     MultiByteToWideChar(CP_ACP, 0, sjis.c_str(), -1, &wbuf[0], wsize);

//     // 2) WideChar -> UTF-8
//     int usize = WideCharToMultiByte(CP_UTF8, 0, wbuf.c_str(), -1, nullptr, 0, nullptr, nullptr);
//     std::string ubuf(usize, '\0');
//     WideCharToMultiByte(CP_UTF8, 0, wbuf.c_str(), -1, &ubuf[0], usize, nullptr, nullptr);
//     return ubuf;
// }
// std::optional<std::string> ConsoleInput::getStringInput() {
//     // ASCII + Shift-JIS想定
//     std::string raw;
//     if (!std::getline(std::cin, raw)) {
//         return std::nullopt;
//     }
//     if (raw.empty()) {
//         return std::nullopt;
//     }
//     // Convert from Shift-JIS to UTF-8
//     return shiftJisToUtf8(raw);
// }



// std::string ConsoleInput::shiftJisToUtf8(const std::string& sjisStr) {
//     // 1) Shift-JIS => ワイド文字
//     int wsize = MultiByteToWideChar(CP_ACP, 0, sjisStr.c_str(), -1, nullptr, 0);
//     std::wstring wbuf(wsize, L'\0');
//     MultiByteToWideChar(CP_ACP, 0, sjisStr.c_str(), -1, &wbuf[0], wsize);

//     // 2) ワイド文字 => UTF-8
//     int usize = WideCharToMultiByte(CP_UTF8, 0, wbuf.c_str(), -1, nullptr, 0, nullptr, nullptr);
//     std::string ubuf(usize, '\0');
//     WideCharToMultiByte(CP_UTF8, 0, wbuf.c_str(), -1, &ubuf[0], usize, nullptr, nullptr);
//     return ubuf;
// }

// // 読み込み例
// std::optional<std::string> ConsoleInput::getStringInput() {
//     std::string input;
//     if (!std::getline(std::cin, input)) {
//         return std::nullopt;
//     }
//     if (input.empty()) {
//         return std::nullopt;
//     }
//     // Shift-JIS → UTF-8 変換
//     return shiftJisToUtf8(input);
// }


//UTF8の場合
std::optional<std::string> ConsoleInput::getStringInput() {
    // コンソールコードページをUTF-8に変更
    SetConsoleOutputCP(CP_UTF8); 
    SetConsoleCP(CP_UTF8);

    // // ロケールを空文字("")にし、システムデフォルトロケールを使用
    // try {
    //     std::locale::global(std::locale(""));
    //     std::wcin.imbue(std::locale(""));
    //     std::wcout.imbue(std::locale(""));
    // } catch (const std::runtime_error& e) {
    //     std::cerr << "Failed to set locale: " << e.what() << std::endl;
    //     // ロケール設定がダメでも続行は可能（ただし文字化けの可能性）
    //     // return std::nullopt; // 必要に応じてエラー扱い
    // }

    // 改行を無視
    if (std::cin.peek() == '\n') {
        std::cin.ignore();
    }

    // ワイド文字で標準入力を受け取る
    std::wstring wstr;
    std::getline(std::wcin, wstr);

    if (wstr.empty()) {
        return std::nullopt;
    }

    // UTF-16 → UTF-8 に変換
    std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
    std::string utf8Str = converter.to_bytes(wstr);

    return utf8Str;
}
