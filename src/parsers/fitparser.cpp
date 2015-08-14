#include "fitparser.h"

#include "../parsers/parser_runtime_exception.h"
#include <QDebug>
#include <fstream>
#include <QDateTime>


/// @file fitparser.cpp
/// @brief Contains definition of fit parser class
/// @author Ilya Churaev ilyachur@gmail.com

FitParser::FitParser(QString file) {
    file_name = file;
    listener.setFileInfo(&fileInfo);

    // Add listeners
    mesgBroadcaster.AddListener((fit::FileIdMesgListener &)listener);
    mesgBroadcaster.AddListener((fit::HrvMesgListener &)listener);

    /*
    mesgBroadcaster.AddListener((fit::MesgDefinitionListener &)listener);
    mesgBroadcaster.AddListener((fit::MesgListener &)listener);
    mesgBroadcaster.AddListener((fit::MesgWithEventListener &)listener);
    mesgBroadcaster.AddListener((fit::BufferedRecordMesgListener &)listener);
    mesgBroadcaster.AddListener((fit::FileCreatorMesgListener &)listener);
    mesgBroadcaster.AddListener((fit::SoftwareMesgListener &)listener);
    mesgBroadcaster.AddListener((fit::SlaveDeviceMesgListener &)listener);
    mesgBroadcaster.AddListener((fit::CapabilitiesMesgListener &)listener);
    mesgBroadcaster.AddListener((fit::FileCapabilitiesMesgListener &)listener);
    mesgBroadcaster.AddListener((fit::MesgCapabilitiesMesgListener &)listener);
    mesgBroadcaster.AddListener((fit::FieldCapabilitiesMesgListener &)listener);
    mesgBroadcaster.AddListener((fit::DeviceSettingsMesgListener &)listener);
    mesgBroadcaster.AddListener((fit::UserProfileMesgListener &)listener);
    mesgBroadcaster.AddListener((fit::HrmProfileMesgListener &)listener);
    mesgBroadcaster.AddListener((fit::SdmProfileMesgListener &)listener);
    mesgBroadcaster.AddListener((fit::BikeProfileMesgListener &)listener);
    mesgBroadcaster.AddListener((fit::ZonesTargetMesgListener &)listener);
    mesgBroadcaster.AddListener((fit::SportMesgListener &)listener);
    mesgBroadcaster.AddListener((fit::HrZoneMesgListener &)listener);
    mesgBroadcaster.AddListener((fit::SpeedZoneMesgListener &)listener);
    mesgBroadcaster.AddListener((fit::CadenceZoneMesgListener &)listener);
    mesgBroadcaster.AddListener((fit::PowerZoneMesgListener &)listener);
    mesgBroadcaster.AddListener((fit::GoalMesgListener &)listener);
    mesgBroadcaster.AddListener((fit::ActivityMesgListener &)listener);
    mesgBroadcaster.AddListener((fit::SessionMesgListener &)listener);
    mesgBroadcaster.AddListener((fit::LapMesgListener &)listener);
    mesgBroadcaster.AddListener((fit::LengthMesgListener &)listener);
    mesgBroadcaster.AddListener((fit::RecordMesgListener &)listener);
    mesgBroadcaster.AddListener((fit::EventMesgListener &)listener);
    mesgBroadcaster.AddListener((fit::DeviceInfoMesgListener &)listener);
    mesgBroadcaster.AddListener((fit::TrainingFileMesgListener &)listener);
    mesgBroadcaster.AddListener((fit::CourseMesgListener &)listener);
    mesgBroadcaster.AddListener((fit::CoursePointMesgListener &)listener);
    mesgBroadcaster.AddListener((fit::SegmentIdMesgListener &)listener);
    mesgBroadcaster.AddListener((fit::SegmentLeaderboardEntryMesgListener &)listener);
    mesgBroadcaster.AddListener((fit::SegmentPointMesgListener &)listener);
    mesgBroadcaster.AddListener((fit::SegmentLapMesgListener &)listener);
    mesgBroadcaster.AddListener((fit::SegmentFileMesgListener &)listener);
    mesgBroadcaster.AddListener((fit::WorkoutMesgListener &)listener);
    mesgBroadcaster.AddListener((fit::WorkoutStepMesgListener &)listener);
    mesgBroadcaster.AddListener((fit::ScheduleMesgListener &)listener);
    mesgBroadcaster.AddListener((fit::TotalsMesgListener &)listener);
    mesgBroadcaster.AddListener((fit::WeightScaleMesgListener &)listener);
    mesgBroadcaster.AddListener((fit::BloodPressureMesgListener &)listener);
    mesgBroadcaster.AddListener((fit::MonitoringInfoMesgListener &)listener);
    mesgBroadcaster.AddListener((fit::MonitoringMesgListener &)listener);
    mesgBroadcaster.AddListener((fit::MemoGlobMesgListener &)listener);
    mesgBroadcaster.AddListener((fit::PadMesgListener &)listener);
    */
}

