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
#include "list_manager.h"

//-----------------------------------
// �N���X��`(CEnemy)
//-----------------------------------
class CEnemy : public CModel
{
public:					// �N�ł��A�N�Z�X�ł���

	// �񋓌^��`
	enum STATE
	{
		STATE_PROGRESS = 0,		// �i�s���
		STATE_CATCH,			// �L���b�`���
		STATE_RETURN,			// �A�ҏ��
		STATE_MAX				// ���̗񋓌^�̑���
	};

	CEnemy();				// �R���X�g���N�^
	~CEnemy();				// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void);		// ����������
	void Uninit(void);		// �I������
	void Update(void);		// �X�V����
	void Draw(void);		// �`�揈��

	void SetData(const D3DXVECTOR3& pos);		// ���̐ݒ菈��

	void Hit(void);			// �q�b�g����

	// �Z�b�g�E�Q�b�g�֌W
	bool IsDamage(void) const;		// �_���[�W�󋵂̎擾����

	// �ÓI�����o�֐�
	static CEnemy* Create(const D3DXVECTOR3& pos);	// ��������

	static CListManager<CEnemy*> GetList(void);		// ���X�g�̎擾����

private:				// ���������A�N�Z�X�ł���

	// �����o�֐�
	void MoveSet(const D3DXVECTOR3& posDest);		// �ړ��ʂ̐ݒ菈��
	void Progress(void);	// �i�s����
	void Catch(void);		// �L���b�`����
	bool Return(void);		// �A�ҏ���

	// �����o�ϐ�
	D3DXVECTOR3 m_move;		// �ړ���
	STATE m_state;			// ���
	int m_nCatchPercent;	// �L���b�`����x��
	int m_nLife;			// �̗�
	int m_nDamageCount;		// �_���[�W�J�E���g��
	int m_nStateCount;		// ��ԃJ�E���g
	bool m_bDamage;			// �_���[�W��

	// �ÓI�����o�ϐ�
	static CListManager<CEnemy*> m_list;		// ���X�g���
};

#endif