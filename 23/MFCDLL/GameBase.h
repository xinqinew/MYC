#pragma once
class GameBase
{
public:
	GameBase(void);
	~GameBase(void);
	static UINT64 GetExeBase();
	static UINT64 GetRoleObj();//返回角色对象地址
};

