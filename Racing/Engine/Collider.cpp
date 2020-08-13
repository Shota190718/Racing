#include "BoxCollider.h"
#include "SphereCollider.h"
#include "GameObject.h"
#include "Model.h"

//�R���X�g���N�^
Collider::Collider():
	pGameObject_(nullptr)
{
}

//�f�X�g���N�^
Collider::~Collider()
{
}

//���^���m�̏Փ˔���
//�����FboxA	�P�ڂ̔��^����
//�����FboxB	�Q�ڂ̔��^����
//�ߒl�F�ڐG���Ă����true
bool Collider::IsHitBoxVsBox(BoxCollider* boxA, BoxCollider* boxB)
{

	XMVECTOR boxPosA = boxA->pGameObject_->GetPosition() + boxA->center_;
	XMVECTOR boxPosB = boxB->pGameObject_->GetPosition() + boxB->center_;


	if ((boxPosA.vecX + boxA->size_.vecX / 2) > (boxPosB.vecX - boxB->size_.vecX / 2) &&
		(boxPosA.vecX - boxA->size_.vecX / 2) < (boxPosB.vecX + boxB->size_.vecX / 2) &&
		(boxPosA.vecY + boxA->size_.vecY / 2) > (boxPosB.vecY - boxB->size_.vecY / 2) &&
		(boxPosA.vecY - boxA->size_.vecY / 2) < (boxPosB.vecY + boxB->size_.vecY / 2) &&
		(boxPosA.vecZ + boxA->size_.vecZ / 2) > (boxPosB.vecZ - boxB->size_.vecZ / 2) &&
		(boxPosA.vecZ - boxA->size_.vecZ / 2) < (boxPosB.vecZ + boxB->size_.vecZ / 2))
	{
		return true;
	}
	return false;
}

//���^�Ƌ��̂̏Փ˔���
//�����Fbox	���^����
//�����Fsphere	�Q�ڂ̔��^����
//�ߒl�F�ڐG���Ă����true
bool Collider::IsHitBoxVsCircle(BoxCollider* box, SphereCollider* sphere)
{
	XMVECTOR circlePos = sphere->pGameObject_->GetPosition() + sphere->center_;
	XMVECTOR boxPos = box->pGameObject_->GetPosition() + box->center_;



	if (circlePos.vecX > boxPos.vecX - box->size_.vecX - sphere->size_.vecX &&
		circlePos.vecX < boxPos.vecX + box->size_.vecX + sphere->size_.vecX &&
		circlePos.vecY > boxPos.vecY - box->size_.vecY - sphere->size_.vecX &&
		circlePos.vecY < boxPos.vecY + box->size_.vecY + sphere->size_.vecX &&
		circlePos.vecZ > boxPos.vecZ - box->size_.vecZ - sphere->size_.vecX &&
		circlePos.vecZ < boxPos.vecZ + box->size_.vecZ + sphere->size_.vecX )
	{
		return true;
	}

	return false;
}

//���̓��m�̏Փ˔���
//�����FcircleA	�P�ڂ̋��̔���
//�����FcircleB	�Q�ڂ̋��̔���
//�ߒl�F�ڐG���Ă����true
bool Collider::IsHitCircleVsCircle(SphereCollider* circleA, SphereCollider* circleB)
{

	XMVECTOR Vec = (circleA->center_ + circleA->pGameObject_->GetPosition()) - (circleB->center_ + circleB->pGameObject_->GetPosition());
	Vec = XMVector3Length(Vec);

	if (Vec.vecX <= (circleA->size_.vecX + circleB->size_.vecX))
	{
		return true;
	}

	return false;
}

//�e�X�g�\���p�̘g��`��
//�����Fposition	�ʒu
void Collider::Draw(XMVECTOR position)
{
	Transform transform;
	transform.position_ = XMVectorSet(position.vecX + center_.vecX, position.vecY + center_.vecY, position.vecZ + center_.vecZ, 0);
	transform.scale_ = XMVectorSet(size_.vecX, size_.vecY, size_.vecZ, 0.0f);
	transform.Calclation();
	Model::SetTransform(hDebugModel_, transform);
	Model::Draw(hDebugModel_);
}
