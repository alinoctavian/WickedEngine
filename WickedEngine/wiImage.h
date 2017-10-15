#pragma once
#include "CommonInclude.h"
#include "wiGraphicsAPI.h"
#include "ShaderInterop.h"

class wiImageEffects;
enum BLENDMODE;

class wiImage
{
private:
	//static mutex MUTEX;
protected:
	CBUFFER(ImageCB, CBSLOT_IMAGE_IMAGE)
	{
		XMMATRIX	mTransform;
		XMFLOAT4	mTexMulAdd;
		XMFLOAT4	mColor;
		XMFLOAT2	mPivot;
		UINT		mMirror;

		UINT		mMask;
		UINT		mDistort;
		UINT		mNormalmapSeparate;
		float		mMipLevel;
		float		mFade;
		float		mOpacity;
		float		pad0;
		float		pad1;
		float		pad2;
	};
	CBUFFER(PostProcessCB, CBSLOT_IMAGE_POSTPROCESS)
	{
		float params0[4];
		float params1[4];
	};
	
	static wiGraphicsTypes::BlendState		*blendState, *blendStateAdd, *blendStateNoBlend, *blendStateAvg, *blendStateDisable;
	static wiGraphicsTypes::GPUBuffer       *constantBuffer, *processCb;

	static wiGraphicsTypes::VertexShader     *vertexShader,*screenVS;
	static wiGraphicsTypes::PixelShader      *pixelShader,*blurHPS,*blurVPS,*shaftPS,*outlinePS,*dofPS,*motionBlurPS,*bloomSeparatePS
		,*fxaaPS,*ssaoPS,*ssssPS,*deferredPS,*linDepthPS,*colorGradePS,*ssrPS, *screenPS, *stereogramPS, *tonemapPS, *reprojectDepthBufferPS, *downsampleDepthBufferPS
		,*temporalAAResolvePS, *sharpenPS;
	

	
	static wiGraphicsTypes::RasterizerState		*rasterizerState;
	static wiGraphicsTypes::DepthStencilState	*depthStencilStateGreater, *depthStencilStateLess, *depthStencilStateEqual,*depthNoStencilState, *depthStencilStateDepthWrite;

public:
	static void LoadShaders();
	static void BindPersistentState(GRAPHICSTHREAD threadID);
private:
	static void LoadBuffers();
	static void SetUpStates();

public:
	wiImage();
	
	static void Draw(wiGraphicsTypes::Texture2D* texture, const wiImageEffects& effects,GRAPHICSTHREAD threadID);

	static void DrawDeferred(wiGraphicsTypes::Texture2D* lightmap_diffuse, wiGraphicsTypes::Texture2D* lightmap_specular, 
		wiGraphicsTypes::Texture2D* ao, GRAPHICSTHREAD threadID, int stencilref = 0);

	static void Load();
	static void CleanUp();
};

