#ifndef CLEVERPARSER_H
#define CLEVERPARSER_H

#include "parser_runtime_exception.h"
#include "abstractparser.h"
#include "fitparser.h"

/**
 * @brief The CleverParser class: Automatically creates necessary parser.
 * AbstractParser is a parent.
 */
class CleverParser: public AbstractParser {
public:
    /**
     * @brief Default constructor
     * @param file - the name for raw file (default = "")
     */
    CleverParser(QString file = "") {
        file_name = file;
    }


    ~CleverParser() {
        removeParser();
    }

    /**
     * @brief Open data file
     * @param file is a variable with raw data
     * @return PARSER_OK if all is ok, else error code
     */
    int open(QString file = "") {
        if (!file.isEmpty())
            file_name = file;
        removeParser();
        if (file_name.endsWith(".fit")) {
            parser = new FitParser(file_name);
            return parser->open();
        } else {
            throw(ParserRuntimeException("Unknown file type!!!"));
            return PARSER_EXCEPTION;
        }
    }

    /**
     * @brief parse file
     * @return PARSER_OK if all is ok, else error code
     */
    int run() {
        if (parser == nullptr) {
            int return_code;
            return_code = open();
            if (return_code != PARSER_OK)
                return return_code;
        }
        return parser->run();
    }

private:
    /**
     * @brief Pointer on necessary parser
     */
    AbstractParser *parser = nullptr;

    /**
     * @brief Function for removing old parser
     */
    void removeParser() {
        if (parser != nullptr)
            delete parser;
        parser = nullptr;
    }
};

#endif // CLEVERPARSER_H
