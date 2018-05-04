#include <cstdio>
#include <cstring>
#include <iostream>
#include <fstream>
#include <windows.h>

using namespace std;

#pragma pack(1)

struct __header {
	WORD bfType; // 位图文件的类型，必须为“BM” 
	DWORD bfSize; // 位图文件的大小，以字节为单位 
	WORD bfReserved1; // 位图文件保留字，必须为0 
	WORD bfReserved2; // 位图文件保留字，必须为0 
	DWORD bfOffBits; // 位图数据的起始位置，以相对于位图文件头的偏移量表示，以字节为单位
} header, header_rtt;

struct __info {
	DWORD biSize; // 本结构所占用字节数 
	LONG biWidth; // 位图的宽度，以像素为单位 
	LONG biHeight; // 位图的高度，以像素为单位 
	WORD biPlanes; // 目标设备的平面数不清，必须为1 
	WORD biBitCount; // 每个像素所需的位数，必须是1(双色), 4(16色)，8(256色)或24(真彩色)之一 
	DWORD biCompression; // 位图压缩类型，必须是 0(不压缩),1(BI_RLE8压缩类型)或2(BI_RLE4压缩类型)之一 
	DWORD biSizeImage; // 位图的大小，以字节为单位
	LONG biXPelsPerMeter; // 位图水平分辨率，每米像素数 
	LONG biYPelsPerMeter; // 位图垂直分辨率，每米像素数 
	DWORD biClrUsed;// 位图实际使用的颜色表中的颜色数 
	DWORD biClrImportant;// 位图显示过程中重要的颜色数
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

