//=======================================
//
// �C����[ocean.cpp]
// Author ��������
//
//=======================================
#include "manager.h"
#include "ocean.h"
#include "renderer.h"
#include "texture.h"
#include "useful.h"

// �萔��`
namespace
{
	const D3DXVECTOR3 POS = D3DXVECTOR3(0.0f, -5.0f, 0.0f);					// �ʒu
	const D3DXVECTOR3 OCEAN_SIZE = D3DXVECTOR3(5000.0f, 0.0f, 5000.0f);		// �T�C�Y
	const char* TEXTURE = "data\\TEXTURE\\Ocean.png";						// �e�N�X�`��
}

//=========================
// �R���X�g���N�^
//=========================
COcean::COcean() : CObject3D(CObject::TYPE_OCEAN, CObject::PRIORITY_BG)
{

}

//=========================
// �f�X�g���N�^
//=========================
COcean::~COcean()
{

}

//=========================
// ����������
//=========================
HRESULT COcean::Init(void)
{
	if (FAILED(CObject3D::Init()))
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
void COcean::Uninit(void)
{
	// �I��
	CObject3D::Uninit();
}

//=========================
// �X�V����
//=========================
void COcean::Update(void)
{
	// ���_���W�̐ݒ菈��
	SetVertex();
}

//=========================
// �`�揈��
//=========================
void COcean::Draw(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::Get()->GetRenderer()->GetDevice();

	// �J�����O�̐ݒ��OFF�ɂ���
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	// �`�揈��
	CObject3D::DrawLightOff();

	// �J�����O�̐ݒ��ON�ɂ���
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
}

//=========================
// ���̐ݒ菈��
//=========================
void COcean::SetData(void)
{
	// �X�N���[���̐ݒ菈��
	SetPos(POS);					// �ʒu
	SetPosOld(NONE_D3DXVECTOR3);	// �O��̈ʒu
	SetRot(NONE_D3DXVECTOR3);		// ����
	SetSize(OCEAN_SIZE);			// �T�C�Y

	// �e�N�X�`���̊��蓖�ď���
	BindTexture(CManager::Get()->GetTexture()->Regist(TEXTURE));

	// ���_���W�̐ݒ菈��
	SetVertex();
}

//=========================
// ��������
//=========================
COcean* COcean::Create(void)
{
	// ���[�J���I�u�W�F�N�g�𐶐�
	COcean* pMap = nullptr;	// �}�b�v�̃C���X�^���X�𐶐�

	if (pMap == nullptr)
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// �I�u�W�F�N�g�𐶐�
		pMap = new COcean;
	}
	else
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// ��~
		assert(false);

		// NULL ��Ԃ�
		return nullptr;
	}

	if (pMap != nullptr)
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// ����������
		if (FAILED(pMap->Init()))
		{ // �������Ɏ��s�����ꍇ

			// ��~
			assert(false);

			// NULL ��Ԃ�
			return nullptr;
		}

		// ���̐ݒ菈��
		pMap->SetData();
	}
	else
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// ��~
		assert(false);

		// NULL ��Ԃ�
		return nullptr;
	}

	// �}�b�v�̃|�C���^��Ԃ�
	return pMap;
}