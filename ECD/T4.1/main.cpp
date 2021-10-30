#include <libusb-1.0/libusb.h>
#include <stdio.h>

#include <iostream>

using namespace std;
void printdev(libusb_device *dev);

int main() {
  libusb_device **devs;  // указатель на указатель на устройство,
                         // используется для получения списка устройств
  libusb_context *ctx = NULL;  // контекст сессии libusb
  int return_value;  // для возвращаемых значений
  ssize_t cnt;       // число найденных USB-устройств
  ssize_t i;  // индексная переменная цикла перебора всех устройств
  // инициализировать библиотеку libusb, открыть сессию работы с libusb
  return_value = libusb_init(&ctx);
  if (return_value < 0) {
    fprintf(stderr, "Ошибка: инициализация не выполнена, код: %d.\n",
            return_value);
    return 1;
  }
  // задать уровень подробности отладочных сообщений
  libusb_set_debug(ctx, 3);
  // получить список всех найденных USB- устройств
  cnt = libusb_get_device_list(ctx, &devs);
  if (cnt < 0) {
    fprintf(stderr, "Ошибка: список USB устройств не получен.\n", return_value);
    return 1;
  }
  // 6 10 10
  printf("Class |Vendor ID |Product ID\n");

  for (i = 0; i < cnt; i++) {  // цикл перебора всех устройств
    printdev(devs[i]);  // печать параметров устройства
  }

  // освободить память, выделенную функцией получения списка устройств
  libusb_free_device_list(devs, 1);
  libusb_exit(ctx);  // завершить работу с библиотекой libusb,
                     // закрыть сессию работы с libusb
  return 0;
}

void printdev(libusb_device *dev) {
  int title1_len = 6;
  int title2_and3_len = 10;
  libusb_device_descriptor desc;  // дескриптор устройства
  libusb_device_handle *dev_handle;
  unsigned char serial[20];

  int r = libusb_get_device_descriptor(dev, &desc);
  if (r < 0) {
    fprintf(stderr, "Ошибка: дескриптор устройства не получен, код: %d.\n", r);
    return;
  }
  r = libusb_open(dev, &dev_handle);
  r = libusb_get_string_descriptor_ascii(dev_handle, desc.iSerialNumber, serial,
                                         20);
  if (r != 0) {
    fprintf(stderr, "Не удалось открыть USB device: %d.\n", r);
    return;
  }
  string device_class, id_vendor, id_product;
  device_class += (int)desc.bDeviceClass;
  id_vendor += desc.idVendor;
  id_product += desc.idProduct;

  if (device_class.length() < title1_len) {
    device_class += title1_len - device_class.length();
  }
  if (id_vendor.length() < title2_and3_len) {
    id_vendor += title2_and3_len - id_vendor.length();
  }
  if (id_product.length() < title2_and3_len) {
    id_product += title2_and3_len - id_product.length();
  }
  cout << device_class << '|' << id_vendor << '|' << id_product < < < < endl;
  // printf("%.2d %.4d %.4d  |  |  |  |\n", (int)desc.bDeviceClass,
  // desc.idVendor,
  //  desc.idProduct);
}
