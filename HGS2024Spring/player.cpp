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
#include "game.h"
#include "camera.h"
#include "collision.h"

//=======================================
// �萔��`
//=======================================
namespace
{
	const D3DXVECTOR3 INIT_POS = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// �ʒu
	const D3DXVECTOR3 INIT_CAMERA_ROT = D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f);		// �J�����̏�������
	const D3DXVECTOR3 SCALE = D3DXVECTOR3(4.0f, 4.0f, 4.0f);		// �g�嗦
	const float CAMERA_ROT_CORRECT = 0.0000020f;		// �J�����̌����̕␳����
	const D3DXVECTOR3 SNOWBALL_POS = D3DXVECTOR3(0.0f, 100.0f, 0.0f);	// ��ʂ̏o��ʒu
	const char* MODEL = "data\\MODEL\\Player\\player.x";			// ���f��
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

	// �J�����̌����ݒ�
	CManager::Get()->GetCamera()->SetRot(INIT_CAMERA_ROT);

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

	// �v���C���[�̏I������
	CGame::DeletePlayer();
}

//=========================
// �X�V����
//=========================
void CPlayer::Update(void)
{
	// �O��̈ʒu��ݒ肷��
	SetPosOld(GetPos());

	// ���쏈��
	Control();

	// �J�����̑��쏈��
	Camera();

	// �ˌ�����
	Shot();

	//�؂Ƃ̓����蔻��
	collision::TreeHit(this);
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
	SetPos(INIT_POS);							// �ʒu
	SetPosOld(INIT_POS);						// �O��̈ʒu
	SetRot(NONE_D3DXVECTOR3);					// ����
	SetScale(SCALE);							// �g�嗦
	SetFileData(CManager::Get()->GetXFile()->Regist(MODEL));
}

//=========================
// �؂Ƃ̃q�b�g����
//=========================
void CPlayer::TreeHit(void)
{
	if (m_state != STATE_CARRY)
	{ // �^�я�Ԃ���Ȃ��ꍇ

		// �^�я�Ԃɂ���
		m_state = STATE_CARRY;
	}
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

		// �J�����̌��������Z����
		fStickRot += CManager::Get()->GetCamera()->GetRot().y;

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
// �J��������
//=========================
void CPlayer::Camera(void)
{
	D3DXVECTOR3 CameraRot = CManager::Get()->GetCamera()->GetRot();		// �J�����̌������擾����
	float fStickRotX, fStickRotY;		// �X�e�B�b�N�̌���

	// �E�X�e�B�b�N�̌X���x���擾����
	fStickRotX = CManager::Get()->GetInputGamePad()->GetGameStickRXPress(0);
	fStickRotY = CManager::Get()->GetInputGamePad()->GetGameStickRYPress(0);

	// �J�����̌��������Z����
	CameraRot.y += (fStickRotX * CAMERA_ROT_CORRECT);

	// �����̐��K��
	useful::RotNormalize(&CameraRot.y);

	// ������K�p����
	CManager::Get()->GetCamera()->SetRot(CameraRot);
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
		CSnowBall::Create(GetPos() + SNOWBALL_POS, GetRot());
	}
}