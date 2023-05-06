#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>
#include <QListWidgetItem>
#include <QTextBrowser>

#include "ui_mainwindow.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    Ui::MainWindow *ui;

private slots:
    void connectButtonClicked();
    void disconnectButtonClicked();
    void runAutoTestButtonClicked();
    void manualTestRegisterButtonClicked();
    void manualTestUnregisterButtonClicked();
    void manualTestCallButtonClicked();
    void manualTestHangupButtonClicked();
    void manualTestAnswerButtonClicked();
    void manualTestDeclineButtonClicked();
    void refreshHIstoryHeadersButtonClicked();
    void historyListItemClicked(QListWidgetItem*);
    void printLog(QTextBrowser *textBrowser, const std::string& data);
    void openLogPopupWindow(const std::string& data);

signals:
    void connectButtonClickedSignal(const std::string &, const std::string&);
    void disconnectButtonClickedSignal();
    void runAutoTestSignal(const std::string& pbxIp, int amount);
    void manualTestRegisterSignal(int index, int id, const std::string& pbxIp);
    void manualTestUnregisterSignal(int index);
    void manualTestCallSignal(int index, const std::string& dest);
    void manualTestHangupSignal(int index);
    void manualTestAnswerSignal(int index);
    void manualTestDeclineSignal(int index);
    void printLogSignal(QTextBrowser *textBrowser, const std::string& data);
    void historyListItemClickedSignal(const std::string& item);
    void openLogPopupWindowSignal(const std::string& data);
    void refreshHIstoryHeadersSignal();


private:

};
#endif // MAINWINDOW_HPP
