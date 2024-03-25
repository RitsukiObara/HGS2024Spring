//===================================
//
// �v���C���[�w�b�_�[[player.h]
// Author ��������
//
//===================================
#ifndef _PLAYER_H_
#define _PLAYER_H_

//***********************************
// �C���N���[�h�t�@�C��
//***********************************
#include "model.h"

//-----------------------------------
// �N���X��`(CPlayer)
//-----------------------------------
class CPlayer : public CModel
{
public:					// �N�ł��A�N�Z�X�ł���

	CPlayer();				// �R���X�g���N�^
	~CPlayer();				// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void);		// ����������
	void Uninit(void);		// �I������
	void Update(void);		// �X�V����
	void Draw(void);		// �`�揈��

	void SetData(void);		// ���̐ݒ菈��

	// �ÓI�����o�֐�
	static CPlayer* Create(void);		// ��������

private:				// ���������A�N�Z�X�ł���

	// �����o�֐�
	void Control(void);		// ���쏈��
};

#endif