struct Material
{
    vector materialAmbient;
    vector materialDiffuse;
    vector materialSpecular;
    vector materialEmissive;
    float  materialPower;
    int hasDiffuseMap;
    int hasSpecularMap;
    int hasNormalMap;
    int hasDisplacementMap;
};