int FitParser::open(QString file) {
    if (!file.isEmpty())
        file_name = file;
    ifile.open(file_name.toStdString(), std::ios::in | std::ios::binary);
    if (!ifile.is_open()) {
        qDebug() << "Error opening file " << file_name;
        return PARSER_OPEN_FILE_ERR;
    }
    if (!decode.CheckIntegrity(ifile)) {
        qDebug() << "FIT file integrity failed.";
        return PARSER_INTEGRITY_FILE_ERR;
    }
    return PARSER_OK;
}

int FitParser::run() {
    if (!ifile.is_open()) {
        int return_code;
        return_code = open();
        if (return_code != PARSER_OK)
            return return_code;
    }

    try {
       mesgBroadcaster.Run(ifile);
    }
    catch (const ParserRuntimeException& e)
    {
       qDebug() << "Exception decoding file: " << e.what();
       return PARSER_EXCEPTION;
    }

    return PARSER_OK;
}


QMap<QString, QMap<QString, QString>> *FitParser::getInfo() {
    return &fileInfo;
}

QDateTime FitParser::getRealTimeFromFit(FIT_DATE_TIME dateTime) {
    QDateTime realTime;
    QDate shiftDate;
    shiftDate.setDate(1989, 12, 31);

    qint64 qDateTimeSec = dateTime;
    realTime.setDate(shiftDate);

    realTime.setMSecsSinceEpoch(realTime.toMSecsSinceEpoch() + (qDateTimeSec * 1000));

    return realTime;
}

//////// LISTENER /////////////////////////

void FitParser::FitListener::OnMesg(fit::FileIdMesg& mesg) {
    QDateTime startTime = getRealTimeFromFit(mesg.GetTimeCreated());
    QMap<QString, QString> testCalue = (*info)["Times"];
    if (testCalue.take("StartTime") == "") {
        testCalue.insert("StartTime", QString::number(startTime.toMSecsSinceEpoch()));
        info->insert("Times", testCalue);
    }
}

