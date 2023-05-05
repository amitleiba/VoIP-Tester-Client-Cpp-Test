#include "MainWindow.hpp"
#include "ui_mainwindow.h"

#include <iostream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->connect_frame_Connect_button, SIGNAL(clicked()), this, SLOT(connectButtonClicked()));
    connect(ui->connect_frame_disconnect_button, SIGNAL(clicked()), this,  SLOT(disconnectButtonClicked()));
    connect(ui->auto_tests_button, SIGNAL(clicked()), this, SLOT(runAutoTestButtonClicked()));
    connect(ui->softphone_register_button_1, SIGNAL(clicked()), this, SLOT(manualTestRegisterButtonClicked()));
    connect(ui->softphone_register_button_2, SIGNAL(clicked()), this, SLOT(manualTestRegisterButtonClicked()));
    connect(ui->softphone_register_button_3, SIGNAL(clicked()), this, SLOT(manualTestRegisterButtonClicked()));
    connect(ui->softphone_unregister_button_1, SIGNAL(clicked()), this, SLOT(manualTestUnregisterButtonClicked()));
    connect(ui->softphone_unregister_button_2, SIGNAL(clicked()), this, SLOT(manualTestUnregisterButtonClicked()));
    connect(ui->softphone_unregister_button_3, SIGNAL(clicked()), this, SLOT(manualTestUnregisterButtonClicked()));
    connect(ui->softphone_call_button_1, SIGNAL(clicked()), this, SLOT(manualTestCallButtonClicked()));
    connect(ui->softphone_call_button_2, SIGNAL(clicked()), this, SLOT(manualTestCallButtonClicked()));
    connect(ui->softphone_call_button_3, SIGNAL(clicked()), this, SLOT(manualTestCallButtonClicked()));
    connect(ui->softphone_hangup_button_1, SIGNAL(clicked()), this, SLOT(manualTestHangupButtonClicked()));
    connect(ui->softphone_hangup_button_2, SIGNAL(clicked()), this, SLOT(manualTestHangupButtonClicked()));
    connect(ui->softphone_hangup_button_3, SIGNAL(clicked()), this, SLOT(manualTestHangupButtonClicked()));
    connect(ui->softphone_answer_button_1, SIGNAL(clicked()), this, SLOT(manualTestAnswerButtonClicked()));
    connect(ui->softphone_answer_button_2, SIGNAL(clicked()), this, SLOT(manualTestAnswerButtonClicked()));
    connect(ui->softphone_answer_button_3, SIGNAL(clicked()), this, SLOT(manualTestAnswerButtonClicked()));
    connect(ui->softphone_decline_button_1, SIGNAL(clicked()), this, SLOT(manualTestDeclineButtonClicked()));
    connect(ui->softphone_decline_button_2, SIGNAL(clicked()), this, SLOT(manualTestDeclineButtonClicked()));
    connect(ui->softphone_decline_button_3, SIGNAL(clicked()), this, SLOT(manualTestDeclineButtonClicked()));
    connect(ui->Log_History_Refresh_button, SIGNAL(clicked()), this, SLOT(refreshHIstoryHeadersButtonClicked()));
    connect(ui->Log_History_List_Widget, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(historyListItemClicked()));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::connectButtonClicked()
{
    std::cout << "onConnectButtonClicked" << std::endl;

    emit connectButtonClickedSignal(ui->connect_frame_ip_edit_text->toPlainText().toStdString(),
                                    ui->connect_frame_port_edit_text->toPlainText().toStdString());
}

void MainWindow::disconnectButtonClicked()
{
    std::cout << "disconnectButtonClicked" << std::endl;

    emit disconnectButtonClickedSignal();
}

void MainWindow::runAutoTestButtonClicked()
{
    std::cout << "runAutoTestButtonClicked" << std::endl;

   emit runAutoTestSignal(ui->auto_tests_pbx_ip_edit_text.toPlainText(), ui->auto_tests_amout_edit_text.toPlainText());
}

void MainWindow::manualTestRegisterButtonClicked()
{
    std::cout << "manualTestRegisterButtonClicked" << std::endl;
}

void MainWindow::manualTestUnregisterButtonClicked()
{
    std::cout << "manualTestUnregisterButtonClicked" << std::endl;
}

void MainWindow::manualTestCallButtonClicked()
{
    std::cout << "manualTestCallButtonClicked" << std::endl;
}

void MainWindow::manualTestHangupButtonClicked()
{
    std::cout << "manualTestHangupButtonClicked" << std::endl;
}

void MainWindow::manualTestAnswerButtonClicked()
{
    std::cout << "manualTestAnswerButtonClicked" << std::endl;
}

void MainWindow::manualTestDeclineButtonClicked()
{
    std::cout << "manualTestDeclineButtonClicked" << std::endl;
}

void MainWindow::refreshHIstoryHeadersButtonClicked()
{
    std::cout << "refreshHIstoryHeadersButtonClicked" << std::endl;
}

void MainWindow::historyListItemClicked()
{
    std::cout << "historyListItemClicked" << std::endl;
}
