#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QByteArray>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

     http = new QHttp(this);     

     connect(http, SIGNAL(requestFinished(int,bool)),
             this, SLOT(httpRequestFinished(int,bool)));

     connect(http, SIGNAL(responseHeaderReceived(QHttpResponseHeader)),
             this, SLOT(readResponseHeader(QHttpResponseHeader)));



}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::changeEvent(QEvent *e)
{
    QMainWindow::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void MainWindow::httpRequestFinished(int requestId, bool error)
{
    if (http->lastResponse().statusCode() == 409){

        this->sessionId.clear();
        this->sessionId.append(http->lastResponse().value("X-Transmission-Session-Id"));

        on_pushButton_clicked();

        return;
    }



//     if (requestId != httpGetId)
//         return;
//     if (httpRequestAborted) {
//         if (file) {
//             file->close();
//             file->remove();
//             delete file;
//             file = 0;
//         }
//
//         progressDialog->hide();
//         return;
//     }
//
//     if (requestId != httpGetId)
//         return;
//
//     progressDialog->hide();
//     file->close();
//
//     if (error) {
//         file->remove();
//         QMessageBox::information(this, tr("HTTP"),
//                                  tr("Download failed: %1.")
//                                  .arg(http->errorString()));
//     } else {
//         QString fileName = QFileInfo(QUrl(urlLineEdit->text()).path()).fileName();
//         statusLabel->setText(tr("Downloaded %1 to current directory.").arg(fileName));
//     }
//
//     downloadButton->setEnabled(true);
//     delete file;
//     file = 0;
 }

void MainWindow::on_pushButton_clicked()
{    
    QString json;
    json += "{\"method\":\"torrent-add\",\"arguments\":{";
    json +=     "\"filename\":\"" + ui->lineEdit->text() + "\"";
    json +=  "}}";

    QByteArray buf;
    buf.append(json);

    QMessageBox::information(this, "eee", json);

    QHttpRequestHeader header("POST", "/transmission/rpc");
    header.setValue("Host", "192.168.1.104");
    http->setHost("192.168.1.104");
    if (this->sessionId.length() > 0){
        header.setValue("X-Transmission-Session-Id", sessionId);
    }

    http->request(header, buf);

}
