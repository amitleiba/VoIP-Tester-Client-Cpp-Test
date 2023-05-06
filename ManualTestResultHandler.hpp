#pragma once

#include <unordered_map>
#include <functional>

#include "ManualTestOpcode.hpp"
#include "Message.hpp"
#include "VTCPManualStatus.hpp"

class ManualTestHandler {
public:
    ManualTestHandler()
    {
        _manualTestHandlers.emplace(ManualTestOpcode::MANUAL_TEST_REGISTER_RES, std::bind(&ManualTestHandler::onRegisterResult, this, std::placeholders::_1));
        _manualTestHandlers.emplace(ManualTestOpcode::MANUAL_TEST_UNREGISTER_RES, std::bind(&ManualTestHandler::onUnregisterResult, this, std::placeholders::_1));
        _manualTestHandlers.emplace(ManualTestOpcode::MANUAL_TEST_CALL_RES, std::bind(&ManualTestHandler::onCallResult, this, std::placeholders::_1));
        _manualTestHandlers.emplace(ManualTestOpcode::MANUAL_TEST_HANGUP_RES, std::bind(&ManualTestHandler::onHangupResult, this, std::placeholders::_1));
        _manualTestHandlers.emplace(ManualTestOpcode::MANUAL_TEST_ANSWER_RES, std::bind(&ManualTestHandler::onAnswerResult, this, std::placeholders::_1));
        _manualTestHandlers.emplace(ManualTestOpcode::MANUAL_TEST_DECLINE_RES, std::bind(&ManualTestHandler::onDeclineResult, this, std::placeholders::_1));
    }

    void handleManualTest(const Message& data)
    {
        try
        {
            auto opcode = static_cast<ManualTestOpcode>(data.readInteger());
            _manualTestHandlers.at(opcode)(data);
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << std::endl;
        }
    }

private:
    void onRegisterResult(const Message& data) {
        // auto index = data.read_integer();
        // auto status = static_cast<VTCPManualStatus>(data.read_integer());
        // auto uri = data.read_string();

        // if (index == 0) {
        //     if (status == VTCPManualStatus::OK) {
        //         _updateManualTestLabel1();
        //     }
        // }
    }

    void onUnregisterResult(const Message& data) {
        // auto index = data.read_integer();
        // auto status = static_cast<VTCPManualStatus>(data.read_integer());
    }

    void onCallResult(const Message& data) {
        // auto index = data.read_integer();
        // auto status = static_cast<VTCPManualStatus>(data.read_integer());
    }

    void onHangupResult(const Message& data) {
        // auto index = data.read_integer();
        // auto status = static_cast<VTCPManualStatus>(data.read_integer());
    }

    void onAnswerResult(const Message& data) {
        // auto index = data.read_integer();
        // auto status = static_cast<VTCPManualStatus>(data.read_integer());
    }

    void onDeclineResult(const Message& data) {
        // auto index = data.read_integer();
        // auto status = static_cast<VTCPManualStatus>(data.read_integer());
    }

    std::unordered_map<ManualTestOpcode, std::function<void(const Message &)>> _manualTestHandlers;
};
