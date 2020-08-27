#pragma once

#include <stdint.h>

namespace SceneTimer
{
	// シーンがスタートしてからの経過時間(sec)
	float	GetElapsedSecounds();

	// フレームのデルタタイム(sec)
	float	GetDelta();

	// シーンタイマーのリセット
	void	Reset();

	// デルタタイムの更新
	void	UpdateFrameDelta();
};
