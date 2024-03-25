//==========================================
//
//  �`���[�g���A���摜(tutorial_polygon.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _TUTORIAL_POLYGON_H_
#define _TUTORIAL_POLYGON_H_
#include "object2D.h"

//==========================================
//  �N���X��`
//==========================================
class CTutorialPolygon : public CObject2D
{
public:

	// �����o�֐�
	CTutorialPolygon(CObject::TYPE type = TYPE_TUTORIAL, PRIORITY priority = PRIORITY_ENTITY);
	~CTutorialPolygon();

	HRESULT Init() override; // ����������
	void Uninit() override; // �I������
	void Update() override; // �X�V����
	void Draw() override; // �`�揈��

	bool GetEnd() { return m_bEnd; } // �`���[�g���A���I���t���O�̎擾

	// �ÓI�����o�֐�
	static CTutorialPolygon* Create();

private:

	// �����o�ϐ�
	bool m_bEnd;
	int m_nIdx;

};

#endif
