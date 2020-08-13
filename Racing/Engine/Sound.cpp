#include<assert.h>
#include "Sound.h"


//�R���X�g���N�^
Sound::Sound() :
	pDSound_(nullptr),
	pPrimary_(nullptr)
{
}


//�f�X�g���N�^
Sound::~Sound()
{
	Release();
}

//������
void Sound::Initialize(HWND hWnd)
{
	HRESULT ret;

	// COM�̏�����
	CoInitialize(NULL);

	// DirectSound8���쐬
	ret = DirectSoundCreate8(NULL, &pDSound_, NULL);
	assert(SUCCEEDED(ret));


	// �������[�h
	ret = pDSound_->SetCooperativeLevel(hWnd, DSSCL_EXCLUSIVE | DSSCL_PRIORITY);
	assert(SUCCEEDED(ret));

	//�v���C�}���T�E���h�o�b�t�@�̍쐬
	CreatePrimaryBuffer();
}



//�v���C�}���T�E���h�o�b�t�@�̍쐬
void Sound::CreatePrimaryBuffer()
{
	HRESULT ret;
	WAVEFORMATEX wf;

	// �v���C�}���T�E���h�o�b�t�@�̍쐬
	DSBUFFERDESC dsdesc;
	ZeroMemory(&dsdesc, sizeof(DSBUFFERDESC));
	dsdesc.dwSize = sizeof(DSBUFFERDESC);
	dsdesc.dwFlags = DSBCAPS_PRIMARYBUFFER;
	dsdesc.dwBufferBytes = 0;
	dsdesc.lpwfxFormat = NULL;
	ret = pDSound_->CreateSoundBuffer(&dsdesc, &pPrimary_, NULL);
	assert(SUCCEEDED(ret));

	// �v���C�}���o�b�t�@�̃X�e�[�^�X������
	wf.cbSize = sizeof(WAVEFORMATEX);
	wf.wFormatTag = WAVE_FORMAT_PCM;
	wf.nChannels = 2;
	wf.nSamplesPerSec = 44100;
	wf.wBitsPerSample = 16;
	wf.nBlockAlign = wf.nChannels * wf.wBitsPerSample / 8;
	wf.nAvgBytesPerSec = wf.nSamplesPerSec * wf.nBlockAlign;
	ret = pPrimary_->SetFormat(&wf);
	assert(SUCCEEDED(ret));
}


//�t�@�C���̃��[�h
HRESULT Sound::Load(LPDIRECTSOUNDBUFFER * dsb, std::string file)
{
	HRESULT ret;
	MMCKINFO mSrcWaveFile;
	MMCKINFO mSrcWaveFmt;
	MMCKINFO mSrcWaveData;
	LPWAVEFORMATEX wf;

	// WAV�t�@�C�������[�h
	HMMIO hSrc;
	hSrc = mmioOpenA((LPSTR)file.c_str(), NULL, MMIO_ALLOCBUF | MMIO_READ | MMIO_COMPAT);
	if (!hSrc)
	{
		return E_FAIL;
	}

	// 'WAVE'�`�����N�`�F�b�N
	ZeroMemory(&mSrcWaveFile, sizeof(mSrcWaveFile));
	ret = mmioDescend(hSrc, &mSrcWaveFile, NULL, MMIO_FINDRIFF);
	assert(mSrcWaveFile.fccType == mmioFOURCC('W', 'A', 'V', 'E'));

	// 'fmt '�`�����N�`�F�b�N
	ZeroMemory(&mSrcWaveFmt, sizeof(mSrcWaveFmt));
	ret = mmioDescend(hSrc, &mSrcWaveFmt, &mSrcWaveFile, MMIO_FINDCHUNK);
	assert(mSrcWaveFmt.ckid == mmioFOURCC('f', 'm', 't', ' '));

	// �w�b�_�T�C�Y�̌v�Z
	int iSrcHeaderSize = mSrcWaveFmt.cksize;
	if (iSrcHeaderSize < sizeof(WAVEFORMATEX))
		iSrcHeaderSize = sizeof(WAVEFORMATEX);

	// �w�b�_�������m��
	wf = (LPWAVEFORMATEX)malloc(iSrcHeaderSize);
	assert(wf);
	ZeroMemory(wf, iSrcHeaderSize);

	// WAVE�t�H�[�}�b�g�̃��[�h
	ret = mmioRead(hSrc, (char*)wf, mSrcWaveFmt.cksize);
	assert(SUCCEEDED(ret));


	// fmt�`�����N�ɖ߂�
	mmioAscend(hSrc, &mSrcWaveFmt, 0);

	// data�`�����N��T��
	while (1) {
		// ����
		ret = mmioDescend(hSrc, &mSrcWaveData, &mSrcWaveFile, 0);
		assert(SUCCEEDED(ret));

		if (mSrcWaveData.ckid == mmioStringToFOURCCA("data", 0))
			break;
		// ���̃`�����N��
		ret = mmioAscend(hSrc, &mSrcWaveData, 0);
	}

	// �T�E���h�o�b�t�@�̍쐬
	DSBUFFERDESC dsdesc;
	ZeroMemory(&dsdesc, sizeof(DSBUFFERDESC));
	dsdesc.dwSize = sizeof(DSBUFFERDESC);
	dsdesc.dwFlags = DSBCAPS_GETCURRENTPOSITION2 | DSBCAPS_STATIC | DSBCAPS_LOCDEFER;
	dsdesc.dwBufferBytes = mSrcWaveData.cksize;
	dsdesc.lpwfxFormat = wf;
	dsdesc.guid3DAlgorithm = DS3DALG_DEFAULT;
	ret = pDSound_->CreateSoundBuffer(&dsdesc, dsb, NULL);
	assert(SUCCEEDED(ret));

	// ���b�N�J�n
	LPVOID pMem1, pMem2;
	DWORD dwSize1, dwSize2;
	ret = (*dsb)->Lock(0, mSrcWaveData.cksize, &pMem1, &dwSize1, &pMem2, &dwSize2, 0);
	assert(SUCCEEDED(ret));

	// �f�[�^��������
	mmioRead(hSrc, (char*)pMem1, dwSize1);
	mmioRead(hSrc, (char*)pMem2, dwSize2);

	// ���b�N����
	(*dsb)->Unlock(pMem1, dwSize1, pMem2, dwSize2);

	// �w�b�_�p���������J��
	free(wf);

	// WAV�����
	mmioClose(hSrc, 0);

	return S_OK;

}

//�Đ�
void Sound::Play(LPDIRECTSOUNDBUFFER* dsb)
{
	(*dsb)->SetCurrentPosition(0);
	(*dsb)->Play(0, 0, 0);

}

//��~
void Sound::Stop(LPDIRECTSOUNDBUFFER* dsb)
{
	(*dsb)->Stop();
}

//�J��
void Sound::Release()
{
	pPrimary_->Release();
	pDSound_->Release();

	// COM�̏I��
	CoUninitialize();
}
