#pragma once

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
