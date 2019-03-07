
//====================================================================================================
// Constant Buffers
//====================================================================================================

Texture2D viewTexture : register(t0);
SamplerState textureSampler : register(s0);

//====================================================================================================
// Structs
//====================================================================================================
struct VS_INPUT
{
	float4 position : POSITION;
	float3 normal	: NORMAL;
	float3 tangent	: TANGENT;
	float2 texCoord : TEXCOORD;
};

struct VS_OUTPUT
{
	float4 position : SV_POSITION;
    float2 texCoord : TEXCOORD;
};

//====================================================================================================
// Vertex Shader
//====================================================================================================

VS_OUTPUT VS(VS_INPUT input)
{
    VS_OUTPUT output = (VS_OUTPUT)0;

    output.texCoord = input.texCoord;
	output.position = input.position;

    return output;
}

//====================================================================================================
// Pixel Shader
//====================================================================================================

float4 PS(VS_OUTPUT input) : SV_Target
{
    float4 ColorBloom = viewTexture.Sample(textureSampler, input.texCoord);

    float Threshold = 0.3f;

    return saturate((ColorBloom - Threshold) / 1 - Threshold);

}

