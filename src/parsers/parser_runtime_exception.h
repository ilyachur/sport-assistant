#ifndef PARSER_RUNTIME_EXCEPTION
#define PARSERRUNTIMEEXCEPTION

#include <stdexcept>
#include <string>

class ParserRuntimeException : public std::runtime_error
{
   public:
      explicit ParserRuntimeException(const std::string& msg = ""): runtime_error(msg) {}
};

#endif // PARSERRUNTIMEEXCEPTION

