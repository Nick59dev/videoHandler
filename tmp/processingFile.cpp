#include <iostream>
#include <thread>
#include <fstream>

#include "st.h"
#include "processingFile.h"

using namespace std;

namespace handler
{
  videoHandler::videoHandler()
  {
    std::cout << "HANDLER" << std::endl;
  }

  std::size_t videoHandler::reading_yuv(const char * filename, unsigned char * writing_stream, const unsigned int& height,
                     const unsigned int& width, const size_t& offset, const char& type)
  {
    POINT im;
  	std::ifstream file(filename, std::ios::binary);
  	std::size_t counter = 0;

  	file.seekg(sizeof(FHDER) + sizeof(INFO));

  	const std::size_t sIze = width * height;

  	for(size_t i = 0; i < sIze; ++i) {
  		if((i % width) == 0 && offset != 0) {
  			file.seekg(offset, std::ios::cur);
  			i += width + 1;
  		}
  		if((i % 2) && (offset != 0)) {
  			file.seekg(sizeof(POINT), std::ios::cur);
  			continue;
  		}

  		file >> im.b;
  		file >> im.g;
  		file >> im.r;

  		writing_stream[counter] = counting_yuv(im, type);
  		++counter;
  	}
  	cout << counter << endl;

  	file.close();
  	return counter;
  }

  unsigned char videoHandler::counting_yuv(const POINT& im, const char& type) const
  {
    return (type == 'y') ? (unsigned char)((int)(0.299 * im.r + 0.587 * im.g + 0.114 * im.b)) :             // если у, то считаем у
  	       (type == 'u') ? ((unsigned char)((int)((-0.14713) * im.r + (-0.28886) * im.g + 0.436 * im.b))) : // если u, то считаем u с другими константами
  				 (unsigned char)((int)(0.615 * im.r + (-0.51499) * im.g + (-0.10001) * im.b));                    // если не то, и не другое, то считаем v
  }

  int videoHandler::reading_rgb(const char * filename, const char * yuv_file,  const std::size_t& yuv_frames,
  								 const std::size_t& yuv_width, const std::size_t& yuv_height, const char * output_file)
  {
    FHDER fh; // начало BMP-файла
  	INFO ih; // метаданные BMP-файла

  	char buffer;

  	std::ifstream yuv_video;
  	std::ofstream yuv_writing;

  	// решил использовать для чтения пикчи библиотеку из си,
  	// так как с ее помощью удобнee считывать структуры.
  	FILE *img;

  	yuv_video.open(yuv_file, std::ios::binary);

  	if(yuv_video.is_open()) {
  		yuv_video.seekg(0);
  		std::cout << "YUV file is opened now." << endl;
  	} else {
  		std::cerr << "cannot open source YUV file. Change the path." << std::endl;
  		return -1;
  	}

  	yuv_writing.open(output_file, std::ios::binary);

  	if((img = fopen(filename, "rb")) != NULL){
  		std::cout << "BMP picture has just been opened." << std::endl;
  	}	else {
  		std::cerr << "Cannot open the image file. Change the directory." << std::endl;
  		return -3;
  	}

  	fread(&fh, 1, sizeof(FHDER), img); // считываем начало картинки
    fread(&ih, 1, sizeof(INFO), img); // считываем метаданные

  	cout << "WIDTH = " << ih.width << endl
  		   << "HEIGHT = " << ih.height << endl;

    fclose(img);

  	unsigned int height = ih.height;
  	unsigned int width = ih.width;

  	unsigned int pixs = height * width;
  	unsigned int pixs2 = pixs / 4;

  	unsigned char * y_s = new unsigned char[ih.height * ih.width];
  	unsigned char * u_s = new unsigned char[(ih.height * ih.width) / 4];
  	unsigned char * v_s = new unsigned char[(ih.height * ih.width) / 4];


  	// std::thread y_processing(this->(&reading_yuv), filename, y_s, height, width, 0, 'y'); // начинаем работу потоков, обрабатывающих чтение картинки
  	// std::thread u_processing(this->(&reading_yuv), filename, u_s, height, width, yuv_width * sizeof(POINT), 'u');
  	// std::thread v_processing(this->(&reading_yuv), filename, v_s, height, width, yuv_width * sizeof(POINT), 'v');

  	// если честно, не вижу смысла использовать потоки при
  	// записи в бинарный файл, так как байты в любом случае должны идти
  	// по порядку, что в итоге обернется тем же временем работы,
  	// которое было бы и без использования потоков, поэтому потоки
  	// было решено использовать только для считывания R, G и B из BMP.

    this->reading_yuv(filename, y_s, height, width, 0, 'y');
    this->reading_yuv(filename, u_s, height, width, yuv_width * sizeof(POINT), 'u');
    this->reading_yuv(filename, v_s, height, width, yuv_width * sizeof(POINT), 'v');


  	// y_processing.join(); // ждем, пока все потоки закончат работу,
  	// u_processing.join(); // так как без данных с картинки нет
  	// v_processing.join(); // никакого смысла продолжать работу

  	size_t yuv_y = yuv_width * yuv_height;
  	size_t yuv_u = yuv_y / 2;
  	size_t yuv_v = yuv_u / 2;

  	cout << yuv_y << endl;

  	for(size_t frame = 0; frame < yuv_frames; ++frame) { // цикл для каждого кадрa
  			//----------------------- YUV PROCESSING  ------------------------
  			size_t counter2 = 0;

  			for(size_t counter = 0; counter < yuv_y + yuv_u; ++counter) { // сперва заполняем массив у-значений
  				if(counter < yuv_y)
  				{
  					if(((int)(counter % yuv_width) < ih.width) && ((int)(counter / yuv_width) < ih.height)) { // проверяем строку и ряд, на котором остановились
  						buffer = y_s[counter2];
  						++counter2;
  						yuv_writing.write(&buffer, 1); // записываем байт в видеофайл
  						yuv_video.seekg(1, std::ios::cur); // сдвигаем указатель в видео, чтобы видео шло параллельно с нашей картинкой
  					} else {
  						yuv_video.read(&buffer, 1);
  						yuv_writing.write(&buffer, 1);
  					}
  				}
  				else
  				{
  					if(((unsigned int)((counter - yuv_y) % yuv_v) % (yuv_width / 2) < (unsigned int)(ih.width / 2) ) &&
  							((unsigned int)((counter - yuv_y) % yuv_v) / (yuv_width / 2) < (unsigned int)(ih.height / 2))) { // проверям, на какой мы строке и на каком символе
  						if((counter - yuv_y) < yuv_v)
  						{
  								buffer = u_s[counter2 - pixs];
  						}
  						else
  						{
  								buffer = v_s[counter2 - pixs - pixs2];
  						}
  							++counter2;
  							yuv_writing.write(&buffer, 1);
  							yuv_video.seekg(1, std::ios::cur);
  						} else { // если текущая ширина или высота больше, чем у картинки, то пишем в видеофайл изначальное видео
  							yuv_video.read(&buffer, 1);
  							yuv_writing.write(&buffer, 1);
  						}
  				}

  			}
  	}

  	yuv_writing.close();
  	yuv_video.close();

  	delete[] y_s;
  	delete[] u_s;
  	delete[] v_s;

  	return 0;
  }

  videoHandler::~videoHandler()
  {
    std::cout << "Handler object has worked." << std::endl;
  }
}
