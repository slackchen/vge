#pragma once

namespace Vge
{
	enum VertexElementType
	{
		VET_None,
		VET_Float1,
		VET_Float2,
		VET_Float3,
		VET_Float4,
		VET_PackedNormal,
		VET_UByte4,
		VET_UByte4N,
		VET_Color,
		VET_Short2
	};

	enum VertexElementUsage
	{
		VEU_Position,
		VEU_TextureCoordinate,
		VEU_BlendWeight,
		VEU_BlendIndices,
		VEU_Normal,
		VEU_Tangent,
		VEU_Binormal,
		VEU_Color
	};

	struct VertexElement
	{
		word mStream;
		word mOffset;
		byte mType;
		byte mMethod;
		byte mUsage;
		byte mUsageIndex;

		VertexElement();

		VertexElement( word stream, word offset, byte type, byte method, byte usageindex )
			: mStream( stream ), mOffset( offset ), mType( type ), mMethod( method ), mUsageIndex( usageindex )
		{
		}
	};

	typedef Array<VertexElement> VertexElementList;

	class VGE_API VertexDeclaration
	{
	public:
		VertexDeclaration( const VertexElementList& elementlist );
	};
}