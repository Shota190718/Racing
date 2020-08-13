#include <d3dcompiler.h>
#include "Direct3D.h"
#include "Global.h"
#include "Transform.h"

//��ʂ̕`��Ɋւ��鏈��
namespace Direct3D
{
	//�y�X���b�v�`�F�[���z
	//��p����2���p�����Ă����A�Е�����ʂɉf���Ă���Ԃɂ�������ɕ`��B
	//1�t���[�����̊G���o���オ�������p���������B����ɂ���ʂ�������Ȃ��B
	//���̕ӂ��i��̂��X���b�v�`�F�[��
	IDXGISwapChain*         pSwapChain_ = nullptr;

	//�y�����_�[�^�[�Q�b�g�r���[�z
	//�`�悵�������̂ƁA�`���i��ł�����p���j�̋��n�����������
	ID3D11RenderTargetView* pRenderTargetView_ = nullptr;

	//�y�f�v�X�X�e���V���z
	//Z�o�b�t�@�@��p���āA3D���̂̑O��֌W�𐳂����\�����邽�߂̂���
	ID3D11Texture2D*		pDepthStencil;

	//�y�f�v�X�X�e���V���r���[�z
	//�f�v�X�X�e���V���̏����V�F�[�_�[�ɓn�����߂̂���
	ID3D11DepthStencilView* pDepthStencilView;

	//�y�u�����h�X�e�[�g�z
	//�������̂��̂��ǂ̂悤�ɕ\�����邩
	ID3D11BlendState*		pBlendState;


	bool		isDrawCollision_ = true;	//�R���W������\�����邩
	bool		_isLighting = false;		//���C�e�B���O���邩



	//extern�錾�����ϐ��̏�����
	ID3D11Device*           pDevice_ = nullptr;
	ID3D11DeviceContext*    pContext_ = nullptr;
	SHADER_BUNDLE			shaderBundle[SHADER_MAX] = { 0 };
	int						screenWidth_ = 0;
	int						screenHeight_ = 0;



	//����������
	HRESULT Direct3D::Initialize(HWND hWnd, int screenWidth, int screenHeight)
	{
		///////////////////////////���낢�돀�����邽�߂̐ݒ�///////////////////////////////
		//���낢��Ȑݒ荀�ڂ��܂Ƃ߂��\����
		DXGI_SWAP_CHAIN_DESC scDesc;

		//�Ƃ肠�����S��0
		ZeroMemory(&scDesc, sizeof(scDesc));

		//�`���̃t�H�[�}�b�g
		scDesc.BufferDesc.Width = screenWidth;		//��ʕ�
		scDesc.BufferDesc.Height = screenHeight;		//��ʍ���
		scDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;	// ���F�g���邩

		//FPS�i1/60�b��1��j
		scDesc.BufferDesc.RefreshRate.Numerator = 60;
		scDesc.BufferDesc.RefreshRate.Denominator = 1;

		//���̑�
		scDesc.Windowed = TRUE;				//�E�B���h�E���[�h���t���X�N���[����
		scDesc.OutputWindow = hWnd;			//�E�B���h�E�n���h��
		scDesc.BufferCount = 1;				//����ʂ̖���
		scDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;	//��ʂɕ`�悷�邽�߂Ɏg��
		scDesc.SampleDesc.Count = 1;		//MSAA�i�A���`�G�C���A�X�j�̐ݒ�
		scDesc.SampleDesc.Quality = 0;		//�@�V



		///////////////////////////��L�ݒ�����ƂɃf�o�C�X�A�R���e�L�X�g�A�X���b�v�`�F�C�����쐬///////////////////////////////
		D3D_FEATURE_LEVEL level;
		HRESULT  hr;
		hr = D3D11CreateDeviceAndSwapChain(
			nullptr,					// �ǂ̃r�f�I�A�_�v�^���g�p���邩�H����Ȃ��nullptr��
			D3D_DRIVER_TYPE_HARDWARE,	// �h���C�o�̃^�C�v��n���B����ȊO�͊�{�I�Ƀ\�t�g�E�F�A�����ŁA�ǂ����Ă��Ƃ�������f�o�O�p�ɗp����ׂ�.
			nullptr,					// ��L��D3D_DRIVER_TYPE_SOFTWARE�ɐݒ肵���ۂɁA���̏������s��DLL�̃n���h����n���B����ȊO���w�肵�Ă���ۂɂ͕K��nullptr��n��.
			0,							// ���炩�̃t���O���w�肷��B�i�f�o�b�O����D3D11_CREATE_DEVICE_DEBUG�H�j
			nullptr,					// �f�o�C�X�A�R���e�L�X�g�̃��x����ݒ�Bnullptr�ɂ��Ƃ��Ή\�Ȍ��荂�����x���ɂ��Ă����
			0,							// ��̈����Ń��x�������w�肵����
			D3D11_SDK_VERSION,			// SDK�̃o�[�W�����B�K�����̒l
			&scDesc,					// ��ł��낢��ݒ肵���\����
			&pSwapChain_,				// ������������SwapChain�̃A�h���X���Ԃ��Ă���
			&pDevice_,					// ������������Device�A�h���X���Ԃ��Ă���
			&level,						// ������������Device�AContext�̃��x�����Ԃ��Ă���
			&pContext_);				// ������������Context�̃A�h���X���Ԃ��Ă���

		//���s������I��
		if (FAILED(hr))	return hr;


		///////////////////////////�`��̂��߂̏���///////////////////////////////
		//�X���b�v�`�F�[������o�b�N�o�b�t�@���擾�i�o�b�N�o�b�t�@ �� ����� �� �`���j
		ID3D11Texture2D* pBackBuffer;
		hr = pSwapChain_->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);

