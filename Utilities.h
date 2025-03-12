#pragma once
#include <filesystem>
#include <string>
#include <cassert>

namespace fs = std::filesystem;

/// <summary>
/// ���f�[�^���w�肵�����l�ŃA���C�����g����
/// </summary>
/// <param name="size">			  �A���C������Ώ�			</param>
/// <param name="alignmentSize">�@�w��A���C�����g�T�C�Y	</param>
/// <returns>					�@�A���C�����g��̃T�C�Y	</returns>
inline size_t AlignBufferSize(size_t size, size_t alignmentSize)
{
	return size + alignmentSize - size % alignmentSize;
}

//�t�@�C���p�X����f�B���N�g���p�X�݂̂��擾
inline std::wstring GetDirPath(const std::wstring& path)
{
    fs::path p = path.c_str();
    return p.remove_filename().c_str();
}

//�t�@�C���̊g���q���擾
inline std::wstring GetFileExtension(const std::wstring& path)
{
    auto idx = path.rfind(L'.');
    return path.substr(idx + 1, path.length() - idx - 1);
}

//Wstring����String�^�ɕϊ�
inline std::string ConvertWString(const std::wstring& wstr)
{
    auto length = WideCharToMultiByte(CP_UTF8, 0U, wstr.data(), -1, nullptr, 0, nullptr, nullptr);

    //Length���z����m��
    auto buffer = new char[length];

    //�m�ۂ����z��ɕϊ���̓��e���R�s�[
    WideCharToMultiByte(CP_UTF8, 0U, wstr.data(), -1, buffer, length, nullptr, nullptr);

    std::string result(buffer);
    delete[] buffer;
    buffer = nullptr;

    return result;
}

//String����Wstring�ɕϊ�
inline std::wstring ConvertString(const std::string& str)
{
    auto num1 = MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED | MB_ERR_INVALID_CHARS, str.c_str(), -1, nullptr, 0);

    std::wstring wstr;
    wstr.resize(num1);

    //�ϊ���̏���wstr�ɃR�s�[
    auto num2 = MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED | MB_ERR_INVALID_CHARS, str.c_str(), -1, &wstr[0], num1);

    //�������`�F�b�N
    assert(num1 == num2);

    return wstr;
}
