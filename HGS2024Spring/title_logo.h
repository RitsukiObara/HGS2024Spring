//==========================================
//
//  �^�C�g�����S�N���X(title_logo.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _TITLE_LOGO_H_
#define _TITLE_LOGO_H_
#include "object2D.h"

//==========================================
//  �N���X��`
//==========================================
class CTitleLogo : CObject2D
{
public:

	// �����o�֐�
	CTitleLogo(CObject::TYPE type = TYPE_LOGOMARK, PRIORITY priority = PRIORITY_ENTITY);
	~CTitleLogo();

	HRESULT Init(); // ����������
	void Uninit(); // �I������
	void Update(); // �X�V����
	void Draw(); // �`�揈��

	// �ÓI�����o�֐�
	static CTitleLogo* Create(); // ��������

private:

};

#endif
