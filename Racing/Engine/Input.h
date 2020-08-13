#pragma once
#define DIRECTINPUT_VERSION 0x0800
#include <dInput.h>
#include <DirectXMath.h>
#include "XInput.h"

#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "dInput8.lib")
#pragma comment(lib, "Xinput.lib")


using namespace DirectX;

//-----------------------------------------------------------
//DirectInput���g�����L�[�{�[�h���͏���
//-----------------------------------------------------------
namespace Input
{
	//������
	//�����FhWnd	�E�B���h�E�n���h��
	void Initialize(HWND hWnd);

	//�X�V
	void Update();


	///////////////////////////�@�L�[�{�[�h�@//////////////////////////////////
	//�L�[��������Ă��邩���ׂ�
	//�����FkeyCode	���ׂ����L�[�̃R�[�h
	//�ߒl�F������Ă����true
	bool IsKey(int keyCode);

	//�L�[���������������ׂ�i�������ςȂ��͖����j
	//�����FkeyCode	���ׂ����L�[�̃R�[�h
	//�ߒl�F�������u�Ԃ�������true
	bool IsKeyDown(int keyCode);

	//�L�[���������������ׂ�
	//�����FkeyCode	���ׂ����L�[�̃R�[�h
	//�ߒl�F�������u�Ԃ�������true
	bool IsKeyUp(int keyCode);


	///////////////////////////�@�}�E�X�@//////////////////////////////////
	//�}�E�X�̃{�^����������Ă��邩���ׂ�
	//�����FbuttonCode	���ׂ����{�^���̔ԍ�
	//�ߒl�F������Ă����true
	bool IsMouseButton(int buttonCode);

	//�}�E�X�̃{�^�����������������ׂ�i�������ςȂ��͖����j
	//�����FbuttonCode	���ׂ����{�^���̔ԍ�
	//�ߒl�F�������u�Ԃ�������true
	bool IsMouseButtonDown(int buttonCode);

	//�}�E�X�̃{�^�����������������ׂ�
	//�����FbuttonCode	���ׂ����{�^���̔ԍ�
	//�ߒl�F�������u�Ԃ�������true
	bool IsMouseButtonUp(int buttonCode);


	//�}�E�X�J�[�\���̈ʒu���擾
	//�ߒl�F�}�E�X�J�[�\���̈ʒu
	XMVECTOR GetMousePosition();

	//���̃t���[���ł̃}�E�X�̈ړ��ʂ��擾
	//�ߒl�FX,Y �}�E�X�̈ړ��ʁ@�^�@Z,�z�C�[���̉�]��
	XMVECTOR GetMouseMove();


	///////////////////////////�@�R���g���[���[�@//////////////////////////////////
	//�R���g���[���[�̃{�^����������Ă��邩���ׂ�
	//�����FbuttonCode	���ׂ����{�^���̔ԍ�
	//�ߒl�F������Ă����true
	bool IsPadButton(int buttonCode, int padID = 0);

	//�R���g���[���[�̃{�^�����������������ׂ�i�������ςȂ��͖����j
	//�����FbuttonCode	���ׂ����{�^���̔ԍ�
	//�ߒl�F�������u�Ԃ�������true
	bool IsPadButtonDown(int buttonCode, int padID = 0);

	//�R���g���[���[�̃{�^�����������������ׂ�
	//�����FbuttonCode	���ׂ����{�^���̔ԍ�
	//�ߒl�F�������u�Ԃ�������true
	bool IsPadButtonUp(int buttonCode, int padID = 0);

	//���X�e�B�b�N�̌X�����擾
	//�ߒl:�X����i-1�`1�j
	XMVECTOR GetPadStickL(int padID = 0);

	//�E�X�e�B�b�N�̌X�����擾
	//�ߒl:�X����i-1�`1�j
	XMVECTOR GetPadStickR(int padID = 0);

	//���g���K�[�̉������݋���擾
	//�ߒl:�������݋�i0�`1�j
	float		GetPadTrrigerL(int padID = 0);

	//�E�g���K�[�̉������݋���擾
	//�ߒl:�������݋�i0�`1�j
	float		GetPadTrrigerR(int padID = 0);

	//�U��������
	void SetPadVibration(int l, int r, int padID = 0);




	//�J��
	void Release();
};
