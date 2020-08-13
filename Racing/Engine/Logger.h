#pragma once

#include <sstream>
#include <iostream>

using std::endl;

enum LOG_TYPE {
	LOG_FATAL,	//�v���I�ȃG���[
	LOG_ERROR,	//����ɏ������s���Ȃ�
	LOG_WARN,	//���͂��邪�����
	LOG_INFO,	//�V�X�e�����
	LOG_DEBUG,	//�f�o�b�O���
	LOG_TRACE,	//���ڍׂȃf�o�b�O���
	LOG_MAX
};

#define LOG_OUTPUT(type, out)	Logger::DebugOutputStream(__FUNCTION__, __LINE__, type, std::ostringstream() << out)
#define LOGGER_FATAL(out)		LOG_OUTPUT(LOG_FATAL, out)
#define LOGGER_ERROR(out)		LOG_OUTPUT(LOG_ERROR, out)
#define LOGGER_WARN(out)		LOG_OUTPUT(LOG_WARN, out)
#define LOGGER_INFO(out)		LOG_OUTPUT(LOG_INFO, out)
#define LOGGER_DEBUG(out)		LOG_OUTPUT(LOG_DEBUG, out)
#define LOGGER_TRACE(out)		LOG_OUTPUT(LOG_TRACE, out)

#define LOGGER_FATAL_2			std::cout << Logger::getInformation(__FUNCTION__, __LINE__, LOG_FATAL)
#define LOGGER_ERROR_2			std::cout << Logger::getInformation(__FUNCTION__, __LINE__, LOG_ERROR)
#define LOGGER_WARN_2			std::cout << Logger::getInformation(__FUNCTION__, __LINE__, LOG_WARN)
#define LOGGER_INFO_2			std::cout << Logger::getInformation(__FUNCTION__, __LINE__, LOG_INFO)
#define LOGGER_DEBUG_2			std::cout << Logger::getInformation(__FUNCTION__, __LINE__, LOG_DEBUG)
#define LOGGER_TRACE_2			std::cout << Logger::getInformation(__FUNCTION__, __LINE__, LOG_TRACE)

namespace Logger {

	void DebugOutputStream(const char* function, const int line, LOG_TYPE type, const std::ostringstream& out);

	std::string getInformation(const char* function, const int line, LOG_TYPE type);
}