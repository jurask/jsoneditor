#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMdiSubWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actionNew_triggered();

    void on_actionClose_triggered();

    void on_actionOpen_triggered();

    void on_mdiArea_subWindowActivated(QMdiSubWindow *window);

    void activeWindowTitleChanged(const QString &title);

private:
    Ui::MainWindow *ui;
    QString nextDocumentName(const QString& baseName) const;
};

#endif // MAINWINDOW_H
