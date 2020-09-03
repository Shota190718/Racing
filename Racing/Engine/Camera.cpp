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

//初期化（プロジェクション行列作成）
void Camera::Initialize()
{
	for (auto i = 0u; i < Direct3D::VIEW_PORT_MAX; ++i) {
		
		_position[i] = XMVectorSet(0, 3, -10, 0);	//カメラの位置
		_target[i] = XMVectorSet(0, 0, 0, 0);	//カメラの焦点
	}

	//プロジェクション行列
	_proj[Direct3D::VIEW_PORT_FULL] = XMMatrixPerspectiveFovLH(XM_PIDIV4, (FLOAT)Direct3D::screenWidth_ / (FLOAT)Direct3D::screenHeight_, 0.1f, 1000.0f);
	_proj[Direct3D::VIEW_PORT_LEFT] = XMMatrixPerspectiveFovLH(XM_PIDIV4, (FLOAT)Direct3D::screenWidth_ / (FLOAT)Direct3D::screenHeight_ / 2, 0.1f, 1000.0f);
	_proj[Direct3D::VIEW_PORT_RIGHT] = XMMatrixPerspectiveFovLH(XM_PIDIV4, (FLOAT)Direct3D::screenWidth_ / (FLOAT)Direct3D::screenHeight_ / 2, 0.1f, 1000.0f);
}

//更新（ビュー行列作成）
void Camera::Update()
{
	//ビュー行列
	for (auto i = 0u; i < Direct3D::VIEW_PORT_MAX; ++i) {
		
		_view[i] = XMMatrixLookAtLH(_position[i], _target[i], XMVectorSet(0, 1, 0, 0));
	}
}

//焦点を設定
void Camera::SetTarget(Direct3D::VIEW_PORT_TYPE type, XMVECTOR target) { _target[type] = target; }

//位置を設定
void Camera::SetPosition(Direct3D::VIEW_PORT_TYPE type, XMVECTOR position) { _position[type] = position; }

//焦点を取得
XMVECTOR Camera::GetTarget(Direct3D::VIEW_PORT_TYPE type) { return _target[type]; }
XMVECTOR Camera::GetPosition() { return _target[Direct3D::GetCurrentViewPort()]; }

//位置を取得
XMVECTOR Camera::GetPosition(Direct3D::VIEW_PORT_TYPE type) { return _position[type]; }

//ビュー行列を取得
XMMATRIX Camera::GetViewMatrix() { return _view[Direct3D::GetCurrentViewPort()]; }

//プロジェクション行列を取得
XMMATRIX Camera::GetProjectionMatrix() { return _proj[Direct3D::GetCurrentViewPort()]; }