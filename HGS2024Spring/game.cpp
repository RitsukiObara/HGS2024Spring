//============================================
//
// �Q�[���̃��C������[game.cpp]
// Author�F��������
//
//============================================
//********************************************
// �C���N���[�h�t�@�C��
//********************************************
#include "manager.h"
#include "input.h"
#include "game.h"
#include "fade.h"
#include "file.h"
#include "renderer.h"
#include "texture.h"

#include "pause.h"
#include "debugproc.h"
#include "sound.h"

#include "objectElevation.h"
#include "ocean.h"
#include "map.h"
#include "mob_tree.h"
#include "player.h"
#include "enemy.h"
#include "enemy_home.h"
#include "base.h"
#include "skybox.h"
#include "gauge.h"
#include "timer.h"
#include "CaveatDirection.h"

//--------------------------------------------
// �}�N����`
//--------------------------------------------
#define TRANS_COUNT		(80)		// �������̑J�ڃJ�E���g

//--------------------------------------------
// �ÓI�����o�ϐ��錾
//--------------------------------------------
CPause* CGame::m_pPause = nullptr;							// �|�[�Y�̏��
CPlayer* CGame::m_pPlayer = nullptr;						// �v���C���[�̏��
CBase* CGame::m_pBase = nullptr;							// ���_�̏��
CGame::STATE CGame::m_GameState = CGame::STATE_START;		// �Q�[���̐i�s���
int CGame::m_nFinishCount = 0;								// �I���J�E���g
bool CGame::m_bPause = false;								// �|�[�Y��

//=========================================
// �R���X�g���N�^
//=========================================
CGame::CGame()
{
	// �S�Ă̒l���N���A����
	m_pPause = nullptr;			// �|�[�Y
	m_pPlayer = nullptr;		// �v���C���[
	m_pBase = nullptr;			// ���_
	m_nFinishCount = 0;			// �I���J�E���g
	m_GameState = STATE_START;	// ���
	m_bPause = false;			// �|�[�Y��
}

//=========================================
// �f�X�g���N�^
//=========================================
CGame::~CGame()
{

}

//=========================================
//����������
//=========================================
HRESULT CGame::Init(void)
{
	// �X�J�C�{�b�N�X�̐�������
	CSkyBox::Create();

	// �C�̐���
	COcean::Create();

	// �}�b�v�̐���
	CMap::Create();

	// �؂̐���
	CMobTree::Create(D3DXVECTOR3(-1700.0f, 0.0f, -1820.0f), 0, 1);
	CMobTree::Create(D3DXVECTOR3(-1230.0f, 0.0f, -1200.0f), 1000, 1);
	CMobTree::Create(D3DXVECTOR3(-690.0f, 0.0f, -980.0f), 2000, 1);
	CMobTree::Create(D3DXVECTOR3(-800.0f, 0.0f, -625.0f), 3000, 2);
	CMobTree::Create(D3DXVECTOR3(-130.0f, 0.0f, -740.0f), 4000, 2);
	CMobTree::Create(D3DXVECTOR3(345.0f, 0.0f, -520.0f), 5000, 2);
	CMobTree::Create(D3DXVECTOR3(735.0f, 0.0f, 75.0f), 6000, 3);

	// �v���C���[�̐���
	m_pPlayer = CPlayer::Create();

	// ���_�̐���
	m_pBase = CBase::Create();

	// �G�̋��_�̐���
	CEnemyHome::Create(D3DXVECTOR3(-900.0f, 200.0f, 800.0f), D3DXVECTOR3(0.0f, -0.5f, D3DX_PI * -0.6f));
	CEnemyHome::Create(D3DXVECTOR3(1700.0f, 200.0f, 100.0f), D3DXVECTOR3(0.0f, -1.4f, D3DX_PI * -0.6f));

	// �Q�[�W�̐���
	CGauge::Create();

	// �^�C�}�[�̐���
	CTimer::Create();

	CCaveatDirection::Create();

	// �V�[���̏�����
	CScene::Init();

	// ���̏�����
	m_nFinishCount = 0;				// �I���J�E���g
	m_GameState = STATE_START;		// ���
	m_bPause = false;				// �|�[�Y��

	// ������Ԃ�
	return S_OK;
}

//=============================================
//�I������
//=============================================
void CGame::Uninit(void)
{
	// �|�C���^�� NULL �ɂ���
	if (m_pPause != nullptr)
	{ // �|�[�Y�� NULL ����Ȃ��ꍇ

		// �|�[�Y�̏I������
		m_pPause->Uninit();
	}

	m_pPlayer = nullptr;		// �v���C���[
	m_pBase = nullptr;			// ���_

	// ��������������
	m_bPause = false;			// �|�[�Y��

	// �I���J�E���g������������
	m_nFinishCount = 0;

	// �I������
	CScene::Uninit();
}

