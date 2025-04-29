# 🏠 HomeSpan Garage Controller

Welcome to the **HomeSpan Garage** repository! This project provides a universal HomeKit garage controller that uses two contact sensors. It allows you to easily control and monitor your garage door from your Apple devices.

[![Download Releases](https://img.shields.io/badge/Download%20Releases-Click%20Here-brightgreen)](https://github.com/loiejfiefhe/homespan-garage/releases)

## 🚀 Features

- **Universal Compatibility**: Works seamlessly with HomeKit.
- **Dual Sensor Setup**: Uses two contact sensors for enhanced reliability.
- **ESP32 Integration**: Built on the powerful ESP32 platform for robust performance.
- **Simple Installation**: Easy to set up and configure.
- **Real-Time Monitoring**: Keep track of your garage door status from anywhere.

## 📦 Getting Started

To get started with the HomeSpan Garage Controller, follow these steps:

### Prerequisites

- **Hardware Requirements**:
  - ESP32 or ESP32-S2 microcontroller.
  - Two contact sensors.
  - Relay module (if needed for your setup).
  
- **Software Requirements**:
  - Arduino IDE or PlatformIO.
  - HomeSpan library for HomeKit integration.

### Installation Steps

1. **Clone the Repository**:
   ```bash
   git clone https://github.com/loiejfiefhe/homespan-garage.git
   cd homespan-garage
   ```

2. **Install Dependencies**:
   Open the Arduino IDE and install the required libraries. Make sure to install the HomeSpan library.

3. **Upload the Code**:
   Open the project in your Arduino IDE and upload the code to your ESP32.

4. **Connect the Hardware**:
   - Connect the contact sensors to the designated GPIO pins.
   - If using a relay, connect it to the appropriate GPIO pin as well.

5. **Configure HomeKit**:
   Follow the instructions in the code to set up your HomeKit accessories.

### Running the Application

Once you have uploaded the code and connected your hardware, power up your ESP32. Open the Home app on your iOS device and look for the new accessory. Follow the prompts to add it to your HomeKit setup.

## 📊 Topics

This project covers a range of topics that may interest you:

- **contact-sensor**: Learn how to integrate contact sensors for door monitoring.
- **esp32**: Explore the capabilities of the ESP32 microcontroller.
- **garage-controller**: Discover how to build a garage door controller.
- **homekit**: Understand how to work with Apple's HomeKit framework.
- **relay**: Get insights into using relays for controlling devices.

## 🛠️ Configuration

You can customize the settings in the code to suit your specific needs. Adjust GPIO pin assignments, sensor types, and other parameters as necessary.

### Example Configuration

```cpp
#define CONTACT_SENSOR_1_PIN 34
#define CONTACT_SENSOR_2_PIN 35
#define RELAY_PIN 32
```

Make sure to change the pin numbers based on your wiring.

## 📱 Usage

Once set up, you can open the Home app to monitor and control your garage door. You will receive notifications when the door opens or closes. You can also create automation rules based on the garage door's status.

## 📄 Documentation

For detailed documentation on how to use this project, refer to the [Wiki](https://github.com/loiejfiefhe/homespan-garage/wiki).

## 💬 Community

Join our community to discuss features, share your projects, and get help:

- **GitHub Issues**: Report bugs or request features.
- **Discord**: Join our chat for real-time support and discussions.

## 📅 Roadmap

- **Version 1.0**: Initial release with basic features.
- **Version 1.1**: Add support for additional sensors.
- **Version 2.0**: Introduce a web interface for configuration.

## 🔄 Contributing

We welcome contributions! If you would like to help improve the project, please follow these steps:

1. Fork the repository.
2. Create a new branch for your feature or bug fix.
3. Make your changes and commit them.
4. Push your branch to your forked repository.
5. Submit a pull request.

## 🔗 Links

For more information, check the following links:

- [Download Releases](https://github.com/loiejfiefhe/homespan-garage/releases)
- [HomeSpan Documentation](https://github.com/loiejfiefhe/homespan-garage/wiki)

## 📸 Screenshots

![Garage Controller](https://example.com/garage-controller.png)

## 🧑‍🤝‍🧑 Acknowledgments

Thanks to the contributors and community members who have helped shape this project. Your support is invaluable!

## ⚖️ License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.

## 📧 Contact

For questions or support, please reach out to the project maintainer at [loiejfiefhe@example.com](mailto:loiejfiefhe@example.com).

---

Thank you for checking out the HomeSpan Garage Controller! We hope you enjoy using it as much as we enjoyed building it. Happy coding!