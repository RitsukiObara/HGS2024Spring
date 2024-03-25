//=======================================
//
// �G�̃��C������[enemy.cpp]
// Author ��������
//
//=======================================
#include "manager.h"
#include "enemy.h"
#include "useful.h"

//=======================================
// �萔��`
//=======================================
namespace
{
	const D3DXVECTOR3 SCALE = D3DXVECTOR3(2.5f, 2.5f, 2.5f);		// �g�嗦
	const char* MODEL = "data\\MODEL\\ENEMY\\enemy.x";		// �G�̃��f��
}

//-------------------------------------------
// �ÓI�����o�ϐ��錾
//-------------------------------------------
CListManager<CEnemy*> CEnemy::m_list = {};			// ���X�g���

//=========================
// �I�[�o�[���[�h�R���X�g���N�^
//=========================
CEnemy::CEnemy() : CModel(TYPE_PLAYER, PRIORITY_PLAYER)
{
	// �S�Ă̒l���N���A����
	m_state = STATE_PROGRESS;		// ���

	// ���X�g�ɒǉ�����
	m_list.Regist(this);
}

//=========================
// �f�X�g���N�^
//=========================
CEnemy::~CEnemy()
{

}

//=========================
// ����������
//=========================
HRESULT CEnemy::Init(void)
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
void CEnemy::Uninit(void)
{
	// �I��
	CModel::Uninit();

	// ������������
	m_list.Pull(this);
}

//=========================
// �X�V����
//=========================
void CEnemy::Update(void)
{
	switch (m_state)
	{
	case CEnemy::STATE_PROGRESS:		// �i�s���



		break;

	case CEnemy::STATE_RETURN:			// �A�ҏ��


		break;

	default:
		
		// ��~
		assert(false);

		break;
	}
}

//=========================
// �`�揈��
//=========================
void CEnemy::Draw(void)
{
	// �`�揈��
	CModel::Draw();
}

//=========================
// ���̐ݒ菈��
//=========================
void CEnemy::SetData(const D3DXVECTOR3& pos)
{
	// �X�N���[���̐ݒ菈��
	SetPos(pos);							// �ʒu
	SetPosOld(pos);							// �O��̈ʒu
	SetRot(NONE_D3DXVECTOR3);				// ����
	SetScale(SCALE);						// �g�嗦
	SetFileData(CManager::Get()->GetXFile()->Regist(MODEL));
}

//=========================
// ��������
//=========================
CEnemy* CEnemy::Create(const D3DXVECTOR3& pos)
{
	// ���[�J���I�u�W�F�N�g�𐶐�
	CEnemy* pEnemy = nullptr;	// �G�̃C���X�^���X�𐶐�

	if (pEnemy == nullptr)
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// �I�u�W�F�N�g�𐶐�
		pEnemy = new CEnemy;
	}
	else
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// ��~
		assert(false);

		// NULL ��Ԃ�
		return nullptr;
	}

	if (pEnemy != nullptr)
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// ����������
		if (FAILED(pEnemy->Init()))
		{ // �������Ɏ��s�����ꍇ

			// ��~
			assert(false);

			// NULL ��Ԃ�
			return nullptr;
		}

		// ���̐ݒ菈��
		pEnemy->SetData(pos);
	}
	else
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// ��~
		assert(false);

		// NULL ��Ԃ�
		return nullptr;
	}

	// �G�̃|�C���^��Ԃ�
	return pEnemy;
}

//=======================================
// ���X�g�̎擾����
//=======================================
CListManager<CEnemy*> CEnemy::GetList(void)
{
	// ���X�g�\���̏���Ԃ�
	return m_list;
}