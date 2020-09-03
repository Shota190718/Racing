#include "Camera.h"
#include <array>

//XMVECTOR _position[Direct3D::VIEW_PORT_MAX];
//XMVECTOR _target[Direct3D::VIEW_PORT_MAX];
//XMMATRIX _view[Direct3D::VIEW_PORT_MAX];
//XMMATRIX _proj[Direct3D::VIEW_PORT_MAX];

std::array<XMVECTOR, Direct3D::VIEW_PORT_MAX> _position;
std::array<XMVECTOR, Direct3D::VIEW_PORT_MAX> _target;
std::array<XMMATRIX, Direct3D::VIEW_PORT_MAX> _view;
std::array<XMMATRIX, Direct3D::VIEW_PORT_MAX> _proj;

//�������i�v���W�F�N�V�����s��쐬�j
void Camera::Initialize()
{
	for (auto i = 0u; i < Direct3D::VIEW_PORT_MAX; ++i) {
		
		_position[i] = XMVectorSet(0, 3, -10, 0);	//�J�����̈ʒu
		_target[i] = XMVectorSet(0, 0, 0, 0);	//�J�����̏œ_
	}

	//�v���W�F�N�V�����s��
	_proj[Direct3D::VIEW_PORT_FULL] = XMMatrixPerspectiveFovLH(XM_PIDIV4, (FLOAT)Direct3D::screenWidth_ / (FLOAT)Direct3D::screenHeight_, 0.1f, 1000.0f);
	_proj[Direct3D::VIEW_PORT_LEFT] = XMMatrixPerspectiveFovLH(XM_PIDIV4, (FLOAT)Direct3D::screenWidth_ / (FLOAT)Direct3D::screenHeight_ / 2, 0.1f, 1000.0f);
	_proj[Direct3D::VIEW_PORT_RIGHT] = XMMatrixPerspectiveFovLH(XM_PIDIV4, (FLOAT)Direct3D::screenWidth_ / (FLOAT)Direct3D::screenHeight_ / 2, 0.1f, 1000.0f);
}

//�X�V�i�r���[�s��쐬�j
void Camera::Update()
{
	//�r���[�s��
	for (auto i = 0u; i < Direct3D::VIEW_PORT_MAX; ++i) {
		
		_view[i] = XMMatrixLookAtLH(_position[i], _target[i], XMVectorSet(0, 1, 0, 0));
	}
}

//�œ_��ݒ�
void Camera::SetTarget(Direct3D::VIEW_PORT_TYPE type, XMVECTOR target) { _target[type] = target; }

//�ʒu��ݒ�
void Camera::SetPosition(Direct3D::VIEW_PORT_TYPE type, XMVECTOR position) { _position[type] = position; }

//�œ_���擾
XMVECTOR Camera::GetTarget(Direct3D::VIEW_PORT_TYPE type) { return _target[type]; }
XMVECTOR Camera::GetPosition() { return _target[Direct3D::GetCurrentViewPort()]; }

//�ʒu���擾
XMVECTOR Camera::GetPosition(Direct3D::VIEW_PORT_TYPE type) { return _position[type]; }

//�r���[�s����擾
XMMATRIX Camera::GetViewMatrix() { return _view[Direct3D::GetCurrentViewPort()]; }

//�v���W�F�N�V�����s����擾
XMMATRIX Camera::GetProjectionMatrix() { return _proj[Direct3D::GetCurrentViewPort()]; }