void FitParser::FitListener::OnMesg(fit::HrvMesg& mesg) {
    QMap<QString, QString> testCalue = (*info)["HrvMesg"];
    if (!time_last) {
        QMap<QString, QString> testTime = (*info)["Times"];
        if (testTime["StartTime"] != "") {
            time_last = testTime["StartTime"].toULongLong();
        }
    }
    if (mesg.GetTime(0) != FIT_FLOAT32_INVALID) {
        int ms_hrv = (int)(mesg.GetTime(0) * 1000);
        testCalue.insert(QString::number(time_last),
                         QString::number(mesg.GetTime(0)));
        time_last += ms_hrv;
        info->insert("HrvMesg", testCalue);
    }
}
/*
void FitParser::FitListener::OnMesg(fit::BloodPressureMesg& mesg) {}

void FitParser::FitListener::OnMesg(fit::UserProfileMesg& mesg) {}

void FitParser::FitListener::OnMesg(fit::DeviceInfoMesg& mesg) {}

void FitParser::FitListener::OnMesg(fit::MonitoringMesg& mesg) {}

void FitParser::FitListener::OnMesg(fit::PadMesg& mesg) {}

void FitParser::FitListener::OnMesgDefinition(fit::MesgDefinition& mesg) {}

void FitParser::FitListener::OnMesg(fit::MemoGlobMesg& mesg) {}

void FitParser::FitListener::OnMesg(fit::MonitoringInfoMesg& mesg) {}

void FitParser::FitListener::OnMesg(fit::WeightScaleMesg& mesg) {}

void FitParser::FitListener::OnMesg(fit::TotalsMesg& mesg) {}

void FitParser::FitListener::OnMesg(fit::WorkoutStepMesg& mesg) {}

void FitParser::FitListener::OnMesg(fit::WorkoutMesg& mesg) {}

void FitParser::FitListener::OnMesg(fit::SegmentPointMesg& mesg) {}

void FitParser::FitListener::OnMesg(fit::SegmentLeaderboardEntryMesg& mesg) {}

void FitParser::FitListener::OnMesg(fit::SegmentIdMesg& mesg) {}

void FitParser::FitListener::OnMesg(fit::CoursePointMesg& mesg) {}

void FitParser::FitListener::OnMesg(fit::CourseMesg& mesg) {}

void FitParser::FitListener::OnMesg(fit::EventMesg& mesg) {}

void FitParser::FitListener::OnMesg(fit::LapMesg& mesg) {}

void FitParser::FitListener::OnMesg(fit::ActivityMesg& mesg) {}

void FitParser::FitListener::OnMesg(fit::GoalMesg& mesg) {}

void FitParser::FitListener::OnMesg(fit::PowerZoneMesg& mesg) {}

void FitParser::FitListener::OnMesg(fit::CadenceZoneMesg& mesg) {}

void FitParser::FitListener::OnMesg(fit::SpeedZoneMesg& mesg) {}

void FitParser::FitListener::OnMesg(fit::HrZoneMesg& mesg) {}

void FitParser::FitListener::OnMesg(fit::SportMesg& mesg) {}

void FitParser::FitListener::OnMesg(fit::ZonesTargetMesg& mesg) {}

void FitParser::FitListener::OnMesg(fit::BikeProfileMesg& mesg) {}

void FitParser::FitListener::OnMesg(fit::SdmProfileMesg& mesg) {}

void FitParser::FitListener::OnMesg(fit::HrmProfileMesg& mesg) {}

void FitParser::FitListener::OnMesg(fit::DeviceSettingsMesg& mesg) {}

void FitParser::FitListener::OnMesg(fit::FieldCapabilitiesMesg& mesg) {}

void FitParser::FitListener::OnMesg(fit::FileCapabilitiesMesg& mesg) {}

void FitParser::FitListener::OnMesg(fit::MesgCapabilitiesMesg& mesg) {}

void FitParser::FitListener::OnMesg(fit::CapabilitiesMesg& mesg) {}

void FitParser::FitListener::OnMesg(fit::SlaveDeviceMesg& mesg) {}

void FitParser::FitListener::OnMesg(fit::SoftwareMesg& mesg) {}

void FitParser::FitListener::OnMesg(fit::FileCreatorMesg& mesg) {}

void FitParser::FitListener::OnMesg(fit::BufferedRecordMesg& mesg) {}

void FitParser::FitListener::OnMesg(fit::MesgWithEvent& mesg) {}

void FitParser::FitListener::OnMesg(fit::TrainingFileMesg& mesg) {}

void FitParser::FitListener::OnMesg(fit::SegmentFileMesg& mesg) {}

void FitParser::FitListener::OnMesg(fit::SegmentLapMesg& mesg) {}

void FitParser::FitListener::OnMesg(fit::ScheduleMesg& mesg) {}

void FitParser::FitListener::OnMesg(fit::RecordMesg& mesg) {}

void FitParser::FitListener::OnMesg(fit::LengthMesg& mesg) {}

void FitParser::FitListener::OnMesg(fit::SessionMesg& mesg) {}

void FitParser::FitListener::OnMesg(fit::Mesg& mesg) {}
*/
