#ifndef FITPARSER_H
#define FITPARSER_H

#include <QString>
#include <fstream>
#include <iostream>
#include "../fit/fit_decode.hpp"
#include "../fit/fit_mesg_broadcaster.hpp"

class FitParser
{

public:
    FitParser(QString file = "");
    int test();
    int open(QString file = "");
    int run();

private:
    QString file_name;
    std::fstream ifile;
    fit::Decode decode;
    fit::MesgBroadcaster mesgBroadcaster;

    class FitListener : public fit::FileIdMesgListener,
            public fit::BloodPressureMesgListener,
            public fit::UserProfileMesgListener,
            public fit::MonitoringMesgListener,
            public fit::DeviceInfoMesgListener,
            public fit::HrvMesgListener,
            public fit::MesgListener {
    public :
        void OnMesg(fit::Mesg& mesg);

        void OnMesg(fit::FileIdMesg& mesg);

        void OnMesg(fit::UserProfileMesg& mesg);

        void OnMesg(fit::DeviceInfoMesg& mesg);

        void OnMesg(fit::MonitoringMesg& mesg);

        void OnMesg(fit::HrvMesg& mesg);

        void OnMesg(fit::BloodPressureMesg& mesg);
    };

    FitListener listener;
};

#endif // FITPARSER_H
