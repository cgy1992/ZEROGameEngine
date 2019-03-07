
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
    
    float BlurDistance = 0.002f;

    float4 Color;
 
    // Get the texel from ColorMapSampler using a modified texture coordinate. This
    // gets the texels at the neighbour texels and adds it to Color.
    Color = viewTexture.Sample(textureSampler, float2(input.texCoord.x + BlurDistance, input.texCoord.y + BlurDistance));
    Color += viewTexture.Sample(textureSampler, float2(input.texCoord.x - BlurDistance, input.texCoord.y - BlurDistance));
    Color += viewTexture.Sample(textureSampler, float2(input.texCoord.x + BlurDistance, input.texCoord.y - BlurDistance));
    Color += viewTexture.Sample(textureSampler, float2(input.texCoord.x - BlurDistance, input.texCoord.y + BlurDistance));
    // We need to devide the color with the amount of times we added
    // a color to it, in this case 4, to get the avg. color
    Color = Color / 4.0f;
 
// returned the blurred color
    return Color;

}

