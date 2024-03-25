//===================================
//
// ���u�؃w�b�_�[[mod_tree.h]
// Author ��������
//
//===================================
#ifndef _MOB_TREE_H_
#define _MOB_TREE_H_

//***********************************
// �C���N���[�h�t�@�C��
//***********************************
#include "model.h"
#include "list_manager.h"

// �O���錾
class CMobTreeLeaf;		// ���u�؂̗t

//-----------------------------------
// �N���X��`(CMobTree)
//-----------------------------------
class CMobTree : public CModel
{
public:					// �N�ł��A�N�Z�X�ł���

	CMobTree();				// �R���X�g���N�^
	~CMobTree();			// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void);		// ����������
	void Uninit(void);		// �I������
	void Update(void);		// �X�V����
	void Draw(void);		// �`�揈��

	void SetData(const D3DXVECTOR3& pos, const int nCount);		// ���̐ݒ菈��

	void SnowBallHit(void);	// ��ʂƂ̏Փˎ�����

	// �ÓI�����o�֐�
	static CMobTree* Create(const D3DXVECTOR3& pos, const int nCount);		// ��������

	static CListManager<CMobTree*> GetList(void);			// ���X�g�̎擾����

private:				// ���������A�N�Z�X�ł���

	// �����o�ϐ�
	CMobTreeLeaf* m_pLeaf;		// �t���ς̏��
	int m_nFloweringCount;		// �炭�܂ł̃J�E���g

	// �ÓI�����o�ϐ�
	static CListManager<CMobTree*> m_list;		// ���X�g���
};

#endif