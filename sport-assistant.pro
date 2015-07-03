#-------------------------------------------------
#
# Project created by QtCreator 2015-07-03T12:46:07
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = sport-assistant
TEMPLATE = app


SOURCES += src/main.cpp\
        src/mainwindow.cpp \
    src/parsers/fitparser.cpp \
    src/fit/fit.cpp \
    src/fit/fit_accumulated_field.cpp \
    src/fit/fit_accumulator.cpp \
    src/fit/fit_buffer_encode.cpp \
    src/fit/fit_buffered_mesg_broadcaster.cpp \
    src/fit/fit_buffered_record_mesg_broadcaster.cpp \
    src/fit/fit_crc.cpp \
    src/fit/fit_decode.cpp \
    src/fit/fit_encode.cpp \
    src/fit/fit_factory.cpp \
    src/fit/fit_field.cpp \
    src/fit/fit_field_definition.cpp \
    src/fit/fit_mesg.cpp \
    src/fit/fit_mesg_broadcaster.cpp \
    src/fit/fit_mesg_definition.cpp \
    src/fit/fit_mesg_with_event_broadcaster.cpp \
    src/fit/fit_profile.cpp \
    src/fit/fit_unicode.cpp

HEADERS  += src/mainwindow.h \
    src/parsers/fitparser.h \
    src/fit/fit.hpp \
    src/fit/fit_accumulated_field.hpp \
    src/fit/fit_accumulator.hpp \
    src/fit/fit_activity_mesg.hpp \
    src/fit/fit_activity_mesg_listener.hpp \
    src/fit/fit_bike_profile_mesg.hpp \
    src/fit/fit_bike_profile_mesg_listener.hpp \
    src/fit/fit_blood_pressure_mesg.hpp \
    src/fit/fit_blood_pressure_mesg_listener.hpp \
    src/fit/fit_buffer_encode.hpp \
    src/fit/fit_buffered_mesg_broadcaster.hpp \
    src/fit/fit_buffered_record_mesg.hpp \
    src/fit/fit_buffered_record_mesg_broadcaster.hpp \
    src/fit/fit_buffered_record_mesg_listener.hpp \
    src/fit/fit_cadence_zone_mesg.hpp \
    src/fit/fit_cadence_zone_mesg_listener.hpp \
    src/fit/fit_capabilities_mesg.hpp \
    src/fit/fit_capabilities_mesg_listener.hpp \
    src/fit/fit_config.hpp \
    src/fit/fit_course_mesg.hpp \
    src/fit/fit_course_mesg_listener.hpp \
    src/fit/fit_course_point_mesg.hpp \
    src/fit/fit_course_point_mesg_listener.hpp \
    src/fit/fit_crc.hpp \
    src/fit/fit_decode.hpp \
    src/fit/fit_device_info_mesg.hpp \
    src/fit/fit_device_info_mesg_listener.hpp \
    src/fit/fit_device_settings_mesg.hpp \
    src/fit/fit_device_settings_mesg_listener.hpp \
    src/fit/fit_encode.hpp \
    src/fit/fit_event_mesg.hpp \
    src/fit/fit_event_mesg_listener.hpp \
    src/fit/fit_factory.hpp \
    src/fit/fit_field.hpp \
    src/fit/fit_field_capabilities_mesg.hpp \
    src/fit/fit_field_capabilities_mesg_listener.hpp \
    src/fit/fit_field_definition.hpp \
    src/fit/fit_file_capabilities_mesg.hpp \
    src/fit/fit_file_capabilities_mesg_listener.hpp \
    src/fit/fit_file_creator_mesg.hpp \
    src/fit/fit_file_creator_mesg_listener.hpp \
    src/fit/fit_file_id_mesg.hpp \
    src/fit/fit_file_id_mesg_listener.hpp \
    src/fit/fit_goal_mesg.hpp \
    src/fit/fit_goal_mesg_listener.hpp \
    src/fit/fit_hr_zone_mesg.hpp \
    src/fit/fit_hr_zone_mesg_listener.hpp \
    src/fit/fit_hrm_profile_mesg.hpp \
    src/fit/fit_hrm_profile_mesg_listener.hpp \
    src/fit/fit_hrv_mesg.hpp \
    src/fit/fit_hrv_mesg_listener.hpp \
    src/fit/fit_lap_mesg.hpp \
    src/fit/fit_lap_mesg_listener.hpp \
    src/fit/fit_length_mesg.hpp \
    src/fit/fit_length_mesg_listener.hpp \
    src/fit/fit_memo_glob_mesg.hpp \
    src/fit/fit_memo_glob_mesg_listener.hpp \
    src/fit/fit_mesg.hpp \
    src/fit/fit_mesg_broadcast_plugin.hpp \
    src/fit/fit_mesg_broadcaster.hpp \
    src/fit/fit_mesg_capabilities_mesg.hpp \
    src/fit/fit_mesg_capabilities_mesg_listener.hpp \
    src/fit/fit_mesg_definition.hpp \
    src/fit/fit_mesg_definition_listener.hpp \
    src/fit/fit_mesg_listener.hpp \
    src/fit/fit_mesg_with_event.hpp \
    src/fit/fit_mesg_with_event_broadcaster.hpp \
    src/fit/fit_mesg_with_event_listener.hpp \
    src/fit/fit_met_zone_mesg.hpp \
    src/fit/fit_met_zone_mesg_listener.hpp \
    src/fit/fit_monitoring_info_mesg.hpp \
    src/fit/fit_monitoring_info_mesg_listener.hpp \
    src/fit/fit_monitoring_mesg.hpp \
    src/fit/fit_monitoring_mesg_listener.hpp \
    src/fit/fit_pad_mesg.hpp \
    src/fit/fit_pad_mesg_listener.hpp \
    src/fit/fit_power_zone_mesg.hpp \
    src/fit/fit_power_zone_mesg_listener.hpp \
    src/fit/fit_profile.hpp \
    src/fit/fit_record_mesg.hpp \
    src/fit/fit_record_mesg_listener.hpp \
    src/fit/fit_runtime_exception.hpp \
    src/fit/fit_schedule_mesg.hpp \
    src/fit/fit_schedule_mesg_listener.hpp \
    src/fit/fit_sdm_profile_mesg.hpp \
    src/fit/fit_sdm_profile_mesg_listener.hpp \
    src/fit/fit_segment_file_mesg.hpp \
    src/fit/fit_segment_file_mesg_listener.hpp \
    src/fit/fit_segment_id_mesg.hpp \
    src/fit/fit_segment_id_mesg_listener.hpp \
    src/fit/fit_segment_lap_mesg.hpp \
    src/fit/fit_segment_lap_mesg_listener.hpp \
    src/fit/fit_segment_leaderboard_entry_mesg.hpp \
    src/fit/fit_segment_leaderboard_entry_mesg_listener.hpp \
    src/fit/fit_segment_point_mesg.hpp \
    src/fit/fit_segment_point_mesg_listener.hpp \
    src/fit/fit_session_mesg.hpp \
    src/fit/fit_session_mesg_listener.hpp \
    src/fit/fit_slave_device_mesg.hpp \
    src/fit/fit_slave_device_mesg_listener.hpp \
    src/fit/fit_software_mesg.hpp \
    src/fit/fit_software_mesg_listener.hpp \
    src/fit/fit_speed_zone_mesg.hpp \
    src/fit/fit_speed_zone_mesg_listener.hpp \
    src/fit/fit_sport_mesg.hpp \
    src/fit/fit_sport_mesg_listener.hpp \
    src/fit/fit_totals_mesg.hpp \
    src/fit/fit_totals_mesg_listener.hpp \
    src/fit/fit_training_file_mesg.hpp \
    src/fit/fit_training_file_mesg_listener.hpp \
    src/fit/fit_unicode.hpp \
    src/fit/fit_user_profile_mesg.hpp \
    src/fit/fit_user_profile_mesg_listener.hpp \
    src/fit/fit_weight_scale_mesg.hpp \
    src/fit/fit_weight_scale_mesg_listener.hpp \
    src/fit/fit_workout_mesg.hpp \
    src/fit/fit_workout_mesg_listener.hpp \
    src/fit/fit_workout_step_mesg.hpp \
    src/fit/fit_workout_step_mesg_listener.hpp \
    src/fit/fit_zones_target_mesg.hpp \
    src/fit/fit_zones_target_mesg_listener.hpp

FORMS    += forms/mainwindow.ui
