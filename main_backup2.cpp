#include <iostream>
#include <thread>
#include <fstream>

#include "tmp/st.h"

using std::cout;
using std::endl;
using std::size_t;

// код был написан в neovim, так что не уверен, как он будет
// отображаться в других текстовых редакторах/IDE.

unsigned char counting_y(int r, int g, int b) {
	return (unsigned char)((int)(0.299 * r + 0.587 * g + 0.114 * b));
}

unsigned char counting_u(int r, int g, int b) {
	return (unsigned char)((int)((-0.14713) * r + (-0.28886) * g + 0.436 * b));
}

unsigned char counting_v(int r, int g, int b) {
	return (unsigned char)((int)(0.615 * r + (-0.51499) * g + (-0.10001) * b));
}

size_t reading_y(const char * filename, unsigned char * writing_stream, const unsigned int height, const unsigned int width) {
	// для каждого треда отдельная функция, обрабатывающая свою компоненту

	IMAGE im;
	std::ifstream file(filename, std::ios::binary);
	size_t counter = 0;

	file.seekg(sizeof(FHDER) + sizeof(INFO));

	for(size_t i = 0; i < height * width; i++) {
		file >> im.b;
		file >> im.g;
		file >> im.r;
		*(writing_stream + i) = counting_y(im.r, im.g, im.b);
		counter++;
	}

	cout << counter << endl;

	file.close();
	return counter;
}

size_t reading_u(const char * filename, unsigned char * writing_stream, const unsigned int height, const unsigned int width) {
	IMAGE im;
	std::ifstream file(filename, std::ios::binary);

	size_t counter = 0;

	file.seekg(sizeof(FHDER) + sizeof(INFO));

	for(size_t i = 0; i < height * width; i++) {
		if(i % width == 0) {
			file.seekg(sizeof(IMAGE) * width, std::ios::cur);
			i += width + 1;
		}
		if(i % 2) {
			file.seekg(sizeof(IMAGE), std::ios::cur);
			continue;
		}

		file >> im.b;
		file >> im.g;
		file >> im.r;

		*(writing_stream + counter) = counting_u(im.r, im.g, im.b);
		counter++;

	}
	cout << counter << endl;

	file.close();
	return counter;
}

size_t reading_v(const char * filename, unsigned char * writing_stream, const unsigned int height, const unsigned int width) {
	IMAGE im;
	std::ifstream file(filename, std::ios::binary);

	size_t counter = 0;

	file.seekg(sizeof(FHDER) + sizeof(INFO));

	for(size_t i = 0; i < height * width; i++) {
		if(i % width == 0) {
			file.seekg(sizeof(IMAGE) + width, std::ios::cur);
			i += width + 1;
		}
		if(i % 2) {
			file.seekg(sizeof(IMAGE), std::ios::cur);
			continue;
		}

		file >> im.b;
		file >> im.g;
		file >> im.r;

		*(writing_stream + counter) = counting_v(im.r, im.g, im.b);
		counter++;

	}
	cout << counter << endl;

	file.close();
	return counter;
}


