//============================================
//
// ��ʃw�b�_�[[snowball.h]
// Author�F��������
//
//============================================
#ifndef _SNOWBALL_H_					// ���̃}�N����`������Ă��Ȃ�������
#define _SNOWBALL_H_					// 2�d�C���N���[�h�h�~�̃}�N�����`����

//********************************************
// �C���N���[�h�t�@�C��
//********************************************
#include "objectbillboard.h"

//--------------------------------------------
// �N���X��`(���)
//--------------------------------------------
class CSnowBall : public CBillboard
{
public:				// �N�ł��A�N�Z�X�ł���

	CSnowBall();			// �R���X�g���N�^
	~CSnowBall();			// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void);		// ����������
	void Uninit(void);		// �I������
	void Update(void);		// �X�V����
	void Draw(void);		// �`�揈��

	void SetData(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot);				// ���̐ݒ菈��

	// �ÓI�����o�ϐ�
	static CSnowBall* Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot);	// ��������

private:			// ���������A�N�Z�X�ł���

	// �����o�֐�
	void Move(void);		// �ړ�����

	// �����o�ϐ�
	D3DXVECTOR3 m_move;		// �ړ���
};

#endif