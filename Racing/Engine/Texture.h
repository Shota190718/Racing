#pragma once
#include <d3d11.h>
#include <DirectXMath.h>
#include <d3dcompiler.h>
#include <wincodec.h>
#include "string"

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")
#pragma comment(lib, "LibFbxSDK-MT.lib")
#pragma comment(lib, "LibXml2-MT.lib")
#pragma comment(lib, "zlib-MT.lib")
#pragma comment( lib, "WindowsCodecs.lib" )

using namespace DirectX;

//-----------------------------------------------------------
//�e�N�X�`���֘A�������N���X
//-----------------------------------------------------------
class Texture
{
	ID3D11SamplerState*			pSampleLinear_;		//�e�N�X�`���T���v���[�i�e�N�X�`���̓\����j
	ID3D11ShaderResourceView*	pTextureSRV_;		//�V�F�[�_�[���\�[�X�r���[�i�e�N�X�`�����V�F�[�_�[�ɑ��邽�߂̂��́j
	XMVECTOR					size_;				//�摜�t�@�C���̃T�C�Y

public:
	Texture();
	~Texture();

	//���[�h
	//�����FfileName	�摜�t�@�C����
	//�ߒl�F����/���s
	HRESULT Load(std::string fileName);


	//�e�A�N�Z�X�֐�
	ID3D11SamplerState* GetSampler() { return pSampleLinear_; }	//�T���v���[�̎擾
	ID3D11ShaderResourceView* GetSRV() { return pTextureSRV_; }	//�V�F�[�_�[���\�[�X�r���[�̎擾
	XMVECTOR GetSize() { return size_; }	//�摜�T�C�Y�̎擾
};

