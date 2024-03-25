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

#include "snowball.h"

//=======================================
// �萔��`
//=======================================
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
	if (CManager::Get()->GetInputGamePad()->GetConnect() == true)
	{ // �R���g���[���[���q�����Ă���ꍇ

		// ���쏈��
		Control();
	}
	else
	{ // ��L�ȊO

		// �L�[�{�[�h����
		Keyboard();
	}

	// �ˌ�����
	Shot();
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

//=========================
// �L�[�{�[�h����
//=========================
void CPlayer::Keyboard(void)
{
	// ���[�J���ϐ���錾����
	D3DXVECTOR3 pos = GetPos();		// �ʒu
	D3DXVECTOR3 rot = GetRot();		// ����
	float fMoveX = 0.0f;			// X���̈ړ���
	float fMoveZ = 0.0f;			// Z���̈ړ���
	float fStickRot = 0.0f;			// ����

	if (CManager::Get()->GetInputKeyboard()->GetPress(DIK_W) == true)
	{ // W�L�[���������ꍇ

		// Z���̈ړ��ʂ�ݒ肷��
		fMoveZ = 1.0f;
	}

	if (CManager::Get()->GetInputKeyboard()->GetPress(DIK_S) == true)
	{ // S�L�[���������ꍇ

		// Z���̈ړ��ʂ�ݒ肷��
		fMoveZ = -1.0f;
	}

	if (CManager::Get()->GetInputKeyboard()->GetPress(DIK_A) == true)
	{ // A�L�[���������ꍇ

		// X���̈ړ��ʂ�ݒ肷��
		fMoveX = -1.0f;
	}

	if (CManager::Get()->GetInputKeyboard()->GetPress(DIK_D) == true)
	{ // D�L�[���������ꍇ

		// X���̈ړ��ʂ�ݒ肷��
		fMoveX = 1.0f;
	}

	if (fMoveX != 0 ||
		fMoveZ != 0)
	{ // �E�X�e�B�b�N���ǂ������ɓ|�����ꍇ

		// �X�e�B�b�N�̌�����ݒ肷��
		fStickRot = atan2f(fMoveX, fMoveZ);

		// �����̐��K��
		useful::RotNormalize(&fStickRot);

		// �ړ�������
		pos.x += sinf(fStickRot) * SPEED;
		pos.z += cosf(fStickRot) * SPEED;

		// ������ݒ肷��
		rot.y = fStickRot;
	}

	// �ʒu�ƌ�����ݒ肷��
	SetPos(pos);
	SetRot(rot);
}

//=========================
// �ˌ�����
//=========================
void CPlayer::Shot(void)
{
	if (CManager::Get()->GetInputGamePad()->GetTrigger(CInputGamePad::JOYKEY_A, 0) == true ||
		CManager::Get()->GetInputKeyboard()->GetTrigger(DIK_SPACE) == true)
	{ // �ˌ�����

		// ��ʂ̐���
		CSnowBall::Create(GetPos(), GetRot());
	}
}