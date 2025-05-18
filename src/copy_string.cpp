#include <string>
#include <cstring>  // for strdup

#include "serial_port.h"

#ifdef _WIN32
#include <windows.h>
#endif

utf8Bytes copyString(const std::string& str) {
    if (str.empty()) {
        return strdup("");
    }

#ifdef _WIN32
    // Step 1: 多字节（ACP） -> UTF-16
    int wlen = MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, nullptr, 0);
    if (wlen == 0) return strdup(str.c_str());

    std::wstring wstr(wlen, L'\0');
    MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, &wstr[0], wlen);

    // Step 2: UTF-16 -> UTF-8
    int utf8len = WideCharToMultiByte(CP_UTF8, 0, wstr.c_str(), -1, nullptr, 0, nullptr, nullptr);
    if (utf8len == 0) return strdup(str.c_str());

    char* utf8str = (char*)malloc(utf8len);
    WideCharToMultiByte(CP_UTF8, 0, wstr.c_str(), -1, utf8str, utf8len, nullptr, nullptr);
    return utf8str;
#else
    // 假设 str 本身就是 UTF-8
    return strdup(str.c_str());
#endif
}
