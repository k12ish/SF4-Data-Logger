# SF4-Data-Logger: A Web Based ElectroCardiogram (ECG)

![Build workflow status](https://github.com/k12ish/SF4-Data-Logger/actions/workflows/firmware.yml/badge.svg)
[![Netlify Status](https://api.netlify.com/api/v1/badges/4b0e29d3-de64-4ff9-9a18-12599fd163bb/deploy-status)](https://app.netlify.com/sites/sf4-data-logger/deploys)

## Features

- **No Installation Required**: Simply plug and play on any machine with a web browser.
- **Cost-effective**: The device costs less than £15.
- **Local Data Processing**: All data is processed locally, ensuring regulatory compliance and enhanced privacy.
- **Three Measurement Modes**: Provides enhanced diagnostic capabilities through multiple measurement modes.
- **Backed by NeuroKit2**: Utilizes the well-established NeuroKit2 Python library for robust analysis. Plots BPM variation and the mean PQRST cardiac cycle.
- **High Sampling Frequency**: Sampling frequency of 2.3kHz far exceeds the recommended 250 Hz for accurate cardiac analysis.
- **Low CPU Usage**: On average, uses less than half a thread when continuously plotting 5,000 data points at 60FPS.
- **Responsive UI**: Includes spinners, status bars, and dynamically enabled buttons for a smooth user experience.

By using a web interface for our ECG, we have many inherent advantages.
Updates can be issued frequently and remotely, leading to future potential for subscription-based services/integrations with telehealth platforms.
In our case, since all data is processed locally, we don't pay for any web hosting costs!

## Try It out

1. **Build the Hardware**: Check out the KiCad schematic files in the `hardware/` directory.
2. **Flash the Firmware**: Open the Arduino IDE in the `firmware/` directory, or download precompiled binaries from the releases tab.
3. **Visit Our Platform**: Access the web application at [sf4-data-logger.netlify.app](https://sf4-data-logger.netlify.app/).
4. **Connect the Hardware**: Plug in the ECG device to your computer.
5. **Start Measuring**: Begin taking measurements and analyzing data instantly through your web browser.

