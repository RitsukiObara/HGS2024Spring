//===================================
//
// �G�̃z�[���w�b�_�[[enemy_home.h]
// Author ��������
//
//===================================
#ifndef _ENEMY_HOME_H_
#define _ENEMY_HOME_H_

//***********************************
// �C���N���[�h�t�@�C��
//***********************************
#include "model.h"

//-----------------------------------
// �N���X��`(CEnemyHome)
//-----------------------------------
class CEnemyHome : public CModel
{
public:					// �N�ł��A�N�Z�X�ł���

	CEnemyHome();			// �R���X�g���N�^
	~CEnemyHome();			// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void);		// ����������
	void Uninit(void);		// �I������
	void Update(void);		// �X�V����
	void Draw(void);		// �`�揈��

	void SetData(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot);		// ���̐ݒ菈��

	// �ÓI�����o�֐�
	static CEnemyHome* Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot);	// ��������

private:				// ���������A�N�Z�X�ł���

	// �����o�ϐ�
	int m_nEnemyCount;	// �G�̏o��J�E���g
};

#endif