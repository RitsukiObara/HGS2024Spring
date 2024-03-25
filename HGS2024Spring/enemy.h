//===================================
//
// �G�w�b�_�[[enemy.h]
// Author ��������
//
//===================================
#ifndef _ENEMY_H_
#define _ENEMY_H_

//***********************************
// �C���N���[�h�t�@�C��
//***********************************
#include "model.h"

//-----------------------------------
// �N���X��`(CEnemy)
//-----------------------------------
class CEnemy : public CModel
{
public:					// �N�ł��A�N�Z�X�ł���

	CEnemy();				// �R���X�g���N�^
	~CEnemy();				// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void);		// ����������
	void Uninit(void);		// �I������
	void Update(void);		// �X�V����
	void Draw(void);		// �`�揈��

	void SetData(const D3DXVECTOR3& pos);		// ���̐ݒ菈��

	// �ÓI�����o�֐�
	static CEnemy* Create(const D3DXVECTOR3& pos);		// ��������

private:				// ���������A�N�Z�X�ł���

};

#endif