//=======================================
//
// ���u�ؗt�̃��C������[mob_tree_leaf.cpp]
// Author ��������
//
//=======================================
#include "manager.h"
#include "mob_tree_leaf.h"
#include "useful.h"

//=======================================
// �萔��`
//=======================================
namespace
{
	const D3DXVECTOR3 MAX_SCALE = D3DXVECTOR3(3.0f, 3.0f, 3.0f);	// �g�嗦�̍ő�l
	const D3DXVECTOR3 MIN_SCALE = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// �g�嗦�̍ŏ��l
	const char* LEAF_MODEL = "data\\MODEL\\leaf.x";					// �t�̃��f��
	const float SCALE_MOVE = 0.005f;			// �g�嗦�̈ړ���
	const D3DXVECTOR3 GET_SCALE_SUB = D3DXVECTOR3(0.1f, 0.1f, 0.1f);	// �g�嗦�̎擾���̌��Z��
}

//=========================
// �I�[�o�[���[�h�R���X�g���N�^
//=========================
CMobTreeLeaf::CMobTreeLeaf() : CModel(TYPE_NONE, PRIORITY_ENTITY)
{

}

//=========================
// �f�X�g���N�^
//=========================
CMobTreeLeaf::~CMobTreeLeaf()
{

}

//=========================
// ����������
//=========================
HRESULT CMobTreeLeaf::Init(void)
{
	if (FAILED(CModel::Init()))
	{ // �������Ɏ��s�����ꍇ

		// ���s��Ԃ�
		return E_FAIL;
	}

	// ������Ԃ�
	return S_OK;
}

//=========================
// �I������
//=========================
void CMobTreeLeaf::Uninit(void)
{
	// �I��
	CModel::Uninit();
}

//=========================
// �X�V����
//=========================
void CMobTreeLeaf::Update(void)
{
	// ��������
	Growth();
}

//=========================
// �`�揈��
//=========================
void CMobTreeLeaf::Draw(void)
{
	// �`�揈��
	CModel::Draw();
}

//=========================
// ���̐ݒ菈��
//=========================
void CMobTreeLeaf::SetData(const D3DXVECTOR3& pos)
{
	// �X�N���[���̐ݒ菈��
	SetPos(pos);					// �ʒu
	SetPosOld(pos);					// �O��̈ʒu
	SetRot(NONE_D3DXVECTOR3);		// ����
	SetScale(MIN_SCALE);			// �g�嗦
	SetFileData(CManager::Get()->GetXFile()->Regist(LEAF_MODEL));
}

//=========================
// ��ʂƂ̏Փˎ�����
//=========================
void CMobTreeLeaf::SnowBallHit(void)
{
	// �g�嗦���擾
	D3DXVECTOR3 scale = GetScale();

	if (scale.x > MIN_SCALE.x)
	{ // �g�嗦����萔�ȏ�̏ꍇ

		// �g�嗦���ŏ��ɂ���
		SetScale(GetScale() - GET_SCALE_SUB);
	}
}

//=========================
// ��������
//=========================
CMobTreeLeaf* CMobTreeLeaf::Create(const D3DXVECTOR3& pos)
{
	// ���[�J���I�u�W�F�N�g�𐶐�
	CMobTreeLeaf* pLeaf = nullptr;	// �t�̃C���X�^���X�𐶐�

	if (pLeaf == nullptr)
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// �I�u�W�F�N�g�𐶐�
		pLeaf = new CMobTreeLeaf;
	}
	else
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// ��~
		assert(false);

		// NULL ��Ԃ�
		return nullptr;
	}

	if (pLeaf != nullptr)
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// ����������
		if (FAILED(pLeaf->Init()))
		{ // �������Ɏ��s�����ꍇ

			// ��~
			assert(false);

			// NULL ��Ԃ�
			return nullptr;
		}

		// ���̐ݒ菈��
		pLeaf->SetData(pos);
	}
	else
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// ��~
		assert(false);

		// NULL ��Ԃ�
		return nullptr;
	}

	// �t�̃|�C���^��Ԃ�
	return pLeaf;
}

//=========================
// ��������
//=========================
void CMobTreeLeaf::Growth(void)
{
	// �g�嗦���擾
	D3DXVECTOR3 scale = GetScale();

	// �ϓ��ȕ␳����
	useful::FrameCorrect(MAX_SCALE.x, &scale.x, SCALE_MOVE);
	useful::FrameCorrect(MAX_SCALE.y, &scale.y, SCALE_MOVE);
	useful::FrameCorrect(MAX_SCALE.z, &scale.z, SCALE_MOVE);

	// �g�嗦�̓K�p
	SetScale(scale);
}