#include "mainwindow.h"
#include "ui_mainwindow.h"
int a1,b1,a2,b2,a3,b3,a4,b4,startframe=1;
int point,frames,pre_count=0, n_save=0;
double minResult[3];
double maxResult[3];
double aveResult[3];
int maxfResult[3];
int minfResult[3];

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->label_5->setStyleSheet("QLabel { background-color : black;}");
    ui->widget->addGraph();
    ui->widget->addGraph();
    ui->widget->addGraph();
    this->setWindowTitle("Points Tracker");
}

MainWindow::~MainWindow()
{
    delete ui;
}
void CallBackFunc(int event, int x, int y, int , void * )
{
    if  ( event == cv::EVENT_LBUTTONDOWN )
    {
        if (point==0) {
            a1=x;
            b1=y;
        }
        else if(point==1){
            a2=x;
            b2=y;
        }

        point++;
    }
    else if (event == cv::EVENT_MOUSEMOVE){
        a3=x;
        b3=y;
    }
}
void CallBackFunc_2(int event, int x, int y, int , void * )
{
    if  ( event == cv::EVENT_LBUTTONDOWN )
    {
        if (point==0) {
            a1=x;
            b1=y;
        }
        else if(point==1){
            a2=x;
            b2=y;
        }
        else if(point==2){
            a4=x;
            b4=y;
        }
        point++;
    }
    else if (event == cv::EVENT_MOUSEMOVE){
        a3=x;
        b3=y;
    }
}
void ResultCompare(double h, double v,double l,bool flag,int f )
{
    aveResult[0]+=h;
    aveResult[1]+=v;
    aveResult[2]+=l;
    if(!flag){
        maxfResult[0]=f;
        maxfResult[1]=f;
        maxfResult[2]=f;
        minfResult[0]=f;
        minfResult[1]=f;
        minfResult[2]=f;
        minResult[0]=h;
        minResult[1]=v;
        minResult[2]=l;
        maxResult[0]=h;
        maxResult[1]=v;
        maxResult[2]=l;
    }
    else{
        if (minResult[0]>h){minResult[0]=h;minfResult[0]=f;}
        if (minResult[1]>v){minResult[1]=v;minfResult[1]=f;}
        if (minResult[2]>l){minResult[2]=l;minfResult[2]=f;}
        if (maxResult[0]<h){maxResult[0]=h;maxfResult[0]=f;}
        if (maxResult[1]<v){maxResult[1]=v;maxfResult[1]=f;}
        if (maxResult[2]<l){maxResult[2]=l;maxfResult[2]=f;}
    }

}

void MainWindow::on_Save_clicked()
{
    QString SavetxtPath = QFileDialog::getSaveFileName(this,"Save data","","Text (*.txt)");
    QFile txtfile(SavetxtPath);
    if(txtfile.open(QIODevice::WriteOnly|QIODevice::Text)){
            txtfile.write(ui->textEdit_2->toPlainText().toUtf8());
            txtfile.write(ui->textEdit->toPlainText().toUtf8());
        }
}

