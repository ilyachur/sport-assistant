#ifndef PARSER_RUNTIME_EXCEPTION
#define PARSER_RUNTIME_EXCEPTION

/// @file parser_runtime_exception.h
/// @brief Contains exeption class for parsers
/// @author Ilya Churaev ilyachur@gmail.com

#include <stdexcept>
#include <string>

/**
 * @brief The ParserRuntimeException class
 */
class ParserRuntimeException : public std::runtime_error
{
   public:
      explicit ParserRuntimeException(const std::string& msg = ""): runtime_error(msg) {}
};

#endif // PARSERRUNTIMEEXCEPTION

