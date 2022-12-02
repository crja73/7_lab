#include "mainwindow.h"
#include "ui_mainwindow.h"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tableWidget->setColumnCount(2); //задаем количество столбцов таблицы
    ui->spinBox_count->setMinimum(3);
    ui->spinBox_count->setMaximum(200);
    ui->label_value2->clear();
    ui->label_value1->clear();
}

MainWindow::~MainWindow() // работа от диманчика, обращайтесь
{
    delete ui;
}

void MainWindow::on_spinBox_count_valueChanged(int arg1)
{
    ui->tableWidget->setRowCount(arg1); //задаем количество строк равное значению в spinbox
    for (int i = 0; i<arg1; i++)
    {
        QTableWidgetItem *item_x = ui->tableWidget->item(i,0); //указатель на ячейку x
        QTableWidgetItem *item_y = ui->tableWidget->item(i,1); //указатель на ячейку y

        if(item_x == nullptr)//если ячейка с x не существует (память не выделена)
        {
            item_x = new QTableWidgetItem; //создаем ячейку (выделяем память)
            ui->tableWidget->setItem(i,0,item_x);//сообщаем таблице, что была создана новая ячейка
        }
        if(item_y == nullptr)//если ячейка с x не существует (память не выделена)
        {
            item_y = new QTableWidgetItem; //создаем ячейку (выделяем память)
            ui->tableWidget->setItem(i,1,item_y);//сообщаем таблице, что была создана новая ячейка
        }
    }
}
int MainWindow::lol(double a)//возвращает знак числа
{
    if(a>0)
        return(1);
    else if (a<0)
        return(-1);
    else
        return (0);
}
void MainWindow::samoper(int N)
{
    peresech=false;
    double x0=0,y0=0,x1=0,x2=0,y1=0,y2=0,
            x3=0,y3=0;
    double v1x,v1y,v2x,v2y,v3x,v3y,v4x,v4y,v1_x,v1_y,v2_x,v2_y,v3_x,v3_y,v4_x,v4_y;
    int a1,a2,a3,a4;
    for (int i=N-1; i>1;i--)//Проверка на самопересечение
    {

        x3=ui->tableWidget->item(i,0)->text().toDouble();//последняя точка
        y3=ui->tableWidget->item(i,1)->text().toDouble();
        x2=ui->tableWidget->item(i-1,0)->text().toDouble();
        y2=ui->tableWidget->item(i-1,1)->text().toDouble();
        for(int j=0;j<i-2;j++)
        {
            x0=ui->tableWidget->item(j,0)->text().toDouble();
            y0=ui->tableWidget->item(j,1)->text().toDouble();
            x1=ui->tableWidget->item(j+1,0)->text().toDouble();
            y1=ui->tableWidget->item(j+1,1)->text().toDouble();

            v1x=x0-x3;
            v1y=y0-y3;
            v2x=x1-x3;
            v2y=y1-y3;
            v3x=x0-x2;
            v3y=y0-y2;
            v4x=x1-x2;
            v4y=y1-y2;

            v1_x=x3-x0;
            v1_y=y3-y0;
            v2_x=x3-x1;
            v2_y=y3-y1;
            v3_x=x2-x0;
            v3_y=y2-y0;
            v4_x=x2-x1;
            v4_y=y2-y1;

            a1=lol(v2x*v1y-v2y*v1x);
            a2=lol(v4x*v3y-v4y*v3x);
            a3=lol(v1_x*v3_y-v1_y*v3_x);
            a4=lol(v2_x*v4_y-v2_y*v4_x);

            if((a1!=a2&&a3!=a4))
            {
                peresech=true;
                break;
            }
        }
        for(int j=i+1;j<N;j++)
        {

            x0=ui->tableWidget->item(j,0)->text().toDouble();
            y0=ui->tableWidget->item(j,1)->text().toDouble();

            if(j==N-1)
            {
                x1=ui->tableWidget->item(0,0)->text().toDouble();
                y1=ui->tableWidget->item(0,1)->text().toDouble();
            }
            else
            {
                x1=ui->tableWidget->item(j+1,0)->text().toDouble();
                y1=ui->tableWidget->item(j+1,1)->text().toDouble();
            }

            v1x=x0-x3;
            v1y=y0-y3;
            v2x=x1-x3;
            v2y=y1-y3;
            v3x=x0-x2;
            v3y=y0-y2;
            v4x=x1-x2;
            v4y=y1-y2;

            v1_x=x3-x0;
            v1_y=y3-y0;
            v2_x=x3-x1;
            v2_y=y3-y1;
            v3_x=x2-x0;
            v3_y=y2-y0;
            v4_x=x2-x1;
            v4_y=y2-y1;

            a1=lol(v2x*v1y-v2y*v1x);
            a2=lol(v4x*v3y-v4y*v3x);
            a3=lol(v1_x*v3_y-v1_y*v3_x);
            a4=lol(v2_x*v4_y-v2_y*v4_x);

            if((a1!=a2&&a3!=a4))
            {
                peresech=true;
                break;
            }
        }
    }
}