void MainWindow::on_Start_clicked()
{

    a1=ui->spinBox->text().toInt();
    a2=ui->spinBox_3->text().toInt();
    b1=ui->spinBox_2->text().toInt();
    b2=ui->spinBox_4->text().toInt();
    a3=0;
    b3=0;
    point=0;
    cv::Mat temp;
    char info[200],info2[200],info3[200],info4[200],info5[200];
    for(int u=0;u<3;u++){
        minResult[u]=0.0;
        maxResult[u]=0.0;
        aveResult[u]=0.0;
        maxfResult[u]=0;
        minfResult[u]=0;
    }
    ui->textEdit->clear();
    ui->textEdit_2->clear();
    cv::Mat Img,Img2_1,Img3_1,Img4_1,Img5_1,Img2_2,Img3_2,Img4_2,Img5_2,Imgblur,ImgH;
    cv::Mat img1, img2;
    counter = 0;
    int save = 2;
    //double length=0.0;
    cv::Mat frameblur,sf1,sf2;
    cv::Mat output1,output2;
    char imageName[200];
    QVector<double> x(frames), y(frames), y1(frames), y2(frames);

    for(int i=1;i<=frames;i++){
        x[i-1]=i;
    }
    sprintf(imageName, "frame%.3d.jpg", startframe-1);
    Img = cv::imread( imageName, 0 );
    cv::namedWindow("Choose two points", 0);
    if((a1+b1+a2+b2)==0){
                   while (point<2) {
                       Img.copyTo(temp);
                       cv::setMouseCallback("Choose two points", CallBackFunc, 0);
                       if(point==1){

                       cv::line(temp,cv::Point(a1,b1),cv::Point(a3,b3),cv::Scalar(0,0,255),1,8);}
                       cv::line(temp,cv::Point(a1+4,b1),cv::Point(a1-4,b1),cv::Scalar(0,255,0),1,4);
                       cv::line(temp,cv::Point(a1,b1+4),cv::Point(a1,b1-4),cv::Scalar(0,255,0),1,4);
                       cv::line(temp,cv::Point(a2+4,b2),cv::Point(a2-4,b2),cv::Scalar(0,255,0),1,4);
                       cv::line(temp,cv::Point(a2,b2+4),cv::Point(a2,b2-4),cv::Scalar(0,255,0),1,4);
                       ImgH=temp+cv::Scalar(brightness,brightness,brightness);
                       sprintf(info,"PointA:(%d, %d)",a1,b1);
                       sprintf(info2,"PointB:(%d, %d)",a3,b3);
                       putText(ImgH,info,cv::Point(20,200),cv::FONT_HERSHEY_COMPLEX_SMALL,0.8,cv::Scalar(255,255,255),1);
                       putText(ImgH,info2,cv::Point(20,220),cv::FONT_HERSHEY_COMPLEX_SMALL,0.8,cv::Scalar(255,255,255),1);
                       cv::imshow("Choose two points",ImgH);
                       cv::waitKey(10);
                  }}
     else{
                       Img.copyTo(temp);
                       cv::line(temp,cv::Point(a1+4,b1),cv::Point(a1-4,b1),cv::Scalar(0,255,0),1,4);
                       cv::line(temp,cv::Point(a1,b1+4),cv::Point(a1,b1-4),cv::Scalar(0,255,0),1,4);
                       cv::line(temp,cv::Point(a2+4,b2),cv::Point(a2-4,b2),cv::Scalar(0,255,0),1,4);
                       cv::line(temp,cv::Point(a2,b2+4),cv::Point(a2,b2-4),cv::Scalar(0,255,0),1,4);
                       ImgH=temp+cv::Scalar(brightness,brightness,brightness);
                       sprintf(info,"PointA:(%d, %d)",a1,b1);
                       sprintf(info2,"PointB:(%d, %d)",a3,b3);
                       putText(ImgH,info,cv::Point(20,200),cv::FONT_HERSHEY_COMPLEX_SMALL,0.8,cv::Scalar(255,255,255),1);
                       putText(ImgH,info2,cv::Point(20,220),cv::FONT_HERSHEY_COMPLEX_SMALL,0.8,cv::Scalar(255,255,255),1);
                       cv::imshow("Choose two points",ImgH);
                       cv::waitKey(10);}

       cv::GaussianBlur( Img, Imgblur, cv::Size( blurx, blury), 0, 0 );
       img1 = Imgblur(cv::Rect(a1-mask, b1-mask2, 2*mask, 2*mask2));
       img2 = Imgblur(cv::Rect(a2-mask, b2-mask2, 2*mask, 2*mask2));

   int output1_cols =  Img.cols - img1.cols + 1;
   int output1_rows = Img.rows - img1.rows + 1;
   output1.create( output1_cols, output1_rows, CV_32FC1 );
   int output2_cols =  Img.cols - img1.cols + 1;
   int output2_rows = Img.rows - img1.rows + 1;
   output2.create( output2_cols, output2_rows, CV_32FC1 );

       cv::destroyWindow("Choose two points");
       y1[0]=abs(a1-a2)*scalex;
       y1[1]=y1[0];
       y2[0]=abs(b1-b2)*scaley;
       y2[1]=y2[0];
       y[0]=sqrt(y1[0]*y1[0]+y2[0]*y2[0]);
       y[1]=y[0];
       ResultCompare(y1[0], y2[0], y[0],false,startframe );
       ui->textEdit->append ("line:\tx1\ty1\tx2\ty2\thorizontal\tvertical\tdistance\n");
       ui->textEdit->append ("frame"+QString::number(startframe)+" : \t"+QString::number(a1)+"\t"+QString::number(b1)+"\t"+QString::number(a2)+"\t"+QString::number(b2)+"\t"+QString::number((int)(y1[0]*100+.5)/100.)+"\t"+QString::number((int)(y2[0]*100+.5)/100.)+"\t"+QString::number((int)(y[0]*100+.5)/100.));
       //ui->textEdit->append ("frame2 : \t"+QString::number(a1)+"\t"+QString::number(b1)+"\t"+QString::number(a2)+"\t"+QString::number(b2)+"\t"+QString::number((int)(y1[0]*100+.5)/100.)+"\t"+QString::number((int)(y2[0]*100+.5)/100.)+"\t"+QString::number((int)(y[0]*100+.5)/100.));
       cv::namedWindow("Video Player",0);

       while(startframe<=frames-1)
       {
               sprintf(imageName, "frame%.3d.jpg", startframe++);
               Img = cv::imread( imageName, 0 );
               cv::GaussianBlur( Img, frameblur, cv::Size( blurx, blury), 0, 0 );
               sf1=Img(cv::Rect(a1-sf_hsize, b1-sf_hsize, 2*sf_hsize, 2*sf_hsize));
               sf2=Img(cv::Rect(a2-sf_hsize, b2-sf_hsize, 2*sf_hsize, 2*sf_hsize));
               cv::matchTemplate(img1,sf1,output1,match_method);
               cv::matchTemplate(img2,sf2,output2,match_method);
               normalize( output1, output1, 0, 1, cv::NORM_MINMAX, -1, cv::Mat() );
               normalize( output2, output2, 0, 1, cv::NORM_MINMAX, -1, cv::Mat() );

               double minVal1; double maxVal1; cv::Point minLoc1; cv::Point maxLoc1;cv::Point matchLoc1;
               double minVal2; double maxVal2; cv::Point minLoc2; cv::Point maxLoc2;cv::Point matchLoc2;

               cv::minMaxLoc( output1, &minVal1, &maxVal1, &minLoc1, &maxLoc1, cv::Mat() );
               cv::minMaxLoc( output2, &minVal2, &maxVal2, &minLoc2, &maxLoc2, cv::Mat() );
               // For SQDIFF and SQDIFF_NORMED, the best matches are lower values. For all the other methods, the higher the better
               if( match_method  == cv::TM_SQDIFF || match_method == cv::TM_SQDIFF_NORMED )
               {
                   matchLoc1 = minLoc1;
                   matchLoc2 = minLoc2;
               }
               else
               { matchLoc1 = maxLoc1;
                 matchLoc2 = maxLoc2;
               }
               a1=matchLoc1.x+a1+mask-sf_hsize;
               b1=matchLoc1.y+b1+mask2-sf_hsize;
               a2=matchLoc2.x+a2+mask-sf_hsize;
               b2=matchLoc2.y+b2+mask2-sf_hsize;

               y1[save]=abs(a1-a2)*scalex;
               y2[save]=abs(b1-b2)*scaley;
               y[save]=sqrt(y1[save]*y1[save]+y2[save]*y2[save]);
               ResultCompare(y1[save], y2[save],y[save],true, (startframe+save)/2 );
               ui->textEdit->append ("frame"+QString::number((startframe+save)/2)+" :\t"+QString::number(a1)+"\t"+QString::number(b1)+"\t"+QString::number(a2)+"\t"+QString::number(b2)+"\t"+QString::number((int)(y1[save]*100+.5)/100.)+"\t"+QString::number((int)(y2[save]*100+.5)/100.)+"\t"+QString::number((int)(y[save]*100+.5)/100.));

               //img1 = frameblur(Rect(a1-mask, b1-mask2, 2*mask, 2*mask2));
               //img2 = frameblur(Rect(a2-mask, b2-mask2, 2*mask, 2*mask2));


               ImgH=Img+cv::Scalar(brightness,brightness,brightness);
               sprintf(info,"PointA:(%d, %d)",a1,b1);
               sprintf(info2,"PointB:(%d, %d)",a3,b3);
               sprintf(info3,"hori_dis:%.2f",(int)(y1[save]/10*100+.5)/100.);
               sprintf(info4,"verti_dis:%.2f",(int)(y2[save]/10*100+.5)/100.);
               sprintf(info5,"Dis:%.2f",(int)(y[save]/10*100+.5)/100.);
               putText(ImgH,info,cv::Point(20,200),cv::FONT_HERSHEY_COMPLEX_SMALL,0.8,cv::Scalar(255,255,255),1);
               putText(ImgH,info2,cv::Point(20,220),cv::FONT_HERSHEY_COMPLEX_SMALL,0.8,cv::Scalar(255,255,255),1);
               putText(ImgH,info3,cv::Point(20,240),cv::FONT_HERSHEY_COMPLEX_SMALL,0.8,cv::Scalar(255,255,255),1);
               putText(ImgH,info4,cv::Point(20,260),cv::FONT_HERSHEY_COMPLEX_SMALL,0.8,cv::Scalar(255,255,255),1);
               putText(ImgH,info5,cv::Point(20,280),cv::FONT_HERSHEY_COMPLEX_SMALL,0.8,cv::Scalar(255,255,255),1);
               cv::line(ImgH,cv::Point(a1,b1),cv::Point(a2,b2),cv::Scalar(255,0,0),1,4);
               cv::imshow("Video Player",ImgH);

//                              switch(save){
//                              case 2:
//                                  cv::GaussianBlur( frame, Imgblur, cv::Size( blurx, blury), 0, 0 );
//                                  Img2_1 = Imgblur(cv::Rect(a1-mask, b1-mask2, 2*mask, 2*mask2));
//                                  Img2_2 = Imgblur(cv::Rect(a2-mask, b2-mask2, 2*mask, 2*mask2));
//                                  break;
//                              case 3:
//                                  cv::GaussianBlur( frame, Imgblur, cv::Size( blurx, blury), 0, 0 );
//                                  Img3_1 = Imgblur(cv::Rect(a1-mask, b1-mask2, 2*mask, 2*mask2));
//                                  Img3_2 = Imgblur(cv::Rect(a2-mask, b2-mask2, 2*mask, 2*mask2));
//                                  break;
//                              case 4:
//                                  cv::GaussianBlur( frame, Imgblur, cv::Size( blurx, blury), 0, 0 );
//                                  Img4_1 = Imgblur(cv::Rect(a1-mask, b1-mask2, 2*mask, 2*mask2));
//                                  Img4_2 = Imgblur(cv::Rect(a2-mask, b2-mask2, 2*mask, 2*mask2));
//                                  break;
//                              case 5:
//                                  cv::GaussianBlur( frame, Imgblur, cv::Size( blurx, blury), 0, 0 );
//                                  Img5_1 = Imgblur(cv::Rect(a1-mask, b1-mask2, 2*mask, 2*mask2));
//                                  Img5_2 = Imgblur(cv::Rect(a2-mask, b2-mask2, 2*mask, 2*mask2));
//                                  break;
//                              default:
//                                  img1=Img2_1;img2=Img2_2;
//                                  Img2_1=Img3_1;Img2_2=Img3_2;
//                                  Img3_1=Img4_1;Img3_2=Img4_2;
//                                  Img4_1=Img5_1;Img4_2=Img5_2;
//                                  cv::GaussianBlur( frame, Imgblur, cv::Size( blurx, blury), 0, 0 );
//                                  Img5_1 = Imgblur(cv::Rect(a1-mask, b1-mask2, 2*mask, 2*mask2));
//                                  Img5_2 = Imgblur(cv::Rect(a2-mask, b2-mask2, 2*mask, 2*mask2));

//                                  break;
//                              }


               save++;

               if(cv::waitKey(50)>=0) break;
           }


aveResult[0]/=(frames);
aveResult[1]/=(frames);
aveResult[2]/=(frames);
ui->textEdit_2->append ("Horizontal_max = "+QString::number((int)(maxResult[0]*100+.5)/100.)+"\tVertical_max = "+QString::number((int)(maxResult[1]*100+.5)/100.)+"\tDistance_max = "+QString::number((int)(maxResult[2]*100+.5)/100.));
ui->textEdit_2->append ("Hori_max_frame = "+QString::number(maxfResult[0])+"\tVerti_max_frame = "+QString::number(maxfResult[1])+"\tDis_max_frame = "+QString::number(maxfResult[2]));
ui->textEdit_2->append ("Horizontal_min = "+QString::number((int)(minResult[0]*100+.5)/100.)+"\tVertical_min = "+QString::number((int)(minResult[1]*100+.5)/100.)+"\tDistance_min = "+QString::number((int)(minResult[2]*100+.5)/100.));
ui->textEdit_2->append ("Hori_min_frame = "+QString::number(minfResult[0])+"\tVerti_min_frame = "+QString::number(minfResult[1])+"\tDis_min_frame = "+QString::number(minfResult[2]));
ui->textEdit_2->append ("Horizontal_ave = "+QString::number((int)(aveResult[0]*100+.5)/100.)+"\tVertical_ave = "+QString::number((int)(aveResult[1]*100+.5)/100.)+"\tDistance_ave = "+QString::number((int)(aveResult[2]*100+.5)/100.)+"\n");
for(int j=0;j<frames;j++){
    y[j]/=10;
    y1[j]/=10;
    y2[j]/=10;

}
ui->widget->graph(0)->setData(x,y);
ui->widget->graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle));
ui->widget->graph(1)->setPen(QPen(Qt::red));
ui->widget->graph(1)->setData(x,y1);
ui->widget->graph(1)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssTriangle));
ui->widget->graph(2)->setPen(QPen(Qt::green));
ui->widget->graph(2)->setData(x,y2);
ui->widget->graph(2)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssSquare));
ui->widget->xAxis->setRange(x.first()-1, x.last()+1);
ui->widget->yAxis->setRange(0.0, maxResult[2]/10+0.5);
ui->doubleSpinBox->setValue(0.0);
ui->doubleSpinBox_2->setValue( maxResult[2]/10+0.5);
ui->widget->replot();
if(n_save!=0){
    int n_delete=0;
    char deletefilename[200];
    while(n_delete<n_save){
        sprintf(deletefilename,"frame%.3d.jpg", n_delete++);
        remove(deletefilename);
    }
}
       cv::destroyWindow("Video Player");
       //cv::destroyWindow("line result");
       cv::waitKey(0);

}

