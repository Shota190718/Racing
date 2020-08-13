#include "Audio.h"

//Sound*	Audio::_pSound = nullptr;

//3D�摜���Ǘ�����
namespace Audio
{
	//�T�E���h�N���X�̃I�u�W�F�N�g
	Sound* _pSound;

	//���[�h�ς݂̉摜�f�[�^�ꗗ
	std::vector<AudioData*>	_datas;


	//������
	void Initialize(HWND hWnd)
	{
		_pSound = new Sound;
		_pSound->Initialize(hWnd);
		AllRelease();
	}


	//�T�E���h�t�@�C�������[�h
	int Load(std::string fileName)
	{
		AudioData* pData = new AudioData;

		//�J�����t�@�C���ꗗ���瓯���t�@�C�����̂��̂��������T��
		bool isExist = false;
		for (int i = 0; i < _datas.size(); i++)
		{
			//���łɊJ���Ă���ꍇ
			if (_datas[i] != nullptr && _datas[i]->fileName == fileName)
			{
				pData->psoundBuffer = _datas[i]->psoundBuffer;
				isExist = true;
				break;
			}
		}

		//�V���Ƀt�@�C�����J��
		if (isExist == false)
		{
			pData->psoundBuffer = new LPDIRECTSOUNDBUFFER;
			if (FAILED(_pSound->Load(pData->psoundBuffer, fileName)))
			{
				//�J���Ȃ�����
				SAFE_DELETE(pData);
				return -1;
			}

			//�����J����
			pData->fileName = fileName;
		}


		//�g���ĂȂ��ԍ����������T��
		for (int i = 0; i < _datas.size(); i++)
		{
			if (_datas[i] == nullptr)
			{
				_datas[i] = pData;
				return i;
			}
		}

		//�V���ɒǉ�
		_datas.push_back(pData);
		return (int)_datas.size() - 1;
	}



	//�Đ�
	void Play(int handle)
	{
		if (handle < 0 || handle >= _datas.size() || _datas[handle] == nullptr)
		{
			return;
		}
		_pSound->Play(_datas[handle]->psoundBuffer);

	}


	//��~
	void Stop(int handle)
	{
		if (handle < 0 || handle >= _datas.size() || _datas[handle] == nullptr)
		{
			return;
		}
		_pSound->Stop(_datas[handle]->psoundBuffer);
	}



	//�C�ӂ̃T�E���h���J��
	void Release(int handle)
	{
		if (handle < 0 || handle >= _datas.size())
		{
			return;
		}

		//�����T�E���h�𑼂ł��g���Ă��Ȃ���
		bool isExist = false;
		for (int i = 0; i < _datas.size(); i++)
		{
			//���łɊJ���Ă���ꍇ
			if (_datas[i] != nullptr && i != handle && _datas[i]->psoundBuffer == _datas[handle]->psoundBuffer)
			{
				isExist = true;
				break;
			}
		}

		//�g���ĂȂ���΃��f�����
		if (isExist == false)
		{
			SAFE_DELETE(_datas[handle]->psoundBuffer);
		}


		SAFE_DELETE(_datas[handle]);
	}



	//�S�ẴT�E���h�����
	void AllRelease()
	{
		for (int i = 0; i < _datas.size(); i++)
		{
			Release(i);
		}
		_datas.clear();
	}


	//�Q�[���I�����ɍs������
	void ReleaseDirectSound()
	{
		SAFE_DELETE(_pSound);
	}
}

