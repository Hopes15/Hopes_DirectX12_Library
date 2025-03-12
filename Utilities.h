#pragma once
#include <filesystem>
#include <string>
#include <cassert>

namespace fs = std::filesystem;

/// <summary>
/// 元データを指定した数値でアライメントする
/// </summary>
/// <param name="size">			  アラインする対象			</param>
/// <param name="alignmentSize">　指定アライメントサイズ	</param>
/// <returns>					　アライメント後のサイズ	</returns>
inline size_t AlignBufferSize(size_t size, size_t alignmentSize)
{
	return size + alignmentSize - size % alignmentSize;
}

//ファイルパスからディレクトリパスのみを取得
inline std::wstring GetDirPath(const std::wstring& path)
{
    fs::path p = path.c_str();
    return p.remove_filename().c_str();
}

//ファイルの拡張子を取得
inline std::wstring GetFileExtension(const std::wstring& path)
{
    auto idx = path.rfind(L'.');
    return path.substr(idx + 1, path.length() - idx - 1);
}

//WstringからString型に変換
inline std::string ConvertWString(const std::wstring& wstr)
{
    auto length = WideCharToMultiByte(CP_UTF8, 0U, wstr.data(), -1, nullptr, 0, nullptr, nullptr);

    //Length分配列を確保
    auto buffer = new char[length];

    //確保した配列に変換後の内容をコピー
    WideCharToMultiByte(CP_UTF8, 0U, wstr.data(), -1, buffer, length, nullptr, nullptr);

    std::string result(buffer);
    delete[] buffer;
    buffer = nullptr;

    return result;
}

//StringからWstringに変換
inline std::wstring ConvertString(const std::string& str)
{
    auto num1 = MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED | MB_ERR_INVALID_CHARS, str.c_str(), -1, nullptr, 0);

    std::wstring wstr;
    wstr.resize(num1);

    //変換後の情報をwstrにコピー
    auto num2 = MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED | MB_ERR_INVALID_CHARS, str.c_str(), -1, &wstr[0], num1);

    //整合性チェック
    assert(num1 == num2);

    return wstr;
}