void MainWindow::on_VideoPath_clicked()
{
    videoPath = QFileDialog::getOpenFileName(this,tr("Open File"),"",tr("*.mp4;*.flv;*.avi" ));
    //blurx=ui->filter->currentIndex(),blury=ui->filter->currentIndex();
    blurx=3,blury=3;
    //mask=ui->maskW->currentIndex(), mask2=ui->maskH->currentIndex();
    mask=30;
    mask2=40;
    // match_method =ui->comboBox->currentIndex();
    match_method= cv::TM_SQDIFF;
    // brightness=ui->brightness->value();
    brightness=0;
    //sf_hsize=ui->searchRange->currentIndex();
    sf_hsize=45;
    //scalex=ui->scalex->text().toDouble();
    //scaley=ui->scaley->text().toDouble();
    scalex=0.008;
    scaley=0.008;
    counter = 0;

    int size=69;
    QVector<double> x(size), y(size);
    for(int i=0;i<size;i++)
    {
        x[i]=i+1;
        y[i]=0;
    }


    std::string sPath = videoPath.toUtf8().constData();
    cv::VideoCapture cap(sPath);
    if ( !cap.isOpened() ){
       QMessageBox msgBox;
       msgBox.setText("Video cannot be opened");
       msgBox.exec();
       }
    cv::Mat frame;
    frames = cap.get(cv::CAP_PROP_FRAME_COUNT);
  //int fps = cap.get(CV_CAP_PROP_FPS);
    char filenamex[200];
    ui->textEdit->clear();
    ui->textEdit_2->clear();
    ui->textEdit_2->append("frames:\t"+QString::number(frames));
    n_save=0;

    while(true)
       {
           bool success = cap.read(frame); // read a new frame from video
           if(success)
           {
              sprintf(filenamex, "frame%.3d.jpg", n_save++);
              cv::imwrite(filenamex, frame);
              if(cv::waitKey(10)>=0) break;
           }
           else
               break;
    }

    //ui->widget->graph(0)->setData(x,y);
    ui->widget->graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle));
    ui->widget->graph(0)->setName("distance");
    ui->widget->graph(1)->setPen(QPen(Qt::red));
    //ui->widget->graph(1)->setData(y,x);
    ui->widget->graph(1)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssTriangle));
    ui->widget->graph(1)->setName("horizontal displacement");
    ui->widget->graph(2)->setPen(QPen(Qt::green));
    //ui->widget->graph(2)->setData(x,x);
    ui->widget->graph(2)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssSquare));
    ui->widget->graph(2)->setName("vertical displacement");
    ui->widget->xAxis->setRange(x.first()-5,x.last()+5);
    ui->widget->yAxis->setRange(0,95);
    ui->widget->legend->setVisible(true);
    ui->widget->legend->setFont(QFont("Helvetica",9));
}

