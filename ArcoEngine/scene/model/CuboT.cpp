#include <d3d11.h>
#include <cmath>
#include "CuboT.h"
#include "../../render/materials/MaterialTexture.h"

void CCuboT::InsertModel(const std::string &modelname)
{
	if (mpDevice == nullptr)
		return;
	sObjMesh mesh = loadModelToVertices(modelname, 0);
	//const float i3r = 0.57735027f;
	vertexVectorType vertices;

	for (const PosNorTexVertex& vrt : mesh.mVertices)
	{
		BasicTexVertex vertx;

		vertx.pos[0] = vrt.pos[0];
		vertx.pos[1] = vrt.pos[1];
		vertx.pos[2] = vrt.pos[2];

		vertx.normal[0] = vrt.normal[0];
		vertx.normal[1] = vrt.normal[1];
		vertx.normal[2] = vrt.normal[2];

		vertx.tex[0] = vrt.texcoords[0];
		vertx.tex[1] = vrt.texcoords[1];

		vertices.push_back(vertx);		
		//vertices.push_back(vrt);
	}
	//{
	//	{ {  0.5f,  0.5f, -0.5f }, { i3r, i3r, -i3r }, {0.334f, 0.f} },
	//	{ { -0.5f,  0.5f, -0.5f }, { -i3r, i3r, -i3r },{ 0.f, 0.f } },
	//	{ { -0.5f, -0.5f, -0.5f }, { -i3r, -i3r, -i3r },{ 0.f, 1.f } },
	//	{ {  0.5f, -0.5f, -0.5f }, { i3r, -i3r, -i3r },{ 0.334f, 1.f } },
	//		  
	//	{ {  0.5f,  0.5f,  0.5f }, { i3r, i3r, i3r },{ 0.667f, 0.f } },
	//	{ { -0.5f,  0.5f,  0.5f }, { -i3r, i3r, i3r },{ 1.f, 0.f } },
	//	{ { -0.5f, -0.5f,  0.5f }, { -i3r, -i3r, i3r },{ 1.f, 1.f } },
	//	{ {  0.5f, -0.5f,  0.5f }, { i3r, -i3r, i3r },{ 0.667f, 1.f } },
	//
	//};
	mAllModelsVertices.insert(mAllModelsVertices.end(), vertices.begin(), vertices.end());

	std::vector<unsigned short> indices;

	for (size_t i = 0; i < mesh.mIndices.size(); i++)
	{
		indices.push_back((unsigned short)i);
	}
	//{
	//	0, 3, 1,  3, 2, 1,  0, 4, 7,  0, 7, 3,
	//	4, 5, 6,  4, 6, 7,  5, 1, 2,  5, 2, 6,
	//	5, 4, 0,  5, 0, 1,  2, 3, 7,  2, 7, 6
	//};
	mAllModelsIndices.insert(mAllModelsIndices.end(), indices.begin(), indices.end());

	setBuffers();
}

void CCuboT::drawModel(float lx, float ly, float lz, float rotationAngleX, float rotationAngleY, float enbigens)
{
	setShaders();
	setRenderProperties();
	activateBuffers();
	ID3D11Buffer* conbuf = mMaterialTexture->GetVConstantBuffer0();

	// Crear y aplicar la matriz de transformación con rotación en X y Y
	MathUtil::CMatrix scalation = MathUtil::MatrixScale(enbigens, enbigens, enbigens);
	MathUtil::CMatrix translation = MathUtil::MatrixTranslation(lx, ly, lz);
	MathUtil::CMatrix rotationX = MathUtil::MatrixRotationX(rotationAngleX);
	MathUtil::CMatrix rotationY = MathUtil::MatrixRotationY(rotationAngleY);
	MathUtil::CMatrix rotation = MathUtil::Multiply(rotationX, rotationY);
	MathUtil::CMatrix transform = MathUtil::Multiply(scalation, rotation); // Combina la rotación y la traslación
	MathUtil::CMatrix transformer = MathUtil::Multiply(transform, translation);
	transformer = MathUtil::MatrixTranspose(transformer);

	mpContext->UpdateSubresource(conbuf, 0, nullptr, &transformer, 0, 0);
	mpContext->VSSetConstantBuffers(0, 1, &conbuf);

	mpContext->DrawIndexed(mIndexBufferSize, 0, 0);
}

