#pragma once

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