void MainWindow::on_filter_activated(int index)
{
    switch(index){
    case 0: blurx = 3;blury = 3;break;
    case 1: blurx = 5;blury = 5;break;
    case 2: blurx = 7;blury = 7;break;
    case 3: blurx = 9;blury = 9;break;
    case 4: blurx = 1; blury = 1;break;
    default: blurx = 3;blury = 3;break;
    }
}

void MainWindow::on_visibility_clicked()
{
    if(ui->visibility->text()=="Hide"){
        ui->visibility->setText("Show");
        ui->widget->legend->setVisible(false);
        ui->widget->replot();
    }
    else{
        ui->visibility->setText("Hide");
        ui->widget->legend->setVisible(true);
        ui->widget->replot();
    }
}

void MainWindow::on_checkBox_toggled(bool checked)
{
    if(!checked){
        ui->widget->graph(0)->clearData();\
        ui->widget->replot();
    }


}

void MainWindow::on_checkBox_2_toggled(bool checked)
{
    if(!checked){
        ui->widget->graph(2)->clearData();
        ui->widget->replot();
    }
}

void MainWindow::on_checkBox_3_toggled(bool checked)
{
    if(!checked){
        ui->widget->graph(1)->clearData();
        ui->widget->replot();
    }
}

void MainWindow::on_doubleSpinBox_editingFinished()
{
    ui->widget->yAxis->setRange(ui->doubleSpinBox->text().toDouble(),ui->doubleSpinBox_2->text().toDouble());
    ui->widget->replot();

}

