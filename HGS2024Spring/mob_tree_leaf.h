//===================================
//
// ���u�؂̗t���σw�b�_�[[mod_tree_leaf.h]
// Author ��������
//
//===================================
#ifndef _MOB_TREE_LEAF_H_
#define _MOB_TREE_LEAF_H_

//***********************************
// �C���N���[�h�t�@�C��
//***********************************
#include "model.h"

//-----------------------------------
// �N���X��`(CMobTreeLeaf)
//-----------------------------------
class CMobTreeLeaf : public CModel
{
public:					// �N�ł��A�N�Z�X�ł���

	CMobTreeLeaf();			// �R���X�g���N�^
	~CMobTreeLeaf();		// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void);		// ����������
	void Uninit(void);		// �I������
	void Update(void);		// �X�V����
	void Draw(void);		// �`�揈��

	void SetData(const D3DXVECTOR3& pos);		// ���̐ݒ菈��

	void SnowBallHit(void);		// ��ʂƂ̏Փˎ�����

	// �ÓI�����o�֐�
	static CMobTreeLeaf* Create(const D3DXVECTOR3& pos);		// ��������

private:				// ���������A�N�Z�X�ł���

	// �����o�֐�
	void Growth(void);		// ��������
};

#endif