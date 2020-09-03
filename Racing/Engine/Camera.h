#pragma once
#include "GameObject.h"
#include "Direct3D.h"

//-----------------------------------------------------------
//カメラ
//-----------------------------------------------------------
namespace Camera
{
	//初期化（プロジェクション行列作成）
	void Initialize();

	//更新（ビュー行列作成）
	void Update();

	//視点（カメラの位置）を設定
	void SetPosition(Direct3D::VIEW_PORT_TYPE type, XMVECTOR position);

	//焦点（見る位置）を設定
	void SetTarget(Direct3D::VIEW_PORT_TYPE type, XMVECTOR target);

	//位置を取得
	XMVECTOR GetPosition(Direct3D::VIEW_PORT_TYPE type);
	XMVECTOR GetPosition();

	//焦点を取得
	XMVECTOR GetTarget(Direct3D::VIEW_PORT_TYPE type);

	//ビュー行列を取得
	XMMATRIX GetViewMatrix();

	//プロジェクション行列を取得
	XMMATRIX GetProjectionMatrix();
};