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
    float cameraNear[2];
    float cameraFar[2];
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

cbuffer BoneConstantBuffer : register(b5)
{
    matrix boneTransforms[64];
}

static matrix Identity =
{
    1, 0, 0, 0,
	0, 1, 0, 0,
	0, 0, 1, 0,
	0, 0, 0, 1
};

Texture2D depthMap : register(t0);
Texture2D diffuseMap : register(t1);
Texture2D specularMap : register(t2);
Texture2D displacementMap : register(t3);
Texture2D normalMap : register(t4);

SamplerState textureSampler : register(s0);
SamplerState depthSampler : register(s1);

//====================================================================================================
// Structs
//====================================================================================================

struct VS_INPUT
{
	float4	position		: POSITION;
	float3	normal			: NORMAL;
	float3	tangent			: TANGENT;
	float2	texCoord		: TEXCOORD;
    int4	blendIndices	: BLENDINDICES;
    float4	blendWeight		: BLENDWEIGHT;
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
// Helpers
//====================================================================================================

matrix GetBoneTransform(int4 indices, float4 weights)
{
    if (length(weights) <= 0.0f)
        return Identity;

    matrix transform;
    transform =	 boneTransforms[indices[0]] * weights[0];
    transform += boneTransforms[indices[1]] * weights[1];
    transform += boneTransforms[indices[2]] * weights[2];
    transform += boneTransforms[indices[3]] * weights[3];
    return transform;
}

//====================================================================================================
// Vertex Shader
//====================================================================================================

VS_OUTPUT VS(VS_INPUT input)
{
	VS_OUTPUT output = (VS_OUTPUT)0;

    matrix boneTransform = GetBoneTransform(input.blendIndices, input.blendWeight);

    float4 positionBone;
    if (material.hasDisplacementMap == 1)
    {
        float displacement = displacementMap.SampleLevel(textureSampler, input.texCoord, 0).r;
        positionBone = input.position + (float4(input.normal, 0.0f) * 0.2f * displacement);
    }
	else
    {
        positionBone = input.position;
    }

        float4 positionLocal = mul(positionBone, boneTransform);
        float4 positionWorld = mul(positionLocal, world);
        float4x4 wv = mul(world, cameraview[0]);
        float4x4 wvp = mul(wv, cameraprojection[0]);
        float4 posProj = mul(positionLocal, wvp);
    
	
        float4x4 wvLight = mul(world, cameraview[1]);
        float4x4 wvpLight = mul(wvLight, cameraprojection[1]);

        float3 normalBone = input.normal;

        float3 normalLocal = mul(float4(normalBone, 0.0f), boneTransform);
        float3 tangent = mul(float4(input.tangent, 0.0f), world).xyz;
        float3 binormal = cross(normalLocal, tangent);
	
        float3 dirToLightDirectionalLight = -normalize(dLight.direction.xyz);
        float3 dirToView = normalize(cameraposition[0].xyz - positionWorld.xyz);

        output.position = posProj;
        output.normal = mul(float4(normalLocal, 0.0f), world).xyz;
        output.tangent = tangent;
        output.binormal = binormal;
        output.dirToLight = dirToLightDirectionalLight;
        output.dirToView = dirToView;
        output.texCoord = input.texCoord;
        output.depthCoord = mul(input.position, wvpLight);
	
        return output;
    }

//====================================================================================================
// Pixel Shader
//====================================================================================================

float4 PS(VS_OUTPUT input) : SV_Target
{
	// Sample normal from normal map
    float3 t;
	float3 b;
	float3 n;
    float3x3 tbn;
    float3 normal;

    if (material.hasNormalMap == 1)
    {
		// Sample normal from normal map
        float4 normalColor = normalMap.Sample(textureSampler, input.texCoord);
        float3 sampledNormal = float3((2.0f * normalColor.xy) - 1.0f, normalColor.z);

		// Transform to world space
        t = normalize(input.tangent);
        b = normalize(input.binormal);
        n = normalize(input.normal);
        tbn = float3x3(t, b, n);
        normal = mul(sampledNormal, tbn);
    }
    else
    {
		// Transform to world space
        t = normalize(input.tangent);
        b = normalize(input.binormal);
        n = normalize(input.normal);
        tbn = float3x3(t, b, n);
        normal = n;
    }
	

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

    if (material.hasSpecularMap == 1)
    {
        specular *= specularMap.Sample(textureSampler, input.texCoord).rrrr;
    }
	

	
	
    if (input.depthCoord.w <= 0.0f)
    {
        if (material.hasDiffuseMap == 1)
        {
            float4 diffuseColor = diffuseMap.Sample(textureSampler, input.texCoord);
            return ambient * diffuseColor;
        }
        return ambient;
    }

	float3 depthCoord = input.depthCoord.xyz / input.depthCoord.w;

	if (abs(depthCoord.x) > 1.0f || abs(depthCoord.y) > 1.0f)
	{
        if (material.hasDiffuseMap == 1)
        {
            float4 diffuseColor = diffuseMap.Sample(textureSampler, input.texCoord);
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
        if (material.hasDiffuseMap == 1)
        {
            float4 diffuseColor = diffuseMap.Sample(textureSampler, input.texCoord);
            return ambient * diffuseColor;
        }
        return ambient;
    }

    if (material.hasDiffuseMap == 1)
    {
        float4 diffuseColor = diffuseMap.Sample(textureSampler, input.texCoord);
        return ((ambient + diffuse) * diffuseColor) + (specular);
    }
    return ambient + diffuse + specular;

}
