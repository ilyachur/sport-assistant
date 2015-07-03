#include "fitparser.h"

#include "../parsers/parser_runtime_exception.h"
#include <QDebug>
#include <fstream>
#include <iostream>

FitParser::FitParser(QString file) {
    file_name = file;
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

void FitParser::FitListener::OnMesg(fit::Mesg& mesg) {
    qDebug() << "On Mesg:\n";
    qDebug() << "   New Mesg: " << mesg.GetName().c_str() << ".  It has " << mesg.GetNumFields() << " field(s).";
    for (int i=0; i<mesg.GetNumFields(); i++) {
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
    }
}

void FitParser::FitListener::OnMesg(fit::FileIdMesg& mesg) {
    printf("File ID:\n");
    if (mesg.GetType() != FIT_FILE_INVALID)
        printf("   Type: %d\n", mesg.GetType());
    if (mesg.GetManufacturer() != FIT_MANUFACTURER_INVALID)
        printf("   Manufacturer: %d\n", mesg.GetManufacturer());
    if (mesg.GetProduct() != FIT_UINT16_INVALID)
        printf("   Product: %d\n", mesg.GetProduct());
    if (mesg.GetSerialNumber() != FIT_UINT32Z_INVALID)
        printf("   Serial Number: %u\n", mesg.GetSerialNumber());
    if (mesg.GetNumber() != FIT_UINT16_INVALID)
        printf("   Number: %d\n", mesg.GetNumber());
}

void FitParser::FitListener::OnMesg(fit::UserProfileMesg& mesg) {
    printf("User profile:\n");
    if (mesg.GetFriendlyName() != FIT_WSTRING_INVALID)
        std::wcout << L"   Friendly Name: " << mesg.GetFriendlyName().c_str() << L"\n";
    if (mesg.GetGender() == FIT_GENDER_MALE)
        printf("   Gender: Male\n");
    if (mesg.GetGender() == FIT_GENDER_FEMALE)
        printf("   Gender: Female\n");
    if (mesg.GetAge() != FIT_UINT8_INVALID)
        printf("   Age [years]: %d\n", mesg.GetAge());
    if (mesg.GetWeight() != FIT_FLOAT32_INVALID)
        printf("   Weight [kg]: %0.2f\n", mesg.GetWeight());
}

void FitParser::FitListener::OnMesg(fit::DeviceInfoMesg& mesg) {
    printf("Device info:\n");
    if (mesg.GetTimestamp() != FIT_UINT32_INVALID)
        printf("   Timestamp: %d\n", mesg.GetTimestamp());

    switch(mesg.GetBatteryStatus()) {
    case FIT_BATTERY_STATUS_CRITICAL:
        printf("   Battery status: Critical\n");
        break;
    case FIT_BATTERY_STATUS_GOOD:
        printf("   Battery status: Good\n");
        break;
    case FIT_BATTERY_STATUS_LOW:
        printf("   Battery status: Low\n");
        break;
    case FIT_BATTERY_STATUS_NEW:
        printf("   Battery status: New\n");
        break;
    case FIT_BATTERY_STATUS_OK:
        printf("   Battery status: OK\n");
        break;
    default:
        printf("   Battery status: Invalid\n");
        break;
    }
}

void FitParser::FitListener::OnMesg(fit::MonitoringMesg& mesg) {
    printf("Monitoring:\n");
    if (mesg.GetTimestamp() != FIT_UINT32_INVALID) {
        printf("   Timestamp: %d\n", mesg.GetTimestamp());
    }

    if(mesg.GetActivityType() != FIT_ACTIVITY_TYPE_INVALID) {
        printf("   Activity type: %d\n", mesg.GetActivityType());
    }

    switch(mesg.GetActivityType()) // The Cycling field is dynamic
    {
    case FIT_ACTIVITY_TYPE_WALKING:
    case FIT_ACTIVITY_TYPE_RUNNING: // Intentional fallthrough
        if(mesg.GetSteps() != FIT_UINT32_INVALID) {
            printf("   Steps: %d\n", mesg.GetSteps());
        }
        break;
    case FIT_ACTIVITY_TYPE_CYCLING:
    case FIT_ACTIVITY_TYPE_SWIMMING: // Intentional fallthrough
        if(mesg.GetStrokes() != (FIT_FLOAT32)(FIT_UINT32_INVALID/2) ) {
            printf(   "Strokes: %d\n", mesg.GetStrokes());
        }
        break;
    default:
        if(mesg.GetCycles() != (FIT_FLOAT32)(FIT_UINT32_INVALID/2) ) {
            printf(   "Cycles: %d\n", mesg.GetStrokes());
        }
        break;
    }
}

void FitParser::FitListener::OnMesg(fit::HrvMesg& mesg) {
    printf("HrvMesg:\n");
    if (mesg.GetNumTime() != FIT_UINT8_INVALID) {
        printf("   NumTime: %d\n", mesg.GetNumTime());
        if (mesg.GetTime(0) != FIT_FLOAT32_INVALID) {
            printf("   Time: %f\n", mesg.GetTime(0));
        }
    }
}

void FitParser::FitListener::OnMesg(fit::BloodPressureMesg& mesg) {
    printf("BloodPressureMesg:\n");
    printf("   GetTimestamp: %d\n", mesg.GetTimestamp());
    printf("   GetSystolicPressure: %d\n", mesg.GetSystolicPressure());
    printf("   GetDiastolicPressure: %d\n", mesg.GetDiastolicPressure());
    printf("   GetMeanArterialPressure: %d\n", mesg.GetMeanArterialPressure());
    printf("   GetMap3SampleMean: %d\n", mesg.GetMap3SampleMean());
    printf("   GetMapMorningValues: %d\n", mesg.GetMapMorningValues());
    printf("   GetMapEveningValues: %d\n", mesg.GetMapEveningValues());
    printf("   GetHeartRate: %d\n", mesg.GetHeartRate());
    printf("   GetHeartRateType: %d\n", mesg.GetHeartRateType());
    printf("   GetStatus: %d\n", mesg.GetStatus());
    printf("   GetUserProfileIndex: %d\n", mesg.GetUserProfileIndex());
}
