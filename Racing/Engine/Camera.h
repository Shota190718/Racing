#pragma once
#include "GameObject.h"
#include "Direct3D.h"

//-----------------------------------------------------------
//�J����
//-----------------------------------------------------------
namespace Camera
{
	//�������i�v���W�F�N�V�����s��쐬�j
	void Initialize();

	//�X�V�i�r���[�s��쐬�j
	void Update();

	//���_�i�J�����̈ʒu�j��ݒ�
	void SetPosition(Direct3D::VIEW_PORT_TYPE type, XMVECTOR position);

	//�œ_�i����ʒu�j��ݒ�
	void SetTarget(Direct3D::VIEW_PORT_TYPE type, XMVECTOR target);

	//�ʒu���擾
	XMVECTOR GetPosition(Direct3D::VIEW_PORT_TYPE type);
	XMVECTOR GetPosition();

	//�œ_���擾
	XMVECTOR GetTarget(Direct3D::VIEW_PORT_TYPE type);

	//�r���[�s����擾
	XMMATRIX GetViewMatrix();

	//�v���W�F�N�V�����s����擾
	XMMATRIX GetProjectionMatrix();
};