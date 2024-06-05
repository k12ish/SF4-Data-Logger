# Rough notes to find the max data possible transferred 

## CPU
> ATMega328P Processor, up to 16MHz
> https://docs.arduino.cc/resources/datasheets/A000066-datasheet.pdf

## Analogue Read
> On ATmega based boards (UNO, Nano, Mini, Mega), it takes about 100
> microseconds (0.0001 s) to read an analog input, so the maximum reading rate
> is about 10,000 times a second.
> https://www.arduino.cc/reference/en/language/functions/analog-io/analogread/

This implies that it takes around 1000 clock cycles to read an analogue pin!!!

Also useful:

| board  | voltage | pins     | bits    | 
|--------|---------|----------|---------|
| UNO R3 | 5 Volts | A0 to A5 | 10 bits | 

## Serial Write
> https://arduino.stackexchange.com/questions/296/how-high-of-a-baud-rate-can-i-go-without-errors

A little less conclusive, but suggests a Baud Rate of 250,000 
=> 80 clock cycles per bit
=> 800 clock cycles per 10 bits!!


- Theoretical max efficiency is ~1800 clock cycles / measurement, or roughly 5kHz

- Human readable ASCII might have four bytes to describe any 10 bit unsigned int and one separator byte
- This results in 40 bits transferred, ~4200 clock cycles / measurement, or roughly 2kHz


## What Sampling rate do we need?


> Down-sampling to 500 or 250 Hz resulted in excellent concordance. Signals down-sampled to 100 Hz produced acceptable results for time-domain analysis and Poincaré plots, but not for frequency-domain analysis. Down-sampling to 50 Hz proved to be unacceptable for both time- and frequency-domain analyses. At 50 Hz, the root-mean-squared successive differences and the power of high frequency tended to have high values and random errors.
> Kwon O, Jeong J, Kim HB, Kwon IH, Park SY, Kim JE, Choi Y. Electrocardiogram Sampling Frequency Range Acceptable for Heart Rate Variability Analysis. Healthc Inform Res. 2018 Jul;24(3):198-206. doi: 10.4258/hir.2018.24.3.198. Epub 2018 Jul 31. PMID: 30109153; PMCID: PMC6085204.
