//=======================================
//
// �G�̃��C������[enemy.cpp]
// Author ��������
//
//=======================================
#include "manager.h"
#include "enemy.h"
#include "useful.h"

#include "game.h"
#include "base.h"

//=======================================
// �萔��`
//=======================================
namespace
{
	const D3DXVECTOR3 SCALE = D3DXVECTOR3(2.5f, 2.5f, 2.5f);	// �g�嗦
	const char* MODEL = "data\\MODEL\\ENEMY\\enemy.x";			// �G�̃��f��
	const float MOVE_CORRECT = 0.001f;							// �ړ��ʂ̕␳��
	const int LIFE = 5;											// �̗�
	const D3DXCOLOR DAMAGE_COL = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);		// �_���[�W�̎��̐F
	const int DAMAGE_COUNT = 5;				// �_���[�W��Ԃ̃J�E���g��
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
	m_move = NONE_D3DXVECTOR3;		// �ړ���
	m_nLife = LIFE;					// �̗�
	m_bDamage = false;				// �_���[�W��

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

		// �i�s���
		Progress();

		break;

	case CEnemy::STATE_CATCH:			// �L���b�`���

		break;

	case CEnemy::STATE_RETURN:			// �A�ҏ��


		break;

	default:
		
		// ��~
		assert(false);

		break;
	}

	if (m_bDamage == true)
	{ // �_���[�W�󋵂� true �̏ꍇ

		// �_���[�W�J�E���g�����Z����
		m_nDamageCount++;

		if (m_nDamageCount >= DAMAGE_COUNT)
		{ // �_���[�W�J�E���g����萔�ȏ�ɂȂ����ꍇ

			// �_���[�W�J�E���g��0�ɂ���
			m_nDamageCount = 0;

			// �_���[�W�󋵂� false �ɂ���
			m_bDamage = false;
		}
	}
}

//=========================
// �`�揈��
//=========================
void CEnemy::Draw(void)
{
	if (m_bDamage == true)
	{ // �_���[�W�󋵂� true �̏ꍇ

		// �`�揈��
		CModel::Draw(DAMAGE_COL);
	}
	else
	{ // ��L�ȊO

		// �`�揈��
		CModel::Draw();
	}
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

	// �S�Ă̒l��ݒ肷��
	m_state = STATE_PROGRESS;		// ���
	m_nLife = LIFE;					// �̗�
	m_bDamage = false;				// �_���[�W��

	// ���_�̃|�C���^���擾
	CBase* pBase = CGame::GetBase();

	if (pBase != nullptr)
	{ // ���_�����݂���ꍇ

		// �ړ��ʂ̐ݒ菈��
		MoveSet(pBase->GetPos());
	}
}

//=========================
// �q�b�g����
//=========================
void CEnemy::Hit(void)
{
	// �̗͂����Z����
	m_nLife--;

	if (m_nLife <= 0)
	{ // �̗͂�0�ȉ��ɂȂ����ꍇ

		// �I������
		Uninit();

		// ���̐�̏������s��Ȃ�
		return;
	}
	else
	{ // ��L�ȊO

		// �_���[�W�󋵂� true �ɂ���
		m_bDamage = true;				// �_���[�W��
	}
}

//=========================
// �_���[�W�󋵂̎擾����
//=========================
bool CEnemy::IsDamage(void) const
{
	// �_���[�W�󋵂�Ԃ�
	return m_bDamage;
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

//=======================================
// �ړ��ʂ̐ݒ菈��
//=======================================
void CEnemy::MoveSet(const D3DXVECTOR3& posDest)
{
	// �ʒu���擾����
	D3DXVECTOR3 pos = GetPos();

	// �ړ��ʂ�ݒ�
	m_move.x = (posDest.x - pos.x) * MOVE_CORRECT;
	m_move.z = (posDest.z - pos.z) * MOVE_CORRECT;
}

//=======================================
// �i�s����
//=======================================
void CEnemy::Progress(void)
{
	// ���_�̃|�C���^���擾
	CBase* pBase = CGame::GetBase();

	if (pBase != nullptr)
	{ // ���_�����݂���ꍇ

		// �ʒu���擾����
		D3DXVECTOR3 posDest = pBase->GetPos();
		D3DXVECTOR3 pos = GetPos();
		D3DXVECTOR3 rot = GetRot();

		// ������ݒ肷��
		rot.y = atan2f(posDest.x - pos.x, posDest.z - pos.z);

		if (useful::FrameCorrect(posDest.x, &pos.x, m_move.x) == true ||
			useful::FrameCorrect(posDest.z, &pos.z, m_move.z) == true)
		{ // ���������ꍇ

			// �L���b�`��Ԃɂ���
			m_state = STATE_CATCH;
		}

		// �ʒu�ƌ�����K�p
		SetPos(pos);
		SetRot(rot);
	}
}