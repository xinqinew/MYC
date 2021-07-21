#include "stdafx.h"
#include "TFindWay.h"

std::queue<TPOINT2POS> TFindWay::m_posqueue;
CWinThread * TFindWay::mpStartThread=NULL;

TFindWay::TFindWay(void)
{

}
TFindWay::~TFindWay(void)
{

}


//计算当前角色与第一个坐标点距离
float TFindWay::获取距离()
{
	float x=GameBase::GetRolePos()[0];
	float y=GameBase::GetRolePos()[1];
	float x2=m_posqueue.front().x;
	float y2=m_posqueue.front().y;

	//勾股定理
	float a=fabs(x2-x);	//fabs绝对值
	float b=fabs(y2-y);
	//求C边 即距离
	float c=sqrt(a*a+b*b);	//开平方
	return c;
}

void TFindWay::反向初始化坐标序列(TPOINT2POS* arrayPos,SIZE_T n)
{
	//清空队列
	{
		std::queue<TPOINT2POS>clearQueue;
		m_posqueue.swap(clearQueue);
	}
	//重建队列
	for (int i = n-1; i >0; i--)
	{
		/* code */
		m_posqueue.push(arrayPos[i]);
	}
}

void TFindWay::正向初始化坐标序列(TPOINT2POS* arrayPos,SIZE_T n)
{
	//清空队列
	{
		std::queue<TPOINT2POS>clearQueue;
		m_posqueue.swap(clearQueue);
	}
	//重建队列
	for (int i = 0; i <n; i++)
	{
		/* 按0,1,2,3次序排队压栈 */
		m_posqueue.push(arrayPos[i]);
	}
}

int TFindWay::退出清理()
{
	if (mpStartThread)
	{
		mpStartThread->ExitInstance();
		/* code */
	}
	return 1;
}
int TFindWay::多点正向寻路(POINT2POS* arrayPos,SIZE_T n)
{
	正向初始化坐标序列(arrayPos,n);
	//return 0;
	if (mpStartThread==NULL)
	{
		mpStartThread=::AfxBeginThread(寻路线程回调,NULL);
		/* code */
	}else
	{
		// mpStartThread->ResumeThread();
	}
	return 1;
}
int TFindWay::多点反向寻路(POINT2POS* arrayPos,SIZE_T n)
{
	正向初始化坐标序列(arrayPos,n);
	//return 0;
	if (mpStartThread==NULL)
	{
		mpStartThread=::AfxBeginThread(寻路线程回调,NULL);
		/* code */
	}else
	{
		// mpStartThread->ResumeThread();
	}
	return 1;
}
int TFindWay::遍历坐标()
{
	char buf[1024];
	while(!m_posqueue.empty())
	{
		float x=m_posqueue.front().x;
		float y=m_posqueue.front().y;
		sprintf_s(buf,"yjx:到达节点(%f,%f),删除此节点 继续移动到下一个节点",x,y);
		OutputDebugStringA(buf);
		m_posqueue.pop();
	}
	return 1;
}

UINT AFX_CDECL TFindWay::寻路线程回调(LPVOID arg1)
{
	//还有多少个坐标点 待寻路
	SIZE_T n=m_posqueue.size();
	char buf[1024]={0};
	while(TRUE)
	{
		if (m_posqueue.empty())
		{
			//如果队列为空 则继续等待
			OutputDebugStringA("yjx:所有寻路已经完成...等待主人下一次寻路...");
			Sleep(1000);
			continue;
			/* code */
		}
		//只要队列不为空 就一直寻路
		//移动到
		float x=m_posqueue.front().x;
		float y=m_posqueue.front().y;
		GameBase::MoveRole(x,y);
		//等待0.2秒
		Sleep(200);
		//等待角色 移动到坐标位置
		//计算角色与坐标点距离
		float 距离=获取距离();
		if (距离<2)
		{
			//如果距离小于10 视为到达目标点 继续移动到下一个点
			//到达了一个点 则删除一个点

			sprintf_s(buf,"yjx:到达节点(%f,%f),删除此节点 继续移动到下一个节点",x,y);
			OutputDebugStringA(buf);
			m_posqueue.pop();//删除此节点
			continue;
		}else
		{
			sprintf_s(buf,"yjx:与坐标(%f,%f),相距=%f,继续移动到此节点",x,y,距离);
			OutputDebugStringA(buf);
			Sleep(1000);//如果距离大于10 则等1秒时间,继续调用寻路
			continue;
		}
	}
}


















