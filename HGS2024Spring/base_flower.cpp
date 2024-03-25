//=======================================
//
// ���_�̉ԏ���[base_flower.cpp]
// Author ��������
//
//=======================================
#include "manager.h"
#include "base_flower.h"
#include "renderer.h"
#include "texture.h"
#include "useful.h"

//=======================================
// �萔��`
//=======================================
namespace
{
	const D3DXVECTOR3 FLOWER_SIZE = D3DXVECTOR3(20.0f, 20.0f, 0.0f);		// �Ԃ̃T�C�Y
	const char* TEXTURE = "data\\TEXTURE\\Flower.png";						// �e�N�X�`��
}

//=========================
// �R���X�g���N�^
//=========================
CBaseFlower::CBaseFlower() : CBillboard(CObject::TYPE_BASEFLOWER, CObject::PRIORITY_ENTITY)
{

}

//=========================
// �f�X�g���N�^
//=========================
CBaseFlower::~CBaseFlower()
{

}

//=========================
// ����������
//=========================
HRESULT CBaseFlower::Init(void)
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
void CBaseFlower::Uninit(void)
{
	// �I��
	CBillboard::Uninit();
}

//=========================
// �X�V����
//=========================
void CBaseFlower::Update(void)
{

}

//=========================
// �`�揈��
//=========================
void CBaseFlower::Draw(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::Get()->GetRenderer()->GetDevice();

	// �`�揈��
	CBillboard::DrawLightOff();
}

//=========================
// ���̐ݒ菈��
//=========================
void CBaseFlower::SetData(const D3DXVECTOR3& pos)
{
	// ���̐ݒ菈��
	SetPos(pos);			// �ʒu
	SetPosOld(pos);			// �O��̈ʒu
	SetSize(FLOWER_SIZE);	// �T�C�Y
	SetEnableLookY(false);	// Y����

	// ���_���̏�����
	SetVertex();

	// �F�̐ݒ菈��
	SetVtxColor(D3DXCOLOR(1.0f, 0.5f, 1.0f, 1.0f));

	// �e�N�X�`���̓ǂݍ��ݏ���
	BindTexture(CManager::Get()->GetTexture()->Regist(TEXTURE));
}

//=========================
// ��������
//=========================
CBaseFlower* CBaseFlower::Create(const D3DXVECTOR3& pos)
{
	// ���[�J���I�u�W�F�N�g�𐶐�
	CBaseFlower* pBaseFlower = nullptr;	// �v���C���[�̃C���X�^���X�𐶐�

	if (pBaseFlower == nullptr)
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// �I�u�W�F�N�g�𐶐�
		pBaseFlower = new CBaseFlower;
	}
	else
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// ��~
		assert(false);

		// NULL ��Ԃ�
		return nullptr;
	}

	if (pBaseFlower != nullptr)
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// ����������
		if (FAILED(pBaseFlower->Init()))
		{ // �������Ɏ��s�����ꍇ

			// ��~
			assert(false);

			// NULL ��Ԃ�
			return nullptr;
		}

		// ���̐ݒ菈��
		pBaseFlower->SetData(pos);
	}
	else
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// ��~
		assert(false);

		// NULL ��Ԃ�
		return nullptr;
	}

	// �I�u�W�F�N�g2D�̃|�C���^��Ԃ�
	return pBaseFlower;
}