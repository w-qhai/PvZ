#include "ConfigConvert.h"

/// <summary>
/// ��ȡһ����������ҷ���KEY��Ӧ��VALUE
/// </summary>
/// <param name="configPath">������λ��</param>
/// <param name="configKey">Ѱ�ҵ�KEY</param>
/// <returns></returns>

std::string ConfigConvert::getConfig(const char* configPath, const char* configKey) {

	// ��һ���ļ�
	std::fstream fin(configPath, std::ios::in);
	std::string szLine("");
	// ������ļ�ʧ�ܣ������ǲ�����Ҳ����������������ڶ�ȡд�룩
	if (!fin) {
		return "";
	}

	// ������ļ��ɹ�

	while (std::getline(fin, szLine)) {

		// ע�ͷ��� # �ڴ�֮��������ַ�����������

		int iCommentPos = szLine.find("#");

		if (iCommentPos != szLine.npos) {

			// ��ѯ���� # ע�ͷ��ţ���ȡǰ������

			szLine = szLine.substr(0, iCommentPos);

		}

		// ��Ѱ�Ƿ��зָ��� = 

		int iDelimiterPos = szLine.find("=");

		std::string currentKey = szLine.substr(0, iDelimiterPos);

		if (iDelimiterPos != szLine.npos) {

			//Ѱ�ҵ��ָ��� = ���Һ���ҪѰ�ҵ�key��ͬ������ȡkey��Ӧ��Value

			if (currentKey == configKey) {

				// ��ȡ��ǰ�еĳ��ȣ���λ�����һ���ַ��ĺ���

				int iLineLength = szLine.length();

				// ��ȡӦ��ȡ���ٸ��ַ�

				int iContentLength = iLineLength - iDelimiterPos - 1;

				// �ӵڼ�����ʼȡ

				int iBef = iDelimiterPos + 1;

				fin.close();

				// ��� iBef(��Ҫȡ�ĵ�һ���ַ�) �Ƿ��� iLineLength(��Ҫȡ�����һ���ַ�)��ǰ��

				if (iBef < iLineLength) {

					// ��������ݣ���ȡ����

					szLine = szLine.substr(iBef, iContentLength);

					return szLine;

				}
				else {

					// ���û�����ݣ��򷵻ؿ�ֵ

					return "";

				}

			}

		}

	}

	fin.close();

	return "";
}


/// <summary>
///  ���һ�������ָ���ļ��У���û�д��ļ����Զ�����
/// </summary>
/// <param name="configPath">�ļ�·��</param>
/// <param name="configKey">������KEY</param>
/// <param name="configValue">������VALUE</param>
/// <param name="configComment">������ע��(Ϊ����д��ע��)</param>
/// <returns></returns>

bool ConfigConvert::addConfig(const char* configPath, const char* configKey, const char* configValue, const char* configComment) {

	// ��һ���ļ�
	std::fstream fout(configPath, std::ios::app);
	// ������ļ�ʧ�ܣ������ǲ�����Ҳ����������������ڶ�ȡд�룩
	if (!fout) {
		return false;
	}

	// ��������ע�Ͳ�Ϊ�գ���д��ע�ͣ���������

	if (configComment != "")
		fout << "# " << configComment << std::endl;

	fout << configKey << "=" << configValue << std::endl;

	fout.close();

	return true;
}