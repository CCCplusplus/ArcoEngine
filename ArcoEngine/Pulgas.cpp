#include "Pulgas.h"

Pulgas::Pulgas()
    : mPulga{ nullptr }, mPulgapatas{ nullptr }, mPulgaojos{ nullptr }
{

}

Pulgas::~Pulgas()
{
    if (mPulga) delete mPulga;
    if (mPulgapatas) delete mPulgapatas;
    if (mPulgaojos) delete mPulgaojos;
}

void Pulgas::Initialize(ID3D11Device* device, ID3D11DeviceContext* context, DXCamera* camera, const std::wstring& textname, const std::string& modelname)
{
    mPulga = new CCuboT(device, context);
    mPulgapatas = new CCuboT(device, context);
    mPulgaojos = new CCuboT(device, context);

    mPulga->Initialize(camera, textname);
    mPulgapatas->Initialize(camera, textname);
    mPulgaojos->Initialize(camera, textname);

    mPulga->InsertModel(modelname);
    mPulgapatas->InsertModel(modelname);
    mPulgaojos->InsertModel(modelname);
}

void Pulgas::update(float elapsedTime)
{

}

void Pulgas::setPosition(float x, float y, float z)
{
    mPosX = x;
    mPosY = y;
    mPosZ = z;
}

float Pulgas::getXPosition() const
{
    return mPosX;
}

float Pulgas::getYPosition() const
{
    return mPosY;
}

float Pulgas::getZPosition() const
{
    return mPosZ;
}

void Pulgas::drawModel(float x, float y, float z, float angX, float angY, float change)
{
    if (alive) 
    {
        mPulga->drawModel(x, y, z, angX, angY, change);
        mPulgapatas->drawModel(x, y, z, angX, angY, change);
        mPulgaojos->drawModel(x, y, z, angX, angY, change);
    }
}