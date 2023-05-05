#pragma once

#include <string>
#include <iostream>
#include <memory>
#include <unordered_map>

#include <QApplication>
#include <QObject>

#include "MainWindow.hpp"
#include "Message.hpp"
#include "VTCPOpcode.hpp"
#include "VTCPClient.hpp"

class GuiHandler : public QObject
{
public:
    GuiHandler(int argc, char *argv[]):
        _app(argc, argv),
        _connected(std::make_shared<std::atomic<bool>>(false)),
        _client(_connected, std::bind(&GuiHandler::onMessageReceived, this, std::placeholders::_1))
    {
        _handlers.emplace(VTCPOpcode::VTCP_CONNECT_RES, std::bind(&GuiHandler::onVtcpConnectResualt, this, std::placeholders::_1));
        _handlers.emplace(VTCPOpcode::VTCP_DISCONNECT_RES, std::bind(&GuiHandler::onVtcpDisconnectResualt, this, std::placeholders::_1));
        _handlers.emplace(VTCPOpcode::VTCP_AUTO_TEST_RES, std::bind(&GuiHandler::onVtcpAutoTestResualt, this, std::placeholders::_1));
        _handlers.emplace(VTCPOpcode::VTCP_MANUAL_TEST_RES, std::bind(&GuiHandler::onVtcpManualTestResualt, this, std::placeholders::_1));
        _handlers.emplace(VTCPOpcode::VTCP_HISTORY_HEADER_RES, std::bind(&GuiHandler::onVtcpHistoryHeaderResualt, this, std::placeholders::_1));
        _handlers.emplace(VTCPOpcode::VTCP_HISTORY_LOG_RES, std::bind(&GuiHandler::onVtcpHistoryLogResualtResualt, this, std::placeholders::_1));
        initSignals();
    }


    ~GuiHandler() = default;

    void runGui()
    {
        _mainWindow.show();
        _app.exec();
    }
private:
    void initSignals()
    {
        std::cout << "init Buttons" << std::endl;
        QObject::connect(&_mainWindow, &MainWindow::connectButtonClickedSignal, this, &GuiHandler::onConnectButtonClicked);
        QObject::connect(&_mainWindow, &MainWindow::disconnectButtonClickedSignal, this, &GuiHandler::onDisconnectButtonClicked);
    }

public slots:
    void onConnectButtonClicked(const std::string& domain, const std::string& port)
    {
        if(*_connected)
            return;

        std::cout << "onConnectButtonClickedSignal " << domain << ", " << port << std::endl;

        try
        {
//            client.connect(domain, std::stoi(port));
            _client.connect(domain, port);
//            *_connected = true;
//            Message message;
//            message.push(static_cast<int>(VTCPOpcode::VTCP_CONNECT_REQ));
//            _client.send(message);
        }
        catch (std::exception e)
        {
            *_connected = false;
            std::cout << e.what() << std::endl;
        }
    }

    void onDisconnectButtonClicked()
    {
        if(!*_connected)
            return;

        std::cout << "onDisconnectButtonClicked " << std::endl;

        Message message;
        message.push(static_cast<int>(VTCPOpcode::VTCP_DISCONNECT_REQ));
        _client.send(message);
        _client.disconnect();
        *_connected = false;
    }

    void onConnnect()
    {

    }

    void onMessageReceived(const Message& request)
    {
        handle(request);
    }

    void handle(const Message& result)
    {
        try
        {
            auto op = result.readInteger();
            auto opcode = static_cast<VTCPOpcode>(op);
            _handlers.at(opcode)(result);
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << std::endl;
        }
    }

    void onVtcpConnectResualt(const Message& result)
    {
        std::cout << "onVtcpConnectResualt"  << std::endl;
    }

    void onVtcpDisconnectResualt(const Message& result)
    {

    }

    void onVtcpAutoTestResualt(const Message& result)
    {

    }

    void onVtcpManualTestResualt(const Message& result)
    {

    }

    void onVtcpHistoryHeaderResualt(const Message& result)
    {

    }

    void onVtcpHistoryLogResualtResualt(const Message& result)
    {

    }

private:
    std::shared_ptr<std::atomic<bool>> _connected;
    QApplication _app;
    MainWindow _mainWindow;
    VTCPClient _client;

    std::unordered_map<VTCPOpcode, std::function<void(const Message &)>> _handlers;
};
