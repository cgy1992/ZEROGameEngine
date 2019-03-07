struct DirectionalLight
{
    vector ambient;
    vector diffuse;
    vector specular;
    float3 direction;
    float pad;

};


struct PointLight
{
    vector ambient;
    vector diffuse;
    vector specular;

    float3 position;
    float range;

    float3 att;
    float pad;

};

struct SpotLight
{
    vector ambient;
    vector diffuse;
    vector specular;

    float3 position;
    float range;

    float3 direction;
    float spot;

    float3 att;
    float pad;

};