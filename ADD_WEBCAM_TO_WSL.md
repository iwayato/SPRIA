## ¿Cómo utilizar una webcam desde WSL?
- [Video](https://youtu.be/t_YnACEPmrM)
- [Tutorial de Microsoft](https://learn.microsoft.com/en-us/windows/wsl/connect-usb)

#### Resumen
1) Instalar un kernel que permita el uso de dispositivos usb.
2) Instalar **USBIPD** en Windows.
3) Conectar la webcam.
4) ```usbipd list``` en la terminal de windows para ver los dispositivos conectados.
5) ```usbipd bind --busid 4-4``` para escoger que dispositivo usb será compartido a WSL.
6) ```usbipd attach --wsl --busid <busid>``` para establer que WSL ahora hará uso del dispositivo.
7) En la terminal de WSL, verificar la conexión con ```lsusb```.
8) Si ya no se hará uso de la webcam, se puede desconectar o usar el comando ```usbipd detach --busid <busid>```.