void MainWindow::on_doubleSpinBox_2_editingFinished()
{
    ui->widget->yAxis->setRange(ui->doubleSpinBox->text().toDouble(),ui->doubleSpinBox_2->text().toDouble());
    ui->widget->replot();
}


void MainWindow::on_comboBox_currentIndexChanged(int index)
{
    switch(index){
    case 0: match_method = cv::TM_SQDIFF;break;
    case 1: match_method = cv::TM_SQDIFF_NORMED;break;
    case 2: match_method = cv::TM_CCORR;break;
    case 3: match_method = cv::TM_CCORR_NORMED;break;
    case 4: match_method = cv::TM_CCOEFF;break;
    case 5: match_method = cv::TM_CCOEFF_NORMED;break;
    default: match_method=cv::TM_SQDIFF;break;
    }

}

void MainWindow::on_searchRange_currentTextChanged(const QString &arg1)
{
    sf_hsize=arg1.toInt();
}

void MainWindow::on_Preview_clicked()
{

       char imageName[200];
       cv::Mat image;
       cv::namedWindow("Preview",1);

       while(true)
       {
           sprintf(imageName, "frame%.3d.jpg", pre_count);
           image = cv::imread( imageName, 0 );
           imshow( "Preview", image );
           if(cv::waitKey(10)>=0) break;
       }
       cv::destroyWindow("Preview");
       cv::waitKey(0);
}

