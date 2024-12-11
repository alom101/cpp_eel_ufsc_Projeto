
all:
	g++ src/*.cpp -U TARGET_ESP32 -U TARGET_ATMEGA -D TARGET_FAKE -o linux.out

atmega:
	avr-g++ -mmcu=atmega328p -U TARGET_FAKE -U TARGET_ESP32 -D TARGET_ATMEGA -Os src/*.cpp -o atmega.out
	avr-objcopy -O ihex -j .text -j .data atmega.out atmega.hex
	# avrdude 

esp32:
	#	compilar setando TARGET_ESP32 e removendo o resto
	#	use a IDE da fabricante para compilar

clean:
	rm *out *.hex
