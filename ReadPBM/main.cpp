#include <stdio.h>
#include <stdlib.h>
#include <QApplication>
#include <QFile>
#include <QFileDialog>
#include <QDir>
#include <QLabel>


typedef unsigned char uchar;

typedef struct {
    char MN[2];
    int width, height;
    uchar **pixelData;
} PBMImage;

enum BoolData {FALSE, TRUE};

int readPBM(char* filename, PBMImage* img);
void releasePBM(PBMImage* img);

int main(int argc, char** argv)
{
    QApplication a(argc, argv);
    PBMImage img;
    int x,y;
#if 0
    if(argc != 2) {
        fprintf(stderr, "usage : %s <filename>\n", argv[0]);
        return -1;
    }
#else
    QString fileName = QFileDialog::getOpenFileName(0,
                      "Open Image", QDir::homePath(), "Image Files (*.pbm)");
#endif
    /* 이미지 파일 읽기 */
    if(readPBM(fileName.toUtf8().data(), &img) != TRUE) {
        return -1;
    }

    for(x =0; x<img.height; x++) {
        for(y=0; y<img.width; y++)
            printf("%s", (img.pixelData[x][y] == 1)? "O":"X");
        printf("\n");
    }
    fflush(NULL);
    releasePBM(&img);

    QLabel label;
    label.setPixmap(QPixmap(fileName).scaled(256, 256));
    label.show();


    return 0;
}

int readPBM(char* filename, PBMImage* img)
{

    FILE* fp;
    unsigned int x, y, tmp;

    fp = fopen(filename, "r");
    if(fp == NULL) {
        fprintf(stderr, "파일을 열 수 없습니다 : %s\n", filename);
        return FALSE;
    }

    fscanf(fp, "%c %c", &img->MN[0], &img->MN[1]);
    if(img->MN[0] != 'P' || img->MN[1] != '1') {
        fprintf(stderr, "PBM 이미지 포맷이 아닙니다 : %s\n", img->MN);
        return FALSE;
    }

    fscanf(fp, "%d %d", &img->width, &img->height);

    img->pixelData = (uchar**)malloc(img->height*sizeof(uchar*));
    for(x=0; x<img->height; x++) {
        img->pixelData[x] = (uchar*)malloc(img->width*sizeof(uchar));
    }

    for(x=0; x<img->height; x++) {
        for(y=0; y<img->width; y++) {
            fscanf(fp, "%u", &tmp);
            img->pixelData[x][y] = (uchar)tmp;
        }
    }
    fclose(fp);

    return TRUE;
}

void releasePBM(PBMImage* img)
{
    for(int i = 0; i<img->height; i++)
        free(img->pixelData[i]);

    free(img->pixelData);
}
