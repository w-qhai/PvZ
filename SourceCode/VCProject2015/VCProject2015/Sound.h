#pragma once
#include <windows.h>
#include <Mmsystem.h>
#pragma comment ( lib, "winmm.lib" ) 
////////////////////////////////////////////////////////////////////////////////
//
// �ࣺSound
// ��Ϸ�������Ź�����. ���о�Ϊ��̬����. �������÷��� CSystem::������();
//
class Sound
{
public:
	// �������ֺ���
	// ���� src��������·�������ƣ�����ֵ���ڱ༭������Դ -> �����������鿴����Ŀ���������Դ�����������Ǹ�·��ֵ��д���ɣ�·��ʹ��\\
	// ���� isLoop���Ƿ�ѭ�����š������ѭ�����ŵ���������Ҫ�ֶ�����APIֹͣ����
	//
	static void Play(const char* src, const bool isLoop);
private:

};