#ifndef ABSTRACTPARSER_H
#define ABSTRACTPARSER_H

#include <QMap>
#include <QString>
#include <fstream>

/**
  * Some parser error codes
  */
#define PARSER_OK                   0
#define PARSER_OPEN_FILE_ERR        1
#define PARSER_INTEGRITY_FILE_ERR   2
#define PARSER_EXCEPTION            3

/**
 * @brief The AbstractParser class: the interface for all parsers.
 */
class AbstractParser
{
public:
    /**
     * @brief Abstruct function for opening data file
     * @param file is a variable with raw data
     * @return PARSER_OK if all is ok, else error code
     */
    virtual int open(QString file = "") = 0;

    /**
     * @brief Abstruct function in order to parse file
     * @return PARSER_OK if all is ok, else error code
     */
    virtual int run() = 0;

    /**
     * @brief get type of parser
     * @return type of file
     */
    inline virtual QString fileType() = 0;

    /**
     * @brief getInfo
     * @return Information from file
     */
    virtual QMap<QString, QMap<QString, QString>> *getInfo() = 0;

protected:
    /**
     * @brief file_name - the name of file with raw data
     */
    QString file_name;
    /**
     * @brief ifile - the object for file with raw data
     */
    std::fstream ifile;

    /**
     * @brief fileInfo - information from file
     */
    QMap<QString, QMap<QString, QString>> fileInfo;
};

#endif // ABSTRACTPARSER_H
