#pragma once

#include <iostream>
#include <unordered_map>
#include <memory>
#include <array>
#include <atomic>
#include <condition_variable>
#include <string>
#include <sstream>

#include <QSharedPointer>
#include <QTextBrowser>
#include <QString>

#include <pjsua2.hpp>

#include "Softphone.hpp"
#include "SoftphoneArguments.hpp"
#include "ManualTestOpcode.hpp"
#include "Message.hpp"
#include "VTCPManualStatus.hpp"
#include "PjManager.hpp"
#include "MainWindow.hpp"

class ManualTestHandler {
public:
    ManualTestHandler(QSharedPointer<MainWindow> mainWindow):
        _mainWindow(std::move(mainWindow))
    {
        _manualTestHandlers.emplace(ManualTestOpcode::MANUAL_TEST_REGISTER_REQ, std::bind(&ManualTestHandler::manualTestRegister, this, std::placeholders::_1));
        _manualTestHandlers.emplace(ManualTestOpcode::MANUAL_TEST_UNREGISTER_REQ, std::bind(&ManualTestHandler::manualTestUnregister, this, std::placeholders::_1));
        _manualTestHandlers.emplace(ManualTestOpcode::MANUAL_TEST_CALL_REQ, std::bind(&ManualTestHandler::manualTestCall, this, std::placeholders::_1));
        _manualTestHandlers.emplace(ManualTestOpcode::MANUAL_TEST_HANGUP_REQ, std::bind(&ManualTestHandler::manualTestHangup, this, std::placeholders::_1));
        _manualTestHandlers.emplace(ManualTestOpcode::MANUAL_TEST_ANSWER_REQ, std::bind(&ManualTestHandler::manualTestAnswer, this, std::placeholders::_1));
        _manualTestHandlers.emplace(ManualTestOpcode::MANUAL_TEST_DECLINE_REQ, std::bind(&ManualTestHandler::manualTestDecline, this, std::placeholders::_1));
    }

    ~ManualTestHandler() = default;

    void handleManualTest(const Message& request)
    {
        try
        {
            auto op = request.readInteger();
            auto opcode = static_cast<ManualTestOpcode>(op);
            _manualTestHandlers.at(opcode)(request);
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << std::endl;
        }
    }

private:
    void manualTestRegister(const Message& request)
    {
        auto index = request.readInteger();
        auto id = request.readInteger();
        auto domain = request.readString();

        QTextBrowser* textBrowser;



        if(!(index >= 0 && index <= 2))
        {
            std::cout << "Manual test index error" << std::endl;
            return;
        }
        else if(index == 0)
        {
            textBrowser = _mainWindow->ui->softphone_log_text_browser_1;
        }
        else if(index == 1)
        {
            textBrowser = _mainWindow->ui->softphone_log_text_browser_2;
        }
        else if(index == 2)
        {
            textBrowser = _mainWindow->ui->softphone_log_text_browser_3;
        }
        if(_manualTestSoftphones[index])
        {
            std::string errorMessage = "The softphone is already registered\n";
            textBrowser->insertPlainText(QString::fromStdString(errorMessage));
        }
        if(id > 0 && id < 9999)
        {
            std::string errorMessage = "Invalid ID, the ID cant be between 0 to 9999\n";
            textBrowser->insertPlainText(QString::fromStdString(errorMessage));
            return;
        }
        else
        {
            _manualTestSoftphones.at(index) = std::make_shared<Softphone>(
                SoftphoneArguments(DEFAULT_SECRET, domain, DEFAULT_TIMEOUT, id),
                std::bind(&ManualTestHandler::onCallState, this, std::placeholders::_1,
                          std::placeholders::_2, std::placeholders::_3),
                std::bind(&ManualTestHandler::onRegState, this, std::placeholders::_1,
                          std::placeholders::_2, std::placeholders::_3),
                std::bind(&ManualTestHandler::onIncomingCall, this, std::placeholders::_1,
                          std::placeholders::_2, std::placeholders::_3));
//            response.push(static_cast<int>(VTCP_MANUAL_STATUS::OK));
//            response.push(index);
//            response.push(_manualTestSoftphones.at(index)->getUri());
        }
    }

    void manualTestUnregister(const Message& request)
    {
        auto index = request.readInteger();

        if(!(index >= 0 && index <= 2) || !_manualTestSoftphones[index])
        {
//            response.push(static_cast<int>(VTCP_MANUAL_STATUS::CLIENT_ERROR));
        }
        else
        {
            _manualTestSoftphones[index]->unregisterAccount();
            sleep(1);
            _manualTestSoftphones[index] = nullptr;
//            response.push(static_cast<int>(VTCP_MANUAL_STATUS::OK));
//            response.push(index);
        }
    }

