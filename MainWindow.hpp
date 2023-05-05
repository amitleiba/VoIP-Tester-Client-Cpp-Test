#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

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
    void historyListItemClicked();

signals:
    void connectButtonClickedSignal(const std::string &, const std::string&);
    void disconnectButtonClickedSignal();
    void runAutoTestSignal(const std::string& pbxIp, const std::string& amount);
    void manualTestRegisterSignal(int index, const std::string& id, const std::string& pbxIp);
    void manualTestUnregisterSignal(int index);
    void manualTestCallSignal(int index, const std::string& dest);
    void manualTestHangupSignal(int index);
    void manualTestAnswerSignal(int index);
    void manualTestDeclineSignal(int index);
//    void printLogSignal(QTextBrowser *textBrowser, const std::string& value);
    void historyListItemClickedSignal(const std::string& item);
    void openPopupWindowSignal(const std::string& data);
    void refreshHIstoryHeadersSignal();


private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_HPP
