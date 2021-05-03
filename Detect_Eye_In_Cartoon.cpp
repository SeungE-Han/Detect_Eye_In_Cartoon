#include <opencv2\opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

int main() {
	Mat img1 = imread("hwfig4-2.jpg", IMREAD_GRAYSCALE); //���� �о��
	Mat img2 = imread("hwfig4-2.jpg", IMREAD_COLOR);
	Point pt;
	Point maxpos1(0, 0), maxpos2(0, 0), p1(0, 0), p2(0, 0);
	float maxval1 = 0.0, maxval2 = 0.0;
	float width1 = 0, width2 = 0;

	for (int w = 20; w < 30; w++) { //width�� 20���� 29����
		for (pt.y = 0; pt.y < img1.rows - w; pt.y++) {
			for (pt.x = 0; pt.x < img1.cols - 3*w; pt.x++) {
				Mat_<uchar> m1(w, w), m2(w, w), m3(w, w); //w*w ��� ����
				
				Rect roi(pt.x, pt.y, w, w); //pt�� ���������� ���� w, ���� w �簢�� ����
				m1 = (Mat)img1(roi); //img1�� roi�κ��� ����� m1�� ����

				Rect roi2(pt.x + w, pt.y, w, w); //(pt.x+w, pt.y)�� ���������� ���� w, ���� w �簢�� ����
				m2 = (Mat)img1(roi2); //img1�� roi2�κ��� ����� m2�� ����

				Rect roi3(pt.x + 2 * w, pt.y, w, w); //(pt.x+2*w, pt.y)�� ���������� ���� w, ���� w �簢�� ����
				m3 = (Mat)img1(roi3); //img1�� roi3�κ��� ����� m3�� ����

				Scalar val = mean(m1); //m1�� ��հ��� val�� ����
				Scalar val2 = mean(m2); //m2�� ��հ��� val2�� ����
				Scalar val3= mean(m3); //m3�� ��հ��� val3�� ����

				float mavg = (val[0] + (255 - val2[0]) + val3[0]) / (255 * 3); //1�� ����� ���� ���̶�� ��
				
				if ((mavg >= maxval1 || mavg >= maxval2) && abs(pt.x - maxpos1.x) > 5 && abs(pt.x - maxpos2.x) > 5) { 
					//abs�� ���� -> 5�� �ȼ��� �������� ã��
					if (maxval2 < maxval1) {
						maxval2 = mavg; 
						width2 = w; 
						maxpos2 = pt; 
					}
					else {
						maxval1 = mavg; //mavg�� ����
						width1 = w; //w ����
						maxpos1 = pt; //���� ��ġ
					}
				}
			}
		}
	}

	cout << "maxval1: " << maxval1 << endl;
	cout << "maxpos1: " << maxpos1.x << endl << "maxpos1.y: " << maxpos1.y << endl;
	cout << "width1: " << width1 << endl;

	cout << "maxval2: " << maxval2 << endl;
	cout << "maxpos2: " << maxpos2.x << endl << "maxpos2.y: " << maxpos2.y << endl;
	cout << "width2: " << width2 << endl;

	p1 = Point(maxpos1.x + width1 * 3, maxpos1.y + width1); //�簢���� ������ �� ���
	p2 = Point(maxpos2.x + width2 * 3, maxpos2.y + width2);

	rectangle(img2, maxpos1, p1, Scalar(0, 0, 255), 2); //�簢�� �׸�
	rectangle(img2, maxpos2, p2, Scalar(0, 0, 255), 2);

	imshow("�Է�", img1);
	imshow("���", img2);

	waitKey(0);
	return 0;
}