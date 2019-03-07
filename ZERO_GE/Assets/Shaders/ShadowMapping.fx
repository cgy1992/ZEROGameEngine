#include "LightHelper.fx"

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

cbuffer DirectionalLightBuffer : register(b2)
{
	DirectionalLight dLight;
}

cbuffer MaterialBuffer : register(b3)
{
	Material material;
}

cbuffer InputBuffer : register(b4)
{
    vector boolTexture;
}

Texture2D diffuseMap : register(t0);
Texture2D depthMap : register(t1);

SamplerState textureSampler : register(s0);
SamplerState depthSampler : register(s1);

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

//----------------------------------------------------------------------------------------------------

struct VS_OUTPUT
{
	float4 position		: SV_POSITION;
	float3 normal		: NORMAL;
	float3 tangent		: TANGENT;
	float3 binormal		: BINORMAL;
	float3 dirToLight	: TEXCOORD0;
	float3 dirToView	: TEXCOORD1;
	float2 texCoord		: TEXCOORD2;
	float4 depthCoord	: TEXCOORD3;
};

//====================================================================================================
// Vertex Shader
//====================================================================================================

VS_OUTPUT VS(VS_INPUT input)
{
	VS_OUTPUT output = (VS_OUTPUT)0;

    float4 position = input.position;

    float4 posWorld = mul(position, world);
    float4x4 wv = mul(world, cameraview[0]);
    float4x4 wvp = mul(wv, cameraprojection[0]);
    float4 posProj = mul(position, wvp);
	
    float4x4 wvLight = mul(world, cameraview[1]);
    float4x4 wvpLight = mul(wvLight, cameraprojection[1]);

	float3 normal = mul(float4(input.normal, 0.0f), world).xyz;
	float3 tangent = mul(float4(input.tangent, 0.0f), world).xyz;
	float3 binormal = cross(normal, tangent);
	
    float3 dirToLightDirectionalLight = -normalize(dLight.direction.xyz);
    float3 dirToView = normalize(cameraposition[0].xyz - posWorld.xyz);

	output.position = posProj;
	output.normal = normal;
	output.tangent = tangent;
	output.binormal = binormal;
    output.dirToLight = dirToLightDirectionalLight;
	output.dirToView = dirToView;
	output.texCoord = input.texCoord;
	output.depthCoord = mul(position, wvpLight);
	
	return output;
}

//====================================================================================================
// Pixel Shader
//====================================================================================================

float4 PS(VS_OUTPUT input) : SV_Target
{
	// Sample normal from normal map
	/*float4 normalColor = normalMap.Sample(textureSampler, input.texCoord);
	float3 sampledNormal = float3((2.0f * normalColor.xy) - 1.0f, normalColor.z);*/

	// Transform to world space
	float3 t = normalize(input.tangent);
	float3 b = normalize(input.binormal);
	float3 n = normalize(input.normal);
	float3x3 tbn = float3x3(t, b, n);
	float3 normal = n;

	float3 dirToLight = normalize(input.dirToLight);
	float3 dirToView = normalize(input.dirToView);
	
    float4 ambient = float4(0.0f, 0.0f, 0.0f, 0.0f);
    float4 diffuse = float4(0.0f, 0.0f, 0.0f, 0.0f);
    float4 specular = float4(0.0f, 0.0f, 0.0f, 0.0f);

    //Sum of the light contribution for each light source
    float4 A, D, S;

    ComputeDirectionalLight(material, dLight, normal, dirToLight, dirToView, A, D, S);
    ambient += A;
    diffuse += D;
    specular += S;

	float4 diffuseColor = diffuseMap.Sample(textureSampler, input.texCoord);
	
	if (input.depthCoord.w <= 0.0f)
	{
        if (boolTexture.x >= 1.0f)
        {
            return ambient * diffuseColor;
        }
        return ambient;
    }

	float3 depthCoord = input.depthCoord.xyz / input.depthCoord.w;

	if (abs(depthCoord.x) > 1.0f || abs(depthCoord.y) > 1.0f)
	{
        if (boolTexture.x >= 1.0f)
        {
            return ((ambient + diffuse) * diffuseColor) + (specular);
        }
		return ambient + diffuse + specular;
	}

	float pixelDepth = depthCoord.z;
	float2 depthUV = (depthCoord.xy + 1.0f) * 0.5f;
	depthUV.y = 1.0f - depthUV.y;
	float sampledDepth = depthMap.Sample(depthSampler, depthUV).r + 0.01f;

	if (pixelDepth > sampledDepth)
	{
        if (boolTexture.x >= 1.0f)
        {
            return ambient * diffuseColor;
        }
		return ambient;
	}

    if (boolTexture.x >= 1.0f)
    {
        return ((ambient + diffuse) * diffuseColor) + (specular);
    }
	return ambient + diffuse + specular;

}
