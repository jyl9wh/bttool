#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QHttp>

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::MainWindow *ui;
    QHttp *http;
    QString sessionId;

private slots:
    void httpRequestFinished(int requestId, bool error);
    void on_pushButton_clicked();
};

#endif // MAINWINDOW_H