int reading_rgb(const char * filename, const char * yuv_file, std::size_t yuv_frames,
								 std::size_t yuv_width, std::size_t yuv_height) {
	FHDER fh; // начало BMP-файла
	INFO ih; // метаданные BMP-файла
	IMAGE im; // структура данных для пикселей

	char buffer;

	std::ifstream yuv_video;
	std::ofstream yuv_writing;

	// решил использовать для чтения пикчи библиотеку из си,
	// так как с ее помощью удобнee считывать структуры.
	FILE *img;

	yuv_video.open(yuv_file, std::ios::binary);
	if(yuv_video >> buffer) {
		yuv_video.seekg(0);
		std::cout << "YUV file is opened now." << endl;
	} else {
		std::cerr << "cannot open source YUV file. Change the path." << std::endl;
		return -1;
	}

	yuv_writing.open("media/newVideo1.yuv", std::ios::binary);

	if(img = fopen(filename, "rb")){
		std::cout << "BMP picture has just been opened." << std::endl;
	}	else {
		std::cerr << "Cannot open the image file. Change the directory." << std::endl;
		return -3;
	}

	fread(&fh, 1, sizeof(FHDER), img); // считываем начало картинки
  fread(&ih, 1, sizeof(INFO), img); // считываем метаданные

	cout << "WIDTH = " << ih.width << endl
		   << "HEIGHT = " << ih.height << endl;

	unsigned int height = ih.height;
	unsigned int width = ih.width;

	unsigned char * y_s = new unsigned char[ih.height * ih.width];
	unsigned char * u_s = new unsigned char[(ih.height * ih.width) / 4 + 1];
	unsigned char * v_s = new unsigned char[(ih.height * ih.width) / 4 + 1];


	std::thread y_processing(reading_y, filename, y_s, height, width); // начинаем работу потоков, обрабатывающих чтение картинки
	std::thread u_processing(reading_u, filename, u_s, height, width);
	std::thread v_processing(reading_v, filename, v_s, height, width);

	// если честно, не вижу смысла использовать потоки при 
	// записи в бинарный файл, так как байты в любом случае должны идти
	// по порядку, что в итоге обернется тем же временем работы,
	// которое было бы и без использования потоков, поэтому потоки
	// было решено использовать только для считывания R, G и B из BMP.
	

	y_processing.join(); // ждем, пока все потоки закончат работу,
	u_processing.join(); // так как без данных с картинки нет 
	v_processing.join(); // никакого смысла продолжать работу

	size_t yuv_y = yuv_width * yuv_height;
	size_t yuv_u = yuv_y / 4;
	size_t yuv_v = yuv_u;

	cout << yuv_y << endl;
	fclose(img);

	for(size_t frame = 0; frame < yuv_frames; frame++) { // цикл для каждого кадрa
			//----------------------- Y-COMPONENT PROCESSING  ------------------------
			size_t counter2 = 0;

			for(size_t counter = 0; counter < yuv_y; counter++) { // сперва заполняем массив у-значений
					if((counter % yuv_width < ih.width) && (counter / yuv_width < ih.height)) { // проверяем строку и ряд, на котором остановились
						buffer = *(y_s + counter2);
						counter2++;
						yuv_writing.write(&buffer, 1); // записываем байт в видеофайл
						yuv_video.seekg(1, std::ios::cur); // сдвигаем указатель в видео, чтобы видео шло параллельно с нашей картинкой
					} else {
						yuv_video.read(&buffer, 1);
						yuv_writing.write(&buffer, 1);
				}

			}
			
			counter2 = 0;

			/*
			buffer = (unsigned char)60;
			for(size_t j = 0; j < yuv_y / 2; j++) {
				yuv_writing << buffer;
				yuv_video.seekg(1, std::ios::cur);
			} 
			*/

			//----------------------- Y-COMPONENT PROCESSING  ------------------------
	
			//--------------------- U-COMPONENT PROCESSING ---------------------------

			for(size_t counter = 0; counter < yuv_u; counter++) { // цикл для значений u
					if((counter % (yuv_width / 2) < (ih.width / 2) ) &&
							(counter / (yuv_width / 2) < (ih.height / 2) )) { // проверям, на какой мы строке и на каком символе
						buffer = *(u_s + counter2);
						counter2++;
						yuv_writing.write(&buffer, 1);
						yuv_video.seekg(1, std::ios::cur);
					} else { // если текущая ширина или высота больше, чем у картинки, то пишем в видеофайл изначальное видео
						yuv_video.read(&buffer, 1);
						yuv_writing.write(&buffer, 1);
				}
			}

			/*
			buffer = (unsigned char)0;
			for(size_t counter = 0; counter < yuv_y / 4; counter++) {
				fwrite(&buffer, 1, 1, yuv_writing);
				fseek(yuv_video, 1, SEEK_CUR);
			}
			*/
			
			counter2 = 0;
			//------------------ U-COMPONENT PROCESSING ---------------------------


			//------------------ V-COMPONENT PROCESSING ---------------------------
			for(size_t counter = 0; counter < yuv_v; counter++) { // цикл для значений u
					if((counter % (yuv_width / 2) < (ih.width / 2) ) &&
							(counter / (yuv_width / 2) < (ih.height / 2) )) { // проверям, на какой мы строке и на каком символе
						buffer = *(v_s + counter2);
						counter2++;
						yuv_writing.write(&buffer, 1);
						yuv_video.seekg(1, std::ios::cur);
					} else { // если текущая ширина или высота больше, чем у картинки, то пишем в видеофайл изначальное видео
						yuv_video.read(&buffer, 1);
						yuv_writing.write(&buffer, 1);
				}
			}

			//------------------ V-COMPONENT PROCESSING ---------------------------
			
	}

	yuv_writing.close();
	yuv_video.close();

	delete[] y_s;
	delete[] u_s;
	delete[] v_s;

	return 0;
}


int main(void) {
	printf("This program is working\n");
	reading_rgb("media/Picture2.bmp", "flower.yuv", 250, 352, 288);

	return 0;
}
