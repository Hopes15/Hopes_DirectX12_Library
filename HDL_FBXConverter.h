#pragma once
#include <fbxsdk.h>
#include <vector>
#include <map>
#include <string>

/// <summary>
/// FBXファイルをコンバートするクラス
/// </summary>
class HDL_FBXConverter
{
public:
	/// <summary>
	/// FBXをTextファイルに変換する
	/// </summary>
	/// <param name="fbxFile">	FBXファイル		</param>
	/// <param name="textFile">	textファイル	</param>
	/// <param name="fx">		x軸のスケール	</param>
	/// <param name="fy">		y軸のスケール	</param>
	/// <param name="fz">		z軸のスケール	</param>
	void ConvertFBX(
		const char* fbxFile,
		const char* textFile,
		float fx = 1,
		float fy = 1,
		float fz = 1,
		int idx0 = 0,
		int idx1 = 1,
		int idx2 = 2
	);

private:
	void LoadMaterial(FbxSurfaceMaterial* material);

	struct Material
	{
		std::vector<float> materials;
		std::string	       textureFile;
	};

	std::map<std::string, Material> mMaterialMap;

	int mIdx0, mIdx1, mIdx2;
	void LoadPosition(FbxMesh* mesh, int k);
	void LoadNormals(FbxMesh* mesh, int k);
	void LoadTexcoords(FbxMesh* mesh, int k);
	void LoadIndices(FbxMesh* mesh, int k);
	void LoadMaterialName(FbxMesh* mesh, int k);

	int NumParts;
	struct Parts
	{
		std::vector<float>		positions;
		std::vector<float>		normals;
		std::vector<float>		texcoords;
		std::vector<uint16_t>	indices;
		std::string				materialName;
	}*m_pParts;

	void CreateTextCombineVertex(const char* textFile, float fx, float fy, float fz);
};

