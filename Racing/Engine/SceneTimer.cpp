#include <windows.h>	// timeGetTime()
#pragma comment(lib, "winmm.lib")

#include "SceneTimer.h"

namespace SceneTimer
{
	static uint64_t TotalFrames = 0;
	static uint64_t ElapsedSecounds = 0;
	static uint64_t	ElapsedFrames = 0;
	static float	Delta = 0.f;
	static float	Secound = 0.f;	// 端数の秒 [0~1)

	static DWORD	ElapsedMilliSecound = 0;

	// シーンがスタートしてからの経過時間(sec)
	float	GetElapsedSecounds()
	{
		return (float)ElapsedSecounds + Secound;	// IEEE754精度に注意
	}

	// フレームのデルタタイム(sec)
	float	GetDelta()
	{
		return Delta;
	}

	// シーンタイマーのリセット
	void		Reset()
	{
		ElapsedSecounds = 0;
		ElapsedFrames = 0;

		ElapsedMilliSecound = 0;
		Delta = 0.f;
	}

	// デルタタイムの更新
	void		UpdateFrameDelta()
	{
		static DWORD prevTime = timeGetTime();	// 前回のミリ秒
		DWORD now = timeGetTime();				// 現在のミリ秒
		DWORD deltaMS = (prevTime <= now) ? now - prevTime : (MAXDWORD - prevTime) + now + 1;	// デルタミリ秒
		prevTime = now;
		ElapsedMilliSecound += deltaMS;
		DWORD second = ElapsedMilliSecound / 1000;
		ElapsedMilliSecound %= 1000;

		Secound = (float)ElapsedMilliSecound * 0.001f;
		Delta = (float)deltaMS * 0.001f;
		ElapsedSecounds += second;
		++ElapsedFrames;
		++TotalFrames;

//		TCHAR  string[256];
//		wsprintf(string, TEXT("d:%d ms:%d %d\n"), deltaMS, ElapsedSecounds, ElapsedMilliSecound);
//		OutputDebugString(string);
	}
};