    void manualTestCall(const Message& request)
    {
        auto index = request.readInteger();
        auto destUri = request.readString();

        if(!(index >= 0 && index <= 2) || !_manualTestSoftphones[index])
        {
//            response.push(static_cast<int>(VTCP_MANUAL_STATUS::CLIENT_ERROR));
        }
        else
        {
            bool found = false;
            for(int i = 0; i < _manualTestSoftphones.max_size(); i++)
            {
                if(i != index && _manualTestSoftphones[i])
                {
                    if(_manualTestSoftphones[i]->getUri() == destUri)
                    {
                        found = true;
                    }
                }
            }

            if(!found)
            {
//                response.push(static_cast<int>(VTCP_MANUAL_STATUS::CLIENT_ERROR));
            }

            else
            {
                _manualTestSoftphones[index]->call(destUri);
//                response.push(index);
//                response.push(static_cast<int>(VTCP_MANUAL_STATUS::OK));
            }
        }
    }

    void manualTestHangup(const Message& request)
    {
        auto index = request.readInteger();

        if(!(index >= 0 && index <= 2) || !_manualTestSoftphones[index])
        {
//            response.push(static_cast<int>(VTCP_MANUAL_STATUS::CLIENT_ERROR));
        }
        else
        {
            _manualTestSoftphones[index]->hangup();
//            response.push(static_cast<int>(VTCP_MANUAL_STATUS::OK));
//            response.push(index);
        }
    }

    void manualTestAnswer(const Message& request)
    {
        auto index = request.readInteger();

        if(!(index >= 0 && index <= 2) || !_manualTestSoftphones[index])
        {
//            response.push(static_cast<int>(VTCP_MANUAL_STATUS::CLIENT_ERROR));
        }
        else
        {
            _manualTestSoftphones[index]->setAnsweredIncomingCall(true);
            _cv.notify_one();
//            response.push(static_cast<int>(VTCP_MANUAL_STATUS::OK));
//            response.push(index);
        }
    }

    void manualTestDecline(const Message& request)
    {
        auto index = request.readInteger();

        if(!(index >= 0 && index <= 2) || !_manualTestSoftphones[index])
        {
//            response.push(static_cast<int>(VTCP_MANUAL_STATUS::CLIENT_ERROR));
        }
        else
        {
            _manualTestSoftphones[index]->setDeclinedIncomingCall(true);
            _cv.notify_one();
//            response.push(static_cast<int>(VTCP_MANUAL_STATUS::OK));
//            response.push(index);
        }
    }

    void onCallState(const pj::OnCallStateParam &prm, const pj::CallInfo &ci, const int softphoneID)
    {
        std::shared_ptr<Softphone> softphone;
        int index = -1;
        for(int i=0; i < _manualTestSoftphones.size(); i++)
        {
            if(_manualTestSoftphones[i])
            {
                if(_manualTestSoftphones[i]->getId() == softphoneID)
                {
                    index = i;
                    softphone = _manualTestSoftphones[i];
                    break;
                }
            }
        }

        QTextBrowser* textBrowser;

        if(!(index >= 0 && index <= 2))
        {
            std::cout << "Manual test index error" << std::endl;
            return;
        }
        else if(index == 0)
        {
            textBrowser = _mainWindow->ui->softphone_log_text_browser_1;
        }
        else if(index == 1)
        {
            textBrowser = _mainWindow->ui->softphone_log_text_browser_2;
        }
        else if(index == 2)
        {
            textBrowser = _mainWindow->ui->softphone_log_text_browser_3;
        }

        PJ_UNUSED_ARG(prm);
        std::cout << "*** Call: " <<  ci.remoteUri << " [" << ci.stateText
                  << "]" << std::endl;
        std::stringstream message;
        message << "*** Call: " <<  ci.remoteUri << " [" << ci.stateText
                << "]" << std::endl;
        textBrowser->insertPlainText(QString::fromStdString(message.str()));
        if (ci.state == PJSIP_INV_STATE_DISCONNECTED)
        {
            softphone->clearCall();
        }
    }

