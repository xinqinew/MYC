#pragma once
class GameBase
{
public:
	GameBase(void);
	~GameBase(void);
	static UINT64 GetExeBase();
	static UINT64 GetRoleObj();//���ؽ�ɫ�����ַ
	static UINT64 MoveRole(float x,float y);
	static float* GetRolePos();
	static void MoveRole2(float x,float y);
};

