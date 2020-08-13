#pragma once

//�C���N���[�h
#include <Windows.h>
#include <d3d11.h>
#include <DirectXMath.h>

//�����J
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")

using namespace DirectX;


//-----------------------------------------------------------
//��ʂ̕`��Ɋւ��鏈��
//-----------------------------------------------------------
namespace Direct3D
{
	////////////////////////�O��������A�N�Z�X����ϐ��Q///////////////////////////////
	//�y�f�o�C�X�z
	//�`����s�����߂̊��⃊�\�[�X�̍쐬�Ɏg��
	extern ID3D11Device*           pDevice_;

	//�y�R���e�L�X�g�z
	//GPU�ɖ��߂��o�����߂̂��
	extern ID3D11DeviceContext*    pContext_;


	//���V�F�[�_�[�֘A�ŕK�v�ȃZ�b�g
	enum SHADER_TYPE{SHADER_3D, SHADER_2D, SHADER_UNLIT, SHADER_MAX};	//3�^�C�v�i3D�p�A2D�p�A�����蔻��g�\���p�j
	struct SHADER_BUNDLE
	{
		//�y���_���̓��C�A�E�g���z
		//1�̒��_�f�[�^���ǂ�ȏ����ǂ�ȏ��ԂŊi�[���Ă邩�i�ʒu�ƐF�Ɩ@���Ɓc�Ƃ��j
		ID3D11InputLayout *pVertexLayout;

		//�y���_�V�F�[�_�z
		//�V�F�[�_�[�i�Z�Z.hlsl�j�̒��̒��_�V�F�[�_�[�iVS�j�������R���p�C���������̂�����
		//�V�F�[�_�[�̓n�[�h�ɂ���ē��삪�قȂ�̂ŁA���s���ɃR���p�C������B
		ID3D11VertexShader *pVertexShader;

		//�y�s�N�Z���V�F�[�_�z
		//�V�F�[�_�[�i�Z�Z.hlsl�j�̒��̃s�N�Z���V�F�[�_�[�iPS�j�������R���p�C���������̂�����
		ID3D11PixelShader *pPixelShader;

		//�y���X�^���C�U�z
		//���_�̕\���ʒu�m���A��ʂ̂ǂ̃s�N�Z�������点��΂��������߂����
		ID3D11RasterizerState*	pRasterizerState;
	};
	extern SHADER_BUNDLE shaderBundle[SHADER_MAX];



	//���̑�
	extern int		screenWidth_;		//�X�N���[���̕�
	extern int		screenHeight_;		//�X�N���[���̍���
	extern bool		isDrawCollision_;	//�R���W������\�����邩�t���O






	////////////////////////��������͊֐�///////////////////////////////

	//����������
	//�����FhWnd			�E�B���h�E�n���h��
	//�����FscreenWidth		�X�N���[���̕�
	//�����FscreenHeight	�X�N���[���̍���
	HRESULT Initialize(HWND hWnd, int screenWidth, int screenHeight);

	//�V�F�[�_�[�֘A�ŕK�v�ȃZ�b�g����
	void InitShaderBundle();

	//������`�悷��ShaderBundle��ݒ�
	//�����Ftype	SHADER_3D, SHADER_2D, SHADER_UNLIT�̂ǂꂩ
	void SetShader(SHADER_TYPE type);

	//�`��J�n
	void BeginDraw();

	//�`��I��
	void EndDraw();

	//�J������
	void Release();


	//�O�p�`�Ɛ����i���C�j�̏Փ˔���i�Փ˔���Ɏg�p�j
	//�����Fstart�@		���C�̃X�^�[�g�ʒu
	//�����Fdirection	���C�̕���
	//�����Fv0,v1,v2	�O�p�`�̊e���_�ʒu
	//�����Fdistance	�Փ˓_�܂ł̋�����Ԃ�
	//�ߒl�F�Փ˂������ǂ���
	bool Intersect(XMVECTOR& start, XMVECTOR& direction, XMVECTOR &v0, XMVECTOR& v1, XMVECTOR& v2, float* distance);

	//Z�o�b�t�@�ւ̏�������ON/OFF
	//�����FisWrite	  true=��������ON�^false=��������OFF
	void SetDepthBafferWriteEnable(bool isWrite);
};

