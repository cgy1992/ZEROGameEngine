
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
    matrix cameraview;
    matrix cameraprojection;
    vector cameraposition;
}

cbuffer DirectionalLightBuffer : register(b2)
{
    DirectionalLight dLight;
}

cbuffer PointLightBufffer : register(b5)
{
    PointLight pLight;
}

cbuffer SpotLightBufffer : register(b6)
{
    SpotLight sLight;
}

cbuffer MaterialBuffer : register(b3)
{
    Material material;
}

cbuffer DisplacementFactorBuffer : register(b4)
{
   float displacementFactor;
}

Texture2D diffuseMap : register(t0);
Texture2D specularMap : register(t1);
Texture2D displacementMap : register(t2);
Texture2D normalMap : register(t3);
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
    float4 position :	            SV_POSITION;
    float3 normal :		            NORMAL;
	float3 tangent:					TANGENT;
	float3 binormal:				BINORMAL;
    float3 dirToDirectionalLight :  TEXCOORD0;
    float3 dirToPointLight :        DIRTOPOINTLIGHT;
    float3 dirToSpotLight :         DIRTOSPOTLIGHT;
	float  distanceToPointLight :	TEXCOORD1;
	float  distanceToSpotLight :	TEXCOORD2;
    float3 dirToView :	            TEXCOORD3;
    float2 texCoord :	            TEXCOORD4;
	
};

//====================================================================================================
// Vertex Shader
//====================================================================================================

VS_OUTPUT VS(VS_INPUT input)
{
    VS_OUTPUT output = (VS_OUTPUT)0;

	float displacement = displacementMap.SampleLevel(textureSampler, input.texCoord, 0).r;
	float4 position = input.position + (float4(input.normal, 0.0f) * 0.2f * displacement );

    float4 posWorld = mul(position, world);
    float4x4 wv = mul(world, cameraview);
    float4x4 wvp = mul(wv, cameraprojection);
    float4 posProj = mul(position, wvp);

	float3 normal = mul(float4(input.normal, 0.0f), world).xyz;
	float3 tangent = mul(float4(input.tangent, 0.0f), world).xyz;
	float3 binormal = cross(normal, tangent);

    float3 dirToLightDirectionalLight = -normalize(dLight.direction.xyz);
    float3 dirToPointLight = -normalize(position - float4(pLight.position.xyz, 0.0f));
    float3 dirToSpotLight = -normalize(sLight.direction.xyz);
    float3 dirToView = normalize(cameraposition.xyz - posWorld.xyz);

	float distanceToPLight = length(float4(pLight.position.xyz, 0.0f) - position);
	float distanceToSLight = length(float4(sLight.position.xyz, 0.0f) - position);

    output.position = posProj;
    output.normal = normal;
	output.tangent = tangent;
	output.binormal = binormal;
    output.dirToDirectionalLight = dirToLightDirectionalLight;
    output.dirToPointLight = dirToPointLight;
    output.dirToSpotLight = dirToSpotLight;
	output.distanceToPointLight = distanceToPLight;
	output.distanceToSpotLight = distanceToSLight;
    output.dirToView = dirToView;
    output.texCoord = input.texCoord;

    return output;
}

//====================================================================================================
// Pixel Shader
//====================================================================================================

float4 PS(VS_OUTPUT input) : SV_Target
{

	// Sample normal from normal map
	float4 normalColor = normalMap.Sample(textureSampler, input.texCoord);
	float3 sampledNormal = float3((2.0f * normalColor.xy) - 1.0f, normalColor.z);

	// Transform to world space
	float3 t = normalize(input.tangent);
	float3 b = normalize(input.binormal);
	float3 n = normalize(input.normal);
	float3x3 tbn = float3x3(t, b, n);
	float3 normal = mul(sampledNormal, tbn);

    float3 dirToDirectionalLight = normalize(input.dirToDirectionalLight);
    float3 dirToPointLight = normalize(input.dirToPointLight);
    float3 dirToSpotLight = normalize(input.dirToSpotLight);
    float3 dirToView = normalize(input.dirToView);


    float4 ambient =    float4(0.0f, 0.0f, 0.0f, 0.0f);
    float4 diffuse =    float4(0.0f, 0.0f, 0.0f, 0.0f);
    float4 specular =   float4(0.0f, 0.0f, 0.0f, 0.0f);

    //Sum of the light contribution for each light source
    float4 A, D, S;

    ComputeDirectionalLight(material, dLight, normal, dirToDirectionalLight, dirToView, A, D, S);
    ambient += A;
    diffuse += D;
    specular += S;

    ComputePointLight(material, pLight, normal, dirToPointLight, dirToView, input.distanceToPointLight, A, D, S);
    ambient += A;
    diffuse += D;
    specular += S;

    ComputeSpotLight(material, sLight, normal, dirToSpotLight, dirToView, input.distanceToSpotLight, A, D, S);
    ambient += A;
    diffuse += D;
    specular += S;


    specular *= specularMap.Sample(textureSampler, input.texCoord).rrrr;
	
    float4 diffuseColor = diffuseMap.Sample(textureSampler, input.texCoord);

	return (((ambient + diffuse) * diffuseColor) + specular);
}

