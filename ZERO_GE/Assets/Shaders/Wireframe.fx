
//====================================================================================================
// Constant Buffers
//====================================================================================================

cbuffer TransformBuffer : register(b0)
{
    matrix world;
}

cbuffer CameraBuffer : register(b1)
{
    matrix cameraview[2];
    matrix cameraprojection[2];
    vector cameraposition[2];
}


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
    float4 position :	            SV_POSITION;
};

//====================================================================================================
// Vertex Shader
//====================================================================================================

VS_OUTPUT VS(VS_INPUT input)
{
    VS_OUTPUT output = (VS_OUTPUT)0;

	float4 position = input.position * 3.0f;

    float4 posWorld = mul(position, world);
    float4x4 wv = mul(world, cameraview[0]);
    float4x4 wvp = mul(wv, cameraprojection[0]);
    float4 posProj = mul(position, wvp);



    output.position = posProj;

    return output;
}

//====================================================================================================
// Pixel Shader
//====================================================================================================

float4 PS(VS_OUTPUT input) : SV_Target
{
    //Sum of the light contribution for each light source
    float4 A = { 0.0f, 1.0f, 0.0f, 1.0f };

	return A;
}

