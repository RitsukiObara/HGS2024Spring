//=======================================
//
// �G�̃z�[���̃��C������[enemy_home.cpp]
// Author ��������
//
//=======================================
#include "manager.h"
#include "enemy_home.h"

#include "enemy.h"

//=======================================
// �萔��`
//=======================================
namespace
{
	const D3DXVECTOR3 SCALE = D3DXVECTOR3(2.0f, 2.0f, 2.0f);			// �g�嗦
	const char* MODEL = "data\\MODEL\\Enemy\\enemy_base.x";				// �G�̃z�[��
	const int ENEMY_INTERVAL = 600;			// �G�̏o��Ԋu
	const float ENEMY_HEIGHT = 100.0f;		// �G�̍���
}

//=========================
// �I�[�o�[���[�h�R���X�g���N�^
//=========================
CEnemyHome::CEnemyHome() : CModel(TYPE_ENEMYHOME, PRIORITY_ENTITY)
{

}

//=========================
// �f�X�g���N�^
//=========================
CEnemyHome::~CEnemyHome()
{

}

//=========================
// ����������
//=========================
HRESULT CEnemyHome::Init(void)
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
void CEnemyHome::Uninit(void)
{
	// �I��
	CModel::Uninit();
}

//=========================
// �X�V����
//=========================
void CEnemyHome::Update(void)
{
	// �G�̏o��J�E���g�����Z����
	m_nEnemyCount++;

	if (m_nEnemyCount % ENEMY_INTERVAL == 0)
	{ // �G�̏o��J�E���g����萔�̏ꍇ

		D3DXVECTOR3 pos = GetPos();

		// �G�̍�����ݒ肷��
		pos.y = ENEMY_HEIGHT;

		// �G�̐�������
		CEnemy::Create(pos);

		// �G�̏o��J�E���g��0�ɂ���
		m_nEnemyCount = 0;
	}
}

//=========================
// �`�揈��
//=========================
void CEnemyHome::Draw(void)
{
	// �`�揈��
	CModel::Draw();
}

//=========================
// ���̐ݒ菈��
//=========================
void CEnemyHome::SetData(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot)
{
	// �X�N���[���̐ݒ菈��
	SetPos(pos);			// �ʒu
	SetPosOld(pos);			// �O��̈ʒu
	SetRot(rot);			// ����
	SetScale(SCALE);		// �g�嗦
	SetFileData(CManager::Get()->GetXFile()->Regist(MODEL));
}

//=========================
// ��������
//=========================
CEnemyHome* CEnemyHome::Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot)
{
	// ���[�J���I�u�W�F�N�g�𐶐�
	CEnemyHome* pEnemy = nullptr;	// �G�̃z�[���̃C���X�^���X�𐶐�

	if (pEnemy == nullptr)
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// �I�u�W�F�N�g�𐶐�
		pEnemy = new CEnemyHome;
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
		pEnemy->SetData(pos, rot);
	}
	else
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// ��~
		assert(false);

		// NULL ��Ԃ�
		return nullptr;
	}

	// �G�̃z�[���̃|�C���^��Ԃ�
	return pEnemy;
}