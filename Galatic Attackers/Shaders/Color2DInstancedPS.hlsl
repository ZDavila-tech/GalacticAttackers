// an ultra simple hlsl pixel shader

struct ATTRIBUTES
{
    float3 Kd; // diffuse reflectivity
    float d; // dissolve (transparency) 
    float3 Ks; // specular reflectivity
    float Ns; // specular exponent
    float3 Ka; // ambient reflectivity
    float sharpness; // local reflection map sharpness
    float3 Tf; // transmission filter
    float Ni; // optical density (index of refraction)
    float3 Ke; // emissive reflectivity
    unsigned int illum; // illumination model
};

struct LIGHT_SETTINGS
{
    float red, green, blue, lightType,
			posX, posY, posZ, padding1,
			rotX, rotY, rotZ, rotW,
			radius, innerRatio, outerRatio, cutoff;
};



struct OutputToRasterizer
{
    float4 posH : SV_POSITION;
    float3 posW : WORLD;
    float3 normW : NORMAL;
};

cbuffer SceneData : register(b0)
{
    float4 sunDirection, sunColor, sunAmbient;
    float4 camerPos;
    float4x4 viewMatrix, projectionMatrix;
};

cbuffer MeshData : register(b1)
{
    float4x4 worldMatrix[500];
    ATTRIBUTES material[300];
};


cbuffer MODEL_IDS : register(b2)
{
    uint mod_id;
    uint mat_id;
    uint numLights;
    float padding;
    float4 color;
};

cbuffer LightData : register(b3)
{
    LIGHT_SETTINGS myLights[400];
};

//Texture2D colorTexture : register(t0);
//SamplerState filter : register(s0)
//{
//    Filter = MIN_MAG_MIP_LINEAR;
//    AddressU = Wrap;
//    AddressV = Wrap;
//};


float4 main(OutputToRasterizer output) : SV_TARGET
{
        
    float3 direct = float3(0.0f, 0.0f, 0.0f);
    float3 normSunDir = normalize(sunDirection.xyz);
    float3 surfaceNormal = normalize(output.normW);
    float lightRatio = saturate(dot(-normSunDir, surfaceNormal));
    direct = lightRatio * sunColor.xyz;

    for (int i = 0; i < numLights; ++i)
    {
        float3 position = float3(myLights[i].posX, myLights[i].posY, myLights[i].posZ);
        float3 color = float3(myLights[i].red, myLights[i].green, myLights[i].blue);
        float3 direction = normalize(float3(myLights[i].rotX, myLights[i].rotY, myLights[i].rotZ));
        switch (myLights[i].lightType)
        {
            case 0:
                float3 pointLightDir = normalize(position - output.posW.xyz);
                float pointLightRatio = saturate(dot(pointLightDir, surfaceNormal));
                float pointAttent = 1.0f - saturate(length(position - output.posW.xyz) / myLights[i].cutoff);
                pointAttent *= pointAttent;
                float3 result = saturate(pointLightRatio * color * pointAttent);
                direct += result;
                break;
            case 1:
                break;
            case 2:
                float3 spotLightDir = normalize(position - output.posW.xyz);
                float surfaceRatio = saturate(dot(-spotLightDir, direction));
                float spotAttent = 1.0f - saturate((myLights[i].innerRatio - surfaceRatio) / (myLights[i].innerRatio - myLights[i].outerRatio));
                spotAttent *= spotAttent;
                float spotFactor = (surfaceRatio > myLights[i].outerRatio) ? 1.0f : 0.0f;
                float spotLightRatio = saturate(dot(spotLightDir, surfaceNormal));
                direct += saturate(spotFactor * spotLightRatio * color * spotAttent);
                break;
            case 3:
                break;
        }

    }
    float3 indirect = sunAmbient.xyz * material[mat_id].Ka;

    float3 diffuse = material[mat_id].Kd * color.xyz;

    float3 emissive = material[mat_id].Ke;

    float3 viewDirection = normalize(camerPos.xyz - output.posW.xyz);
    float3 halfVector = normalize(-normSunDir + viewDirection);
    float intensity = pow(max(saturate(dot(normalize(output.normW), halfVector)), 0), material[mat_id].Ns + 0.00001f);
    float3 reflected = material[mat_id].Ks * intensity * 1.0f;

    float3 result = saturate(direct + indirect) * diffuse + reflected + emissive;
    return float4(/*(colorTexture.Sample(filter, material[mat_id].Ks) **/ result/*)*/, material[mat_id].d);

}


