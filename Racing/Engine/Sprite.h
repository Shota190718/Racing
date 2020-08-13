#pragma once
#include <d3d11.h>
#include <DirectXMath.h>
#include <d3dcompiler.h>

#include "string"
#include "Texture.h"
#include "Transform.h"

using namespace DirectX;


//-----------------------------------------------------------
//2D�摜��\�����邽�߂̃N���X
//�Ƃ͌����Ă����Ԃ̓|���S���𕽖ʓI�ɕ\�����Ă��邾��
//-----------------------------------------------------------
class Sprite
{
	// ��̒��_�����i�[����\����
	struct VERTEX
	{
		XMVECTOR position;
		XMVECTOR uv;
	};


	//�y�R���X�^���g�o�b�t�@�[�z
	// GPU(�V�F�[�_��)�֑��鐔�l���܂Ƃ߂��\����
	//Simple2D.hlsl�̃O���[�o���ϐ��ƑΉ�������
	struct CONSTANT_BUFFER
	{
		XMMATRIX	world;		// ���_���W�ϊ��s��
		XMMATRIX	uvTrans;	// �e�N�X�`�����W�ϊ��s��
		XMFLOAT4	color;		// �e�N�X�`���Ƃ̍����F
	};

	//�y���_�o�b�t�@�z
	//�e���_�̏��i�ʒu�Ƃ��F�Ƃ��j���i�[����Ƃ���
	//���_�����̔z��ɂ��Ďg��
	ID3D11Buffer *pVertexBuffer_;

	//�y�C���f�b�N�X�o�b�t�@�z
	//�u�ǂ̒��_�v�Ɓu�ǂ̒��_�v�Ɓu�ǂ̒��_�v�łR�p�`�|���S���ɂȂ邩�̏����i�[����Ƃ���
	ID3D11Buffer *pIndexBuffer_;

	//�y�e�N�X�`���z
	Texture*	pTexture_;

	//�y�萔�o�b�t�@�z
	//�V�F�[�_�[�iSimple2D.hlsl�j�̃O���[�o���ϐ��ɒl��n�����߂̂���
	ID3D11Buffer *pConstantBuffer_;


	//////////////////////////private�֐��iLoad�֐�����Ă΂��j/////////////////////////////
	void InitVertex();			//���_�o�b�t�@����
	void InitIndex();			//�C���f�b�N�X�o�b�t�@����
	void InitConstantBuffer();	//�R���X�^���g�o�b�t�@�i�V�F�[�_�[�ɏ��𑗂��j����


public:
	Sprite();
	~Sprite();

	//���[�h
	//�����FfileName	�摜�t�@�C����
	//�ߒl�F����/���s
	HRESULT Load(std::string fileName);

	//�`��
	//�����Fmatrix	�ϊ��s��i���[���h�s��j
	//�����Frect	�摜�̐؂蔲���͈�
	//�����Falpha	�A���t�@�l�i�s�����x�j
	void Draw(Transform& transform, RECT rect, float alpha);


	//�摜�T�C�Y�̎擾
	//�ߒl�F�摜�T�C�Y
	XMVECTOR GetTextureSize() {	return pTexture_->GetSize();}

};