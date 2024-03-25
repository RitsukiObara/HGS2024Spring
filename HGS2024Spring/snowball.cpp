//=======================================
//
// ��ʂ̃��C������[snowball.cpp]
// Author ��������
//
//=======================================
#include "manager.h"
#include "snowball.h"
#include "collision.h"
#include "renderer.h"
#include "texture.h"
#include "useful.h"

//=======================================
// �������O���
//=======================================
namespace
{
	const D3DXVECTOR3 SNOWBALL_SIZE = D3DXVECTOR3(40.0f, 40.0f, 0.0f);		// �T�C�Y
	const char* TEXTURE = "data\\TEXTURE\\snow.jpg";		// �e�N�X�`��
	const float SPEED = 30.0f;			// ���x
	const int LIFE = 30;				// ����
}

//-------------------------------------------
// �ÓI�����o�ϐ��錾
//-------------------------------------------
CListManager<CSnowBall*> CSnowBall::m_list = {};			// ���X�g���

//=========================
// �R���X�g���N�^
//=========================
CSnowBall::CSnowBall() : CBillboard(CObject::TYPE_SNOWBALL, CObject::PRIORITY_ENTITY)
{
	// �S�Ă̒l���N���A����
	m_move = NONE_D3DXVECTOR3;		// �ړ���
	m_nLife = LIFE;					// ����

	// ���X�g�ɒǉ�����
	m_list.Regist(this);
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

	// ������������
	m_list.Pull(this);
}

//=========================
// �X�V����
//=========================
void CSnowBall::Update(void)
{
	// ������������
	m_nLife--;

	// �ړ�����
	Move();

	if (m_nLife <= 0 ||
		collision::TreeHit(GetPos(), GetSize()) == true)
	{ // ������ 0 �ȉ��ɂȂ邩�A�؂ɓ��������ꍇ

		// �I������
		Uninit();

		// ���̐�̏������s��Ȃ�
		return;
	}

	// ���_���W�̐ݒ菈��
	SetVertex();

	// �G�Ƃ̓����蔻��
	collision::EnemyToSnowBallHit(GetPos(), GetSize());
}

//=========================
// �`�揈��
//=========================
void CSnowBall::Draw(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::Get()->GetRenderer()->GetDevice();

	//���u�����f�B���O�����Z�����ɐݒ�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	// �`�揈��
	CBillboard::DrawLightOff();

	//���u�����f�B���O�����ɖ߂�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
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

	// �ړ��ʂ�ݒ肷��
	m_move.x = sinf(rot.y) * SPEED;
	m_move.y = 0.0f;
	m_move.z = cosf(rot.y) * SPEED;
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

//=======================================
// ���X�g�̎擾����
//=======================================
CListManager<CSnowBall*> CSnowBall::GetList(void)
{
	// ���X�g�\���̏���Ԃ�
	return m_list;
}

//=========================
// �ړ�����
//=========================
void CSnowBall::Move(void)
{
	// �ʒu���擾
	D3DXVECTOR3 pos = GetPos();

	// �ړ�
	pos += m_move;

	// �ʒu��K�p
	SetPos(pos);
}