void MainWindow::on_brightness_sliderMoved(int position)
{
    brightness=position;
}

void MainWindow::on_maskW_currentTextChanged(const QString &arg1)
{
    mask=arg1.toInt();
}

void MainWindow::on_maskH_currentTextChanged(const QString &arg1)
{
    mask2=arg1.toInt();
}


void MainWindow::on_pushButton_clicked()
{
    if(pre_count>0){
    pre_count--;}
}

void MainWindow::on_pushButton_2_clicked()
{
    if(pre_count<frames-1){
    pre_count++;}
}

void MainWindow::on_StartFrame_editingFinished()
{
    startframe=ui->StartFrame->text().toInt();
}


void MainWindow::on_Start_2_clicked()
{
    a1=ui->spinBox->text().toInt();
    a2=ui->spinBox_3->text().toInt();
    b1=ui->spinBox_2->text().toInt();
    b2=ui->spinBox_4->text().toInt();
    a3=0;
    b3=0;
    a4=ui->spinBox_5->text().toInt();
    b4=ui->spinBox_6->text().toInt();
    point=0;
    cv::Mat temp;
    char info[200],info2[200],info3[200],info4[200],info5[200],info6[200];
    for(int u=0;u<3;u++){
        minResult[u]=0.0;
        maxResult[u]=0.0;
        aveResult[u]=0.0;
        maxfResult[u]=0;
        minfResult[u]=0;
    }
    ui->textEdit->clear();
    ui->textEdit_2->clear();
    cv::Mat Img,Img2_1,Img3_1,Img4_1,Img5_1,Img2_2,Img3_2,Img4_2,Img5_2,Imgblur,ImgH;
    cv::Mat img1, img2,img3;
    counter = 0;
    int save = 2;
    //double length=0.0;
    cv::Mat frameblur,sf1,sf2;
    cv::Mat output1,output2;
    char imageName[200];
    QVector<double> x(frames), y(frames), y1(frames), y2(frames);

    for(int i=1;i<=frames;i++){
        x[i-1]=i;
    }
    sprintf(imageName, "frame%.3d.jpg", startframe-1);
    Img = cv::imread( imageName, 0 );
    cv::namedWindow("Choose two points", 0);
    if((a1+b1+a2+b2)==0){
                   while (point<3) {
                       Img.copyTo(temp);
                       cv::setMouseCallback("Choose two points", CallBackFunc_2, 0);
                       if(point==1){

                       cv::line(temp,cv::Point(a1,b1),cv::Point(a3,b1),cv::Scalar(0,255,0),2,8);}
                       cv::line(temp,cv::Point(a1,b1),cv::Point(a1,b3),cv::Scalar(0,255,0),2,8);
                       cv::line(temp,cv::Point(a1,b3),cv::Point(a3,b3),cv::Scalar(0,255,0),2,8);
                       cv::line(temp,cv::Point(a3,b1),cv::Point(a3,b3),cv::Scalar(0,255,0),2,8);

                       ImgH=temp+cv::Scalar(brightness,brightness,brightness);
                       sprintf(info,"PointA:(%d, %d)",a1,b1);
                       sprintf(info2,"PointB:(%d, %d)",a3,b3);
                       putText(ImgH,info,cv::Point(20,200),cv::FONT_HERSHEY_COMPLEX_SMALL,0.8,cv::Scalar(255,255,255),1);
                       putText(ImgH,info2,cv::Point(20,220),cv::FONT_HERSHEY_COMPLEX_SMALL,0.8,cv::Scalar(255,255,255),1);
                       cv::imshow("Choose two points",ImgH);
                       cv::waitKey(10);
                  }}
                       else if(point==2){
                       Img.copyTo(temp);
                       cv::line(temp,cv::Point(a1,b1),cv::Point(a2,b1),cv::Scalar(0,255,0),2,8);}
                       cv::line(temp,cv::Point(a1,b1),cv::Point(a1,b2),cv::Scalar(0,255,0),2,8);
                       cv::line(temp,cv::Point(a1,b2),cv::Point(a2,b2),cv::Scalar(0,255,0),2,8);
                       cv::line(temp,cv::Point(a2,b1),cv::Point(a2,b2),cv::Scalar(0,255,0),2,8);
                       ImgH=temp+cv::Scalar(brightness,brightness,brightness);
                       sprintf(info,"PointA:(%d, %d)",a1,b1);
                       sprintf(info2,"PointB:(%d, %d)",a2,b2);
                       sprintf(info6,"PointC:(%d, %d)",a3,b3);
                       putText(ImgH,info,cv::Point(20,200),cv::FONT_HERSHEY_COMPLEX_SMALL,0.8,cv::Scalar(255,255,255),1);
                       putText(ImgH,info2,cv::Point(20,220),cv::FONT_HERSHEY_COMPLEX_SMALL,0.8,cv::Scalar(255,255,255),1);
                       putText(ImgH,info6,cv::Point(20,240),cv::FONT_HERSHEY_COMPLEX_SMALL,0.8,cv::Scalar(255,255,255),1);
                       cv::imshow("Choose two points",ImgH);
                       cv::waitKey(10);}


       cv::GaussianBlur( Img, Imgblur, cv::Size( blurx, blury), 0, 0 );
       img1 = Imgblur(cv::Rect(a1, b1, a2, b2));
       img2 = Imgblur(cv::Rect(a4-mask, b4-mask2, 2*mask, 2*mask2));
       img3 = Img(cv::Rect(a1, b1, a2, b2));
       int cn =img3.channels();

   int output1_cols =  Img.cols - img1.cols + 1;
   int output1_rows = Img.rows - img1.rows + 1;
   output1.create( output1_cols, output1_rows, CV_32FC1 );
   int output2_cols =  Img.cols - img1.cols + 1;
   int output2_rows = Img.rows - img1.rows + 1;
   output2.create( output2_cols, output2_rows, CV_32FC1 );

       cv::destroyWindow("Choose two points");
       y1[0]=abs(a1-a2)*scalex;
       y1[1]=y1[0];
       y2[0]=abs(b1-b2)*scaley;
       y2[1]=y2[0];
       y[0]=sqrt(y1[0]*y1[0]+y2[0]*y2[0]);
       y[1]=y[0];
       ResultCompare(y1[0], y2[0], y[0],false,startframe );
       ui->textEdit->append ("line:\tx1\ty1\tx2\ty2\thorizontal\tvertical\tdistance\n");
       ui->textEdit->append ("frame"+QString::number(startframe)+" : \t"+QString::number(a1)+"\t"+QString::number(b1)+"\t"+QString::number(a2)+"\t"+QString::number(b2)+"\t"+QString::number((int)(y1[0]*100+.5)/100.)+"\t"+QString::number((int)(y2[0]*100+.5)/100.)+"\t"+QString::number((int)(y[0]*100+.5)/100.));
       //ui->textEdit->append ("frame2 : \t"+QString::number(a1)+"\t"+QString::number(b1)+"\t"+QString::number(a2)+"\t"+QString::number(b2)+"\t"+QString::number((int)(y1[0]*100+.5)/100.)+"\t"+QString::number((int)(y2[0]*100+.5)/100.)+"\t"+QString::number((int)(y[0]*100+.5)/100.));
       cv::namedWindow("Video Player",0);

       while(startframe<=frames-1)
       {
               sprintf(imageName, "frame%.3d.jpg", startframe++);
               Img = cv::imread( imageName, 0 );
               cv::GaussianBlur( Img, frameblur, cv::Size( blurx, blury), 0, 0 );
               sf1=Img(cv::Rect(a1-sf_hsize, b1-sf_hsize, 2*sf_hsize, 2*sf_hsize));
               sf2=Img(cv::Rect(a2-sf_hsize, b2-sf_hsize, 2*sf_hsize, 2*sf_hsize));
               cv::matchTemplate(img1,sf1,output1,match_method);
               cv::matchTemplate(img2,sf2,output2,match_method);
               normalize( output1, output1, 0, 1, cv::NORM_MINMAX, -1, cv::Mat() );
               normalize( output2, output2, 0, 1, cv::NORM_MINMAX, -1, cv::Mat() );

               double minVal1; double maxVal1; cv::Point minLoc1; cv::Point maxLoc1;cv::Point matchLoc1;
               double minVal2; double maxVal2; cv::Point minLoc2; cv::Point maxLoc2;cv::Point matchLoc2;

               cv::minMaxLoc( output1, &minVal1, &maxVal1, &minLoc1, &maxLoc1, cv::Mat() );
               cv::minMaxLoc( output2, &minVal2, &maxVal2, &minLoc2, &maxLoc2, cv::Mat() );
               // For SQDIFF and SQDIFF_NORMED, the best matches are lower values. For all the other methods, the higher the better
               if( match_method  == cv::TM_SQDIFF || match_method == cv::TM_SQDIFF_NORMED )
               {
                   matchLoc1 = minLoc1;
                   matchLoc2 = minLoc2;
               }
               else
               { matchLoc1 = maxLoc1;
                 matchLoc2 = maxLoc2;
               }
               a1=matchLoc1.x+a1+mask-sf_hsize;
               b1=matchLoc1.y+b1+mask2-sf_hsize;
               a2=matchLoc2.x+a2+mask-sf_hsize;
               b2=matchLoc2.y+b2+mask2-sf_hsize;

               y1[save]=abs(a1-a2)*scalex;
               y2[save]=abs(b1-b2)*scaley;
               y[save]=sqrt(y1[save]*y1[save]+y2[save]*y2[save]);
               ResultCompare(y1[save], y2[save],y[save],true, (startframe+save)/2 );
               ui->textEdit->append ("frame"+QString::number((startframe+save)/2)+" :\t"+QString::number(a1)+"\t"+QString::number(b1)+"\t"+QString::number(a2)+"\t"+QString::number(b2)+"\t"+QString::number((int)(y1[save]*100+.5)/100.)+"\t"+QString::number((int)(y2[save]*100+.5)/100.)+"\t"+QString::number((int)(y[save]*100+.5)/100.));

               //img1 = frameblur(Rect(a1-mask, b1-mask2, 2*mask, 2*mask2));
               //img2 = frameblur(Rect(a2-mask, b2-mask2, 2*mask, 2*mask2));


               ImgH=Img+cv::Scalar(brightness,brightness,brightness);
               sprintf(info,"PointA:(%d, %d)",a1,b1);
               sprintf(info2,"PointB:(%d, %d)",a3,b3);
               sprintf(info3,"hori_dis:%.2f",(int)(y1[save]/10*100+.5)/100.);
               sprintf(info4,"verti_dis:%.2f",(int)(y2[save]/10*100+.5)/100.);
               sprintf(info5,"Dis:%.2f",(int)(y[save]/10*100+.5)/100.);
               putText(ImgH,info,cv::Point(20,200),cv::FONT_HERSHEY_COMPLEX_SMALL,0.8,cv::Scalar(255,255,255),1);
               putText(ImgH,info2,cv::Point(20,220),cv::FONT_HERSHEY_COMPLEX_SMALL,0.8,cv::Scalar(255,255,255),1);
               putText(ImgH,info3,cv::Point(20,240),cv::FONT_HERSHEY_COMPLEX_SMALL,0.8,cv::Scalar(255,255,255),1);
               putText(ImgH,info4,cv::Point(20,260),cv::FONT_HERSHEY_COMPLEX_SMALL,0.8,cv::Scalar(255,255,255),1);
               putText(ImgH,info5,cv::Point(20,280),cv::FONT_HERSHEY_COMPLEX_SMALL,0.8,cv::Scalar(255,255,255),1);
               cv::line(ImgH,cv::Point(a1,b1),cv::Point(a2,b2),cv::Scalar(255,0,0),1,4);
               cv::imshow("Video Player",ImgH);

               save++;

               if(cv::waitKey(50)>=0) break;
           }