		//���s������I��
		if (FAILED(hr))	return hr;

		//�����_�[�^�[�Q�b�g�r���[���쐬
		hr = pDevice_->CreateRenderTargetView(pBackBuffer, NULL, &pRenderTargetView_);

		//���s������I��
		if (FAILED(hr))	return hr;

		//�ꎞ�I�Ƀo�b�N�o�b�t�@���擾���������Ȃ̂ŁA���
		pBackBuffer->Release();




		/////////////////////////////////////////////////////////////////////////////////////////////


		// �r���[�|�[�g�̐ݒ�
		//�����_�����O���ʂ�\������͈�
		D3D11_VIEWPORT vp;
		vp.Width = (float)screenWidth;			//��
		vp.Height = (float)screenHeight;		//����
		vp.MinDepth = 0.0f;		//��O
		vp.MaxDepth = 1.0f;		//��
		vp.TopLeftX = 0;		//��
		vp.TopLeftY = 0;		//��


		//�e�p�^�[���̃V�F�[�_�[�Z�b�g����
		InitShaderBundle();
		Direct3D::SetShader(Direct3D::SHADER_3D);


		//�[�x�X�e���V���r���[�̍쐬
		D3D11_TEXTURE2D_DESC descDepth;
		descDepth.Width = screenWidth;
		descDepth.Height = screenHeight;
		descDepth.MipLevels = 1;
		descDepth.ArraySize = 1;
		descDepth.Format = DXGI_FORMAT_D32_FLOAT;
		descDepth.SampleDesc.Count = 1;
		descDepth.SampleDesc.Quality = 0;
		descDepth.Usage = D3D11_USAGE_DEFAULT;
		descDepth.BindFlags = D3D11_BIND_DEPTH_STENCIL;
		descDepth.CPUAccessFlags = 0;
		descDepth.MiscFlags = 0;
		pDevice_->CreateTexture2D(&descDepth, NULL, &pDepthStencil);
		pDevice_->CreateDepthStencilView(pDepthStencil, NULL, &pDepthStencilView);


		//�u�����h�X�e�[�g
		D3D11_BLEND_DESC BlendDesc;
		ZeroMemory(&BlendDesc, sizeof(BlendDesc));
		BlendDesc.AlphaToCoverageEnable = FALSE;
		BlendDesc.IndependentBlendEnable = FALSE;
		BlendDesc.RenderTarget[0].BlendEnable = TRUE;
		BlendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
		BlendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
		BlendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
		BlendDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
		BlendDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
		BlendDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
		BlendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
		pDevice_->CreateBlendState(&BlendDesc, &pBlendState);
		float blendFactor[4] = { D3D11_BLEND_ZERO, D3D11_BLEND_ZERO, D3D11_BLEND_ZERO, D3D11_BLEND_ZERO };
		pContext_->OMSetBlendState(pBlendState, blendFactor, 0xffffffff);


