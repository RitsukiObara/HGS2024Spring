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
#include "base_flower.h"

//=======================================
// �萔��`
//=======================================
namespace
{
	const D3DXVECTOR3 POS = D3DXVECTOR3(1100.0f, 0.0f, 1300.0f);		// �ʒu
	const char* MODEL = "data\\MODEL\\ayakasi.x";		// ���f��
	const float FLOWERPOINT_HEIGHT = 500.0f;			// �Ԃ��炭����
}

//=========================
// �I�[�o�[���[�h�R���X�g���N�^
//=========================
CBase::CBase() : CModel(TYPE_BASE, PRIORITY_ENTITY)
{
	// �S�Ă̒l���N���A����
	m_pPosVtx = nullptr;		// ���_�̃|�C���^
	m_nNumVtx = 0;				// ���_��
	m_nNowFlowPoint = 0;		// ���ݍ炢�Ă���|�C���g
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
	// �J�ԃ|�C���g��j������
	delete[] m_pPosVtx;

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
	SetScale(NONE_SCALE);			// �g�嗦
	SetFileData(CManager::Get()->GetXFile()->Regist(MODEL));

	// ���f���̒��_�����擾
	int nNumFlowPoint = 0;
	int nNowPoint = 0;
	m_nNumVtx = GetFileData().pMesh->GetNumVertices();

	for (int nCnt = 0; nCnt < m_nNumVtx; nCnt++)
	{
		if (GetPos().y + GetFileData().vtxPos[nCnt].y >= FLOWERPOINT_HEIGHT)
		{ // ���̒��_���ȏ�̏ꍇ

			// �J�ԃ|�C���g�����Z����
			nNumFlowPoint++;
		}
	}

	// �S�Ă̒l��ݒ肷��
	m_pPosVtx = new D3DXVECTOR3[nNumFlowPoint];	// �J�Ԃ����钸�_

	for (int nCnt = 0; nCnt < m_nNumVtx; nCnt++)
	{
		if (GetPos().y + GetFileData().vtxPos[nCnt].y >= FLOWERPOINT_HEIGHT)
		{ // ���̒��_���ȏ�̏ꍇ

			// �J�ԃ|�C���g�����Z����
			m_pPosVtx[nNowPoint] = GetFileData().vtxPos[nCnt];

			// ���݂̃|�C���g�����Z����
			nNowPoint++;
		}
	}

	// ���_�����Đݒ肷��
	m_nNumVtx = nNumFlowPoint;
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

//=========================
// �J�ԏ���
//=========================
void CBase::Flowering(void)
{
	for (int nCnt = m_nNowFlowPoint; nCnt < m_nNowFlowPoint + 170; nCnt++)
	{
		// �Ԃ̐���
		CBaseFlower::Create(GetPos() + m_pPosVtx[nCnt]);
	}

	// ���ݍ炢�Ă���|�C���g�����Z����
	m_nNowFlowPoint += 170;
}