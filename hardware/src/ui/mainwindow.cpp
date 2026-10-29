#include "mainwindow.h"

#include <QBuffer>
#include <QMediaDevices>
#include <QtWidgets>

#include "ui_mainwindow.h"

namespace {
QString imageToBase64(const QImage& image) {
    QByteArray data;
    QBuffer buffer(&data);
    image.save(&buffer, "JPG");
    data = data.toBase64();
    QString dataString = QString(data);  // depend whether you need QString
    return dataString;
}

QImage base64ToImage(const QString& dataString) {
    QByteArray data = dataString.toUtf8();
    QImage image;
    image.loadFromData(QByteArray::fromBase64(data));
    return image;
}
};  // namespace

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    const auto cameras = QMediaDevices::videoInputs();

    if (cameras.empty()) {
        qDebug() << "Keine Kamera wurde gefunden";
        return;
    }

    m_camera = std::make_unique<QCamera>(cameras.first());
    m_captureSession.setCamera(m_camera.get());
    m_mediaRecorder = std::make_unique<QMediaRecorder>();
    m_imageCapture = std::make_unique<QImageCapture>();

    connect(m_imageCapture.get(), &QImageCapture::readyForCaptureChanged,
            ui->recordButton, &QPushButton::setEnabled);

    connect(m_imageCapture.get(), &QImageCapture::imageCaptured, this,
            [this](int requestId, const QImage& img) {
                Q_UNUSED(requestId);
                QImage scaledImage =
                    img.scaled(ui->viewfinder->size(), Qt::KeepAspectRatio,
                               Qt::SmoothTransformation);

                const qsizetype lastChars{20};
                ui->statusbar->showMessage(imageToBase64(img).last(lastChars));
                ui->label->setPixmap(QPixmap::fromImage(scaledImage));
            });

    m_captureSession.setRecorder(m_mediaRecorder.get());
    m_captureSession.setImageCapture(m_imageCapture.get());

    ui->recordButton->setEnabled(m_imageCapture->isReadyForCapture());

    connect(ui->recordButton, &QPushButton::clicked, this,
            [this]() { m_imageCapture->captureToFile("image.jpg"); });

    m_captureSession.setVideoOutput(ui->viewfinder);
    m_camera->start();
}

MainWindow::~MainWindow() { delete ui; }
