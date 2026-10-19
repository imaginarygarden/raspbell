#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QCamera>
#include <QImageCapture>
#include <QMainWindow>
#include <QMediaCaptureSession>
#include <QMediaRecorder>
#include <QPointer>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

   public:
    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow() override;

   private:
    Ui::MainWindow* ui;
    std::unique_ptr<QCamera> m_camera;
    std::unique_ptr<QMediaRecorder> m_mediaRecorder;
    std::unique_ptr<QImageCapture> m_imageCapture;
    QMediaCaptureSession m_captureSession;
};
#endif  // MAINWINDOW_H
