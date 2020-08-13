#pragma once
#include <DirectXMath.h>
#include <list>
#include <string>
#include <assert.h>
#include "SphereCollider.h"
#include "BoxCollider.h"
#include "Transform.h"




using namespace DirectX;


//-----------------------------------------------------------
//�S�ẴQ�[���I�u�W�F�N�g�i�V�[�����܂߂āj���p������C���^�[�t�F�[�X
// �Q�[���I�u�W�F�N�g�́A�e�q�\���ɂȂ��Ă��āA
// �}�g���N�X�̉e�����󂯂邱�ƂɂȂ�
//-----------------------------------------------------------
class GameObject
{
protected:
	
	//�ʒu������Ȃǂ��Ǘ�����I�u�W�F�N�g
	Transform				transform_;

	//�I�u�W�F�N�g�̖��O
	std::string				objectName_;

	//�Փ˔��胊�X�g
	std::list<Collider*>	colliderList_;	

public:
	//�R���X�g���N�^
	GameObject();
	GameObject(GameObject* parent);
	GameObject(GameObject* parent, const std::string& name);

	//�f�X�g���N�^
	virtual ~GameObject();

	//�e�I�u�W�F�N�g�ŕK�����֐�
	virtual void Initialize(void) = 0;
	virtual void Update(void) = 0;
	virtual void Draw() = 0;
	virtual void Release(void) = 0;

	//�����̊Y���֐���ǂ񂾌�A�q���̊֐����Ă�
	void UpdateSub();
	void DrawSub();
	void ReleaseSub();


	////���[�J���s��̎擾�i���̃I�u�W�F�N�g�̍s��j
	////�ߒl�F���[�J���s��
	//XMMATRIX GetLocalMatrix();

	//���[���h�s��̎擾�i�e�̉e�����󂯂��ŏI�I�ȍs��j
	//�ߒl�F���[���h�s��
	XMMATRIX GetWorldMatrix();



	//�e�t���O�̐���
	bool IsDead();			// �폜���邩�ǂ���
	void KillMe();			// �������폜����
	void Enter();			// Update������
	void Leave();			// Update������
	void Visible();			// Draw������
	void Invisible();		// Draw������
	bool IsInitialized();	// �������ς݂��ǂ���
	void SetInitialized();	// �������ς݂ɂ���
	bool IsEntered();		// Update���s���Ă�����
	bool IsVisibled();		// Draw���s���Ă�����


	//�q�I�u�W�F�N�g���X�g���擾
	//�ߒl�F�q�I�u�W�F�N�g���X�g
	std::list<GameObject*>* GetChildList();

	//�e�I�u�W�F�N�g���擾
	//�ߒl�F�e�I�u�W�F�N�g�̃A�h���X
	GameObject* GetParent();

	//���O�ŃI�u�W�F�N�g�������i�Ώۂ͎����̎q���ȉ��j
	//�����Fname	�������閼�O
	//�ߒl�F�������I�u�W�F�N�g�̃A�h���X�i������Ȃ����nullptr�j
	GameObject* FindChildObject(const std::string& name);

	//���O�ŃI�u�W�F�N�g�������i�Ώۂ͑S�́j
	//�����F�������閼�O
	//�ߒl�F�������I�u�W�F�N�g�̃A�h���X
	GameObject* FindObject(const std::string& name) { return GetRootJob()->FindChildObject(name); }

	//�I�u�W�F�N�g�̖��O���擾
	//�ߒl�F���O
	const std::string& GetObjectName(void) const;

	//�q�I�u�W�F�N�g��ǉ��i���X�g�̍Ō�ցj
	//�����F�ǉ�����I�u�W�F�N�g
	void PushBackChild(GameObject* obj);

	//�q�I�u�W�F�N�g��ǉ��i���X�g�̐擪�ցj
	//�����Fobj �ǉ�����I�u�W�F�N�g
	void PushFrontChild(GameObject* obj);

	//�q�I�u�W�F�N�g��S�č폜
	void KillAllChildren();



	//�R���C�_�[�i�Փ˔���j��ǉ�����
	void AddCollider(Collider * collider);

	//�����ƏՓ˂����ꍇ�ɌĂ΂��i�I�[�o�[���C�h�p�j
	//�����FpTarget	�Փ˂�������
	virtual void OnCollision(GameObject* pTarget) {};

	//�Փ˔���
	//�����FpTarget	�Փ˂��Ă邩���ׂ鑊��
	void Collision(GameObject* pTarget);

	//�e�X�g�p�̏Փ˔���g��\��
	void CollisionDraw();

	//RootJob���擾
	GameObject* GetRootJob();


	//�e�A�N�Z�X�֐�
	XMVECTOR GetPosition() { return transform_.position_; }
	XMVECTOR GetRotate() { return transform_.rotate_; }
	XMVECTOR GetScale() { return transform_.scale_; }
	void SetPosition(XMVECTOR position) { transform_.position_ = position; }
	void SetPosition(float x, float y, float z) { SetPosition(XMVECTOR{ x, y, z }); }
	void SetRotate(XMVECTOR rotate) { transform_.rotate_ = rotate; }
	void SetRotate(float x, float y, float z) { SetRotate(XMVECTOR{ x, y, z }); }
	void SetRotateX(float x) { SetRotate(x, transform_.rotate_.vecY, transform_.rotate_.vecZ); }
	void SetRotateY(float y) { SetRotate(transform_.rotate_.vecX, y, transform_.rotate_.vecZ); }
	void SetRotateZ(float z) { SetRotate(transform_.rotate_.vecX, transform_.rotate_.vecY, z); }
	void SetScale(XMVECTOR scale) { transform_.scale_ = scale; }
	void SetScale(float x, float y, float z) { SetScale(XMVectorSet(x, y, z, 0)); }


private:

	//�I�u�W�F�N�g�폜�i�ċA�j
	//�����Fobj�@�폜����I�u�W�F�N�g
	void KillObjectSub(GameObject* obj);


private:
	//�t���O
	struct OBJECT_STATE
	{
		unsigned initialized : 1;	//�������ς݂�
		unsigned entered : 1;		//�X�V���邩
		unsigned visible : 1;		//�`�悷�邩
		unsigned dead : 1;			//�폜���邩
	};
	OBJECT_STATE state_;

	//�e�I�u�W�F�N�g
	GameObject* pParent_;

	//�q�I�u�W�F�N�g���X�g
	std::list<GameObject*> childList_;
};


//�I�u�W�F�N�g���쐬����e���v���[�g
template <class T>
T* Instantiate(GameObject* pParent)
{
	T* pNewObject = new T(pParent);
	if (pParent != nullptr)
	{
		pParent->PushBackChild(pNewObject);
	}
	pNewObject->Initialize();
	return pNewObject;
}

