<img src="Nice.png" width="100"></img>

# NiceOpener
An ESPressif (ESP) code to open a Nice FLOR-S garage doors remotely using Internet/Wi-Fi with an RF433 Transmitter.


## Installation

Install by cloning project or downloading source code

```bash
  git clone https://github.com/Jev1337/NiceOpener.git
```


    
## Usage/Examples
1. Pair your ESP card with the receiver, using the code provided in the pair folder. Make sure to replace the codes with generated ones using <a href="https://github.com/Jev1337/NiceFlor-Encoder"> this generator</a>. Serial Code MUST be random, you should not use your remote's serial number it will make it out of sync.
```c
    //Fill these out with code being 1
    byte data1[] = { 0x1 , 0xf6 , 0x60 , 0xba , 0x62 , 0xb , 0x4c };
    byte data2[] = { 0x1 , 0xc6 , 0x60 , 0xba , 0x62 , 0xb , 0x4c };
    byte data3[] = { 0x1 , 0xd6 , 0x60 , 0xba , 0x62 , 0xb , 0x4c };
    byte data4[] = { 0x1 , 0xa6 , 0x60 , 0xba , 0x62 , 0xb , 0x4c };
    byte data5[] = { 0x1 , 0xb6 , 0x60 , 0xba , 0x62 , 0xb , 0x4c };
    byte data6[] = { 0x1 , 0x86 , 0x60 , 0xba , 0x62 , 0xb , 0x4c };
    //...
    //Fill these out with code being 2
    byte data01[] = { 0x1 , 0xf9 , 0x73 , 0x54 , 0x5d , 0x34 , 0x73 };
    byte data02[] = { 0x1 , 0xc9 , 0x73 , 0x54 , 0x5d , 0x34 , 0x73 };
    byte data03[] = { 0x1 , 0xd9 , 0x73 , 0x54 , 0x5d , 0x34 , 0x73 };
    byte data04[] = { 0x1 , 0xa9 , 0x73 , 0x54 , 0x5d , 0x34 , 0x73 };
    byte data05[] = { 0x1 , 0xb9 , 0x73 , 0x54 , 0x5d , 0x34 , 0x73 };
    byte data06[] = { 0x1 , 0x89 , 0x73 , 0x54 , 0x5d , 0x34 , 0x73 };
    //...
    //Fill these out with code being 3
    byte data001[] = { 0x1 , 0xf7 , 0x71 , 0xdd , 0x53 , 0x3a , 0x7d };
    byte data002[] = { 0x1 , 0xc7 , 0x71 , 0xdd , 0x53 , 0x3a , 0x7d };
    byte data003[] = { 0x1 , 0xd7 , 0x71 , 0xdd , 0x53 , 0x3a , 0x7d };
    byte data004[] = { 0x1 , 0xa7 , 0x71 , 0xdd , 0x53 , 0x3a , 0x7d };
    byte data005[] = { 0x1 , 0xb7 , 0x71 , 0xdd , 0x53 , 0x3a , 0x7d };
    byte data006[] = { 0x1 , 0x87 , 0x71 , 0xdd , 0x53 , 0x3a , 0x7d };
```
2. Install necessary library (Arduino IDE > Tools > Manage Libraries... > Install RF433send
3. Using your Transceiver module's Rx on Pin 2 (of course with VCC and GND on their own pins)
4. Run the code next to the receiver of the garage
5. Follow instructions on Serial, for example when it says to send 3 from your working remote, press 3 times
6. Once paired, you can use the main code which consist of using an API, I host the same <a href="https://github.com/Jev1337/NiceFlor-Encoder"> generator we used earlier </a> on a website using the same serial you just used to pair your card with. (You could use without an API, however you would need storage to keep the count of the codes and store the count in a database)


## API

The way the API would work is that the server would send a GET Request containing the encoded code as a JSON, example:
```json
  {'code': '0x1 0xf7 0x71 0xdd 0x53 0x3a 0x7d'}
```

## FAQ

#### What does this do and why?

This allows you to clone your remote using cheap RF433 modules with an Arduino or Raspberry Pi. This allows you to make home automations for example.

#### Is this illegal?

Cloning a remote is illegal in some countries, as capturing signals itself is illegal. So use at your own risk, this is only for educational purposes.


## Optimizations

There are no optimizations that I see that should be done, there are functions that could be deleted as they are there to let you know how things work.


## Used By

This is tested on:
- Nice FLO2 R-S (Also known as: Nice FLOR-S, Nice FLOR-S2)

## Credits

[Kaiju](https://rolling.pandwarf.com/): This helped me with confirming that the encoder works perfectly.

[rtl_433](https://github.com/merbanan/rtl_433/): This helped me with the python code, as it was not originaly mine. I modified it in a way it displays the encbuff which we use to transmit using RF433_Send library on Arduino

## License

[Apache 2.0](https://www.apache.org/licenses/LICENSE-2.0)

