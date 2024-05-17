#pragma once
#include <vector>
#include <memory>
#include "ModelBase.h"
#include "../../render/materials/VertexFormat.h"

class DXCamera;
class MaterialTexture;

class CModelRTT : public CModelBase<BasicTexVertex>
{
public:
	~CModelRTT(void);

	void Initialize(DXCamera *camera);

	virtual void drawModel();
	//virtual phyVector3D getColor() { return mColor; }
	//virtual void setColor(phyVector3D color) { mbColorNeedsUpdate = true; mColor = color; }

protected:
	CModelRTT(ID3D11Device *device, ID3D11DeviceContext *context);
	void setRenderProperties();

protected:
	MaterialTexture *mMaterialTexture;

	DXCamera *mCamera;
	//phyVector3D mColor;
	//bool mbColorNeedsUpdate;
};
