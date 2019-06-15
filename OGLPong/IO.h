#ifndef _H_SEIO_
#define _H_SEIO_
#include <string>
class SEIO {
public:
	SEIO();
	static void Init();
	static std::string GetContentPath(const std::string& in);
private:
	static std::string absPath;
};
#endif