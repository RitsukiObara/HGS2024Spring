//=======================================
//
// 2D�G�t�F�N�g�̃��C������[effect2D.cpp]
// Author ��������
//
//=======================================
#include "manager.h"
#include "result_logo.h"
#include "renderer.h"
#include "texture.h"
#include "useful.h"

#include "game.h"

//=======================================
// �萔��`
//=======================================
namespace
{
	const D3DXVECTOR3 POS = D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f);		// �ʒu
	const D3DXVECTOR3 POLY_SIZE = D3DXVECTOR3(530.0f, 140.0f, 0.0f);		// �T�C�Y
	const char* CLEAR_TEXTURE = "data\\TEXTURE\\gameclear00.png";		// �Q�[���N���A
	const char* GAMEOVER_TEXTURE = "data\\TEXTURE\\gameover00.png";	// �Q�[���I�[�o�[
}

//=========================
// �R���X�g���N�^
//=========================
CResultLogo::CResultLogo() : CObject2D(CObject2D::TYPE_RESULTLOGO, CObject::PRIORITY_UI)
{

}

//=========================
// �f�X�g���N�^
//=========================
CResultLogo::~CResultLogo()
{

}

//=========================
// ����������
//=========================
HRESULT CResultLogo::Init(void)
{
	if (FAILED(CObject2D::Init()))
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
void CResultLogo::Uninit(void)
{
	// �I��
	CObject2D::Uninit();
}

//=========================
// �X�V����
//=========================
void CResultLogo::Update(void)
{

}

//=========================
// �`�揈��
//=========================
void CResultLogo::Draw(void)
{
	// �`�揈��
	CObject2D::Draw();
}

//=========================
// ���̐ݒ菈��
//=========================
void CResultLogo::SetData(void)
{
	// �X�N���[���̐ݒ菈��
	SetPos(POS);				// �ʒu�ݒ�
	SetRot(NONE_D3DXVECTOR3);	// �����ݒ�
	SetSize(POLY_SIZE);			// �T�C�Y�ݒ�
	SetLength();				// �����ݒ�
	SetAngle();					// �����ݒ�

	// ���_���̏�����
	SetVertex();

	switch (CGame::GetState())
	{
	case CGame::STATE_CLEAR:

		// �e�N�X�`���̓ǂݍ��ݏ���
		BindTexture(CManager::Get()->GetTexture()->Regist(CLEAR_TEXTURE));

		break;

	case CGame::STATE_GAMEOVER:

		// �e�N�X�`���̓ǂݍ��ݏ���
		BindTexture(CManager::Get()->GetTexture()->Regist(GAMEOVER_TEXTURE));

		break;

	default:

		// ��~
		assert(false);

		break;
	}
}

//=========================
// ��������
//=========================
CResultLogo* CResultLogo::Create(void)
{
	// ���[�J���I�u�W�F�N�g�𐶐�
	CResultLogo* pLogo = nullptr;	// �v���C���[�̃C���X�^���X�𐶐�

	if (pLogo == nullptr)
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// �I�u�W�F�N�g�𐶐�
		pLogo = new CResultLogo;
	}
	else
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// ��~
		assert(false);

		// NULL ��Ԃ�
		return nullptr;
	}

	if (pLogo != nullptr)
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// ����������
		if (FAILED(pLogo->Init()))
		{ // �������Ɏ��s�����ꍇ

			// ��~
			assert(false);

			// NULL ��Ԃ�
			return nullptr;
		}

		// ���̐ݒ菈��
		pLogo->SetData();
	}
	else
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// ��~
		assert(false);

		// NULL ��Ԃ�
		return nullptr;
	}

	// �I�u�W�F�N�g2D�̃|�C���^��Ԃ�
	return pLogo;
}