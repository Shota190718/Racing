#pragma once
#include <DirectXMath.h>


#define vecX  m128_f32[0]
#define vecY  m128_f32[1]
#define vecZ  m128_f32[2]


using namespace DirectX;


//-----------------------------------------------------------
//�ʒu�A�����A�g�嗦�Ȃǂ��Ǘ�����N���X
//-----------------------------------------------------------
class Transform
{
public:
	XMMATRIX matTranslate_;	//�ړ��s��
	XMMATRIX matRotate_;	//��]�s��	
	XMMATRIX matScale_;		//�g��s��
	XMVECTOR position_;		//�ʒu
	XMVECTOR rotate_;		//����
	XMVECTOR scale_;		//�g�嗦
	Transform * pParent_;	//�e�I�u�W�F�N�g�̏��

	//�R���X�g���N�^
	Transform();

	//�f�X�g���N�^
	~Transform();

	//�e�s��̌v�Z
	//�����F�Ȃ�
	//�ߒl�F�Ȃ�
	void Calclation();

	//���[���h�s����擾
	//�����F�Ȃ�
	//�ߒl�F���̎��_�ł̃��[���h�s��
	XMMATRIX GetWorldMatrix();
};

