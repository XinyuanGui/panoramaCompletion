#ifndef IMAGECOMPLETION_H
#define IMAGECOMPLETION_H

#include <QtGui/QMainWindow>
#include "ui_imagecompletion.h"

#include <omp.h>

#include <QAction>
#include <QMessageBox>
#include <QImage>
#include <QFileDialog>
#include <math.h>
#include <stdio.h>
#include "Patch.h"
#include "Node.h"
#include "GCoptimization.h"
#include <stdint.h>

#include <iostream>
using namespace std;

struct UKPixels
{
	int x;
	int y;
	bool flag_boundary;
};

class ImageCompletion : public QMainWindow
{
	Q_OBJECT

public:
	ImageCompletion(QWidget *parent = 0, Qt::WFlags flags = 0);
	~ImageCompletion();

public:
	QImage *_imgRGB;       //�����ԭʼ���޲���ɫͼ��
	double *_imgYCbCr;     //ת��YCbCr��ɫ�ռ��ĻҶ�����
	int *_WHT;             //WHT�任��16���任��
	QImage *_imgMask;      //��λͼ��ȱ��λ��8λ��Ĥͼ��
	int *_mask;            //��Ĥ�Ķ����Ʊ�ʾ 1Ϊ��֪���� 0Ϊδ֪����
	int _imgwidth;         //ͼ��Ŀ��
	int _imgheight;        //ͼ��ĸ߶� ԭʼͼ������Ĥͼ��ߴ���ͬ
	int _ukpixels_count;   //ͼ���д��޲������ظ���
	int _patchsize;        //patch�ĳߴ�
	Patch *_imgPatch;      //ָ����ͳ�ƴ��������е�Patch
	int _patch_count;      //patch������Ŀ

	int _x0;               //�������ڵ����Ͻ�x����
	int _y0;               //�������ڵ����Ͻ�y����
	int _x1;               //�������ڵ����½�x����
	int _y1;               //�������ڵ����½�y����

	UKPixels *_upixels;    //���д��޲����ص�ͼ������
	Node *_nodeArray;      // KD-Tree������Ҷ�ӽڵ��Ӧ��ָ��
	int _nodes_count;      //KD-Tree��Ҷ�ӽڵ����Ŀ
	int *_index_frompixeltopatch;
	bool *_flagmatched;   //�жϸ�λ�õ�patch�Ƿ������match
	int *_deltx;
	int *_delty;
	int *_deltx2;
	int *_delty2;

	int _minoffsetx;
	int _minoffsety;
	int _maxoffsetx;
	int _maxoffsety;

	double *_histogram;
	int _sizex;
	int _sizey;

	double *_peaksvalue;
	int *_peaksx;
	int *_peaksy;
	int _peaks_count;

	int *_offsetx_candidates;
	int *_offsety_candidates;
	int _candidates_count;

	int *_optimization_result;

public:
	void createWHTBases(int PatchSize);
	void findRectangle();
	bool judge1(int x, int y, int size); //�ж���(x,y)Ϊ���Ͻǵ�size x size��
										 //patch���Ƿ�������޲�������
	bool judge2(Node *node, int count);  //����K-D��ʱ  �����ж�һ���ڵ��Ƿ���Ҫ���зֽ�
	double* computeWHTVector(int x, int y, int PatchSize);
	int calHyperPlane(Node *node, long double &yuzhi, bool &flag);
	double calL2Distance1(Patch patch1, Patch patch2);
	int propagationProcess(int x, int y);
	double calL2Distance2(Patch patch1, Patch patch2);
	void statisticOffset(int &min1, int &max1, int &min2, int &max2);
	void gaussianFilter();
	void pickoutKCandidates();
	void searchPeaks();
	int findVNeighbor(int index, int x, int y);

private slots:
	void openRGBImage();
	void openMaskImage();
	void toYCbCrChannel();
	void generateWHTVector();
	void generateKDTree();
	void statisticsPatchOffset();
	void gcOptimization();
	void completionImage();

private:
	Ui::ImageCompletionClass ui;
};

#endif // IMAGECOMPLETION_H
