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
	const D3DXVECTOR3 SCALE = D3DXVECTOR3(3.0f, 3.0f, 3.0f);	// �g�嗦
	const D3DXCOLOR IMMATURE_COL = D3DXCOLOR(0.2f, 1.0f, 0.2f, 1.0f);		// ���n��Ԃ̗t�̐F
	const char* LEAF_MODEL = "data\\MODEL\\leaf.x";				// �t�̃��f��
}

//=========================
// �I�[�o�[���[�h�R���X�g���N�^
//=========================
CMobTreeLeaf::CMobTreeLeaf() : CModel(TYPE_NONE, PRIORITY_ENTITY)
{
	// �S�Ă̒l���N���A����
	m_col = IMMATURE_COL;		// �F
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

}

//=========================
// �`�揈��
//=========================
void CMobTreeLeaf::Draw(void)
{
	// �`�揈��
	CModel::Draw(m_col);
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
	SetScale(SCALE);				// �g�嗦
	SetFileData(CManager::Get()->GetXFile()->Regist(LEAF_MODEL));

	// �S�Ă̒l��ݒ肷��
	m_col = IMMATURE_COL;		// �F
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