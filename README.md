# Hyper_Dush_Temp
STM32F1, HAL, MQTT, Web

I. NodeMCU: (Work in Windows) ( Sử dụng Arduino IDE)

1. Cài đặt Board ESP:
+ Arduino IDE -> Tool -> Board -> Board Manager -> Gõ ESP -> Chọn ESP8266 by ESP Community -> Chọn board phù hợp. Ở đây, mình dùng NodeMCU 0.9(ESP-12 Module).

2. Cài đặt thư viện MQTT:
+ Download thư viện PubSubClient: https://github.com/knolleary/pubsubclient/
+ Arduino IDE -> Sketch -> Include Library -> Add .Zip library -> Thêm thư viện ở trên vào.

3. Cài đặt bản tin JSON:
+ Arduino IDE -> Sketch -> Include Library -> Library Manager -> Chọn ArduinoJson by Benoit Blanchon.

II. STM32-LCD: (Work in Windows) ( Sử dụng Keil C v5)

1. Kiểm tra device: STM32F103C8

2. Sơ đồ cắm chân:
+ A9:Tx - MCU:Rx
+ A10:Rx - MCU:Tx
+ A15: DHT11
+ A5: ADC - Dust
+ A6: Led - Dust
+ B6: I2C_SCL
+ B7: I2C_SDA

III. Nodejs: (Work in Ubuntu) ( Sử dụng VS Code)

1. Cài đặt thư viện:
+ Terminal: npm install <gói sử dụng> ( các gói sử dụng trong file package.json phần dependencies)
VD: npm install ejs
+ Build code: node + tên chương trình hoặc nodemon + tên chương trình ( nếu đã cài nodemon)
VD: node app.js hoặc nodemon app.js

2. Chạy file HTML:
+ Chuột phải vào file index.html -> Chọn Copy Path -> Copy link lên google -> Chọn phần biểu đồ -> Ấn F12 kiểm tra bản tin JSON.
