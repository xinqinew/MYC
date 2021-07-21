#pragma once
{
	float x;
	float y;
}TPOINT2POS;
{
	float x;
	float y;
	float z;
}TPOINT3POS;

class TFindWay
{
public:
	TFindWay(void);
	~TFindWay(void);

	static float 获取距离();	//计算当前角色与第一个坐标点距离
	static UINT32 m寻路状态;	//0表示寻路结束,1表示寻路中.
	static std::queue<TPOINT2POS> m_posqueue;	//queue队列
	static void TFindWay::正向初始化坐标序列(TPOINT2POS* arrayPos,SIZE_T n);
	static void TFindWay::反向初始化坐标序列(TPOINT2POS* arrayPos,SIZE_T n);
	static UINT AFX_CDECL TFindWay::寻路线程回调(LPVOID arg1);
	static CWinThread *mpStartThread;
	static int TFindWay::多点反向寻路(TPOINT2POS* arrayPos,SIZE_T n);
	static int 多点正向寻路(POINT2POS* arrayPos,SIZE_T n);
	static int TFindWay::遍历坐标();
	static int 退出清理();
}