    void onRegState(const pj::OnRegStateParam &prm, const pj::AccountInfo &ai, const int softphoneID)
    {
        int index = -1;
        for(int i=0; i < _manualTestSoftphones.size(); i++)
        {
            if(_manualTestSoftphones[i])
            {
                if(_manualTestSoftphones[i]->getId() == softphoneID)
                {
                    index = i;
                    break;
                }
            }
        }
        QTextBrowser* textBrowser;

        if(!(index >= 0 && index <= 2))
        {
            std::cout << "Manual test index error" << std::endl;
            return;
        }
        else if(index == 0)
        {
            textBrowser = _mainWindow->ui->softphone_log_text_browser_1;
        }
        else if(index == 1)
        {
            textBrowser = _mainWindow->ui->softphone_log_text_browser_2;
        }
        else if(index == 2)
        {
            textBrowser = _mainWindow->ui->softphone_log_text_browser_3;
        }
        std::cout << (ai.regIsActive? "*** Register: code=" : "*** Unregister: code=")
                  << prm.code << std::endl;
        std::stringstream message;
        message << (ai.regIsActive? "*** Register: code=" : "*** Unregister: code=")
                << prm.code << std::endl;
        textBrowser->insertPlainText(QString::fromStdString(message.str()));
    }

    void onIncomingCall(std::shared_ptr<SSPCall> &mainCall, std::shared_ptr<SSPCall> incomingCall, const int softphoneID)
    {
        std::shared_ptr<Softphone> softphone;
        int index = -1;
        for(int i=0; i < _manualTestSoftphones.size(); i++)
        {
            if(_manualTestSoftphones[i])
            {
                if(_manualTestSoftphones[i]->getId() == softphoneID)
                {
                    index = i;
                    softphone = _manualTestSoftphones[i];
                    break;
                }
            }
        }

        QTextBrowser* textBrowser;

        if(!(index >= 0 && index <= 2))
        {
            std::cout << "Manual test index error" << std::endl;
            return;
        }
        else if(index == 0)
        {
            textBrowser = _mainWindow->ui->softphone_log_text_browser_1;
        }
        else if(index == 1)
        {
            textBrowser = _mainWindow->ui->softphone_log_text_browser_2;
        }
        else if(index == 2)
        {
            textBrowser = _mainWindow->ui->softphone_log_text_browser_3;
        }

        pj::CallInfo ci = incomingCall->getInfo();

        std::cout << "*** Incoming Call: " <<  ci.remoteUri << " ["
                  << ci.stateText << "]" << std::endl;
        std::stringstream message;
        message << "*** Incoming Call: " <<  ci.remoteUri << " ["
                << ci.stateText << "]" << std::endl;
        textBrowser->insertPlainText(QString::fromStdString(message.str()));

        if(mainCall && mainCall->isActive())
        {
            pj::CallOpParam opcode;
            opcode.statusCode = PJSIP_SC_BUSY_HERE;
            incomingCall->hangup(opcode);
        }
        else
        {
            std::shared_ptr<Softphone> softphone;
            for(const auto &sp : _manualTestSoftphones)
            {
                if(sp->getId() == softphoneID)
                {
                    softphone = sp;
                    break;
                }
            }

            std::unique_lock<std::mutex> lock(_mutex);

            auto now = std::chrono::steady_clock::now();
            auto wait_until = now + std::chrono::milliseconds(90000); // wait for 1.5 minutes

            auto statusFlag = _cv.wait_until(lock, wait_until);

            if(statusFlag == std::cv_status::timeout || softphone->getDeclinedIncomingCall())
            {
                pj::CallOpParam opcode;
                opcode.statusCode = PJSIP_SC_DECLINE;
                incomingCall->hangup(opcode);
            }

            else if(softphone->getAnsweredIncomingCall())
            {
                mainCall = std::move(incomingCall);

                pj::CallOpParam prm;

                prm.statusCode = PJSIP_SC_OK;
                mainCall->answer(prm);
            }

            softphone->setAnsweredIncomingCall(false);
            softphone->setDeclinedIncomingCall(false);

            lock.unlock();
        }
    }

    PjManager _pjManager;
    QSharedPointer<MainWindow> _mainWindow;

    std::unordered_map<ManualTestOpcode, std::function<void(const Message &)>> _manualTestHandlers;
    std::array<std::shared_ptr<Softphone>, 3> _manualTestSoftphones;

    std::mutex _mutex;
    std::condition_variable _cv;

    static constexpr int DEFAULT_ID_MULTIPLICATION_VALUE = 10000;

    static constexpr auto DEFAULT_SECRET = "12345678";
    static constexpr auto DEFAULT_TIMEOUT = 5000;
};
