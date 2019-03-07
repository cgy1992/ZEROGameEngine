#include "LightTypes.fx"
#include "Material.fx"

void ComputeDirectionalLight(Material material, DirectionalLight L, float3 normal, float3 dirToLight, float3 dirToView
                                , out vector ambient
                                , out vector diffuse
                                , out vector specular)
{
    // Initialize outputs.
    ambient = float4(0.0f, 0.0f, 0.0f, 0.0f);
    diffuse = float4(0.0f, 0.0f, 0.0f, 0.0f);
    specular = float4(0.0f, 0.0f, 0.0f, 0.0f);

    // The light vector aims opposite the direction the light rays travel.

    // Add ambient term.
    ambient = L.ambient * material.materialAmbient;

    // Add diffuse and specular term, provided the surface is in
    // the line of site of the light.
    // Diffuse
    float d = saturate(dot(dirToLight, normal));
    diffuse = d * L.diffuse * material.materialDiffuse;

    // Flatten to avoid dynamic branching.
    [flatten]
    if (d > 0.0f)
    {
        float3 h = normalize(dirToLight + dirToView);
        float s = saturate(dot(h, normal));
        specular = pow(s, material.materialPower) * L.specular * material.materialSpecular;
    }

}

void ComputePointLight(Material material, PointLight L, float3 normal, float3 dirToLight, float3 dirToView, float r
                                , out vector ambient
                                , out vector diffuse
                                , out vector specular)
{
    // Initialize outputs.
    ambient = float4(0.0f, 0.0f, 0.0f, 0.0f);
    diffuse = float4(0.0f, 0.0f, 0.0f, 0.0f);
    specular = float4(0.0f, 0.0f, 0.0f, 0.0f);

    //Range Test
    if (r > L.range)
    {
        return;
    }
    // Add ambient term.
    ambient = L.ambient * material.materialAmbient;

    // Add diffuse and specular term, provided the surface is in
    // the line of site of the light.
    // Diffuse
    float d = saturate(dot(dirToLight, normal));
    diffuse = d * L.diffuse * material.materialDiffuse;

    // Flatten to avoid dynamic branching.
    [flatten]
    if (d > 0.0f)
    {
        float3 h = normalize(dirToLight + dirToView);
        float s = saturate(dot(h, normal));
        specular = pow(s, material.materialPower) * L.specular * material.materialSpecular;
    }

    //Attenuate
    float att = 1.0f / dot(L.att, float3(1.0f, r, r * r));
    diffuse *= att;
    specular *= att;

}

void ComputeSpotLight(Material material, SpotLight L, float3 normal, float3 dirToLight, float3 dirToView, float r
                                , out vector ambient
                                , out vector diffuse
                                , out vector specular)
{
    // Initialize outputs.
    ambient = float4(0.0f, 0.0f, 0.0f, 0.0f);
    diffuse = float4(0.0f, 0.0f, 0.0f, 0.0f);
    specular = float4(0.0f, 0.0f, 0.0f, 0.0f);


    //Range Test
    if (r > L.range)
    {
        return;
    }
    // Add ambient term.
    ambient = L.ambient * material.materialAmbient;

    // Add diffuse and specular term, provided the surface is in
    // the line of site of the light.
    // Diffuse
    float d = saturate(dot(dirToLight, normal));
    diffuse = d * L.diffuse * material.materialDiffuse;

    // Flatten to avoid dynamic branching.
    [flatten]
    if (d > 0.0f)
    {
        float3 h = normalize(dirToLight + dirToView);
        float s = saturate(dot(h, normal));
        specular = pow(s, material.materialPower) * L.specular * material.materialSpecular;
    }

    //Scale by SpotLight factor and attenuate
    float spot = pow(max(dot(-dirToLight, L.direction), 0.0f), L.spot);

    float att = spot / dot(L.att, float3(1.0f, r, r * r));

    ambient *= spot;
    diffuse *= att;
    specular *= att;

}