/*
#include <QApplication>
#include <QWidget>
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>
#include <QBoxLayout>
#include <QFileDialog>
#include <QDir>
#include <QFile>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QWidget w;

    QLineEdit* widthLineEdit = new QLineEdit("256", &w);
    QLineEdit* heightLineEdit = new QLineEdit("256", &w);
    QPushButton* button = new QPushButton("Load", &w);
    QLabel* imageLabel = new QLabel(&w);

    QHBoxLayout* layout = new QHBoxLayout();
    layout->addWidget(widthLineEdit);
    layout->addWidget(heightLineEdit);
    layout->addStretch(1);
    layout->addWidget(button);

    QVBoxLayout* mainLayout = new QVBoxLayout(&w);
    mainLayout->addLayout(layout);
    mainLayout->addWidget(imageLabel);

    QObject::connect(button, &QPushButton::clicked, [&](){
        QString fileName = QFileDialog::getOpenFileName(0,
                                                        "Open a file", QDir::homePath(),
                                                        "image file(*.raw *.pbm *.pgm *.ppm *.bmp *.jpg *.png)");
        QFile file(fileName);
        file.open(QFile::ReadOnly);
        QByteArray byteArray = file.readAll();
        file.close();

        int width = widthLineEdit->text().toInt();
        int height = heightLineEdit->text().toInt();
        uchar *data = (uchar*)(byteArray.data());

        QImage image = QImage(data, width, height, QImage::Format_Grayscale8);
        QFileInfo fileInfo(fileName);
        if(fileInfo.suffix() == "raw")
            imageLabel->setPixmap(QPixmap::fromImage(image, Qt::AutoColor));
        else
            imageLabel->setPixmap(QPixmap(fileName).scaled(width, height));
        w.setWindowTitle(fileName);
    });

    w.show();
    return a.exec();
}
*/

/* 마리오! */
#include <QApplication>
#include <QFile>
#include <QLabel>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    char pixelData[17][14] = {
         {'_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_'},
         {'_', '_', '_', '_', 'C', 'C', 'C', 'C', 'C', '_', '_', '_', '_', '_'},
         {'_', '_', '_', 'C', 'C', 'C', 'C', 'C', 'C', 'C', 'C', 'C', '_', '_'},
         {'_', '_', '_', 'B', 'B', 'B', 'S', 'S', 'B', 'S', '_', '_', '_', '_'},
         {'_', '_', 'B', 'S', 'B', 'S', 'S', 'S', 'B', 'S', 'S', 'S', '_', '_'},
         {'_', '_', 'B', 'S', 'B', 'B', 'S', 'S', 'S', 'B', 'S', 'S', 'B', '_'},
         {'_', '_', 'B', 'B', 'S', 'S', 'S', 'S', 'B', 'B', 'B', 'B', '_', '_'},
         {'_', '_', '_', '_', 'S', 'S', 'S', 'S', 'S', 'S', 'S', '_', '_', '_'},
         {'_', '_', '_', 'C', 'C', 'O', 'C', 'C', 'C', 'C', '_', '_', '_', '_'},
         {'_', '_', 'C', 'C', 'C', 'O', 'C', 'C', 'O', 'C', 'C', 'C', '_', '_'},
         {'_', 'C', 'C', 'C', 'C', 'O', 'O', 'O', 'O', 'C', 'C', 'C', 'C', '_'},
         {'_', 'W', 'W', 'C', 'O', 'Y', 'O', 'O', 'Y', 'O', 'C', 'W', 'W', '_'},
         {'_', 'W', 'W', 'W', 'O', 'O', 'O', 'O', 'O', 'O', 'W', 'W', 'W', '_'},
         {'_', 'W', 'W', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'W', 'W', '_'},
         {'_', '_', '_', 'O', 'O', 'O', '_', '_', 'O', 'O', 'O', '_', '_', '_'},
         {'_', '_', 'B', 'B', 'B', '_', '_', '_', '_', 'B', 'B', 'B', '_', '_'},
         {'_', 'B', 'B', 'B', 'B', '_', '_', '_', '_', 'B', 'B', 'B', 'B', '_'}
    };

    const char *C = "100  50   0";
    const char *B = "100  50   0";
    const char *S = "0 200 150";
    const char *O = "35   0 0";
    const char *Y = "100 50   0";
    const char *W = "0 200 150";
    const char *A = "229 230 232";

    QFile file("mario.ppm");
    file.open(QFile::WriteOnly);
    file.write("P3\n");
    file.write("14 17\n");
    file.write("255\n");

    for(int i = 0; i < 17; i++) {
        for(int j = 0; j < 14; j++) {
            if(pixelData[i][j] == 'C') {
                file.write(C);
                file.write(" ");
            } else if(pixelData[i][j] == 'B') {
                file.write(B);
                file.write(" ");
            } else if(pixelData[i][j] == 'S') {
                file.write(S);
                file.write(" ");
            } else if(pixelData[i][j] == 'O') {
                file.write(O);
                file.write(" ");
            } else if(pixelData[i][j] == 'Y') {
                file.write(Y);
                file.write(" ");
            } else if(pixelData[i][j] == 'W') {
                file.write(W);
                file.write(" ");
            } else if(pixelData[i][j] == '_') {
                file.write(A);
                file.write(" ");
            }
        }
        file.write("\n");
    }
    file.close();
    QLabel label;
    label.setPixmap(QPixmap("mario.ppm").scaled(500, 500));
    label.show();


    return a.exec();
}



