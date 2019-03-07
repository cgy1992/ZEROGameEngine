//====================================================================================================
// Filename:	DephMap.fx
// Created by:	Erick Tavares
// Description: Shader for deph map
//====================================================================================================
#include "LightHelper.fx"

//====================================================================================================
// Constant Buffer
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

struct VS_OUTPUT
{
    float4 position : SV_POSITION;
};

struct VS_DEBUG_INPUT
{
	float4 position : POSITION;
	float2 texCoord : TEXCOORD;
};

struct VS_DEBUG_OUTPUT
{
	float4 position : SV_POSITION;
	float2 texCoord : TEXCOORD;
};

matrix GetBoneTransform(int4 indices, float4 weights)
{
    if (length(weights) <= 0.0f)
        return Identity;

    matrix transform;
    transform = boneTransforms[indices[0]] * weights[0];
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
    VS_OUTPUT output = (VS_OUTPUT) 0;
	
    matrix boneTransform = GetBoneTransform(input.blendIndices, input.blendWeight);

    float4 positionBone = input.position;
    
    float4 positionLocal = mul(positionBone, boneTransform);
    float4 positionWorld = mul(positionLocal, world);
    float4x4 wv = mul(world, cameraview[1]);
    float4x4 wvp = mul(wv, cameraprojection[1]);
    float4 posProj = mul(positionLocal, wvp);

    output.position = posProj;
    return output;
}


VS_DEBUG_OUTPUT VSDEBUG(VS_DEBUG_INPUT input)
{
	VS_DEBUG_OUTPUT output = (VS_DEBUG_OUTPUT)0;
	output.position = input.position;
	output.texCoord = input.texCoord;
	return output;
}

float4 PSDEBUG(VS_DEBUG_OUTPUT input) : SV_Target
{
	float depth = depthMap.Sample(textureSampler, input.texCoord).r;
	float near = cameraNear[1];
	float far = cameraFar[1];
	float linearDepth = (2.0f * near) / (far + near - depth *(far - near));
	return linearDepth;
}