#pragma once
#include "GameObject.h"


//-----------------------------------------------------------
//��ԃg�b�v�ɗ���I�u�W�F�N�g
//���ׂẴI�u�W�F�N�g�́A����̎q���ɂȂ�
//-----------------------------------------------------------
class RootObject :	public GameObject
{
public:
	RootObject();
	~RootObject();

	//������
	void Initialize() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//�J��
	void Release() override;
};

