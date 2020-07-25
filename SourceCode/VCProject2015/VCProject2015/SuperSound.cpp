#include "SuperSound.h"
/// <summary>
/// �����ļ�λ��(���·�������·��)
/// </summary>

const char* SuperSound::configPath = "pvzConfig.ini";

/// <summary>
/// ��Ч�����ʱ��ֵ(��)
/// �����ӳٶ೤ʱ���ر���Ƶ��
/// </summary>

const int SuperSound::maxMusicLength = 2;

/// <summary>
/// �������ֲ���
/// </summary>
/// <param name="key">����KEY</param>
/// <returns></returns>

void SuperSound::sendASoundCommand(const char* key) {

	std::string szSoundContent = ConfigConvert::getConfig(configPath, key);

	if (szSoundContent != "") {

		int i = mciSendString(szSoundContent.c_str(), NULL, 0, NULL);

		std::cout << szSoundContent << "--->" << i << std::endl;

	}

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

		SuperSound::sendASoundCommand(openkey);

		SuperSound::sendASoundCommand(playkey);

		Sleep(maxMusicLength * 1000);
		
		SuperSound::sendASoundCommand(closekey);	

	});

	t.detach();

}






