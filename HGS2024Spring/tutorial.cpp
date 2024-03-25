//============================================
//
// �`���[�g���A����ʂ̃��C������[tutorial.cpp]
// Author�F��������
//
//============================================
//********************************************
// �C���N���[�h�t�@�C��
//********************************************
#include "manager.h"
#include "tutorial.h"
#include "fade.h"
#include "renderer.h"
#include "tutorial_polygon.h"

// �}�N����`
#define TRANS_COUNT				(120)									// �J�ڂ܂ł̃J�E���g��

//==========================================
//  �ÓI�����o�ϐ��錾
//==========================================
CTutorialPolygon* CTutorial::m_pPolygon = nullptr;

//=========================================
// �R���X�g���N�^
//=========================================
CTutorial::CTutorial()
{
	// �S�Ă̏����N���A����
	m_nEndCount = 0;			// �I���܂ł̃J�E���g
}

//=========================================
// �f�X�g���N�^
//=========================================
CTutorial::~CTutorial()
{

}

//=========================================
//����������
//=========================================
HRESULT CTutorial::Init(void)
{
	// �V�[���̏�����
	CScene::Init();

	// �摜�𐶐�
	m_pPolygon = CTutorialPolygon::Create();

	// �S�Ă̒l���N���A����
	m_nEndCount = 0;			// �I���܂ł̃J�E���g

	// ������Ԃ�
	return S_OK;
}

//=============================================
//�I������
//=============================================
void CTutorial::Uninit(void)
{
	// �|���S���̏I��
	if (m_pPolygon != nullptr)
	{
		m_pPolygon = nullptr;
	}

	// �I������
	CScene::Uninit();
}

//======================================
//�X�V����
//======================================
void CTutorial::Update(void)
{
	// �I���J�E���g�����Z����
	m_nEndCount++;

	if (m_nEndCount >= TRANS_COUNT && m_pPolygon->GetEnd())
	{ // �X�L�b�v���܂��́A�I�����̏ꍇ

		// �Q�[�����[�h�ɂ���
		CManager::Get()->GetFade()->SetFade(MODE_GAME);
	}

	if (CManager::Get()->GetRenderer() != nullptr)
	{ // �����_���[�� NULL ����Ȃ��ꍇ

		// �X�V����
		CManager::Get()->GetRenderer()->Update();
	}
}

//======================================
//�`�揈��
//======================================
void CTutorial::Draw(void)
{

}

//======================================
// ���̐ݒ菈��
//======================================
void CTutorial::SetData(const MODE mode)
{
	// ���̐ݒ菈��
	CScene::SetData(mode);
}