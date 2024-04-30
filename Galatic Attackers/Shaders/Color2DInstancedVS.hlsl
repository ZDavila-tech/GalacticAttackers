#pragma pack_matrix(row_major)
// an ultra simple hlsl vertex shader


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

struct VERTEX_IN
{
    float3 pos : POSITION;
    float3 uvm : UV;
    float3 nrm : NORMAL;
};

//cbuffer SPRITE_DATA : register(b4)
//{
//    float2 pos_offset;
//    float2 scale;
//    float rotation;
//    float depth;
//};


OutputToRasterizer main(VERTEX_IN vert, uint id : SV_InstanceID)
{
   /* float2 r = float2(cos(rotation), sin(rotation));
    float2x2 rotate = float2x2(r.x, -r.y, r.y, r.x);
    float2 pos = pos_offset + mul(rotate, vert.pos * scale);*/
    float4 inputVertex = float4(vert.pos,/*, depth,*/ 1.0f);
    inputVertex = mul(inputVertex, worldMatrix[mod_id + id]);

    OutputToRasterizer output;

    output.posW = inputVertex.xyz;

    output.normW = float3(vert.nrm.x, vert.nrm.y, vert.nrm.z);
    output.normW = mul(float4(output.normW, 0.0f), worldMatrix[mod_id + id]).xyz;

    inputVertex = mul(inputVertex, viewMatrix);
    inputVertex = mul(inputVertex, projectionMatrix);
    output.posH = inputVertex;
    return output;
}