#pragma once

#pragma once

#include <vector>
#include <string>
#include "Global.h"
#include "Sound.h"


//-----------------------------------------------------------
//���ʉ����Ǘ�����
//-----------------------------------------------------------
namespace Audio
{
	//�ЂƂ̃T�E���h�̏��
	struct AudioData
	{
		//�t�@�C����
		std::string fileName;

		//�T�E���h�o�b�t�@�i�ǂݍ��񂾃T�E���h������j
		LPDIRECTSOUNDBUFFER* 	psoundBuffer;


		//�R���X�g���N�^
		AudioData() :psoundBuffer(nullptr)
		{
		}

	};



	//������
	//�����FhWnd	�E�B���h�E�n���h��
	void Initialize(HWND hWnd);


	//�T�E���h�t�@�C�������[�h
	//���łɓ������O�̃t�@�C�������[�h�ς݂̏ꍇ�́A�����̃f�[�^�̔ԍ���Ԃ�
	//�����FfileName�@�t�@�C����
	//�ߒl�F���̃T�E���h�f�[�^�Ɋ��蓖�Ă�ꂽ�ԍ�
	int Load(std::string fileName);

	//�Đ�
	//�����Fhandle	�Đ��������T�E���h�̔ԍ�
	void Play(int handle);

	//��~
	//�����Fhandle	�~�߂����T�E���h�̔ԍ�
	void Stop(int handle);

	//�C�ӂ̃T�E���h���J��
	//�����Fhandle	�J���������T�E���h�̔ԍ�
	void Release(int handle);

	//�S�ẴT�E���h�����
	//�i�V�[�����؂�ւ��Ƃ��͕K�����s�j
	void AllRelease();

	//�Q�[���I�����ɍs������
	void ReleaseDirectSound();
}