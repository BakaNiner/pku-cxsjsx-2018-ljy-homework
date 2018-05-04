#include <cstdio>
#include <cstring>
#include <iostream>
#include <fstream>
#include <windows.h>

using namespace std;

#pragma pack(1)

struct __header {
	WORD bfType; // λͼ�ļ������ͣ�����Ϊ��BM�� 
	DWORD bfSize; // λͼ�ļ��Ĵ�С�����ֽ�Ϊ��λ 
	WORD bfReserved1; // λͼ�ļ������֣�����Ϊ0 
	WORD bfReserved2; // λͼ�ļ������֣�����Ϊ0 
	DWORD bfOffBits; // λͼ���ݵ���ʼλ�ã��������λͼ�ļ�ͷ��ƫ������ʾ�����ֽ�Ϊ��λ
} header, header_rtt;

struct __info {
	DWORD biSize; // ���ṹ��ռ���ֽ��� 
	LONG biWidth; // λͼ�Ŀ�ȣ�������Ϊ��λ 
	LONG biHeight; // λͼ�ĸ߶ȣ�������Ϊ��λ 
	WORD biPlanes; // Ŀ���豸��ƽ�������壬����Ϊ1 
	WORD biBitCount; // ÿ�����������λ����������1(˫ɫ), 4(16ɫ)��8(256ɫ)��24(���ɫ)֮һ 
	DWORD biCompression; // λͼѹ�����ͣ������� 0(��ѹ��),1(BI_RLE8ѹ������)��2(BI_RLE4ѹ������)֮һ 
	DWORD biSizeImage; // λͼ�Ĵ�С�����ֽ�Ϊ��λ
	LONG biXPelsPerMeter; // λͼˮƽ�ֱ��ʣ�ÿ�������� 
	LONG biYPelsPerMeter; // λͼ��ֱ�ֱ��ʣ�ÿ�������� 
	DWORD biClrUsed;// λͼʵ��ʹ�õ���ɫ���е���ɫ�� 
	DWORD biClrImportant;// λͼ��ʾ��������Ҫ����ɫ��
} info, info_rtt;

struct __pixel {
	BYTE R, G, B;
} p[2000][2000]; 

int main(int argc, char *argv[]) {
	ios::sync_with_stdio(false);
	ifstream fin(argv[1], ios::in | ios::binary);
	ofstream fout(argv[2], ios::out | ios::binary);

	fin.read((char *)&header, sizeof(header));
	fin.read((char *)&info, sizeof(info));
	int n = info.biHeight, m = info.biWidth;

	for(int i = 0; i < n; i++) {
		for(int j = 0; j < m; j++)
			fin.read((char *)&p[i][j], sizeof(p[i][j]));

		int res = (m * 3 + 3) / 4 * 4 - m * 3;
		BYTE tmp;
		for(int j = 0; j < res; j++)
			fin.read((char *)&tmp, sizeof(tmp));
	}

	info_rtt = info;
	info_rtt.biHeight = m; info_rtt.biWidth = n;
	info_rtt.biSizeImage = (n * 24 + 31) / 8 * m;

	header_rtt = header;
	header_rtt.bfSize = header_rtt.bfOffBits + info_rtt.biSizeImage;

	fout.write((char *)&header_rtt, sizeof(header_rtt));
	fout.write((char *)&info_rtt, sizeof(info_rtt));
	for(int i = m - 1; i >= 0; i--) {
		for(int j = 0; j < n; j++)
			fout.write((char *)&p[j][i], sizeof(p[j][i]));

		int res = (n * 3 + 3) / 4 * 4 - n * 3;
		BYTE tmp = 0;
		for(int j = 0; j < res; j++)
			fout.write((char *)&tmp, sizeof(tmp));
	}

	fin.close();
	fout.close();
	return 0;
}

