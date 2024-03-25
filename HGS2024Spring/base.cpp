//=======================================
//
// ���_�̃��C������[base.cpp]
// Author ��������
//
//=======================================
#include "manager.h"
#include "base.h"
#include "useful.h"

#include "game.h"

//=======================================
// �萔��`
//=======================================
namespace
{
	const D3DXVECTOR3 POS = D3DXVECTOR3(1100.0f, 0.0f, 1300.0f);		// �ʒu
	const D3DXVECTOR3 SCALE = D3DXVECTOR3(7.0f, 7.0f, 7.0f);		// �g�嗦
	const char* MODEL = "data\\MODEL\\wood.x";		// ���f��
}

//=========================
// �I�[�o�[���[�h�R���X�g���N�^
//=========================
CBase::CBase() : CModel(TYPE_BASE, PRIORITY_ENTITY)
{

}

//=========================
// �f�X�g���N�^
//=========================
CBase::~CBase()
{

}

//=========================
// ����������
//=========================
HRESULT CBase::Init(void)
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
void CBase::Uninit(void)
{
	// �I��
	CModel::Uninit();

	// ���_��NULL������
	CGame::DeleteBase();
}

//=========================
// �X�V����
//=========================
void CBase::Update(void)
{

}

//=========================
// �`�揈��
//=========================
void CBase::Draw(void)
{
	// �`�揈��
	CModel::Draw();
}

//=========================
// ���̐ݒ菈��
//=========================
void CBase::SetData(void)
{
	// �X�N���[���̐ݒ菈��
	SetPos(POS);					// �ʒu
	SetPosOld(POS);					// �O��̈ʒu
	SetRot(NONE_D3DXVECTOR3);		// ����
	SetScale(SCALE);				// �g�嗦
	SetFileData(CManager::Get()->GetXFile()->Regist(MODEL));
}

//=========================
// ��������
//=========================
CBase* CBase::Create(void)
{
	// ���[�J���I�u�W�F�N�g�𐶐�
	CBase* pTree = nullptr;	// �؂̃C���X�^���X�𐶐�

	if (pTree == nullptr)
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// �I�u�W�F�N�g�𐶐�
		pTree = new CBase;
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
		pTree->SetData();
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