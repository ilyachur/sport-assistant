#ifndef CLEVERPARSER_H
#define CLEVERPARSER_H

#include "parser_runtime_exception.h"
#include "abstractparser.h"
#include "fitparser.h"

#include <QDebug>

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
    explicit CleverParser(QString file = "") {
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
        } else if  (file_name.endsWith(".tcx")) {
            qDebug() << "tcx is not yet supported";
            return PARSER_EXCEPTION;
        } else {
            qDebug() << "Unknown file type!!! " << file_name;
            return PARSER_EXCEPTION;
        }
        return PARSER_EXCEPTION;
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

    /**
     * @brief getInfo
     * @return Information from file
     */
    QMap<QString, QMap<QString, QString>> *getInfo() {
        if (parser == nullptr) {
            return nullptr;
        }
        return parser->getInfo();
    }

    /**
     * @brief get type of parser
     * @return type of file
     */
    inline QString fileType() {
        if (parser == nullptr)
            return QString();
        return parser->fileType();
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
