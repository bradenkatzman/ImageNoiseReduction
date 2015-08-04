CC=g++
CFLAGS=-Wall

noise: noise.cpp stb.cpp SimpleImage.cpp SimpleImage.h stb_image.h stb_image_write.h
	$(CC) $(CFLAGS) noise.cpp stb.cpp SimpleImage.cpp -o noise

clean:
	rm noise noiseReduce.png