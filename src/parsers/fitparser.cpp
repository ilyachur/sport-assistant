#include "fitparser.h"

#include "../parsers/parser_runtime_exception.h"
#include <QDebug>
#include <fstream>

FitParser::FitParser(QString file) {
    file_name = file;
    listener.setFileInfo(&fileInfo);
    mesgBroadcaster.AddListener((fit::FileIdMesgListener &)listener);
    mesgBroadcaster.AddListener((fit::UserProfileMesgListener &)listener);
    mesgBroadcaster.AddListener((fit::MonitoringMesgListener &)listener);
    mesgBroadcaster.AddListener((fit::DeviceInfoMesgListener &)listener);
    mesgBroadcaster.AddListener((fit::RecordMesgListener &)listener);
    mesgBroadcaster.AddListener((fit::HrvMesgListener &)listener);
    mesgBroadcaster.AddListener((fit::BloodPressureMesgListener &)listener);
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

//////// LISTENER /////////////////////////

void FitParser::FitListener::OnMesg(fit::Mesg& mesg) {
    /*qDebug() << "On Mesg:\n";
    qDebug() << "   New Mesg: " << mesg.GetName().c_str() << ".  It has " << mesg.GetNumFields() << " field(s).";
    for (int i=0; i< mesg.GetNumFields(); i++) {
        fit::Field* field = mesg.GetFieldByIndex(i);
        qDebug() << "   Field" << i << " (" << field->GetName().c_str() << ") has " << field->GetNumValues() << " value(s).";
        for (int j=0; j<field->GetNumValues(); j++) {
            qDebug() << "       Val" << j << ": ";
            switch (field->GetType()) {
            case FIT_BASE_TYPE_ENUM:
                qDebug() << "           " << field->GetENUMValue(j);
                break;
            case FIT_BASE_TYPE_SINT8:
                qDebug() << "           " << field->GetSINT8Value(j);
                break;
            case FIT_BASE_TYPE_UINT8:
                qDebug() << "           " << field->GetUINT8Value(j);
                break;
            case FIT_BASE_TYPE_SINT16:
                qDebug() << "           " << field->GetSINT16Value(j);
                break;
            case FIT_BASE_TYPE_UINT16:
                qDebug() << "           " << field->GetUINT16Value(j);
                break;
            case FIT_BASE_TYPE_SINT32:
                qDebug() << "           " << field->GetSINT32Value(j);
                break;
            case FIT_BASE_TYPE_UINT32:
                qDebug() << "           " << field->GetUINT32Value(j);
                break;
            case FIT_BASE_TYPE_FLOAT32:
                qDebug() << "           " << field->GetFLOAT32Value(j);
                break;
            case FIT_BASE_TYPE_FLOAT64:
                qDebug() << "           " << field->GetFLOAT64Value(j);
                break;
            case FIT_BASE_TYPE_UINT8Z:
                qDebug() << "           " << field->GetUINT8ZValue(j);
                break;
            case FIT_BASE_TYPE_UINT16Z:
                qDebug() << "           " << field->GetUINT16ZValue(j);
                break;
            case FIT_BASE_TYPE_UINT32Z:
                qDebug() << "           " << field->GetUINT32ZValue(j);
                break;
            default:
                break;
            }
        }
    }*/
}

void FitParser::FitListener::OnMesg(fit::FileIdMesg& mesg) {
    /*qDebug() << "File ID:\n";
    if (mesg.GetType() != FIT_FILE_INVALID)
        qDebug() << "   Type: " << mesg.GetType();
    if (mesg.GetManufacturer() != FIT_MANUFACTURER_INVALID)
        qDebug() << "   Manufacturer: " << mesg.GetManufacturer();
    if (mesg.GetProduct() != FIT_UINT16_INVALID)
        qDebug() << "   Product: " << mesg.GetProduct();
    if (mesg.GetSerialNumber() != FIT_UINT32Z_INVALID)
        qDebug() << "   Serial Number: " << mesg.GetSerialNumber();
    if (mesg.GetNumber() != FIT_UINT16_INVALID)
        qDebug() << "   Number: " << mesg.GetNumber();*/
    mesg.GetType();
}

void FitParser::FitListener::OnMesg(fit::UserProfileMesg& mesg) {
    /*qDebug() << "User profile:";
    if (mesg.GetFriendlyName() != FIT_WSTRING_INVALID)
        qDebug() << "   Friendly Name: " << mesg.GetFriendlyName().c_str();
    if (mesg.GetGender() == FIT_GENDER_MALE)
        qDebug() << "   Gender: Male";
    if (mesg.GetGender() == FIT_GENDER_FEMALE)
        qDebug() << "   Gender: Female";
    if (mesg.GetAge() != FIT_UINT8_INVALID)
        qDebug() << "   Age [years]: ", mesg.GetAge();
    if (mesg.GetWeight() != FIT_FLOAT32_INVALID)
        qDebug() << "   Weight [kg]: " << mesg.GetWeight();*/
}

void FitParser::FitListener::OnMesg(fit::DeviceInfoMesg& mesg) {
    //qDebug() << "Device info:";
    if (mesg.GetTimestamp() != FIT_UINT32_INVALID) {
        //qDebug() << "   Timestamp: " << mesg.GetTimestamp();

        QMap<QString, QString> testCalue = (*info)["Times"];
        if (testCalue.take("StartTime") == "") {
            testCalue.insert("StartTime", QString::number(mesg.GetTimestamp()));
            info->insert("Times", testCalue);
        }
    }

    switch(mesg.GetBatteryStatus()) {
    case FIT_BATTERY_STATUS_CRITICAL:
        //qDebug() <<"   Battery status: Critical";
        break;
    case FIT_BATTERY_STATUS_GOOD:
        //qDebug() << "   Battery status: Good";
        break;
    case FIT_BATTERY_STATUS_LOW:
        //qDebug() << "   Battery status: Low";
        break;
    case FIT_BATTERY_STATUS_NEW:
        //qDebug() << "   Battery status: New";
        break;
    case FIT_BATTERY_STATUS_OK:
        //qDebug() << "   Battery status: OK";
        break;
    default:
        //qDebug() << "   Battery status: Invalid";
        break;
    }
}

void FitParser::FitListener::OnMesg(fit::MonitoringMesg& mesg) {
    //qDebug() << "Monitoring: ";
    if (mesg.GetTimestamp() != FIT_UINT32_INVALID) {
        //qDebug() << "   Timestamp: " << mesg.GetTimestamp();
    }

    if(mesg.GetActivityType() != FIT_ACTIVITY_TYPE_INVALID) {
        //qDebug() << "   Activity type: " << mesg.GetActivityType();
    }

    switch(mesg.GetActivityType()) // The Cycling field is dynamic
    {
    case FIT_ACTIVITY_TYPE_WALKING:
    case FIT_ACTIVITY_TYPE_RUNNING: // Intentional fallthrough
        if(mesg.GetSteps() != FIT_UINT32_INVALID) {
            //qDebug() << "   Steps: " << mesg.GetSteps();
        }
        break;
    case FIT_ACTIVITY_TYPE_CYCLING:
    case FIT_ACTIVITY_TYPE_SWIMMING: // Intentional fallthrough
        if(mesg.GetStrokes() != (FIT_FLOAT32)(FIT_UINT32_INVALID/2) ) {
            //qDebug() << "Strokes: " << mesg.GetStrokes();
        }
        break;
    default:
        if(mesg.GetCycles() != (FIT_FLOAT32)(FIT_UINT32_INVALID/2) ) {
            //qDebug() << "Cycles: " << mesg.GetStrokes();
        }
        break;
    }
}

void FitParser::FitListener::OnMesg(fit::HrvMesg& mesg) {
    //qDebug() << "HrvMesg: ";
    QMap<QString, QString> testCalue = (*info)["HrvMesg"];
    static unsigned long long time_last = 0;
    if (!time_last) {
        QMap<QString, QString> testTime = (*info)["Times"];
        if (testTime["StartTime"] != "") {
            time_last = testTime["StartTime"].toULongLong();
            time_last *= 1000;
        }
    }
    if (mesg.GetTime(0) != FIT_FLOAT32_INVALID) {
        int ms_hrv = int(mesg.GetTime(0) * 1000.0);
        time_last += ms_hrv;
        testCalue.insert(QString::number(time_last),
                         QString::number(mesg.GetTime(0)));
        info->insert("HrvMesg", testCalue);
        //qDebug() <<"   Time: " << mesg.GetTime(0);
    }
    if (mesg.GetNumTime() != FIT_UINT8_INVALID) {
        //qDebug() << "   NumTime: " << mesg.GetNumTime();

    }
}

void FitParser::FitListener::OnMesg(fit::BloodPressureMesg& mesg) {
/*    qDebug() << "BloodPressureMesg:";
    qDebug() << "   GetTimestamp: " << mesg.GetTimestamp();
    qDebug() << "   GetSystolicPressure: " << mesg.GetSystolicPressure();
    qDebug() << "   GetDiastolicPressure: "<< mesg.GetDiastolicPressure();
    qDebug() << "   GetMeanArterialPressure: " << mesg.GetMeanArterialPressure();
    qDebug() << "   GetMap3SampleMean: " << mesg.GetMap3SampleMean();
    qDebug() << "   GetMapMorningValues: " << mesg.GetMapMorningValues();
    qDebug() << "   GetMapEveningValues: " << mesg.GetMapEveningValues();
    qDebug() << "   GetHeartRate: " << mesg.GetHeartRate();
    qDebug() << "   GetHeartRateType: " << mesg.GetHeartRateType();
    qDebug() << "   GetStatus: " << mesg.GetStatus();
    qDebug() << "   GetUserProfileIndex: " << mesg.GetUserProfileIndex();*/
}
