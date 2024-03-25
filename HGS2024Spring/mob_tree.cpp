//=======================================
//
// ���u�؂̃��C������[mob_tree.cpp]
// Author ��������
//
//=======================================
#include "manager.h"
#include "mob_tree.h"
#include "useful.h"

#include "mob_tree_leaf.h"

//=======================================
// �萔��`
//=======================================
namespace
{
	const D3DXVECTOR3 SCALE = D3DXVECTOR3(3.0f, 3.0f, 3.0f);	// �g�嗦
	const D3DXVECTOR3 LEAF_SHIFT = D3DXVECTOR3(0.0f, 230.0f, 0.0f);			// �t�̂��炷��
	const char* TREE_MODEL = "data\\MODEL\\wood.x";				// �؂̃��f��
}

//-------------------------------------------
// �ÓI�����o�ϐ��錾
//-------------------------------------------
CListManager<CMobTree*> CMobTree::m_list = {};			// ���X�g���

//=========================
// �I�[�o�[���[�h�R���X�g���N�^
//=========================
CMobTree::CMobTree() : CModel(TYPE_TREE, PRIORITY_ENTITY)
{
	// �S�Ă̒l���N���A����
	m_pLeaf = nullptr;		// �t�̃��f��
	m_nFloweringCount = 0;	// �炭�܂ł̃J�E���g

	// ���X�g�ɒǉ�����
	m_list.Regist(this);
}

//=========================
// �f�X�g���N�^
//=========================
CMobTree::~CMobTree()
{

}

//=========================
// ����������
//=========================
HRESULT CMobTree::Init(void)
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
void CMobTree::Uninit(void)
{
	if (m_pLeaf != nullptr)
	{ // �t�� NULL ����Ȃ��ꍇ

		// �I������
		m_pLeaf->Uninit();
		m_pLeaf = nullptr;
	}

	// �I��
	CModel::Uninit();

	// ������������
	m_list.Pull(this);
}

//=========================
// �X�V����
//=========================
void CMobTree::Update(void)
{
	if (m_nFloweringCount <= 0)
	{ // �J�ԃJ�E���g��0�ȉ��̏ꍇ

		if (m_pLeaf != nullptr)
		{ // �t���ς� NULL ����Ȃ��ꍇ

			// �X�V����
			m_pLeaf->Update();
		}
	}
	else
	{ // ��L�ȊO

		// �J�ԃJ�E���g�����Z����
		m_nFloweringCount--;
	}
}

//=========================
// �`�揈��
//=========================
void CMobTree::Draw(void)
{
	// �`�揈��
	CModel::Draw();

	if (m_pLeaf != nullptr)
	{ // �t�� NULL ����Ȃ��ꍇ

		// �`�揈��
		m_pLeaf->Draw();
	}
}

//=========================
// ���̐ݒ菈��
//=========================
void CMobTree::SetData(const D3DXVECTOR3& pos, const int nCount)
{
	// �X�N���[���̐ݒ菈��
	SetPos(pos);					// �ʒu
	SetPosOld(pos);					// �O��̈ʒu
	SetRot(NONE_D3DXVECTOR3);		// ����
	SetScale(SCALE);				// �g�嗦
	SetFileData(CManager::Get()->GetXFile()->Regist(TREE_MODEL));

	// �S�Ă̒l��ݒ肷��
	if (m_pLeaf == nullptr)
	{ // �t�� NULL �̏ꍇ

		// �t�𐶐�
		m_pLeaf = CMobTreeLeaf::Create(pos + LEAF_SHIFT);
	}
	m_nFloweringCount = nCount;	// �炭�܂ł̃J�E���g
}

//=========================
// �v���C���[�Ƃ̏Փˎ�����
//=========================
void CMobTree::SnowBallHit(void)
{
	if (m_pLeaf != nullptr)
	{ // �t�� NULL ����Ȃ��ꍇ

		// ��ʂƂ̏Փˎ�����
		m_pLeaf->SnowBallHit();
	}
}

//=========================
// ��������
//=========================
CMobTree* CMobTree::Create(const D3DXVECTOR3& pos, const int nCount)
{
	// ���[�J���I�u�W�F�N�g�𐶐�
	CMobTree* pTree = nullptr;	// �؂̃C���X�^���X�𐶐�

	if (pTree == nullptr)
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// �I�u�W�F�N�g�𐶐�
		pTree = new CMobTree;
	}
	else
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// ��~
		assert(false);

		// NULL ��Ԃ�
		return nullptr;
	}

	if (pTree != nullptr)
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// ����������
		if (FAILED(pTree->Init()))
		{ // �������Ɏ��s�����ꍇ

			// ��~
			assert(false);

			// NULL ��Ԃ�
			return nullptr;
		}

		// ���̐ݒ菈��
		pTree->SetData(pos, nCount);
	}
	else
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// ��~
		assert(false);

		// NULL ��Ԃ�
		return nullptr;
	}

	// �؂̃|�C���^��Ԃ�
	return pTree;
}

//=======================================
// ���X�g�̎擾����
//=======================================
CListManager<CMobTree*> CMobTree::GetList(void)
{
	// ���X�g�\���̏���Ԃ�
	return m_list;
}