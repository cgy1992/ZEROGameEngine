
//====================================================================================================
// Constant Buffers
//====================================================================================================

cbuffer TransformBuffer : register(b0)
{
    matrix world;
}

cbuffer CameraBuffer : register(b1)
{
	matrix cameraView[2];
	matrix cameraProjection[2];
	vector cameraPosition[2];
}

Texture2D diffuseMap : register(t0);
SamplerState textureSampler : register(s0);

//====================================================================================================
// Structs
//====================================================================================================

struct VS_INPUT
{
	float4 position	: POSITION;
	float3 normal	: NORMAL;
	float3 tangent	: TANGENT;
	float2 texCoord	: TEXCOORD;
};

struct VS_OUTPUT
{
	float4 position	  : SV_POSITION;
	float2 texCoord	  : TEXCOORD;
};

//====================================================================================================
// Vertex Shader
//====================================================================================================

VS_OUTPUT VS(VS_INPUT input)
{
	VS_OUTPUT output = (VS_OUTPUT)0;

    float4 position = input.position;

    float4 posWorld = mul(position, world);
    float4x4 wv = mul(world, cameraView[0]);
    float4x4 wvp = mul(wv, cameraProjection[0]);
    float4 posProj = mul(position, wvp);

    output.texCoord = input.texCoord;
    output.position = posProj;

	return output;
}

//====================================================================================================
// Pixel Shader
//====================================================================================================

float4 PS(VS_OUTPUT input) : SV_Target
{
    return diffuseMap.Sample(textureSampler, input.texCoord);
}