//#include <QApplication>
//#include <QFile>
//#include <QLabel>

//int main(int argc, char *argv[])
//{
//    QApplication a(argc, argv);

//    const char *o = "255   0   0";
//    const char *x = "255 255 255";

//    char H[5][5] = {
//        {'o','x','x','x','o'},
//        {'o','x','x','x','o'},
//        {'o','o','o','o','o'},
//        {'o','x','x','x','o'},
//        {'o','x','x','x','o'}
//    };

//    char I[5][5] = {
//        {'o','o','o','o','o'},
//        {'x','x','o','x','x'},
//        {'x','x','o','x','x'},
//        {'x','x','o','x','x'},
//        {'o','o','o','o','o'}
//    };

//    char E[5][5] = {
//        {'o','o','o','o','o'},
//        {'x','o','o','o','x'},
//        {'x','o','o','o','x'},
//        {'x','x','o','x','x'},
//        {'o','o','o','o','o'}
//    };

//    QLabel label;
//    label.show();
//    int op = 0;

//    QFile file1("1.ppm");
//    file1.open(QFile::WriteOnly);
//    file1.remove();
//    file1.write("P3\n");
//    file1.write("5 5\n");
//    file1.write("255\n");
//    for(int i = 0; i < 5; i++) {
//        for(int j = 0; j < 5; j++) {
//            if(H[i][j] == 'o') {
//                file1.write(o);
//                file1.write(" ");
//            } else if(H[i][j] == 'x') {
//                file1.write(x);
//                file1.write(" ");
//            }
//        }
//        file1.write("\n");
//    }
//    file1.close();

//    QFile file2("2.ppm");
//    file2.open(QFile::WriteOnly);
//    file2.remove();
//    file2.write("P3\n");
//    file2.write("5 5\n");
//    file2.write("255\n");
//    for(int i = 0; i < 5; i++) {
//        for(int j = 0; j < 5; j++) {
//            if(I[i][j] == 'o') {
//                file2.write(o);
//                file2.write(" ");
//            } else if(I[i][j] == 'x') {
//                file2.write(x);
//                file2.write(" ");
//            }
//        }
//        file2.write("\n");
//    }
//    file2.close();

//    QFile file3("3.ppm");
//    file3.open(QFile::WriteOnly);
//    file3.remove();
//    file3.write("P3\n");
//    file3.write("5 5\n");
//    file3.write("255\n");
//    for(int i = 0; i < 5; i++) {
//        for(int j = 0; j < 5; j++) {
//            if(E[i][j] == 'o') {
//                file3.write(o);
//                file3.write(" ");
//            } else if(E[i][j] == 'x') {
//                file3.write(x);
//                file3.write(" ");
//            }
//        }
//        file3.write("\n");
//    }
//    file3.close();

//    while(1) {
//        switch (op) {
//        case 0:
//            label.setPixmap(QPixmap("1.ppm").scaled(500, 500));
//            break;
//        case 1:
//            label.setPixmap(QPixmap("2.ppm").scaled(500, 500));
//            break;
//        case 2:
//            label.setPixmap(QPixmap("3.ppm").scaled(500, 500));
//            break;
//        }
//        op++;
//        op = op % 3;
//    }

//    return a.exec();
//}
