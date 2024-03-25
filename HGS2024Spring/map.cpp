//=======================================
//
// �}�b�v����[map.cpp]
// Author ��������
//
//=======================================
#include "manager.h"
#include "map.h"
#include "renderer.h"
#include "texture.h"
#include "useful.h"

// �萔��`
namespace
{
	const D3DXVECTOR3 MAP_SIZE = D3DXVECTOR3(2000.0f, 0.0f, 2000.0f);	// �T�C�Y
	const char* TEXTURE = "data\\TEXTURE\\Map.png";						// �e�N�X�`��
}

//=========================
// �R���X�g���N�^
//=========================
CMap::CMap() : CObject3D(CObject::TYPE_MAP, CObject::PRIORITY_BG)
{

}

//=========================
// �f�X�g���N�^
//=========================
CMap::~CMap()
{

}

//=========================
// ����������
//=========================
HRESULT CMap::Init(void)
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
void CMap::Uninit(void)
{
	// �I��
	CObject3D::Uninit();
}

//=========================
// �X�V����
//=========================
void CMap::Update(void)
{
	// ���_���W�̐ݒ菈��
	SetVertex();
}

//=========================
// �`�揈��
//=========================
void CMap::Draw(void)
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
void CMap::SetData(void)
{
	// �X�N���[���̐ݒ菈��
	SetPos(NONE_D3DXVECTOR3);		// �ʒu�ݒ�
	SetPosOld(NONE_D3DXVECTOR3);	// �ʒu�ݒ�
	SetRot(NONE_D3DXVECTOR3);		// �����ݒ�
	SetSize(MAP_SIZE);				// �T�C�Y�ݒ�

	// �e�N�X�`���̊��蓖�ď���
	BindTexture(CManager::Get()->GetTexture()->Regist(TEXTURE));

	// ���_���W�̐ݒ菈��
	SetVertex();
}

//=========================
// ��������
//=========================
CMap* CMap::Create(void)
{
	// ���[�J���I�u�W�F�N�g�𐶐�
	CMap* pMap = nullptr;	// �}�b�v�̃C���X�^���X�𐶐�

	if (pMap == nullptr)
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// �I�u�W�F�N�g�𐶐�
		pMap = new CMap;
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