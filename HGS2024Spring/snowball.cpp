//=======================================
//
// ��ʂ̃��C������[snowball.cpp]
// Author ��������
//
//=======================================
#include "manager.h"
#include "snowball.h"
#include "renderer.h"
#include "texture.h"
#include "useful.h"

//=======================================
// �������O���
//=======================================
namespace
{
	const D3DXVECTOR3 SNOWBALL_SIZE = D3DXVECTOR3(30.0f, 30.0f, 0.0f);		// �T�C�Y
	const char* TEXTURE = "data\\TEXTURE\\";		// �e�N�X�`��
}

//=======================================
// �}�N����`
//=======================================


//=========================
// �R���X�g���N�^
//=========================
CSnowBall::CSnowBall() : CBillboard(CObject::TYPE_EFFECT, CObject::PRIORITY_EFFECT)
{
	// �S�Ă̒l���N���A����
	m_move = NONE_D3DXVECTOR3;		// �ړ���
}

//=========================
// �f�X�g���N�^
//=========================
CSnowBall::~CSnowBall()
{

}

//=========================
// ����������
//=========================
HRESULT CSnowBall::Init(void)
{
	if (FAILED(CBillboard::Init()))
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
void CSnowBall::Uninit(void)
{
	// �I��
	CBillboard::Uninit();
}

//=========================
// �X�V����
//=========================
void CSnowBall::Update(void)
{
	// ���_���W�̐ݒ菈��
	SetVertex();
}

//=========================
// �`�揈��
//=========================
void CSnowBall::Draw(void)
{
	// �`�揈��
	CBillboard::DrawLightOff();
}

//=========================
// ���̐ݒ菈��
//=========================
void CSnowBall::SetData(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot)
{
	// ���̐ݒ菈��
	SetPos(pos);				// �ʒu
	SetPosOld(pos);				// �O��̈ʒu
	SetSize(SNOWBALL_SIZE);		// �T�C�Y
	SetEnableLookY(true);		// Y����

	// ���_���̏�����
	SetVertex();

	// �e�N�X�`���̓ǂݍ��ݏ���
	BindTexture(CManager::Get()->GetTexture()->Regist(TEXTURE));
}

//=========================
// ��������
//=========================
CSnowBall* CSnowBall::Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot)
{
	// ���[�J���I�u�W�F�N�g�𐶐�
	CSnowBall* pSnowball = nullptr;		// ��ʂ̃C���X�^���X�𐶐�

	if (pSnowball == nullptr)
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// �I�u�W�F�N�g�𐶐�
		pSnowball = new CSnowBall;
	}
	else
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// ��~
		assert(false);

		// NULL ��Ԃ�
		return nullptr;
	}

	if (pSnowball != nullptr)
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// ����������
		if (FAILED(pSnowball->Init()))
		{ // �������Ɏ��s�����ꍇ

			// ��~
			assert(false);

			// NULL ��Ԃ�
			return nullptr;
		}

		// ���̐ݒ菈��
		pSnowball->SetData(pos, rot);
	}
	else
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// ��~
		assert(false);

		// NULL ��Ԃ�
		return nullptr;
	}

	// ��ʂ̃|�C���^��Ԃ�
	return pSnowball;
}