aveResult[0]/=(frames);
aveResult[1]/=(frames);
aveResult[2]/=(frames);
ui->textEdit_2->append ("Horizontal_max = "+QString::number((int)(maxResult[0]*100+.5)/100.)+"\tVertical_max = "+QString::number((int)(maxResult[1]*100+.5)/100.)+"\tDistance_max = "+QString::number((int)(maxResult[2]*100+.5)/100.));
ui->textEdit_2->append ("Hori_max_frame = "+QString::number(maxfResult[0])+"\tVerti_max_frame = "+QString::number(maxfResult[1])+"\tDis_max_frame = "+QString::number(maxfResult[2]));
ui->textEdit_2->append ("Horizontal_min = "+QString::number((int)(minResult[0]*100+.5)/100.)+"\tVertical_min = "+QString::number((int)(minResult[1]*100+.5)/100.)+"\tDistance_min = "+QString::number((int)(minResult[2]*100+.5)/100.));
ui->textEdit_2->append ("Hori_min_frame = "+QString::number(minfResult[0])+"\tVerti_min_frame = "+QString::number(minfResult[1])+"\tDis_min_frame = "+QString::number(minfResult[2]));
ui->textEdit_2->append ("Horizontal_ave = "+QString::number((int)(aveResult[0]*100+.5)/100.)+"\tVertical_ave = "+QString::number((int)(aveResult[1]*100+.5)/100.)+"\tDistance_ave = "+QString::number((int)(aveResult[2]*100+.5)/100.)+"\n");
for(int j=0;j<frames;j++){
    y[j]/=10;
    y1[j]/=10;
    y2[j]/=10;

}
ui->widget->graph(0)->setData(x,y);
ui->widget->graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle));
ui->widget->graph(1)->setPen(QPen(Qt::red));
ui->widget->graph(1)->setData(x,y1);
ui->widget->graph(1)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssTriangle));
ui->widget->graph(2)->setPen(QPen(Qt::green));
ui->widget->graph(2)->setData(x,y2);
ui->widget->graph(2)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssSquare));
ui->widget->xAxis->setRange(x.first()-1, x.last()+1);
ui->widget->yAxis->setRange(0.0, maxResult[2]/10+0.5);
ui->doubleSpinBox->setValue(0.0);
ui->doubleSpinBox_2->setValue( maxResult[2]/10+0.5);
ui->widget->replot();
if(n_save!=0){
    int n_delete=0;
    char deletefilename[200];
    while(n_delete<n_save){
        sprintf(deletefilename,"frame%.3d.jpg", n_delete++);
        remove(deletefilename);
    }
}
       cv::destroyWindow("Video Player");
       cv::waitKey(0);
}
