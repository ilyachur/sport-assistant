#ifndef FITPARSER_H
#define FITPARSER_H

/// @file fitparser.h
/// @brief Contains definition of fit parser class
/// @author Ilya Churaev ilyachur@gmail.com

#include "abstractparser.h"
#include "fit/fit_decode.hpp"
#include "fit/fit_mesg_broadcaster.hpp"

#include <QDateTime>

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
    explicit FitParser(QString file = "");
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
     * @brief Get date and time for training from fit
     * @param dateTime - date and time in Msec from fit file
     * @return real date and time
     */
    static QDateTime getRealTimeFromFit(FIT_DATE_TIME dateTime);

    /**
     * @brief The FitListener class: Listener for all messages from mesgBroadcaster
     */


    class FitListener : public fit::HrvMesgListener,
            public fit::FileIdMesgListener
            /*public fit::MesgDefinitionListener,
            public fit::MesgListener,
            public fit::MesgWithEventListener,
            public fit::BufferedRecordMesgListener,
            public fit::FileCreatorMesgListener,
            public fit::SoftwareMesgListener,
            public fit::SlaveDeviceMesgListener,
            public fit::CapabilitiesMesgListener,
            public fit::FileCapabilitiesMesgListener,
            public fit::MesgCapabilitiesMesgListener,
            public fit::FieldCapabilitiesMesgListener,
            public fit::DeviceSettingsMesgListener,
            public fit::UserProfileMesgListener,
            public fit::HrmProfileMesgListener,
            public fit::SdmProfileMesgListener,
            public fit::BikeProfileMesgListener,
            public fit::ZonesTargetMesgListener,
            public fit::SportMesgListener,
            public fit::HrZoneMesgListener,
            public fit::SpeedZoneMesgListener,
            public fit::CadenceZoneMesgListener,
            public fit::PowerZoneMesgListener,
            public fit::GoalMesgListener,
            public fit::ActivityMesgListener,
            public fit::SessionMesgListener,
            public fit::LapMesgListener,
            public fit::LengthMesgListener,
            public fit::RecordMesgListener,
            public fit::EventMesgListener,
            public fit::DeviceInfoMesgListener,
            public fit::TrainingFileMesgListener,
            public fit::CourseMesgListener,
            public fit::CoursePointMesgListener,
            public fit::SegmentIdMesgListener,
            public fit::SegmentLeaderboardEntryMesgListener,
            public fit::SegmentPointMesgListener,
            public fit::SegmentLapMesgListener,
            public fit::SegmentFileMesgListener,
            public fit::WorkoutMesgListener,
            public fit::WorkoutStepMesgListener,
            public fit::ScheduleMesgListener,
            public fit::TotalsMesgListener,
            public fit::WeightScaleMesgListener,
            public fit::BloodPressureMesgListener,
            public fit::MonitoringInfoMesgListener,
            public fit::MonitoringMesgListener,
            public fit::MemoGlobMesgListener,
            public fit::PadMesgListener*/
    {
    public :

        FitListener() {}

        /**
         * @brief OnMesg - function for processing messages
         * @param message with type fit::Mesg
         */
        void OnMesg(fit::FileIdMesg& mesg);
        void OnMesg(fit::HrvMesg& mesg);
        /*
        void OnMesg(fit::Mesg& mesg);
        void OnMesgDefinition(fit::MesgDefinition& mesg);
        void OnMesg(fit::MesgWithEvent& mesg);
        void OnMesg(fit::BufferedRecordMesg& mesg);
        void OnMesg(fit::FileCreatorMesg& mesg);
        void OnMesg(fit::SoftwareMesg& mesg);
        void OnMesg(fit::SlaveDeviceMesg& mesg);
        void OnMesg(fit::CapabilitiesMesg& mesg);
        void OnMesg(fit::FileCapabilitiesMesg& mesg);
        void OnMesg(fit::MesgCapabilitiesMesg& mesg);
        void OnMesg(fit::FieldCapabilitiesMesg& mesg);
        void OnMesg(fit::DeviceSettingsMesg& mesg);
        void OnMesg(fit::HrmProfileMesg& mesg);
        void OnMesg(fit::SdmProfileMesg& mesg);
        void OnMesg(fit::BikeProfileMesg& mesg);
        void OnMesg(fit::ZonesTargetMesg& mesg);
        void OnMesg(fit::SportMesg& mesg);
        void OnMesg(fit::HrZoneMesg& mesg);
        void OnMesg(fit::SpeedZoneMesg& mesg);
        void OnMesg(fit::CadenceZoneMesg& mesg);
        void OnMesg(fit::PowerZoneMesg& mesg);
        void OnMesg(fit::GoalMesg& mesg);
        void OnMesg(fit::ActivityMesg& mesg);
        void OnMesg(fit::LapMesg& mesg);
        void OnMesg(fit::EventMesg& mesg);
        void OnMesg(fit::CourseMesg& mesg);
        void OnMesg(fit::CoursePointMesg& mesg);
        void OnMesg(fit::SegmentIdMesg& mesg);
        void OnMesg(fit::SegmentLeaderboardEntryMesg& mesg);
        void OnMesg(fit::SegmentPointMesg& mesg);
        void OnMesg(fit::WorkoutMesg& mesg);
        void OnMesg(fit::TotalsMesg& mesg);
        void OnMesg(fit::WeightScaleMesg& mesg);
        void OnMesg(fit::MonitoringInfoMesg& mesg);
        void OnMesg(fit::MemoGlobMesg& mesg);
        void OnMesg(fit::PadMesg& mesg);
        void OnMesg(fit::WorkoutStepMesg& mesg);
        void OnMesg(fit::SegmentFileMesg& mesg);
        void OnMesg(fit::LengthMesg& mesg);
        void OnMesg(fit::SegmentLapMesg& mesg);
        void OnMesg(fit::ScheduleMesg& mesg);
        void OnMesg(fit::RecordMesg& mesg);
        void OnMesg(fit::TrainingFileMesg& mesg);
        void OnMesg(fit::SessionMesg& mesg);
        void OnMesg(fit::UserProfileMesg& mesg);
        void OnMesg(fit::DeviceInfoMesg& mesg);
        void OnMesg(fit::MonitoringMesg& mesg);
        void OnMesg(fit::BloodPressureMesg& mesg);
        */

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
