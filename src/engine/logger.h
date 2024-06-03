#ifndef SG_ENGINE_LOGGER_H_
#define SG_ENGINE_LOGGER_H_

#include <ostream>
#include <string>
using namespace std;
class Logger {
public:
    static void SetEnabled(bool enabled) { enabled_ = enabled; }//�����Ƿ����
    static void SetOutputStream(std::ostream &os) { os_ = &os; }//�����������

    static void LogError(const std::string &message);
    static void LogInfo(const std::string &message);
    static void LogDebug(const std::string &message);

private:
    Logger() {}

    static void LogHeader(const std::string &log_type);

    static bool enabled_;
    static std::ostream *os_;
};

#endif // SG_ENGINE_LOGGER_H_
