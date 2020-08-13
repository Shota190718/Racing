#include "SphereCollider.h"
#include "BoxCollider.h"
#include "Model.h"

//�R���X�g���N�^�i�����蔻��̍쐬�j
//�����FbasePos	�����蔻��̒��S�ʒu�i�Q�[���I�u�W�F�N�g�̌��_���猩���ʒu�j
//�����Fsize	�����蔻��̃T�C�Y
SphereCollider::SphereCollider(XMVECTOR center, float radius)
{
	center_ = center;
	size_ = XMVectorSet(radius, radius, radius, 0);
	type_ = COLLIDER_CIRCLE;

	//�����[�X���͔���g�͕\�����Ȃ�
#ifdef _DEBUG
	//�e�X�g�\���p����g
	hDebugModel_ = Model::Load("DebugCollision/sphereCollider.fbx");
#endif
}

//�ڐG����
//�����Ftarget	����̓����蔻��
//�ߒl�F�ڐG���Ă��true
bool SphereCollider::IsHit(Collider* target)
{
	if (target->type_ == COLLIDER_BOX)
		return IsHitBoxVsCircle((BoxCollider*)target, this);
	else
		return IsHitCircleVsCircle((SphereCollider*)target, this);
}