		//�p�C�v���C���̍\�z
		//�f�[�^����ʂɕ`�悷�邽�߂̈�ʂ�̐ݒ�
		pContext_->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);  // �f�[�^�̓��͎�ނ��w��
		pContext_->OMSetRenderTargets(1, &pRenderTargetView_, pDepthStencilView);            // �`����ݒ�i����̓����_�[�^�[�Q�b�g�r���[����ĕ`�悵�Ăˁj
		pContext_->RSSetViewports(1, &vp);                                      // �r���[�|�[�g�̃Z�b�g






		//�R���W�����\�����邩
		isDrawCollision_ = GetPrivateProfileInt("DEBUG", "ViewCollider", 0, ".\\setup.ini") != 0;


		screenWidth_ = screenWidth;
		screenHeight_ = screenHeight;

		return S_OK;
	}


	//�V�F�[�_�[�֘A�ŕK�v�ȃZ�b�g����
	void InitShaderBundle()
	{
		DWORD vectorSize = sizeof(XMVECTOR);

		//3D
		{
			// ���_�V�F�[�_�̍쐬�i�R���p�C���j
			ID3DBlob *pCompileVS = NULL;
			D3DCompileFromFile(L"Shader/Simple3D.hlsl", nullptr, nullptr, "VS", "vs_5_0", NULL, 0, &pCompileVS, NULL);
			pDevice_->CreateVertexShader(pCompileVS->GetBufferPointer(), pCompileVS->GetBufferSize(), NULL, &shaderBundle[SHADER_3D].pVertexShader);


			// �s�N�Z���V�F�[�_�̍쐬�i�R���p�C���j
			ID3DBlob *pCompilePS = NULL;
			D3DCompileFromFile(L"Shader/Simple3D.hlsl", nullptr, nullptr, "PS", "ps_5_0", NULL, 0, &pCompilePS, NULL);
			pDevice_->CreatePixelShader(pCompilePS->GetBufferPointer(), pCompilePS->GetBufferSize(), NULL, &shaderBundle[SHADER_3D].pPixelShader);


			// ���_���C�A�E�g�̍쐬�i1���_�̏�񂪉��̃f�[�^���ǂ�ȏ��ԂŎ����Ă��邩�j
			D3D11_INPUT_ELEMENT_DESC layout[] = {
				{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, vectorSize * 0,  D3D11_INPUT_PER_VERTEX_DATA, 0 },	//���_�ʒu
				{ "NORMAL",   0, DXGI_FORMAT_R32G32B32_FLOAT, 0, vectorSize * 1, D3D11_INPUT_PER_VERTEX_DATA, 0 },	//�@��
				{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT,    0, vectorSize * 2, D3D11_INPUT_PER_VERTEX_DATA, 0 },	//�e�N�X�`���iUV�j���W
			};
			pDevice_->CreateInputLayout(layout, 3, pCompileVS->GetBufferPointer(), pCompileVS->GetBufferSize(), &shaderBundle[SHADER_3D].pVertexLayout);


			//�V�F�[�_�[�������쐬�ł����̂ŁA�R���p�C��������͂���Ȃ�
			pCompileVS->Release();
			pCompilePS->Release();

			//���X�^���C�U�쐬
			D3D11_RASTERIZER_DESC rdc = {};
			rdc.CullMode = D3D11_CULL_BACK;
			rdc.FillMode = D3D11_FILL_SOLID;
			rdc.FrontCounterClockwise = TRUE;
			pDevice_->CreateRasterizerState(&rdc, &shaderBundle[SHADER_3D].pRasterizerState);
		}


		//2D
		{
			// ���_�V�F�[�_�̍쐬�i�R���p�C���j
			ID3DBlob *pCompileVS = NULL;
			D3DCompileFromFile(L"Shader/Simple2D.hlsl", nullptr, nullptr, "VS", "vs_5_0", NULL, 0, &pCompileVS, NULL);
			pDevice_->CreateVertexShader(pCompileVS->GetBufferPointer(), pCompileVS->GetBufferSize(), NULL, &shaderBundle[SHADER_2D].pVertexShader);


			// �s�N�Z���V�F�[�_�̍쐬�i�R���p�C���j
			ID3DBlob *pCompilePS = NULL;
			D3DCompileFromFile(L"Shader/Simple2D.hlsl", nullptr, nullptr, "PS", "ps_5_0", NULL, 0, &pCompilePS, NULL);
			pDevice_->CreatePixelShader(pCompilePS->GetBufferPointer(), pCompilePS->GetBufferSize(), NULL, &shaderBundle[SHADER_2D].pPixelShader);


			// ���_���C�A�E�g�̍쐬�i1���_�̏�񂪉��̃f�[�^���ǂ�ȏ��ԂŎ����Ă��邩�j
			D3D11_INPUT_ELEMENT_DESC layout[] = {
				{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, vectorSize * 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
				{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT,    0, vectorSize * 1, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			};
			pDevice_->CreateInputLayout(layout, 2, pCompileVS->GetBufferPointer(), pCompileVS->GetBufferSize(), &shaderBundle[SHADER_2D].pVertexLayout);


			//�V�F�[�_�[�������쐬�ł����̂ŁA�R���p�C��������͂���Ȃ�
			pCompileVS->Release();
			pCompilePS->Release();

			//���X�^���C�U�쐬
			D3D11_RASTERIZER_DESC rdc = {};
			rdc.CullMode = D3D11_CULL_BACK;
			rdc.FillMode = D3D11_FILL_SOLID;
			rdc.FrontCounterClockwise = TRUE;
			pDevice_->CreateRasterizerState(&rdc, &shaderBundle[SHADER_2D].pRasterizerState);
		}

		//DEBUG�p
		{
			// ���_�V�F�[�_�̍쐬�i�R���p�C���j
			ID3DBlob *pCompileVS = NULL;
			D3DCompileFromFile(L"Shader/Debug3D.hlsl", nullptr, nullptr, "VS", "vs_5_0", NULL, 0, &pCompileVS, NULL);
			pDevice_->CreateVertexShader(pCompileVS->GetBufferPointer(), pCompileVS->GetBufferSize(), NULL, &shaderBundle[SHADER_UNLIT].pVertexShader);


			// �s�N�Z���V�F�[�_�̍쐬�i�R���p�C���j
			ID3DBlob *pCompilePS = NULL;
			D3DCompileFromFile(L"Shader/Debug3D.hlsl", nullptr, nullptr, "PS", "ps_5_0", NULL, 0, &pCompilePS, NULL);
			pDevice_->CreatePixelShader(pCompilePS->GetBufferPointer(), pCompilePS->GetBufferSize(), NULL, &shaderBundle[SHADER_UNLIT].pPixelShader);


			// ���_���C�A�E�g�̍쐬�i1���_�̏�񂪉��̃f�[�^���ǂ�ȏ��ԂŎ����Ă��邩�j
			D3D11_INPUT_ELEMENT_DESC layout[] = {
				{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0,  0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			};
			pDevice_->CreateInputLayout(layout, 1, pCompileVS->GetBufferPointer(), pCompileVS->GetBufferSize(), &shaderBundle[SHADER_UNLIT].pVertexLayout);


			//�V�F�[�_�[�������쐬�ł����̂ŁA�R���p�C��������͂���Ȃ�
			pCompileVS->Release();
			pCompilePS->Release();

			//���X�^���C�U�쐬
			D3D11_RASTERIZER_DESC rdc = {};
			rdc.CullMode = D3D11_CULL_NONE;
			rdc.FillMode = D3D11_FILL_WIREFRAME;
			rdc.FrontCounterClockwise = TRUE;
			pDevice_->CreateRasterizerState(&rdc, &shaderBundle[SHADER_UNLIT].pRasterizerState);
		}
	}


	//������`�悷��ShaderBundle��ݒ�
	void SetShader(SHADER_TYPE type)
	{
		pContext_->RSSetState(shaderBundle[type].pRasterizerState);
		pContext_->VSSetShader(shaderBundle[type].pVertexShader, NULL, 0);                         // ���_�V�F�[�_���Z�b�g
		pContext_->PSSetShader(shaderBundle[type].pPixelShader, NULL, 0);                          // �s�N�Z���V�F�[�_���Z�b�g
		pContext_->IASetInputLayout(shaderBundle[type].pVertexLayout);
	}


	//�`��J�n
	void BeginDraw()
	{
		//���������ł��ĂȂ����̂�����������߂�
		if (NULL == pDevice_) return;
		if (NULL == pContext_) return;
		if (NULL == pRenderTargetView_) return;
		if (NULL == pSwapChain_) return;

		//�w�i�̐F
		float clearColor[4] = { 0.1f, 0.5f, 0.5f, 1.0f };//R,G,B,A

		//��ʂ��N���A
		pContext_->ClearRenderTargetView(pRenderTargetView_, clearColor);

		//�[�x�o�b�t�@�N���A
		pContext_->ClearDepthStencilView(pDepthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);	
	}


	//�`��I��
	void EndDraw()
	{
		//�X���b�v�i�o�b�N�o�b�t�@��\�ɕ\������j
		pSwapChain_->Present(0, 0);
	}


	//�J������
	void Release()
	{
		SAFE_RELEASE(pDepthStencil);
		SAFE_RELEASE(pDepthStencilView);
		SAFE_RELEASE(pBlendState);
		SAFE_RELEASE(pRenderTargetView_);
		SAFE_RELEASE(pSwapChain_);

		for (int i = 0; i < SHADER_MAX; i++)
		{
			SAFE_RELEASE(shaderBundle[i].pRasterizerState);
			SAFE_RELEASE(shaderBundle[i].pVertexLayout);
			SAFE_RELEASE(shaderBundle[i].pVertexShader);
			SAFE_RELEASE(shaderBundle[i].pPixelShader);
		}

		if (pContext_)
		{
			pContext_->ClearState();
		}

		SAFE_RELEASE(pRenderTargetView_);
		SAFE_RELEASE(pSwapChain_);
		SAFE_RELEASE(pContext_);
		SAFE_RELEASE(pDevice_);
	}


	//�O�p�`�Ɛ����̏Փ˔���i�Փ˔���Ɏg�p�j
	//https://pheema.hatenablog.jp/entry/ray-triangle-intersection
	bool Intersect(XMVECTOR & start, XMVECTOR & direction, XMVECTOR & v0, XMVECTOR & v1, XMVECTOR & v2, float* distance)
	{
		// �����Ȓ萔([M?ller97] �ł̒l)
		constexpr float kEpsilon = 1e-6f;

		//�O�p�`�̂Q��
		XMVECTOR edge1 = XMVectorSet(v1.vecX - v0.vecX, v1.vecY - v0.vecY, v1.vecZ - v0.vecZ, 0.0f);
		XMVECTOR edge2 = XMVectorSet(v2.vecX - v0.vecX, v2.vecY - v0.vecY, v2.vecZ - v0.vecZ, 0.0f);

		XMVECTOR alpha = XMVector3Cross(direction, edge2);
		float det = XMVector3Dot(edge1, alpha).m128_f32[0];

		// �O�p�`�ɑ΂��āA���C�����s�ɓ��˂���悤�ȏꍇ det = 0 �ƂȂ�B
		// det ������������� 1/det ���傫���Ȃ肷���Đ��l�I�ɕs����ɂȂ�̂�
		// det ? 0 �̏ꍇ�͌������Ȃ����ƂƂ���B
		if (-kEpsilon < det && det < kEpsilon) 
		{
			return false;
		}

		float invDet = 1.0f / det;
		XMVECTOR r = start - v0;

		// u �� 0 <= u <= 1 �𖞂����Ă��邩�𒲂ׂ�B
		float u = XMVector3Dot(alpha, r).vecX * invDet;
		if (u < 0.0f || u > 1.0f)
		{
			return false;
		}

		XMVECTOR beta = XMVector3Cross(r, edge1);

		// v �� 0 <= v <= 1 ���� u + v <= 1 �𖞂������Ƃ𒲂ׂ�B
		// ���Ȃ킿�Av �� 0 <= v <= 1 - u ���݂����Ă��邩�𒲂ׂ��OK�B
		float v = XMVector3Dot(direction, beta).vecX * invDet;
		if (v < 0.0f || u + v > 1.0f) 
		{
			return false;
		}

		// t �� 0 <= t �𖞂������Ƃ𒲂ׂ�B
		float t = XMVector3Dot(edge2, beta).vecX * invDet;
		if (t < 0.0f) 
		{
			return false;
		}

		*distance = t;
		return true;
	}

	//Z�o�b�t�@�ւ̏�������ON/OFF
	void SetDepthBafferWriteEnable(bool isWrite)
	{
		//ON
		if (isWrite)
		{
			//Z�o�b�t�@�i�f�v�X�X�e���V�����w�肷��j
			pContext_->OMSetRenderTargets(1, &pRenderTargetView_, pDepthStencilView);
		}

		//OFF
		else
		{
			pContext_->OMSetRenderTargets(1, &pRenderTargetView_, nullptr);
		}
	}

}
