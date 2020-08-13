#include "camera.h"
#include "Direct3D.h"

XMVECTOR _position;
XMVECTOR _target;
XMMATRIX _view;
XMMATRIX _proj;

//�������i�v���W�F�N�V�����s��쐬�j
void Camera::Initialize()
{
	_position = XMVectorSet(0, 3, -10, 0);	//�J�����̈ʒu
	_target = XMVectorSet(0, 0, 0, 0);	//�J�����̏œ_

	//�v���W�F�N�V�����s��
	_proj = XMMatrixPerspectiveFovLH(XM_PIDIV4, (FLOAT)Direct3D::screenWidth_ / (FLOAT)Direct3D::screenHeight_, 0.1f, 1000.0f);
}

//�X�V�i�r���[�s��쐬�j
void Camera::Update()
{
	//�r���[�s��
	_view = XMMatrixLookAtLH(XMVectorSet(_position.vecX, _position.vecY, _position.vecZ, 0),
		XMVectorSet(_target.vecX, _target.vecY, _target.vecZ, 0), XMVectorSet(0, 1, 0, 0));
}

//�œ_��ݒ�
void Camera::SetTarget(XMVECTOR target) { _target = target; }

//�ʒu��ݒ�
void Camera::SetPosition(XMVECTOR position) { _position = position; }

//�œ_���擾
XMVECTOR Camera::GetTarget() { return _target; }

//�ʒu���擾
XMVECTOR Camera::GetPosition() { return _position; }

//�r���[�s����擾
XMMATRIX Camera::GetViewMatrix() { return _view; }

//�v���W�F�N�V�����s����擾
XMMATRIX Camera::GetProjectionMatrix() { return _proj; }