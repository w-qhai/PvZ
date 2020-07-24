#include "SuperSound.h"
/// <summary>
/// �����ļ�λ��(���·�������·��)
/// </summary>

const char* SuperSound::configPath = "pvzConfig.ini";

/// <summary>
/// ����һ������ָ��(���򿪻���ر�)
/// </summary>
/// <param name="key">����KEY</param>
/// <returns></returns>

void SuperSound::sendASoundCommand(const char* key) {

	std::string szSoundContent = ConfigConvert::getConfig(configPath, key);

	mciSendStringW(stringToLPCWSTR(szSoundContent), NULL, 0, NULL);

}

/// <summary>
/// ��Ч���ֲ���
/// �����̣߳���������UI���Ƽ���Ч�����ô˺�������
/// </summary>
/// <param name="openkey">���ô�KEY</param>
/// <param name="playkey">���ò���KEY</param>
/// <param name="closekey">���ùر�KEY</param>
/// <returns></returns>

void SuperSound::closeAndPlay(const char* openkey, const char* playkey, const char* closekey) {

	std::thread t([=] {

		SuperSound::sendASoundCommand(closekey);

		SuperSound::sendASoundCommand(openkey);

		SuperSound::sendASoundCommand(playkey);


	});

	t.detach();

}




LPCWSTR stringToLPCWSTR(std::string orig)
{
	size_t origsize = orig.length() + 1;

	const size_t newsize = 100;

	size_t convertedChars = 0;

	wchar_t* wcstring = (wchar_t*)malloc(sizeof(wchar_t) * (orig.length() - 1));

	mbstowcs_s(&convertedChars, wcstring, origsize, orig.c_str(), _TRUNCATE);

	return wcstring;
}

