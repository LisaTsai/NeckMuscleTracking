//test
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <math.h>
#include <fstream>
#include <QMessageBox>
#include <QVector>
//#include "opencv2/core/core.hpp"
//#include "opencv2/highgui/highgui.hpp"
//#include "opencv2/imgproc/imgproc.hpp"
#include "opencv.hpp"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:


    void on_Save_clicked();

    void on_Start_clicked();

    void on_VideoPath_clicked();

    void on_filter_activated(int index);

    void on_visibility_clicked();

    void on_checkBox_toggled(bool checked);

    void on_checkBox_2_toggled(bool checked);

    void on_checkBox_3_toggled(bool checked);

    void on_doubleSpinBox_editingFinished();

    void on_doubleSpinBox_2_editingFinished();

    void on_comboBox_currentIndexChanged(int index);

    void on_searchRange_currentTextChanged(const QString &arg1);

    void on_Preview_clicked();

    //void on_StartFrame_editingFinished();

    void on_brightness_sliderMoved(int position);

    void on_maskW_currentTextChanged(const QString &arg1);

    void on_maskH_currentTextChanged(const QString &arg1);

    void on_pushButton_clicked();

    void on_StartFrame_editingFinished();
    
    void on_pushButton_2_clicked();


    void on_Start_2_clicked();

private:
    Ui::MainWindow *ui;
    QPixmap image;
    QImage *ImageObject;
    QString videoPath;
    //QString SaveTxtPath;
    int blurx, blury;
    int mask, mask2;
    double scalex, scaley;
    int match_method;
    int counter;
    int sf_hsize;
    //QVector<double> x,y,y1,y2;
    int brightness;
    int start_frame;

};

#endif // MAINWINDOW_H
