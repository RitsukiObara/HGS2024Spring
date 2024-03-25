//=======================================
//
// �v���C���[�̃��C������[player.cpp]
// Author ��������
//
//=======================================
#include "manager.h"
#include "input.h"
#include "player.h"
#include "useful.h"

// �萔��`
namespace
{
	const D3DXVECTOR3 POS = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// �ʒu
	const char* MODEL = "data\\MODEL\\Platform\\Ripple.x";		// ���f��
	const float SPEED = 10.0f;					// ���x
}

//=========================
// �I�[�o�[���[�h�R���X�g���N�^
//=========================
CPlayer::CPlayer() : CModel(TYPE_PLAYER, PRIORITY_PLAYER)
{

}

//=========================
// �f�X�g���N�^
//=========================
CPlayer::~CPlayer()
{

}

//=========================
// ����������
//=========================
HRESULT CPlayer::Init(void)
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
void CPlayer::Uninit(void)
{
	// �I��
	CModel::Uninit();
}

//=========================
// �X�V����
//=========================
void CPlayer::Update(void)
{
	// ���쏈��
	Control();
}

//=========================
// �`�揈��
//=========================
void CPlayer::Draw(void)
{
	// �`�揈��
	CModel::Draw();
}

//=========================
// ���̐ݒ菈��
//=========================
void CPlayer::SetData(void)
{
	// �X�N���[���̐ݒ菈��
	SetPos(POS);								// �ʒu
	SetPosOld(POS);								// �O��̈ʒu
	SetRot(NONE_D3DXVECTOR3);					// ����
	SetScale(NONE_SCALE);						// �g�嗦
	SetFileData(CManager::Get()->GetXFile()->Regist(MODEL));
}

//=========================
// ��������
//=========================
CPlayer* CPlayer::Create(void)
{
	// ���[�J���I�u�W�F�N�g�𐶐�
	CPlayer* pPlayer = nullptr;	// �v���C���[�̃C���X�^���X�𐶐�

	if (pPlayer == nullptr)
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// �I�u�W�F�N�g�𐶐�
		pPlayer = new CPlayer;
	}
	else
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// ��~
		assert(false);

		// NULL ��Ԃ�
		return nullptr;
	}

	if (pPlayer != nullptr)
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// ����������
		if (FAILED(pPlayer->Init()))
		{ // �������Ɏ��s�����ꍇ

			// ��~
			assert(false);

			// NULL ��Ԃ�
			return nullptr;
		}

		// ���̐ݒ菈��
		pPlayer->SetData();
	}
	else
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// ��~
		assert(false);

		// NULL ��Ԃ�
		return nullptr;
	}

	// �v���C���[�̃|�C���^��Ԃ�
	return pPlayer;
}

//=========================
// ���쏈��
//=========================
void CPlayer::Control(void)
{
	// ���[�J���ϐ���錾����
	D3DXVECTOR3 pos = GetPos();	// �ʒu
	D3DXVECTOR3 rot = GetRot();	// ����
	float fStickRotX = 0.0f;	// �X�e�B�b�N��X���W
	float fStickRotY = 0.0f;	// �X�e�B�b�N��Y���W
	float fStickRot = 0.0f;		// �X�e�B�b�N�̌���

	// �X�e�B�b�N�̌��������
	fStickRotY = (float)(CManager::Get()->GetInputGamePad()->GetGameStickLYPress(0));
	fStickRotX = (float)(CManager::Get()->GetInputGamePad()->GetGameStickLXPress(0));

	if (fStickRotY != 0 ||
		fStickRotX != 0)
	{ // �E�X�e�B�b�N���ǂ������ɓ|�����ꍇ

		// �X�e�B�b�N�̌�����ݒ肷��
		fStickRot = atan2f(fStickRotX, fStickRotY);

		// �����̐��K��
		useful::RotNormalize(&fStickRot);

		// �ړ�������
		pos.x += sinf(fStickRot) * SPEED;
		pos.z += cosf(fStickRot) * SPEED;

		// ������ݒ肷��
		rot.y = fStickRot;
	}

	// �ʒu��������K�p
	SetPos(pos);
	SetRot(rot);
}