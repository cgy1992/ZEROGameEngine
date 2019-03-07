
//====================================================================================================
// Constant Buffers
//====================================================================================================
cbuffer TweekBloom : register(b0)
{
    vector BiOiBsOs;
}

Texture2D OriginalTexture       : register(t0);
Texture2D BloomTexture          : register(t1);

SamplerState OriginalSampler    : register(s0);
SamplerState BloomSampler       : register(s1);

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
    float4 bioibsos : ADDITIONALVALUES;
};


float4 AdjustSaturation(float4 color, float saturation)
{
    float grey = dot(color.rbg, float3(0.3, 0.59, 0.11));
    return lerp(grey, color, saturation);
}


//====================================================================================================
// Vertex Shader
//====================================================================================================

VS_OUTPUT VS(VS_INPUT input)
{
    VS_OUTPUT output = (VS_OUTPUT)0;

    output.texCoord = input.texCoord;
	output.position = input.position;
    output.bioibsos = BiOiBsOs;

    return output;
}

//====================================================================================================
// Pixel Shader
//====================================================================================================

float4 PS(VS_OUTPUT input) : SV_Target
{
    // Controls the Intensity of the bloom texture
    float BloomIntensity = BiOiBsOs.x;

    // Controls the Intensity of the original scene texture
    float OriginalIntensity = BiOiBsOs.y;

    // Saturation amount on bloom
    float BloomSaturation = BiOiBsOs.z;

    // Saturation amount on original scene
    float OriginalSaturation = BiOiBsOs.w;

    float4 BloomColor = BloomTexture.Sample(BloomSampler, input.texCoord);
    float4 OriginalColor = OriginalTexture.Sample(OriginalSampler, input.texCoord);

    // Adjust color saturation and intensity based on the input variables to the shader

    BloomColor = AdjustSaturation(BloomColor, BloomSaturation) * BloomIntensity;

    OriginalColor = AdjustSaturation(OriginalColor, OriginalSaturation) * OriginalIntensity;

    // make the originalColor darker in very bright areas, avoiding these areas look burned-out

    OriginalColor *= 1 - saturate(BloomColor);

    // Combine the two images.

    return OriginalColor + BloomColor;

}

