file = avr

$(file).hex : $(file).c
	avr-gcc -mmcu=atmega328p -O $(file).c -o $(file).elf
	avr-objcopy -O ihex $(file).elf $(file).hex
	rm $(file).elf

download : 
	touch download.hex
	sudo avrdude -p m328p -c avrisp2 -U flash:r:download.hex:i

upload : $(file).hex
	sudo avrdude -p m328p -c avrisp2 -U flash:w:$(file).hex

verify : $(file).hex 
	sudo avrdude -p m328p -c avrisp2 -U flash:v:$(file).hex:i

get-fuses :
	sudo avrdude -p m328p -c avrisp2 -U efuse:r:-:b -U hfuse:r:-:b -U lfuse:r:-:b

status : 
	sudo avrdude -p m328p -c avrisp2

get-lock :
	sudo avrdude -p m328p -c avrisp2 -U lock:r:-:b

clean :
	rm $(file).hex