void MainWindow::on_pushButton_calculate_clicked()
{
    //int pointsCount = ui->spinBox_count->value();
    int pointsCount = ui->tableWidget->rowCount();

    bool flag = true;
    for (int i = 0; i<pointsCount; i++)
    {
        QString str_x = ui->tableWidget->item(i,0)->text();
        QString str_y = ui->tableWidget->item(i,1)->text();

        bool flagX, flagY;
        double x = str_x.toDouble(&flagX);
        double y = str_y.toDouble(&flagY);

        if(flagX)
            ui->tableWidget->item(i,0)->setBackground(Qt::white);
        else
        {
            flag = false;
            ui->tableWidget->item(i,0)->setBackground(Qt::red);
        }

        if(flagY)
            ui->tableWidget->item(i,1)->setBackground(Qt::white);
        else
        {
            flag = false;
            ui->tableWidget->item(i,1)->setBackground(Qt::red);
        }
    }
    if(!flag)
    {
        QMessageBox::information(this,"error","Неверное значение в ячейке");
        return;
    }

    double P = 0;
    for(int i = 0; i<pointsCount-1; i++)
    {
        double x1=ui->tableWidget->item(i,0)->text().toDouble();
        double x2=ui->tableWidget->item(i+1,0)->text().toDouble();
        double y1=ui->tableWidget->item(i,1)->text().toDouble();
        double y2=ui->tableWidget->item(i+1,1)->text().toDouble();
        double storona = sqrt((pow((x2-x1),2))+(pow((y2-y1),2)));
        P+=storona;
    }

    double a1=0;
    double a2=0;
    for (int i = 0; i<pointsCount-1; i++)
    {

        double a111 = ui->tableWidget->item(i,0)->text().toDouble();
        double a112 = ui->tableWidget->item(i+1,1)->text().toDouble();                
        double a11 = a111*a112;
        a1+=a11;



        double a211 = ui->tableWidget->item(i+1,0)->text().toDouble();
        double a212 = ui->tableWidget->item(i,1)->text().toDouble();        
        double a22 = a211*a212;        
        a2+=a22;

    }
    double a121 = ui->tableWidget->item(pointsCount-1,0)->text().toDouble();
    double a122 = ui->tableWidget->item(0,1)->text().toDouble();
    double b1 = a121*a122;
    double a221 = ui->tableWidget->item(0,0)->text().toDouble();
    double a222 = ui->tableWidget->item(pointsCount-1,1)->text().toDouble();
    double b2 = a221*a222;
    double square = 0.5*abs(a1+b1-a2-b2);


    bool tochka=true;
    bool pryam=true;
    for(int i=1; i<pointsCount; i++)
    {
        double x1 = ui->tableWidget->item(0,0)->text().toDouble();
        double y1 = ui->tableWidget->item(0,1)->text().toDouble();
        double xi = ui->tableWidget->item(i,0)->text().toDouble();
        double yi = ui->tableWidget->item(i,1)->text().toDouble();
        if(abs(xi-x1)>0 || abs(yi-y1)>0)
        {
            tochka=false;
            if(!tochka)
            {
                for(int i=2; i<=pointsCount-1; i++)
                {
                    double xn = ui->tableWidget->item(pointsCount-1,0)->text().toDouble();
                    double yn = ui->tableWidget->item(pointsCount-1,1)->text().toDouble();
                    if(abs(((xi-x1)/(xn-x1))-((yi-y1)/(yn-y1)))>0)
                    {
                        pryam=false;
                    }
                }
            }
            else
            {
                pryam=false;
            }
        }
    }
    if(qIsInf(square))
    {
        ui->label_value1->clear();
        QMessageBox::information(this,"error","Слишком большое значение площади");
        return;
    }
    if(qIsNaN(square))
    {
       ui->label_value1->clear();
        pryam = false;
        QMessageBox::information(this,"error","Слишком маленькое значение площади");
        return;
    }
    if(!tochka)
    {
        if(!pryam)
        {
            samoper(pointsCount);
            if(!peresech)
            {
                ui->label_value2->setNum(P);
                ui->label_value1->setNum(square);
            }
            else
            {
                ui->label_value2->clear();
                ui->label_value1->clear();
                QMessageBox::information(this,"error","многоугольник - самопересекающийся");
            }
        }
        else
        {
            ui->label_value2->clear();
            ui->label_value1->clear();
            QMessageBox::information(this,"erroe","Введены координаты прямой");
        }
    }
    else
    {
        ui->label_value2->clear();
        ui->label_value1->clear();
        QMessageBox::information(this,"error","Введены координаты точки");
    }
}

void MainWindow::on_tableWidget_cellChanged(int row, int column)
{
    bool flag;
    ui->label_value2->clear();
    ui->label_value1->clear();
    ui->tableWidget->item(row,column)->text().toDouble(&flag);
    if (flag)
    {
        ui->tableWidget->item(row,column)->setBackground(Qt::white);
    }
    else
    {
        ui->tableWidget->item(row,column)->setBackground(Qt::red);
        ui->label_value2->clear();
        ui->label_value1->clear();
    }
}



