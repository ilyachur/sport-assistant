#ifndef FITPARSER_H
#define FITPARSER_H

#include "abstractparser.h"
#include "fit/fit_decode.hpp"
#include "fit/fit_mesg_broadcaster.hpp"

/**
 * @brief The FitParser class: Parser for fit files
 */
class FitParser: public AbstractParser
{

public:
    /**
     * @brief Default constructor
     * @param file - the name for raw file (default = "")
     */
    FitParser(QString file = "");
    /**
     * @brief Open data file
     * @param file is a variable with raw data
     * @return PARSER_OK if all is ok, else error code
     */
    int open(QString file = "");
    /**
     * @brief parse file
     * @return PARSER_OK if all is ok, else error code
     */
    int run();

    /**
     * @brief getInfo
     * @return Information from file
     */
    QMap<QString, QMap<QString, QString>> *getInfo();

    /**
     * @brief get type of parser
     * @return type of file
     */
    inline QString fileType() {
        return "fit";
    }

private:
    /**
     * @brief fit decoder
     */
    fit::Decode decode;
    /**
     * @brief Broadcaster for messages
     */
    fit::MesgBroadcaster mesgBroadcaster;

    /**
     * @brief The FitListener class: Listener for all messages from mesgBroadcaster
     */
    class FitListener : public fit::FileIdMesgListener,
            public fit::BloodPressureMesgListener,
            public fit::UserProfileMesgListener,
            public fit::MonitoringMesgListener,
            public fit::DeviceInfoMesgListener,
            public fit::HrvMesgListener,
            public fit::MesgListener {
    public :
        /**
         * @brief OnMesg - function for processing messages
         * @param message with type fit::Mesg
         */
        void OnMesg(fit::Mesg& mesg);

        /**
         * @brief OnMesg - function for processing messages
         * @param message with type fit::FileIdMesg
         */
        void OnMesg(fit::FileIdMesg& mesg);

        /**
         * @brief OnMesg - function for processing messages
         * @param message with type fit::UserProfileMesg
         */
        void OnMesg(fit::UserProfileMesg& mesg);

        /**
         * @brief OnMesg - function for processing messages
         * @param message with type fit::DeviceInfoMesg
         */
        void OnMesg(fit::DeviceInfoMesg& mesg);

        /**
         * @brief OnMesg - function for processing messages
         * @param message with type fit::MonitoringMesg
         */
        void OnMesg(fit::MonitoringMesg& mesg);

        /**
         * @brief OnMesg - function for processing messages
         * @param message with type fit::HrvMesg
         */
        void OnMesg(fit::HrvMesg& mesg);

        /**
         * @brief OnMesg - function for processing messages
         * @param message with type fit::BloodPressureMesg
         */
        void OnMesg(fit::BloodPressureMesg& mesg);

        inline void setFileInfo(QMap<QString, QMap<QString, QString>> *fInfo) {
            info = fInfo;
        }

    private:
        QMap<QString, QMap<QString, QString>> *info;
    };

    /**
     * @brief listener object
     */
    FitListener listener;
};

#endif // FITPARSER_H