//======================================
//�X�V����
//======================================
void CGame::Update(void)
{
	switch (m_GameState)
	{
	case CGame::STATE_START:

		// �|�[�Y����
		Pause();

		break;

	case CGame::STATE_PLAY:

		// �|�[�Y����
		Pause();

		break;

	case CGame::STATE_CLEAR:

		// �J�ڏ���
		Transition();

		break;

	case CGame::STATE_GAMEOVER:

		// �J�ڏ���
		Transition();

		break;

	default:

		// ��~
		assert(false);

		break;
	}

	//if (CManager::Get()->GetInputKeyboard()->GetTrigger(DIK_RETURN) == true ||
	//	CManager::Get()->GetInputGamePad()->GetTrigger(CInputGamePad::JOYKEY_START, 0) == true ||
	//	CManager::Get()->GetInputGamePad()->GetTrigger(CInputGamePad::JOYKEY_A, 0) == true)
	//{ // ENTER�L�[���������ꍇ

	//	// ���U���g�ɑJ�ڂ���
	//	CManager::Get()->GetFade()->SetFade(CScene::MODE_RESULT);

	//	// ���̐�̏������s��Ȃ�
	//	return;
	//}

	if (m_bPause == true)
	{ // �|�[�Y�󋵂� true �̏ꍇ

		// �X�V����
		m_pPause->Update();
	}
	else
	{ // ��L�ȊO

		if (CManager::Get()->GetRenderer() != nullptr)
		{ // �����_���[�� NULL ����Ȃ��ꍇ

			// �����_���[�̍X�V
			CManager::Get()->GetRenderer()->Update();
		}
	}

	CManager::Get()->GetDebugProc()->Print("��ԁF%d", m_GameState);
}

//======================================
//�`�揈��
//======================================
void CGame::Draw(void)
{
	if (m_pPause != nullptr &&
		m_bPause == true)
	{ // �|�[�Y���̏ꍇ

		// �`�揈��
		m_pPause->Draw();
	}
}

//======================================
// ���̐ݒ菈��
//======================================
void CGame::SetData(const MODE mode)
{
	// ���̐ݒ菈��
	CScene::SetData(mode);

	// �S�Ă̒l��ݒ肷��
	m_GameState = STATE_START;	// �X�^�[�g��Ԃɂ���
	m_bPause = false;			// �|�[�Y��

	// ���̏�����
	m_nFinishCount = 0;				// �I���J�E���g
}

//======================================
// �|�[�Y����
//======================================
void CGame::Pause(void)
{
	if (CManager::Get()->GetInputKeyboard()->GetTrigger(DIK_P) == true ||
		CManager::Get()->GetInputGamePad()->GetTrigger(CInputGamePad::JOYKEY_BACK, 0) == true)
	{ // P�L�[���������ꍇ

		if (CManager::Get()->GetFade()->GetFade() == CFade::FADE_NONE)
		{ // �t�F�[�h������Ԃ��A�I���ȊO�̏ꍇ

			if (m_bPause == false)
			{ // �|�[�Y�� false �������ꍇ

				if (m_pPause == nullptr)
				{ // �|�[�Y�ւ̃|�C���^�� NULL �̏ꍇ

					// �|�[�Y�̐�������
					m_pPause = CPause::Create();
				}
				else
				{ // ��L�ȊO
					
					// ��~
					assert(false);
				}

				// �|�[�Y�󋵂� true �ɂ���
				m_bPause = true;
			}
			else
			{ // �|�[�Y�� true �������ꍇ

				if (m_pPause != nullptr)
				{ // �|�[�Y�ւ̃|�C���^�� NULL ����Ȃ��ꍇ

					// �I������
					m_pPause->Uninit();
					m_pPause = nullptr;
				}

				// �|�[�Y�󋵂� false �ɂ���
				m_bPause = false;
			}

			// ���艹��炷
			CManager::Get()->GetSound()->Play(CSound::SOUND_LABEL_SE_DECIDE);
		}
	}
}

//======================================
// �J�ڏ���
//======================================
void CGame::Transition(void)
{
	// �I���J�E���g�����Z����
	m_nFinishCount++;

	if (m_nFinishCount % TRANS_COUNT == 0)
	{ // �I���J�E���g����萔�𒴂����ꍇ

		// ���U���g�ɑJ�ڂ���
		CManager::Get()->GetFade()->SetFade(CScene::MODE_RESULT);
	}
}

//======================================
// �|�[�Y�󋵂̐ݒ菈��
//======================================
void CGame::SetEnablePause(const bool bPause)
{
	// �|�[�Y�󋵂�ݒ肷��
	m_bPause = bPause;
}

//======================================
// �|�[�Y�󋵂̎擾����
//======================================
bool CGame::IsPause(void)
{
	// �|�[�Y�󋵂��擾����
	return m_bPause;
}

//======================================
// �Q�[���̐i�s��Ԃ̐ݒ菈��
//======================================
void CGame::SetState(const STATE state)
{
	// �Q�[���̐i�s��Ԃ�ݒ肷��
	m_GameState = state;
}

//======================================
// �Q�[���̐i�s��Ԃ̎擾����
//======================================
CGame::STATE CGame::GetState(void)
{
	// �Q�[���̐i�s��Ԃ�Ԃ�
	return m_GameState;
}

//======================================
// �v���C���[�̎擾����
//======================================
CPlayer* CGame::GetPlayer(void)
{
	// �v���C���[�̏���Ԃ�
	return m_pPlayer;
}

//======================================
// ���_�̎擾����
//======================================
CBase* CGame::GetBase(void)
{
	// ���_�̏���Ԃ�
	return m_pBase;
}

//======================================
// �|�[�Y��NULL������
//======================================
void CGame::DeletePause(void)
{
	// �|�[�Y�̃|�C���^�� NULL �ɂ���
	m_pPause = nullptr;
}

//======================================
// �v���C���[��NULL������
//======================================
void CGame::DeletePlayer(void)
{
	// �v���C���[�̃|�C���^�� NULL �ɂ���
	m_pPlayer = nullptr;
}

//======================================
// ���_��NULL������
//======================================
void CGame::DeleteBase(void)
{
	// ���_�� NULL �ɂ���
	m_pBase = nullptr;
}