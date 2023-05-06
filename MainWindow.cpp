#include "MainWindow.hpp"
#include "ui_mainwindow.h"

#include <iostream>

#include "LogPopupWindow.hpp"
#include "CheckableComboBox.hpp"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->comboBox = new CheckableComboBox(this);

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
    connect(ui->Log_History_List_Widget, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(historyListItemClicked(QListWidgetItem*)));
    connect(this, &MainWindow::printLogSignal, this, &MainWindow::printLog);
    connect(this, &MainWindow::openLogPopupWindowSignal, this, &MainWindow::openLogPopupWindow);
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

    emit runAutoTestSignal(ui->auto_tests_pbx_ip_edit_text->toPlainText().toStdString(),
                           ui->auto_tests_amout_edit_text->toPlainText().toInt());
}

void MainWindow::manualTestRegisterButtonClicked()
{
    std::cout << "manualTestRegisterButtonClicked" << std::endl;

    QObject* sender = QObject::sender();
    if (sender == ui->softphone_register_button_1) {
        emit manualTestRegisterSignal(0, ui->softphone_id_edit_text_1->toPlainText().toInt(),
                                         ui->softphone_pbx_ip_edit_text_1->toPlainText().toStdString());
    } else if (sender == ui->softphone_register_button_2) {
        emit manualTestRegisterSignal(1, ui->softphone_id_edit_text_2->toPlainText().toInt(),
                                         ui->softphone_pbx_ip_edit_text_2->toPlainText().toStdString());
    } else if (sender == ui->softphone_register_button_3) {
        emit manualTestRegisterSignal(2, ui->softphone_id_edit_text_3->toPlainText().toInt(),
                                         ui->softphone_pbx_ip_edit_text_3->toPlainText().toStdString());
    }

}

void MainWindow::manualTestUnregisterButtonClicked()
{
    std::cout << "manualTestUnregisterButtonClicked" << std::endl;

    QObject* sender = QObject::sender();
    if (sender == ui->softphone_unregister_button_1) {
        emit manualTestUnregisterSignal(0);
    } else if (sender == ui->softphone_unregister_button_2) {
        emit manualTestUnregisterSignal(1);
    } else if (sender == ui->softphone_unregister_button_3) {
        emit manualTestUnregisterSignal(2);
    }
}

void MainWindow::manualTestCallButtonClicked()
{
    std::cout << "manualTestCallButtonClicked" << std::endl;

    QObject* sender = QObject::sender();
    if (sender == ui->softphone_call_button_1) {
        emit manualTestCallSignal(0, ui->softphone_dest_edit_text_1->toPlainText().toStdString());
    } else if (sender == ui->softphone_call_button_2) {
        emit manualTestCallSignal(1, ui->softphone_dest_edit_text_2->toPlainText().toStdString());
    } else if (sender == ui->softphone_call_button_3) {
        emit manualTestCallSignal(2, ui->softphone_dest_edit_text_3->toPlainText().toStdString());
    }
}

void MainWindow::manualTestHangupButtonClicked()
{
    std::cout << "manualTestHangupButtonClicked" << std::endl;

    QObject* sender = QObject::sender();
    if (sender == ui->softphone_hangup_button_1) {
        emit manualTestHangupSignal(0);
    } else if (sender == ui->softphone_hangup_button_2) {
        emit manualTestHangupSignal(1);
    } else if (sender == ui->softphone_hangup_button_3) {
        emit manualTestHangupSignal(2);
    }
}

void MainWindow::manualTestAnswerButtonClicked()
{
    std::cout << "manualTestAnswerButtonClicked" << std::endl;

    QObject* sender = QObject::sender();
    if (sender == ui->softphone_answer_button_1) {
        emit manualTestAnswerSignal(0);
    } else if (sender == ui->softphone_answer_button_2) {
        emit manualTestAnswerSignal(1);
    } else if (sender == ui->softphone_answer_button_3) {
        emit manualTestAnswerSignal(2);
    }
}

void MainWindow::manualTestDeclineButtonClicked()
{
    std::cout << "manualTestDeclineButtonClicked" << std::endl;

    QObject* sender = QObject::sender();
    if (sender == ui->softphone_decline_button_1) {
        emit manualTestDeclineSignal(0);
    } else if (sender == ui->softphone_decline_button_2) {
        emit manualTestDeclineSignal(1);
    } else if (sender == ui->softphone_decline_button_3) {
        emit manualTestDeclineSignal(2);
    }
}

void MainWindow::refreshHIstoryHeadersButtonClicked()
{
    std::cout << "refreshHIstoryHeadersButtonClicked" << std::endl;

    emit refreshHIstoryHeadersSignal();
}

void MainWindow::historyListItemClicked(QListWidgetItem* item)
{
    std::cout << "historyListItemClicked" << std::endl;

    emit historyListItemClickedSignal(item->text().toStdString());
}

void MainWindow::printLog(QTextBrowser *textBrowser, const std::string &data)
{
    textBrowser->setText(QString::fromStdString(data));
}

void MainWindow::openLogPopupWindow(const std::string &data)
{
    LogPopupWindow popupWindow(QString::fromStdString(data));
    popupWindow.exec();
}
